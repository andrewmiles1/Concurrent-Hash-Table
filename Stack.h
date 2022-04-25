#include <iostream>

template <class T>
class Stack{
    public:
    Stack(size_t size);//constructor - size required.
    void push(T new_item);//push new item to top of stack
    void update(T new_item, size_t index);//over-write existing item index items deep
    T get(size_t index=0);//return an item index items deep, defaults to top item.

    private:
    size_t size;
    size_t top;//index top item in stack.
    T data_table[];
};

template <class T>
Stack<T>::Stack(size_t size){
    this->size = size;
    data_table [size];
    top = 0;//set top of stack at front of array
}

/**
 * @brief //push new item to top of stack
 * 
 * @tparam T 
 * @param new_item new item to push onto stack
 */
template <class T>
void Stack<T>::push(T new_item){
    if(top == size-1){
        //if we're at the end of the looped stack
        top = 0;
    }
    else{
        //if we're not at the top
        top++;
    }
    data_table[top] = new_item;
}

/**
 * @brief updates item at index deep in stack.
 * 
 * @tparam T item type 
 * @param new_item new data to overwite with
 * @param index how deep in the stack to write the data
 */
template <class T>
void Stack<T>::update(T new_item, size_t index){
    //find requested index from cycle based stack.
    if(index > top){//if our index will put us out of bounds,
        //loop around from the back of the table.
        data_table[size - (index - top)] = new_item;
    }
    else{
        //don't have to loop around, just get index away from top.
        data_table[top-index] = new_item;
    }
}

/**
 * @brief returns index deep from stack.
 * 
 * @tparam T 
 * @param index requested index deep from stack
 * @return T 
 */
template <class T>
T Stack<T>::get(size_t index){
    //if index will put us out of bounds,
    if(index > top){
        return data_table[size - (index - top)];
    }
    else{
        //return top - index
        return data_table[top - index];
    }
}


