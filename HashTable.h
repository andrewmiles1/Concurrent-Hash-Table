#ifndef HASHTABLE_H
#define HASHTABLE_H
#endif
#pragma once

#include "LinkedList.h"
#include <iostream>
#include <math.h>
#include <functional>
#include <thread>
#include <mutex>

enum CollisionHandleType {OPEN_ADDRESSING, CHAINING};
enum HashType {MULTIPLICATION, DIVISION};

//HashTable in working good state

template<class T, class U>
class HashTable{
    struct Item {
        T myKey;
        U myData;
    };

    public:
        HashTable(int (*func)(T), CollisionHandleType handle_type = CHAINING, HashType hash_type = DIVISION);
        ~HashTable();
        void addItem(T key, U item);
        void removeItem(T key);
        unsigned int getSize();
        void displayDiagnostic(bool display_full_list = false);
        bool search(T find_key);//returns true/false if key exists in table.
        void clear();//clears table.
    private:
        int hash(T key);
        unsigned int size;//number of items in table.
        unsigned int table_size;//number of cells in table
        LinkedList<Item>* table;//the actual array of linked lists
        void resizeAndRehash(int new_table_size);//used when item amount is disproportionate to table size
        int (*keyToInt)(T);
        bool isPrime(int);
        CollisionHandleType myCollisionHandling;
        HashType myHashType;
};

template<class T, class U>
HashTable<T, U>::HashTable(int (*func)(T), CollisionHandleType handleType, HashType hash_type){
    keyToInt = func;//save parsing function for hashing
    //FIXME - add ability to set approximate table size. 
    //initialize our table to a prime size.
    //just set to a good default prime number 59
    table = new LinkedList<Item>[59]();
    table_size = 59;
    size = 0;

    myCollisionHandling = handleType;
}

template<class T, class U>
HashTable<T, U>::~HashTable(){
    delete[] table;
}

template<class T, class U>
int HashTable<T, U>::hash(T key){
    //convert passed key,
    int key_int = keyToInt(key);
    //FIXME - should return differently based on hash type,
    // returns division type by default.
    return key_int % table_size;
}

template<class T, class U>
void HashTable<T, U>::resizeAndRehash(int new_table_size){

    LinkedList<Item>* new_table = new LinkedList<Item>[new_table_size];
    LinkedList<Item>* old_table = table;
    int old_size = table_size;
    table_size = new_table_size;
    table = new_table;//so that hashing functions will use the new table.

    for(int i = 0; i < old_size; i++){
        Item temp_item = old_table[i];
        addItem(temp_item.myKey, temp_item.myData);
    }

    delete old_table;//completed transition, delete old.

}

template<class T, class U>
void HashTable<T, U>::addItem(T key, U data){
    int key_index = hash(key);
    Item new_item;
    new_item.myKey = key;
    new_item.myData = data;
    //insert into linked list at key_index
    table[key_index].addLast(new_item);
    size++;
}

template<class T, class U>
void HashTable<T, U>::removeItem(T key){
    int key_index = hash(key);
    //iterate through linked list at index and remove if existing
    for(Item it : table[key_index]){
        if(it.myKey == key){
            table[key_index].remove(it);//remove it haha
        }
    }
    size--;
}

template<class T, class U>
void HashTable<T, U>::clear(){
    //clears list without resizing.
    for(int i = 0; i < table_size; i++){
        table[i].clear();
    }
}

template<class T, class U>
unsigned int HashTable<T, U>::getSize(){
    return size;
}

template<class T, class U>
void HashTable<T, U>::displayDiagnostic(bool display_full_list){
    int count = 0;
    int min_cluster = size;
    int max_cluster = 0;
    //loop through list to find info
    for(int i = 0; i < table_size; i++){
        int cell_size = table[i].size();
        //add to count
        count += cell_size;
        //find smallest/largest collision cluster in one cell.
        if(cell_size > 0){
            if(cell_size < min_cluster && cell_size != 0){
                min_cluster = cell_size;
            }
            if(cell_size > max_cluster){
                max_cluster = cell_size;
            }
        }
    }
    std::cout << "listed size is: " << size << std::endl;
    std::cout << "Counted size is: " << count << std::endl;
    std::cout << "Max cluster size: " << max_cluster << std::endl;
    std::cout << "Min cluster size: " << min_cluster << std::endl;  
    if(display_full_list){
        std::cout << "Table cells:" << std::endl;
        for(int i = 0; i < table_size; i++){
            std::cout << i << ": " << table[i].size() << std::endl;
        }
    }
}

template<class T, class U>
bool HashTable<T, U>::search(T find_key){
    int key_index = hash(find_key);
    for(Item it : table[key_index]){
        //TODO check each item in linked list for the key.
        if(it.myKey == find_key){
            return true;
        }
    }
    return false;
}