#ifndef HASHTABLE_H
#define HASHTABLE_H
#endif
#pragma once

#include "LinkedList.h"
#include <iostream>

template<class T>
class HashTable{
    private:
        int size;//number of items in table.
        vector<LinkedList<T>> table;//the actual table
        void resize_and_rehash();//too many items in table, resize!
    public:
        HashTable();
        
};