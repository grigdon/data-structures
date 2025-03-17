#include <iostream>
#include "hashtable.h"

int main() {
    // Create a HashTable instance
    cop4530::HashTable<std::string, std::string> hashtable;

    // Load data from input.txt into the hash table
    const char* inputFile = "input.txt";
    if (!hashtable.load(inputFile)) {
        std::cerr << "Failed to load data from " << inputFile << std::endl;
        return 1;
    }

    // Print the contents of the hash table to the console
    std::cout << "Contents of the hash table loaded from " << inputFile << ":\n";
    hashtable.dump();

    // Write the contents of the hash table to output.txt
    const char* outputFile = "output.txt";
    if (!hashtable.write_to_file(outputFile)) {
        std::cerr << "Failed to write data to " << outputFile << std::endl;
        return 1;
    }

    std::cout << "Hash table contents successfully written to " << outputFile << "\n";
    return 0;
}
