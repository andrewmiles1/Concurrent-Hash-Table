#ifndef HASHTABLE_H
#define HASHTABLE_H
#endif
#pragma once

/* Concurrent HashTable using locks (thread safe)
* @author andrewmiles2
* Made this as a learning exercise and boy did I learn a thing or two.
*/

#include "LinkedList.h"
#include <iostream>
#include <math.h>
#include <functional>
#include <thread>
#include <mutex>

namespace andrewmiles2 {

    enum HashType {MULTIPLICATION, DIVISION};

    template<class T, class U>
    class HashTable{
        struct Item {
                Item();
                Item(const Item& other);//copy constructor
                Item(Item&& other);//move constructor
                Item(T key, U data);//constructor with data.
                ~Item();
                Item& operator=(const Item& other) ;//copy assignment operator
                Item& operator=(Item&& other) noexcept;//move assignment operator

                T my_key;
                U my_data;
                mutable std::recursive_mutex my_mutex;
        };

        public:
            HashTable(int (*func)(T), HashType hash_type = DIVISION);
            ~HashTable();
            void update(T key, U item);//adds/updates item
            U get(T key);//gets item from table
            //void removeItem(T key);
            unsigned int getSize();
            void displayDiagnostic(bool display_full_list = false);
            bool search(T find_key);//returns true/false if key exists in table.
            //void clear();//clears table.
        private:
            int hash(T key);
            double fractionalPart(double num);
            unsigned int size;//number of items in table.
            unsigned int table_size;//number of cells in table
            LinkedList<Item>* table;//the actual array of linked lists
            void resizeAndRehash();//used when item amount is disproportionate to table size
            bool isPrime(int num);
            int (*keyToInt)(T);
            HashType myHashType;
            bool table_is_resizing;//true when table is in resizing process
            int current_usage_count;//used to count threads using table
            double const MULT_CONST = 0.618033;
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
    HashTable<T, U>::HashTable(int (*func)(T), HashType hash_type){
        keyToInt = func;//save parsing function for hashing
        //FIXME - add ability to set approximate table size. (this requires overloading)
        //initialize our table to a prime size.
        //just set to a good default prime number 59
        table = new LinkedList<Item>[59]();
        table_size = 59;
        size = 0;
        current_usage_count = 0;
        table_is_resizing = false;
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
        if(myHashType == DIVISION){
            return key_int % table_size;
        }
        else{// if myHashType == MULTIPLICATION
            return std::floor(table_size * (fractionalPart(MULT_CONST * double(key_int))));
        }
    }

    template<class T, class U>
    double HashTable<T, U>::fractionalPart(double num){
        return num - int(num);
    }

    /**
     * @brief called when hash table needs to be resized. This can double as shrinking function or expansion function.
     * 
     * @tparam T key type
     * @tparam U value type
     * @param new_table_size size to shrink/expand to
     */
    template<class T, class U>
    void HashTable<T, U>::resizeAndRehash(){
        table_is_resizing = true;//TODO could this be a lock instead?
        while(current_usage_count > 0);//spinning wait for table logouts

        unsigned int new_table_size = table_size * 2;//multiply it by two
        while(isPrime(new_table_size)){//and make it prime.
            new_table_size++;
        }

        LinkedList<Item>* new_table = new LinkedList<Item>[new_table_size];
        LinkedList<Item>* old_table = table;
        int old_size = table_size;
        table_size = new_table_size;
        table = new_table;//so that hashing functions will use the new table.

        for(int i = 0; i < old_size; i++){
            //iterate through list at i
            for(Item it: old_table[i]){
                Item temp_item = it;
                int key_int = hash(temp_item.my_key);
                table[key_int].addLast(temp_item);
            }
        }
        delete[] old_table;//completed transition, delete old.

        table_is_resizing = false;
    }

    /**
     * @brief returns if num is prime or not
     * 
     * @param num integer to test if prime
     * @return if num is prime
     */
    template<class T, class U>
    bool HashTable<T, U>::isPrime(int num){
        float num_sqrt = std::sqrt(num);//so I only have to calculate once
        //check some outlier numbers:
        if(num < 2 || (!(num&1) && num != 2))
            return true;

        //loop through all factors until sure.
        for(int i=3; i<=num_sqrt; i+=2){
            if(!(num % i))
                return true;
        }
        return false;
    }

    /**
     * @brief updates item if it already exists, adds it if it doesn't.
     * 
     * @tparam T key type
     * @tparam U value type
     * @param key item's key
     * @param data item's new value
     */
    template<class T, class U>
    void HashTable<T, U>::update(T key, U data){
        while(table_is_resizing);//spinning wait until done
        current_usage_count++;//log current table usage

        int key_index = hash(key);
        //look to see if item already exists
        for(Item &it : table[key_index]){
            if(it.my_key == key){//if key already exists in table
                //lock access to item
                
                std::unique_lock<std::recursive_mutex> update_lock(it.my_mutex);
                //update data
                it.my_data = data;
                //retrn and unlock
                current_usage_count--;
                return;
            }
        }

        //reached here, it doesn't exist.
        //ADD NEW ITEM - since it doesn't exist in the table
        table[key_index].addLast(Item(key, data));
        size++;//increment size

        current_usage_count--;//decrement usage count.

        //check table size to see if it's too big and needs resizing.
        if(size / table_size > 0.75){//if table load factor is too high
            resizeAndRehash();
        }
    }

    /**
     * @brief returns value at key BY VALUE
     * 
     * @tparam T key type
     * @tparam U value type
     * @param key requested key
     * @return U the value at requested key, COPIED
     */
    template <class T, class U>
    U HashTable<T, U>::get(T key){

        //convert key to index
        int key_index = hash(key);

        //return value
        for(Item &it : table[key_index]){
            if(it.my_key == key){
                return it.my_data;
            }
        }
        return NULL;
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
        std::cout << "**HashTable Diagnostic**" << std::endl;
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
        std::cout << "**End Diagnostic**" << std::endl;
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
            if(it.my_key == find_key){
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
    HashTable<T, U>::Item::Item(T key, U data)
    :my_key{key}, my_data{data}{}

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
        //lock other and current
        std::unique_lock<std::recursive_mutex> other_lock(other.my_mutex);
        std::unique_lock<std::recursive_mutex> this_lock(my_mutex);

        //copy data
        my_data = other.my_data;
        my_key = other.my_key;
    }

    /**
     * @brief move-constructor
     * 
     * @tparam T key type
     * @tparam U value type
     * @param other object to move from
     */
    template<class T, class U>
    HashTable<T, U>::Item::Item(Item&& other){
        //lock other and current
        std::unique_lock<std::recursive_mutex> other_lock(other.my_mutex);
        std::unique_lock<std::recursive_mutex> this_lock(my_mutex);

        //move data, leave other in empty state
        my_data = std::move(other.my_data);
        my_key = std::move(other.my_key);
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
    typename HashTable<T, U>::Item& HashTable<T, U>::Item::operator=(const Item& other){
        if(this == &other){
            return *this;//prevent self assignment
        }
        //lock both other and current,
        std::unique_lock<std::recursive_mutex> other_lock(other.my_mutex);
        std::unique_lock<std::recursive_mutex> this_lock(my_mutex);

        //copy data
        my_data = other.my_data;
        my_key = other.my_key;
        return *this;
    }

    /**
     * @brief move assignment overload
     * 
     * @tparam T key type
     * @tparam U value type
     * @param other item to move from
     * @return HashTable<T, U>::Item& freshly moved item
     */
    template<class T, class U>
    typename HashTable<T, U>::Item& HashTable<T, U>::Item::operator=(Item&& other) noexcept{
        if(this == &other){
            return;//prevent self assignment
        }

        //lock other and current
        std::unique_lock<std::recursive_mutex> other_lock(other.my_mutex);
        std::unique_lock<std::recursive_mutex> this_lock(my_mutex);

        //move data, leaving other in empty state.
        my_data = std::move(other.my_data);
        my_key = std::move(other.my_data);
        return *this;
    }

}//end namespace andrewmiles2