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


template<class T, class U>
class HashTable{
    struct Item {
            Item();
            Item(const Item& other);
            ~Item();
            Item& operator=(const Item& other);

            T myKey;
            U myData;
            std::mutex my_mutex;
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

/**
 * @brief Construct a new Hash Table object
 * 
 * @tparam T key type
 * @tparam U value type
 * @param func conversion function of custom key type to integer. Must return integer with single T parameter
 * @param handleType how should hash collisions be handled. OPEN_ADDRESSING or CHAINING
 * @param hash_type how should hash be calculated from key in int form. MULTIPLICATION or DIVISION
 */
template<class T, class U>
HashTable<T, U>::HashTable(int (*func)(T), CollisionHandleType handleType, HashType hash_type){
    keyToInt = func;//save parsing function for hashing
    //FIXME - add ability to set approximate table size. (this requires overloading)
    //initialize our table to a prime size.
    //just set to a good default prime number 59
    table = new LinkedList<Item>[59]();
    table_size = 59;
    size = 0;

    myCollisionHandling = handleType;
}

/**
 * @brief Destroy the Hash Table object
 * 
 * @tparam T key type
 * @tparam U value type
 */
template<class T, class U>
HashTable<T, U>::~HashTable(){
    delete[] table;
}

/**
 * @brief return hash value from int key
 * 
 * @tparam T key type
 * @tparam U value type
 * @param key integer to be converted
 * @return int converted hash location
 */
template<class T, class U>
int HashTable<T, U>::hash(T key){
    //convert passed key,
    int key_int = keyToInt(key);
    //FIXME - should return differently based on hash type,
    // returns division type by default.
    return key_int % table_size;
}

/**
 * @brief called when hash table needs to be resized. This can double as shrinking function or expansion function.
 * 
 * @tparam T key type
 * @tparam U value type
 * @param new_table_size size to shrink/expand to
 */
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

/**
 * @brief Adds item to hash table
 * 
 * @tparam T key type
 * @tparam U value type
 * @param key item's key 
 * @param data item's data
 */
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

/**
 * @brief Removes item from HashTable. if Item doesn't exist in table, nothing happens.
 * 
 * @tparam T key type
 * @tparam U value type
 * @param key item to be deleted's key
 */
template<class T, class U>
void HashTable<T, U>::removeItem(T key){
    int key_index = hash(key);
    //iterate through linked list at index and remove if existing
    for(Item it : table[key_index]){
        if(it.myKey == key){
            table[key_index].remove(it);//remove it haha
            size--;
        }
    }
    
}

/**
 * @brief empties list of all items. sets table to default size 59
 * 
 * @tparam T key type
 * @tparam U value type
 */
template<class T, class U>
void HashTable<T, U>::clear(){
    //TODO resize table to 59 or a default size
    //clears list without resizing.
    for(int i = 0; i < table_size; i++){
        table[i].clear();
    }
}

/**
 * @brief returns number of items in the hash table
 * 
 * @tparam T key type
 * @tparam U value type
 * @return unsigned int number of items in table 
 */
template<class T, class U>
unsigned int HashTable<T, U>::getSize(){
    return size;
}

/**
 * @brief Displays through cout the stored size count, a manual size count,
 *        max collisions in one cell, minimum collisions in one cell
 *       (not counting cells with 0 items.), and optionally every item in list.
 * 
 * @tparam T key type
 * @tparam U value type
 * @param display_full_list instructs function to display full list
 */
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

/**
 * @brief searches to see if key exists in table
 * 
 * @tparam T key type
 * @tparam U value type
 * @param find_key key to be found
 * @return true key exists in table
 * @return false key does not exist in table
 */
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

//******************* HASHTABLE::ITEM IMPLEMENTATION *************************************
template<class T, class U>
HashTable<T, U>::Item::Item(){
    //I'm not convinced I need a constructor destructor in this case
}

template<class T, class U>
HashTable<T, U>::Item::~Item(){
    //maybe something has to happen here with mutex?
}

/**
 * @brief Construct a new Item from passed other item
 * 
 * @tparam T key type
 * @tparam U value type
 * @param other passed object to copy
 */
template<class T, class U>
HashTable<T, U>::Item::Item(const Item& other){
    std::unique_lock other_lock(other.my_mutex);
    std::unique_lock this_lock(my_mutex);

    myData = other.myData;
    myKey = other.myKey;
}

/**
 * @brief copy details of other item to mine
 * 
 * @tparam T key type
 * @tparam U value type
 * @param other item to copy from
 * @return HashTable<T, U>::Item& freshly copied to item
 */
template<class T, class U>
HashTable<T, U>::Item& HashTable<T, U>::Item::operator=(const Item& other){
    std::unique_lock other_lock(other.my_mutex);
    std::unique_lock this_lock(my_mutex);

    myData = other.myData;
    myKey = other.myKey;
    return this;
}