#include <iostream>


template <class T>
struct node{
    T data;
    node* next;
};

template<class T>
class LinkedList{
    public:
        class LinkedListIterator{
                node<T>* ref_node;
            public:
                LinkedListIterator();
                LinkedListIterator(node<T>* node);
                LinkedListIterator& operator++();
                T operator*(){return ref_node->data; };
                bool operator==(LinkedListIterator other){return other.ref_node == ref_node;};
                bool operator!=(LinkedListIterator other){return other.ref_node != ref_node;};
                void testFunc();

        };
        LinkedListIterator begin(){LinkedListIterator start(head); return start;};
        LinkedListIterator end(){LinkedListIterator ending; return ending;};
        //TODO Implement rule of 5's!
        LinkedList();
        ~LinkedList();
        void addLast(T new_data);
        void addFirst(T new_data);
        int size();
        void clear();
    private:   
        node<T>* head;//first node
        node<T>* tail;//last node
        node<T>* empty_node;//used for flagging end of list.
};


//typedef LinkedListIterator LinkedListIterator;


//IMPLEMENTED FUNCTIONS:

//no param constructor:
template<class T>
LinkedList<T>::LinkedList(){
    head = nullptr;
}

//destructor
template<class T>
LinkedList<T>::~LinkedList(){
    clear();//deletes all pointer owned data's.
    
}

//clear the entire list
template<class T>
void LinkedList<T>::clear(){
    node<T>* delete_me;

    while(head != nullptr){
        delete_me = head;//set to current head
        head = head->next;//move head to next or nullptr
        delete delete_me;//delete old head.
    }
}

//return size of the list.
template <class T>
int LinkedList<T>::size(){
    
    //define some helper variables
    int count = 0;
    node<T>* count_node;
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
    node<T>* new_node = new node<T>();
    new_node->data = new_data;
    new_node->next = nullptr;
    
    //check if head does not exist yet:
    if(head == nullptr){
        head = new_node;
        tail = new_node;
        return;//node added, all done
    }
    
    
    //if head node exists, then iterate through and add at end:
    node<T>* iter_node = head;//iterating node
    while(iter_node->next != nullptr){//check if next node is tail node
        iter_node = iter_node->next;
    }
    //finally, add the node
    iter_node->next = new_node;
    tail = new_node;
}

//add new node at head of list
template <class T>
void LinkedList<T>::addFirst(T new_data){
    //create new node to add to list
    node<T>* new_node = new node<T>();
    //populate data into new node
    new_node->data = new_data;
    new_node->next = head;
    //shift head reference:
    head = new_node;
}

/*
    ITERATOR IMPLEMENTATION **************************
*/

//empty constructor to make a nullptr reference
template <class T>
LinkedList<T>::LinkedListIterator::LinkedListIterator(){
    ref_node = nullptr;
}

template <class T>
LinkedList<T>::LinkedListIterator::LinkedListIterator(node<T>* node){
    //created with a reference node passed:
    ref_node = node;
}

//barf what a declaration 
template <class T>
typename LinkedList<T>::LinkedListIterator& LinkedList<T>::LinkedListIterator::operator++(){
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

