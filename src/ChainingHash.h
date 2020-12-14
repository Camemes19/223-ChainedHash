/*
 *  Separate chaining hashtable
 */

/*
Name: Quinn Barnwell
Description: three examples of implementations of hashing one using 
chaining, another using linear probing, and the last using linear 
probing using parallel programming.
*/

#ifndef __CHAINING_HASH_H
#define __CHAINING_HASH_H

// Standard library includes
#include <iostream>
#include <vector>
#include <list>
#include <stdexcept>
#include <cmath>
#include <string>
#include <utility>

// Custom project includes
//#include "Hash.h"

// Namespaces to include
using std::vector;
using std::list;
using std::pair;
using std::string;

using std::cout;
using std::endl;

//
// Separate chaining based hash table - derived from Hash
//
template<typename K, typename V>
class ChainingHash {
private:

public:
    //constructor 
    ChainingHash(int n = 11) {
        sizeofTable = n;
        numElements = 0;
        table.resize(sizeofTable);
    }
    //destructor
    ~ChainingHash() {
        this->clear();
    }

    //check if table is empty
    bool empty() {
        if(numElements != 0)
            return false;
        else
            return true;
    }

    //check how many elements are in the table
    int size() {
        return numElements;
    }

    //return value for a key in the hash table
    V& at(const K& key) {
        int spot = hash(key);

        for(auto i = table[spot].begin(); i != table[spot].end(); ++i)
        {
            if(i->first == key)
                return i->second;
        }

        throw std::out_of_range("Key not in hash");

       //exit;
        
    }

    //return value for a key in the hash table
    V& operator[](const K& key) {
        int spot = hash(key);

        for(auto i = table[spot].begin(); i != table[spot].end(); ++i)
        {
            if(i->first == key)
                return i->second;      
        }

        throw std::out_of_range("Key not in hash");

        //exit;
    }

    //get the number of elements in a bucket for a certain key
    int count(const K& key) {
        int spot = hash(key);
        int num = 0;

        for(auto i: table[spot])
        {
            if(i.first == key)
                ++num;
        }

        return num;
    }

    //insert key and value into hash table
    void emplace(K key, V value) {
        int spot = hash(key);
        pair<K, V> pair(key, value);
        table[spot].push_back(pair);
        ++numElements;

        if(load_factor() >= 0.75)
            rehash();
    }

    //insert key and value pair into hash table
    void insert(const std::pair<K, V>& pair) {
        int spot = hash(pair.first);
        table[spot].push_back(pair);
        ++numElements;

        if(load_factor() >= 0.75)
            rehash();
    }

    //erase the element in table with certain key
    void erase(const K& key) {

        int spot = hash(key);
        
        for(int t = table[spot].size(); t > 0; --t)
        {
            for (auto i = table[spot].begin(); i != table[spot].end(); ++i)
            {   
                if(i->first == key)
                {
                    table[spot].erase(i);
                    --numElements;
                    break;
                }
            }
        }
        
    }

    //clear the hash table of all elements
    void clear() {
        numElements = 0;
        table.clear();
    }

    //get number of buckets in table
    int bucket_count() {
        return sizeofTable;
    }

    //get the size of a certain bucket in the table
    int bucket_size(int n) {
        return table[n].size();
    }

    //get the bucket that a certain key would be placed in
    int bucket(const K& key) {
        int spot = hash(key);

        if(spot <= sizeofTable)
            return spot;
        else
            throw std::out_of_range("Key not in hash");
    }

    //ge the load factor for the hash table
    float load_factor() {

        return ((float)numElements/(float)sizeofTable);
    }

    //rehash all the elements into a new hash table about double the size of last table
    void rehash() {
        vector<list<pair<K,V>>> oldTable = table;
        sizeofTable = (findNextPrime(2* sizeofTable));
        
        this->clear();
        table.resize(sizeofTable);

        for(unsigned int i = 0; i < oldTable.size(); i++)
        {
            for(auto s = oldTable[i].begin(); s != oldTable[i].end(); s++)
                insert(*s);
        }
    }

    //rehash all elements into new hash table the size of closes prime to n
    void rehash(int n) {
        vector<list<pair<K,V>>> oldTable = table;
        sizeofTable = (findNextPrime(n));
        
        this->clear();
        table.resize(sizeofTable);

        for(unsigned int i = 0; i < oldTable.size(); i++)
        {
            for(auto s = oldTable[i].begin(); s != oldTable[i].end(); s++)
                insert(*s);
        }
    }


private:

    //private varaibles for hash table
    int sizeofTable;
    int numElements;

    vector<list<pair<K,V>>> table;

    //find the next prime to inputed n
    int findNextPrime(int n)
    {
        while (!isPrime(n))
        {
            n++;
        }
        return n;
    }

    //check if a number is prime
    int isPrime(int n)
    {
        for (int i = 2; i <= sqrt(n); i++)
        {
            if (n % i == 0)
            {
                return false;
            }
        }

        return true;
    }

    //hash a key for a certain slot in the hash table
    /*int hash(const K& key) {
        return key %= sizeofTable;
    }*/

    int hash(const string& key){
        int value = 0;

        for(int i = 0; i < key.length(); i++)
            value = 37 * value + key[i];
        
        value %= sizeofTable;

        if(value < 0)
            value += sizeofTable;

        return value;
    }

};

#endif //__CHAINING_HASH_H