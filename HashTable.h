#ifndef HASHTABLE_H
#define HASHTABLE_H
#endif
#pragma once

#include "LinkedList.h"
#include <iostream>

template<class T>
class HashTable{
    private:
        int large_prime;
        vector<LinkedList<T>> table;
        
    public:
        HashTable();
        
};