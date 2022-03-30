#ifndef HASHTABLE_H
#define HASHTABLE_H
#endif
#pragma once

#include "LinkedList.h"
#include <iostream>
#include <math.h>
#include <functional>

template<class T, class U>
class HashTable{
    private:
        unsigned int size;//number of items in table.
        unsigned int table_size;//number of cells in table
        LinkedList<U>* table;//the actual array of linked lists
        void resizeAndRehash();//too many items in table, resize!
        int keyToInt(U key);
        bool isPrime(int);
    public:
        HashTable(std::function<int(T)>&  keyParseFunction);
        ~HashTable();
        void addItem(T key, U item);
        unsigned int getSize();
};

template<class T, class U>
HashTable<T, U>::HashTable(std::function<int(T)>&  keyParseFunction){
    keyToInt = keyParseFunction;//save parsing function for hashing

    //initialize our table to a prime size.
    //just set to a good default prime number 59
    table = new LinkedList<U>[59]();
    table_size = 59;

}

template<class T, class U>
HashTable<T, U>::~HashTable(){
    delete table;
}

template<class T, class U>
void HashTable<T, U>::addItem(T key, U item){
    //convert key to int
    int key_int = keyToInt(key);
    //make sure negative doesn't happen - FIXME should have a different solution to this, maybe unsigned int as return type to keyToInt
    if(key_int < 0) key_int * -1;
    //hash integer based on hash type
    //FIXME this uses modulous hashing or division hashing just for first version,
    // ideally I want it to be able to utilize division or the multiplication method based on programmer preference.
    int key_index = key_int % table_size;
    //insert into linked list at key_index
    table[key_index].addLast(item);
}

template<class T, class U>
unsigned int HashTable<T, U>::getSize(){
    return size;
}