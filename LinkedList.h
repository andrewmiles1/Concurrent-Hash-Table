#ifndef LINKEDLIST_H
#define LINKEDLIST_H
#endif
#pragma once

#include <iostream>
#include <memory>

template <class T>
struct node{
    T data;
    std::shared_ptr<node<T>> next;
};

template<class T>
class LinkedList{
    public:
        class Iterator;//implemented after LinkedList 
        Iterator begin(){Iterator start(head); return start;};
        Iterator end(){Iterator ending; return ending;};
        //TODO Implement rule of 5's!
        LinkedList();
        LinkedList(const LinkedList& copy_list);//copy constructor
        ~LinkedList();
        LinkedList& operator=(const LinkedList& rhs);

        void addLast(T new_data);
        void addFirst(T new_data);
        T removeLast();//remove last and return it
        T remove(T remove_me);//remove and return item
        bool find(T find_me);
        int size();
        void clear();
    private:   
        //node<T>* head;//first node
        std::shared_ptr<node<T>> head;
};


/*
* ***************************************************
* *  LINKEDLIST IMPLEMENTATION                      *
* ***************************************************
* !Required to be in the .h because of templates!
*/

//no param constructor:
template<class T>
LinkedList<T>::LinkedList(){
    head = nullptr;
}

//copy constructor:
template<class T>
LinkedList<T>::LinkedList(const LinkedList& copy_list) {

    //iterate through copy list and deep copy it into this
    for (std::shared_ptr<node<T>> temp_node = copy_list.head; temp_node != nullptr; temp_node = temp_node->next) {
        this->addLast(temp_node->data);
    }
    
}

//destructor
template<class T>
LinkedList<T>::~LinkedList(){
    clear();//deletes all pointer owned data's.
}

//copy assignment operator overload
template<class T>
LinkedList<T>& LinkedList<T>::operator=(const LinkedList& rhs) {
    if (this == &rhs) {//prevent self assignment
        return *this;
    }

    clear();//clear my current list.

    //deep copy each node from rhs
    for (std::shared_ptr<node<T>> temp_node = rhs.head; temp_node != nullptr; temp_node = temp_node->next) {
        this->addLast(temp_node->data);
    }
    //return me for chaining assignments
    return *this;
}


//clear the entire list
template<class T>
void LinkedList<T>::clear(){
    std::shared_ptr<node<T>> delete_me;

    while(head != nullptr){
        delete_me = head;//set to current head
        head = head->next;//move head to next or nullptr
        delete_me.reset();
        //delete delete_me;//delete old head.
    }
}

//return size of the list.
template <class T>
int LinkedList<T>::size(){
    
    //define some helper variables
    int count = 0;
    std::shared_ptr<node<T>> count_node;
    count_node = head;
    
    //iterate and count.
    while(count_node != nullptr){
        count++;
        count_node = count_node->next;
    }

    //return result
    return count;
}

//add item to end of list
template <class T>
void LinkedList<T>::addLast(T new_data){
    
    //create node to add into list:
    std::shared_ptr<node<T>> new_node = std::make_shared<node<T>>();//new node<T>();
    new_node->data = new_data;
    new_node->next = nullptr;
    
    //check if head does not exist yet:
    if(head == nullptr){
        head = new_node;
        return;//node added, all done
    }
    
    
    //if head node exists, then iterate through and add at end:
    std::shared_ptr<node<T>> iter_node = head;//iterating node
    while(iter_node->next != nullptr){//check if next node exists
        iter_node = iter_node->next;
    }
    //finally, add the node
    iter_node->next = new_node;
}

//add new node at head of list
template <class T>
void LinkedList<T>::addFirst(T new_data){
    //create new node to add to list
    std::shared_ptr<node<T>> new_node = std::make_shared<node<T>>();//new node<T>();
    //populate data into new node
    new_node->data = new_data;
    new_node->next = head;
    //shift head reference:
    head = new_node;
}

//remove last and return it
template <class T>
T LinkedList<T>::removeLast() {
    if (head == nullptr) {
        //if list is empty do nothing, return null
        return NULL;
    }

    T temp_data;

    //is head last
    if (head->next == nullptr) {
        temp_data = head->data;
        head.reset();
        //delete head;
        //head = nullptr;
        return temp_data;
    }

    //iterate through to second to last node
    std::shared_ptr<node<T>> temp_node = head;
    while (temp_node->next->next != nullptr) {
        temp_node = temp_node->next;
    }

    //save the emd node's data to return, and destroy end node.
    temp_data = temp_node->next->data;
    temp_node.reset();
    //delete temp_node->next;
    //temp_node->next = nullptr;
    return temp_data;

}

//remove requested node -!Returns T so I can return NULL if remove_me wasn't found in list. a search/remove all in one.
template<class T>
T LinkedList<T>::remove(T remove_me) {
    //return null if empty
    if(head == nullptr){
        return NULL;
    }
    
    //check head node
    if (head->data == remove_me) {
        std::shared_ptr<node<T>> delete_me = head;//get deletion reference ready
        head = head->next;//remove existance from list
        //delete delete_me;//deletes itself when out of scope.
        return remove_me;
    }
    //iterate through and find node if it exists.
    for (std::shared_ptr<node<T>> temp_node = head; temp_node != nullptr; temp_node = temp_node->next) {
        if (temp_node->next->data == remove_me) {
            std::shared_ptr<node<T>> delete_me = temp_node->next;//get a deletion reference ready
            temp_node->next = temp_node->next->next;//remove existance from list
            //delete delete_me;//deletes itself when out of scope
            return remove_me;
        }
    }
    //if we got here we never found the requested T, return NULL to signal not found
    return NULL;
}

//Search for passed item in list.
template<class T>
bool LinkedList<T>::find(T find_me) {
    for (Iterator it = begin(); it != end(); it++) {//iterate through list.
        if (*it == find_me) {//if value is what we're looking for,
            return true;//return true
        }
    }
    return false;//if we got here, we never found it.
}

/*
* ***************************************************
* *  ITERATOR IMPLEMENTATION                        *
* ***************************************************
*/
template<class T>
class LinkedList<T>::Iterator {
        std::shared_ptr<node<T>> ref_node;
    public:
        Iterator();
        Iterator(std::shared_ptr<node<T>> node) { ref_node = node; }; //copy assignment operator
        Iterator& operator++();
        Iterator operator++(int amt) { Iterator temp_it = *this; ref_node = ref_node->next; return temp_it; };//untested
        T operator*() { return ref_node->data; };
        bool operator==(Iterator other) { return other.ref_node == ref_node; };
        bool operator!=(Iterator other) { return other.ref_node != ref_node; };
};

//empty constructor to make a nullptr reference
template <class T>
LinkedList<T>::Iterator::Iterator() {
    ref_node = nullptr;
}


//barf what a declaration 
template <class T>
typename LinkedList<T>::Iterator& LinkedList<T>::Iterator::operator++(){
    //return next node if not empty or last node,
    if(ref_node != nullptr && ref_node->next != nullptr){
        ref_node = ref_node->next;
    }
    else{
        //if empty or last node, we'll just set our ref to nullptr
        ref_node = nullptr;
    }
    return *this;
}

