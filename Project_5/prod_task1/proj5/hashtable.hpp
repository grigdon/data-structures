#include "hashtable.h"
using namespace cop4530;

// ************************
// Private Member Functions
// ************************

template <typename K, typename V>
void HashTable<K, V>::makeEmpty() {
    for (size_t i = 0; i < numBuckets; ++i) {
        auto& chain = table[i];
        chain.clear();
    }
    numPairs = 0;
}

template <typename K, typename V>
void HashTable<K, V>::rehash() {
    auto oldTable = table;
    numBuckets = prime_below(2 * numBuckets);
    table.resize(numBuckets);
    for (auto& chain : table) {
        chain.clear();
    }
    numPairs = 0;
    for (const auto& chain : oldTable) {
        for (const auto& kv : chain) {
            insert(kv);
        }
    }
}

template <typename K, typename V>
size_t HashTable<K, V>::myHash(const K& k) const {
    return std::hash<K>{}(k) % numBuckets;
}

template <typename K, typename V>
unsigned long HashTable<K, V>::prime_below(unsigned long n) {
    if (n > max_prime)
    {
        std::cerr << "** input too large for prime_below()\n";
        return 0;
    }
    if (n == max_prime)
    {
        return max_prime;
    }
    if (n <= 1)
    {
        std::cerr << "** input too small \n";
        return 0;
    }

    // now: 2 <= n < max_prime
    std::vector <unsigned long> v(n + 1);
    setPrimes(v);
    while (n > 2)
    {
        if (v[n] == 1)
            return n;
        --n;
    }

    return 2;
}

//Sets all prime number indexes to 1. Called by method prime_below(n) 
template <typename K, typename V>
void HashTable<K, V>::setPrimes(std::vector<unsigned long>& vPrimes)
{
    int i = 0;
    int j = 0;

    vPrimes[0] = 0;
    vPrimes[1] = 0;
    int n = vPrimes.capacity();

    for (i = 2; i < n; ++i)
        vPrimes[i] = 1;

    for (i = 2; i * i < n; ++i)
    {
        if (vPrimes[i] == 1)
            for (j = i + i; j < n; j += i)
                vPrimes[j] = 0;
    }
}

// ************************
//  Public Member Functions
// ************************

template <typename K, typename V>
HashTable<K, V>::HashTable(unsigned long size) {
    numBuckets = prime_below(size);
    std::cout << numBuckets;
    table.resize(numBuckets);
}

template <typename K, typename V>
HashTable<K, V>::~HashTable() {
    clear();
}

template <typename K, typename V>
bool HashTable<K, V>::contains(const K& k) const {
    size_t index = myHash(k);
    for (const auto& kv : table[index]) {
        if (kv.first == k) {
            return true;
        }
    }
    return false;
}

template <typename K, typename V>
bool HashTable<K, V>::match(const std::pair<K, V>& kv) const {
    size_t index = myHash(kv.first);
    for (const auto& pair : table[index]) {
        if (pair == kv) {
            return true;
        }
    }
    return false;
}

template <typename K, typename V>
bool HashTable<K, V>::insert(const std::pair<K, V>& kv) {
    size_t index = myHash(kv.first);
    if (match(kv)) {
        return false; // pair already exists in table
    }

    if (contains(kv.first)) {
        for (auto& i : table[index]) {
            if (i.first == kv.first) {
                i.second = kv.second;
            }
        }
        return true;
    }

    if (++numPairs > table.size()) {
        rehash();
    }

    table[index].push_back(kv);
    return true;
}

template <typename K, typename V>
bool HashTable<K, V>::insert(std::pair<K, V>&& kv) {
    size_t index = myHash(kv.first);
    if (match(kv)) {
        return false; // pair already exists in table
    }

    if (contains(kv.first)) {
        for (auto& i : table[index]) {
            if (i.first == kv.first) {
                i.second = std::move(kv.second);
            }
        }
        return true;
    }

    if (++numPairs > table.size()) {
        rehash();
    }

    table[index].push_back(std::move(kv));
    return true;
}

template <typename K, typename V>
bool HashTable<K, V>::remove(const K& k) {
    size_t index = myHash(k);
    auto& chain = table[index];
    for (auto it = chain.begin(); it != chain.end(); ++it) {
        if (it->first == k) {
            chain.erase(it);
            --numPairs;
            return true;
        }
    }
    return false;
}

template <typename K, typename V>
void HashTable<K, V>::clear() {
    makeEmpty();
}

template <typename K, typename V>
bool HashTable<K, V>::load(const char* filename) {
    std::ifstream infile(filename);
    if (!infile) {
        return false;
    }
    K key;
    V value;
    while (infile >> key >> value) {
        insert({ key, value });
    }
    return true;
}

template <typename K, typename V>
void HashTable<K, V>::dump() const {
    for (size_t i = 0; i < numBuckets; ++i) {
        std::cout << "[v]" << i << ": ";
        for (const auto& it : table[i]) {
            std::cout << it.first << " " << it.second << " ";
        }
        std::cout << "\n";
    }
}

template <typename K, typename V>
size_t HashTable<K, V>::size() const {
    return numPairs;
}

template <typename K, typename V>
bool HashTable<K, V>::write_to_file(const char* filename) const {
    std::ofstream outfile(filename);
    if (!outfile) {
        return false;
    }
    for (const auto& chain : table) {
        for (const auto& it : chain) {
            outfile << it.first << " " << it.second << "\n";
        }
    }
    return true;
}
