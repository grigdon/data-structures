#ifndef HASHTABLE_H
#define HASHTABLE_H

#include <iostream>
#include <vector>
#include <list>
#include <fstream>
#include <utility>

static const unsigned int max_prime = 1301081; // max_prime is used by the helpful functions provided to you
static const unsigned int default_capacity = 101; // the default_capacity is used if the initial capacity of the underlying vector of the hash table is zero

namespace cop4530 {
    template <typename K, typename V>
    class HashTable {
    private:
        std::vector<std::list<std::pair<K, V>>> table; // underlying data structure for the HashTable
        size_t numBuckets; // number of lists (buckets) in the vector
        size_t numPairs; // number of key-value pairs

        void makeEmpty(); // clears all elements
        void rehash(); // resizes and rehashes table
        size_t myHash(const K& k) const; // hash function
        unsigned long prime_below(unsigned long n); // finds largest prime below n
        void setPrimes(std::vector<unsigned long>& vPrimes); // helper for prime below
    public:
        HashTable(unsigned long size = 101); // constructor
        ~HashTable(); // destructor
        bool contains(const K& k) const; // checks if key is in table
        bool match(const std::pair<K, V>& kv) const; // checks if key-value pair is in table
        bool insert(const std::pair<K, V>& kv); // inserts key-value pair in table
        bool insert(std::pair<K, V>&& kv); // move version of insert function
        bool remove(const K& k); // removes key from table
        void clear(); // clears table
        bool load(const char* filename); // loads file to table
        void dump() const; // prints table to console
        size_t size() const; // returns numBuckets
        bool write_to_file(const char* filename) const; // writes table to file
    };
} // end of namespace COP4530
#include "hashtable.hpp"
#endif