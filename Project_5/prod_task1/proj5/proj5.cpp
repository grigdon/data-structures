#include <iostream>
#include <string>
#include <utility>
#include "passserver.h" // Include passserver.h instead of directly using HashTable

void Menu();

int main() {
    bool continueProgram = true;
    unsigned long capSize;
    char input;

    std::cout << "Enter preferred hash table capacity (integer): ";
    std::cin >> capSize;

    PassServer passServer(capSize); // Use PassServer instead of directly creating HashTable

    while (continueProgram) {
        Menu();
        std::cin >> input;
        std::cout << "Choice: " << input << "\n";

        switch (input) {
        case 'l': {
            std::string passwordFile;
            std::cout << "Enter password file to load from: ";
            std::cin >> passwordFile;

            if (!passServer.load(passwordFile.c_str())) {
                std::cerr << "\nFailed to load data from " << passwordFile << "\n";
            }
        }
                break;
        case 'a': {
            std::string username;
            std::string password;

            std::cout << "Enter username: ";
            std::cin >> username;
            std::cout << "Enter password: ";
            std::cin >> password;
            std::pair<std::string, std::string> kv = make_pair(username, password);

            if (!passServer.addUser(kv)) { 
                std::cerr << "\nFailed to insert " << kv.first << " " << kv.second << "\n";
            }
            else {
                std::cout << "\nUser " << username << " added.\n";
            }
        }
                break;
        case 'r': {
            std::string username;

            std::cout << "Enter username: ";
            std::cin >> username;

            if (!passServer.removeUser(username)) { // Using passServer methods
                std::cerr << "\n*****Error: User not found. Could not delete user\n";
            }
            else {
                std::cout << "\nUser " << username << " deleted.\n";
            }
        }
                break;
        case 'c': {
            std::string username;
            std::string oldPassword;
            std::string newPassword;

            std::cout << "Enter username: ";
            std::cin >> username;
            std::cout << "Enter password: ";
            std::cin >> oldPassword;
            std::cout << "\nEnter new password: ";
            std::cin >> newPassword;

            std::pair<std::string, std::string> oldKv = make_pair(username, oldPassword);
            std::pair<std::string, std::string> newKv = make_pair(username, newPassword);

            if (passServer.changePassword(oldKv, newPassword)) { // Using passServer methods
                std::cout << "\nPassword changed for user " << username << "\n";
            }
            else {
                std::cerr << "\n*****Error: Could not change user password\n";
            }
        }
                break;
        case 'f': {
            std::string username;

            std::cout << "Enter username: ";
            std::cin >> username;

            if (passServer.find(username)) { // Using passServer methods
                std::cout << "\nUser '" << username << "' found.\n";
            }
            else {
                std::cerr << "\nUser '" << username << "' not found.\n";
            }
        }
                break;
        case 'd': {
            passServer.dump(); // Using passServer methods
        }
                break;
        case 's': {
            std::cout << "Size of hashtable: " << passServer.size() << "\n"; // Using passServer methods
        }
                break;
        case 'w': {
            std::string passwordFile;
            std::cout << "Enter password file to write to: ";
            std::cin >> passwordFile;

            if (!passServer.write_to_file(passwordFile.c_str())) { // Using passServer methods
                std::cerr << "Failed to write data to " << passwordFile << "\n";
            }
        }
                break;
        case 'x': {
            continueProgram = false;
        }
                break;
        default: {
            std::cout << "\n*****Error: Invalid entry. Try again.";
        }
        }
    }
    return (0);
}

void Menu() {
    std::cout << "\n";
    std::cout << "l - Load From File" << "\n";
    std::cout << "a - Add User" << "\n";
    std::cout << "r - Remove User" << "\n";
    std::cout << "c - Change User Password" << "\n";
    std::cout << "f - Find User" << "\n";
    std::cout << "d - Dump HashTable" << "\n";
    std::cout << "s - HashTable Size" << "\n";
    std::cout << "w - Write to Password File" << "\n";
    std::cout << "x - Exit program" << "\n";
    std::cout << "\nEnter choice : ";
}
