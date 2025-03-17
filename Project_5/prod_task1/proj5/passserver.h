#ifndef PASSSERVER_H
#define PASSSERVER_H

#include <utility>
#include <iostream>
#include <fstream>
#include <string>
#include <crypt.h>
#include <unistd.h>

#include "hashtable.h"

class PassServer {
    private:
        HashTable<std::string, std::string>* adaptedTable; // adapted hash table
        std::string encrypt(const std::string & str); // encrypts key
    public:
        PassServer(size_t size = 101); // constructor
        ~PassServer(); // destructor
        bool load(const char *filename); // loads hash table from file
        bool addUser(std::pair<std::string, std::string> & kv); // adds user to hash table
        bool addUser(std::pair<std::string, std::string> && kv); // move version of addUser
        bool removeUser(const std::string & k); // removes user from hash table
        bool changePassword(const std::pair<std::string, std::string> &p, const std::string & newpassword); // changes password of user
        bool find(const std::string & user) const; // finds user in hash table
        void dump(); // prints contents of hash table
        size_t size() const; // number of elements in hash table
        bool write_to_file(const char *filename) const; // writes hash table contents to file
}; // end of class

#include "passserver.cpp"
#endif