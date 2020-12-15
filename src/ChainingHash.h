/*
Name: Quinn Barnwell
Description: implementation of hashing one using 
chaining.
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
    
    
    //resets the table to its initial state (see default constructor) - used for testing purposes
    void reset() {
        this->sizeOfTable = 11;
        this->clear();
        this->table.resize(11);
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
    
    /*
        prints the contents of the hash table in the format
            [0] 
                (key | value) ->
                (key | value) ->
                ...
            [1]
                (key | value) ->
                (key | value) ->
                ...
            [2] EMPTY
            [3]
            ...
        this function is called in the TestChainingHash class so we can verify that the hash table is updating key/value pairs properly
    */
    void printTable() const {
        this->printTableHeader();
        for(int i = 0; i < this->table.size(); ++i)
            printBucket(i)
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
    
    /*******************************
    - PRIVATE PRINT HASH TABLE HELPER FUNCTIONS  -
    ********************************/
    
    /*
        displays the current size, bucket count, and empty value of the hash table before its contents are displayed
        in the public printTable() function above
    */
    void printTableHeader() const {
        string bucketCountStr = "Bucket count: " + std::to_string(this->bucket_count());
        string sizeStr = "Size: " + std::to_string(this->size());
        string emptyStr = "Empty: " + (this->empty() ? "true" : "false");

        print(bucketCountStr + " " + sizeStr + " " + emptyStr + "\n");
    }
  
    /*
        prints a key value pair in the format (key | value) -> (our buckets are doubly linked lists (std::list stl container class), which is where the "->" comes from)
    */
    void printKeyValue(const pair<K, V> &keyValue) const {
        print("\t\t(" + keyValue.first + " | " + keyValue.second + ") ->\n");
    }

    /*
        prints the index of a bucket before its contents are displayed
        format is [index]
    */
    void printIndex() const {
        print("\n\t[" + std::to_string(index) + "]\n");
    }

    /*
        prints the contents of the bucket at the given index using the helper functions above
    */
    void printBucket(int index) const {
        list<pair<K, V>> bucket = this->table[index];
        int bucketSize = bucket.size();

        printIndex(index);
        if(bucketSize == 0)
            print("\t\tEMPTY");
        else {
            for(auto it = bucket.begin(); it != bucket.end(); ++it)
                this->printKeyValue(*it);
        }
    
    }

};

#endif //__CHAINING_HASH_H