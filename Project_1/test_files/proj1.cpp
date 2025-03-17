// *************************************
// * Title: Project 1                  *
// * Name: Gabe Rigdon COP4530         *
// * Due Date: 25 Sept., 2024          *
// * Desc: This program parses input   *
// * and prints the (up to) top 10 of  *
// * of each word, number & character  *
// * in the input string.              *
// *************************************

// *************************************
// Definitions used in this program:   *
// ****************************************************************************************************************************************************************************
// Word: Any continuous string of letters. For example, "a", "ab", "bool", "encyclopedia". All words are stored in their lowercase forms.
// Number: Any continuous string of numbers. For example, "0", "123", "0500". "00" and "000", "0800" and "0080", etc. are all considered unique nums, despite having same value.
// Character: Any printable ASCII character such as 'A', 'b', '&', '\n', etc.
// ****************************************************************************************************************************************************************************

#include <iostream>
#include <string>
#include <vector>
#include <cctype>
#include <unordered_map>
#include <iomanip>
#include <utility>

    void toLower(std::string &str);
    void stringParse(std::vector<char>& charVector, std::vector<std::string>& numVector, std::vector<std::string>& wordVector, std::string& inputString);
    void pushIntoMap(std::vector<char>& charVector, const std::vector<std::string>& numVector, const std::vector<std::string>& wordVector, std::unordered_map<char, int>& charMap, std::unordered_map<std::string, int>& numMap, std::unordered_map<std::string, int>& wordMap);
    void charMapSummary(std::unordered_map<char, int>& map, std::vector<std::pair<char, int>>& charTopEntries, std::vector<int>& numElementsInMap);
    void wordMapSummary(std::unordered_map<std::string, int>& map, const std::vector<std::string>& wordString, std::vector<std::pair<std::string, int>>& wordTopEntries, std::vector<int>& numElementsInMap);
    void numMapSummary(std::unordered_map<std::string, int>& map, const std::vector<std::string>& numString, std::vector<std::pair<std::string, int>>& numTopEntries, std::vector<int>& numElementsInMap);
    void printSummary(const std::vector<std::pair<char, int>>& charTopEntries, const std::vector<std::pair<std::string, int>>& numTopEntries, const std::vector<std::pair<std::string, int>>& wordTopEntries, const std::vector<int>& numElementsInMap);

    int main(void) {

        std::string inputString;

        std::vector<char> charVector;
        std::vector<std::string> wordVector, numVector;
        std::vector<int> numElementsInMap;

        std::unordered_map<char, int> charMap;
        std::unordered_map<std::string, int> numMap, wordMap;

        std::vector<std::pair<char, int>> charTopEntries;
        std::vector<std::pair<std::string, int>> numTopEntries, wordTopEntries;

        // Populates the inputString. Recall that getline removes the '\n' character, so it is added back to the end of the inputString for every string.
        // In the instance that there is only a single line of text with no newline characters, check that it is not the end of the file. If it is, then do not append a newline character.

        bool endFileDetected = false;

        while(getline(std::cin, inputString)) {
            endFileDetected = std::cin.eof();
            if(!endFileDetected) { inputString += '\n'; } 

            stringParse(charVector, numVector, wordVector, inputString);
        }

        // Pushes the type's vector into its corresponding unordered_map and simultaneously counts the number of instances of each key.

        pushIntoMap(charVector, numVector, wordVector, charMap, numMap, wordMap);  

        // Calculates the summary statistics.

        charMapSummary(charMap, charTopEntries, numElementsInMap);
        wordMapSummary(wordMap, wordVector, wordTopEntries, numElementsInMap);
        numMapSummary(numMap, numVector, numTopEntries, numElementsInMap);

        // Prints the summary statistics.

        printSummary(charTopEntries, numTopEntries, wordTopEntries, numElementsInMap);
        
        return(0);
    }

    // ***********************************************************************************************************
    // Function Name: toLower
    // Description: Changes each character in the string to its lowercase form.
    // Assumptions: This function assumes that the user will only enter words (no numbers or special characters).
    // Example: HELLO --> hello
    // ***********************************************************************************************************

    void toLower(std::string &str) {
        for(int i = 0; i < str.length(); i++) {
            str[i] = tolower(str[i]);
        }
    }
    // *************************************************************************************************************************************************************
    // Function Name: stringParse
    // Description: Parses inputString and places all individual chars into charVector, all words into wordVector, etc.
    // Assumptions: This function assumes that inputString will be populated. In this program, the while-loop in main() ensures the inputString is always populated.
    // Example: If inputString == "Hello, test 123!"
    //          charVector = {H,e,l,l,o, ,t,e,s,t, ,1,2,3,!}
    //          wordVector = {hello, test}
    //          numVector  = {123}
    // *************************************************************************************************************************************************************

    void stringParse(std::vector<char>& charVector, std::vector<std::string>& numVector, std::vector<std::string>& wordVector, std::string& inputString) {

        // currentString is used to build and separate the words and numbers from the inputString.

        std::string currentString = "";

        for(int i = 0; i < inputString.length(); i++) {

            // Stores every char into the charVector.

            charVector.push_back(inputString[i]);

            // If the current character in the inputString is alphanumeric, then check if the current alphanumeric character can be added to the inputString, i.e., they are the same type.
            // If it can be added, add it and carry on. If not, then push the inputString into the corresponding vector, then store the current alphanumeric character in the inputString.

            if(isalnum(inputString[i])) {
                if(isdigit(inputString[i])) {
                    if(currentString.empty() || isdigit(currentString.back())) {
                        currentString += inputString[i];
                    } else {
                        if(isalpha(currentString.front())) {
                            toLower(currentString);
                            wordVector.push_back(currentString);
                        }
                        currentString = inputString[i];
                    }
                }
                else if(isalpha(inputString[i])) {
                    if(currentString.empty() || isalpha(currentString.back())) {
                        currentString += inputString[i];
                    } else {
                        if(isdigit(currentString.front())) {
                            numVector.push_back(currentString);
                        }
                        currentString = inputString[i];
                    }
                }

            // If the current character in the inputString is not alphanumeric, then it has no place in the the wordVector or numVector. So, if the currentString is populated, push
            // the currentString into its corresponding vector, then clear the currentString.

            } else {
                if(!currentString.empty()) {
                    if(isalpha(currentString.front())) {
                        toLower(currentString);
                        wordVector.push_back(currentString);
                    } else if(isdigit(currentString.front())) {
                        numVector.push_back(currentString);
                    }
                    currentString = "";
                }
            }
        }

            // If, at the end of the loop, there is still data stored in currentString, push the currentString into its corresponding vector.

            if(!currentString.empty()) {
                if(isalpha(currentString.front())) {
                    toLower(currentString);
                    wordVector.push_back(currentString);
                } else if(isdigit(currentString.front())) {
                    numVector.push_back(currentString);
                  }
            }
    }

    // **************************************************************************************************************************************************************
    // Function Name: pushIntoMap
    // Description: Pushes each vector into an unordered_map corresponding to their respective type. It also keeps track of the number of instances of each key value.
    // Assumptions: This function assumes that each vector is already populated. If a vector is not populated, no data will be stored into the maps.
    // Example: If charVector == {H,e,l,l,o, ,t,e,s,t, ,1,2,3,!}
    //          charMap['H'] = 1
    //          charMap['e'] = 2
    //          charMap['l] = 2
    //          charMap['o'] = 1
    //              .
    //              .
    //              .
    //          charMap['!'] = 1
    // *************************************************************************************************************************************************************

    void pushIntoMap(std::vector<char>& charVector, const std::vector<std::string>& numVector, const std::vector<std::string>& wordVector, std::unordered_map<char, int>& charMap, std::unordered_map<std::string, int>& numMap, std::unordered_map<std::string, int>& wordMap) {

        // Loop through the charVector and set each char as a key in the charMap. For every instance of each key, add one to its corresponding integer value.

        for(int i = 0; i < charVector.size(); i++) {
            const char& ch = charVector[i];
            charMap[ch]++;
        }

        // At this point, we do not need to keep track of the order of chars, so the charVector can be cleared. 

        charVector.clear();

        // The idea is the same for the numVector and wordVector, with the only difference being we will not clear numVector and wordVector. 
        // These vectors will later be used to keep track of the order of words and numbers for breaking ties in the <type>MapSummary(...) function.

        for(int i = 0; i < numVector.size(); i++) {
            const std::string& str = numVector[i];
            numMap[str]++;
        }

        for(int i = 0; i < wordVector.size(); i++) {
            const std::string& str = wordVector[i];
            wordMap[str]++;
        }
    }

    // *********************************************************************************************************************************************
    // Function Name: charMapSummary
    // Description: Summarizes (up to) the top 10 highest values and their corresponding keys in the charMap which was populated using pushIntoMap(...)
    //              If two chars have the same value in the unordered_map, the value that has the lower ASCII value is chosen for that ranking.
    //              Places the top ranking into charTopEntries.
    // Assumptions: This function assumes that the charMap was already populated using pushIntoMap(...)
    //**********************************************************************************************************************************************

    void charMapSummary(std::unordered_map<char, int>& map, std::vector<std::pair<char, int>>& charTopEntries, std::vector<int>& numElementsInMap) {

        // Ensures that there are not more rankings than number of pairs in the map. There can only be a maximum of 10 rankings, per the project specifications.

        int numRankings = map.size();
        if(numRankings >= 10) { numRankings = 10; }  

        for (int i = 0; i < numRankings; ++i) {
            
            // maxVal is initialized with a value lower than the lowest possible value in the map (1) to ensure maxVal and maxKey get assigned to a pair in the map.

            int maxVal = 0;
            char maxKey;
            
            // Search through the charMap and find the largest value, called maxVal. Store all pairs that share that also equal maxVal into competingKeys. 

            std::vector<std::pair<char, int>> competingKeys;

            for (const auto& element : map) {
                if (element.second > maxVal) {
                    maxKey = element.first;
                    maxVal = element.second;
                    competingKeys.clear();
                    competingKeys.push_back(element);
                } else if(element.second == maxVal) {
                    competingKeys.push_back(element);
                  }
            }

            // Now, search through competingKeys and find the char with the lowest ASCII value. This condition will be used to break the tie. 
            // The char with the lowest ASCII value is treated as the true maxKey/maxVal.

            if(competingKeys.size() > 1) {
                char lowestASCII = competingKeys[0].first;
                for(const auto& element: competingKeys) {
                    if(element.first < lowestASCII) {
                        lowestASCII = element.first;
                        maxKey = element.first;
                        maxVal = element.second;
                    }
                }
            }

            // Inserts the i-th rank into a separate container which will be printed using printSummary(...).

            charTopEntries.push_back(std::make_pair(maxKey, maxVal));

            // Finally, to ensure a key is not printed more than once, set its value to 0.

            map[maxKey] = 0;
        }
        
            // Adds the number of pairs in the map. This will be used in printSummary(...).

            numElementsInMap.push_back(map.size());
    }   

    // *********************************************************************************************************************************************
    // Function Name: wordMapSummary
    // Description: Summarizes (up to) the top 10 highest values and their corresponding keys in the wordMap which was populated using pushIntoMap(...)
    //              If two words have the same value in the unordered_map, the key that occurred first in the numVector is chosen for that ranking
    //              Places the top ranking into wordTopEntries.
    // Assumptions: This function assumes that the wordMap was already populated using pushIntoMap(...) and wordVector is still populated
    //**********************************************************************************************************************************************

    void wordMapSummary(std::unordered_map<std::string, int>& map, const std::vector<std::string>& wordVector, std::vector<std::pair<std::string, int>>& wordTopEntries, std::vector<int>& numElementsInMap) {
    
        // Ensures that there are not more rankings than number of pairs in the map. There can only be a maximum of 10 rankings, per the project specifications.

        int numRankings = map.size();
        if(numRankings >= 10) { numRankings = 10; }

        for (int i = 0; i < numRankings; ++i) {

            // maxVal is initialized with a value lower than the lowest possible value in the map (1) to ensure maxVal and maxKey get assigned to a pair in the map.

            int maxVal = 0;
            std::string maxKey;
            
            // Search through the wordMap and find the largest value, called maxVal. Store all pairs that share that also equal maxVal into competingKeys.

            std::vector<std::pair<std::string, int>> competingKeys;

            for (const auto& element : map) {
                if (element.second > maxVal) {
                    maxKey = element.first;
                    maxVal = element.second;
                    competingKeys.clear();
                    competingKeys.push_back(element);
                } else if(element.second == maxVal) {
                    competingKeys.push_back(element);
                  }
            }

            // Now, recall that wordVector still contains all words in order of when they were inputted. To break the tie, we need to check which word occurred sooner in the 
            // original input. So, for each string in wordVector, check if the string matches a string in competingKeys. The first match will be set as the true maxKey/maxVal.

            if(competingKeys.size() > 1) {
                bool continueSearch = true;
                while(continueSearch) {
                    for(int i = wordVector.size() - 1; i >= 0; --i) {
                        for(const auto& element: competingKeys) {
                            if(element.first == wordVector[i]) {
                                maxKey = element.first;
                                maxVal = element.second;
                                continueSearch = false;
                            }
                        }
                    }
                }
            }

            // Inserts the i-th rank into a separate container which will be printed using printSummary(...).

            wordTopEntries.push_back(std::make_pair(maxKey, maxVal));

            // Finally, to ensure a key is not printed more than once, set its value to 0.

            map[maxKey] = 0;
        }
            // Adds the number of pairs in the map. This will be used in printSummary(...).

            numElementsInMap.push_back(map.size());
    }

    // *********************************************************************************************************************************************
    // Function Name: numMapSummary
    // Description: Summarizes (up to) the top 10 highest values and their corresponding keys in the numMap which was populated using pushIntoMap(...)
    //              If two nums have the same value in the unordered_map, the key that occurred first in the numVector is chosen for that ranking
    //              Places the top ranking into numTopEntries.
    // Assumptions: This function assumes that the numMap was already populated using pushIntoMap(...) and numVector is still populated
    //**********************************************************************************************************************************************

    void numMapSummary(std::unordered_map<std::string, int>& map, const std::vector<std::string>& numVector, std::vector<std::pair<std::string, int>>& numTopEntries, std::vector<int>& numElementsInMap) {

        // Ensures that there are not more rankings than number of pairs in the map. There can only be a maximum of 10 rankings, per the project specifications.

        int numRankings = map.size();
        if(numRankings >= 10) { numRankings = 10; }

        for (int i = 0; i < numRankings; ++i) {

            // maxVal is initialized with a value lower than the lowest possible value in the map (1) to ensure maxVal and maxKey get assigned to a pair in the map.

            int maxVal = 0;
            std::string maxKey;        

            // Search through the numMap and find the largest value, called maxVal. Store all pairs that share that also equal maxVal into competingKeys. 

            std::vector<std::pair<std::string, int>> competingKeys;

            for (const auto& element : map) {
                if (element.second > maxVal) {
                    maxKey = element.first;
                    maxVal = element.second;
                    competingKeys.clear();
                    competingKeys.push_back(element);
                } else if(element.second == maxVal) {
                    competingKeys.push_back(element);
                  }
            }

            // Now, recall that numVector still contains all numbers in order of when they were inputted. To break the tie, we need to check which number occurred sooner in the 
            // original input. So, for each string in numVector, check if the string matches a string in competingKeys. The first match will be set as the true maxKey/maxVal.

            if(competingKeys.size() > 1) {
                bool continueSearch = true;
                while(continueSearch) {
                    for(int i = numVector.size() - 1; i >= 0 ; --i) {
                        for(const auto& element: competingKeys) {
                            if(element.first == numVector[i]) {
                                maxKey = element.first;
                                maxVal = element.second;
                                continueSearch = false;
                            }
                        }
                    }
                }
            }

           // Inserts the i-th rank into a separate container which will be printed using printSummary(...).

            numTopEntries.push_back(std::make_pair(maxKey, maxVal));

            // Finally, to ensure a key is not printed more than once, set its value to 0.

            map[maxKey] = 0;
        }

            // Adds the number of pairs in the map. This will be used in printSummary(...).

            numElementsInMap.push_back(map.size());
    }

    // *************************************************************************************************************
    // Function Name: printSummary
    // Description: Prints the summaries found using <datatype>MapSummary according to the project specifications.
    // Assumptions: This function assumes that the each container was already populated using wordMapSummary(...) 
    // *************************************************************************************************************

    void printSummary(const std::vector<std::pair<char, int>>& charTopEntries, const std::vector<std::pair<std::string, int>>& numTopEntries, const std::vector<std::pair<std::string, int>>& wordTopEntries, const std::vector<int>& numElementsInMap) {
        
        // Finds the longest word or number and stores its size in maxStringSize. This value is used to set the width for the ouput below.

        int maxStringSize = 0;  
        int rank = 0;
        for(const auto& element: numTopEntries) {
            if(element.first.size() > maxStringSize) {
                maxStringSize = element.first.size();
            }
        }

        for(const auto& element: wordTopEntries){
            if(element.first.size() > maxStringSize) {
                maxStringSize = element.first.size();
            }
        }

        std::cout << "Total " << numElementsInMap[0] << " different characters, " << charTopEntries.size() << " most used characters:\n";

        for(const auto& element: charTopEntries) {
            if(element.first == '\n') {
                std::cout << "No. " << rank << ": " << std::left << std::setw(maxStringSize + 5) << "\\n" <<  element.second << std::endl;
            } 
            else if(element.first == '\t') {
                std::cout << "No. " << rank << ": " << std::left << std::setw(maxStringSize + 5) << "\\t" <<  element.second << std::endl;
            } else {
                std::cout << "No. " << rank << ": " << std::left << std::setw(maxStringSize + 5) << element.first <<  element.second << std::endl;
              }
              
            rank++;
        }

        rank = 0;

        std::cout << "\nTotal " << numElementsInMap[1] << " different words, " << wordTopEntries.size() << " most used words:\n";

        for(const auto& element: wordTopEntries) {
            std::cout << "No. " << rank << ": " << std::left << std::setw(maxStringSize + 5) << element.first <<  element.second << std::endl;

            rank++;
        }

        rank = 0;

        std::cout << "\nTotal " << numElementsInMap[2] << " different numbers, " << wordTopEntries.size() << " most used numbers:\n";

        for(const auto& element: numTopEntries) {
             std::cout << "No. " << rank << ": " << std::left << std::setw(maxStringSize + 5) << element.first <<  element.second << std::endl;

            rank++;
        }       
    }