#pragma once

#include <iostream>
#include "Stack.h"

void TestStack(){
    std::cout << "================Stack Testing==================" << std::endl;
    std::cout << "==Creating empty and non-empty stack size 100...\n";
    Stack<int> empty_stack(100);
    Stack<int> myStack(100);

    std::cout << "==Adding 150 items to stack sized 100...\n";
    for(int i = 150-1; i >= 0; i--){
        myStack.push(i);
        //leaves list to be 0 to 100
    }
    std::cout << "==Getting item from list...\n";
    std::cout << "Should be the number 60: " << myStack.get(60) << std::endl;
    std::cout << "==Updating number 60 to be 99...\n";
    myStack.update(99, 60);
    std::cout << "Now it should be 99: " << myStack.get(60) << std::endl;
    std::cout << "top of stack should be 0: " << myStack.get() << std::endl;
    std::cout << "==Updating top of stack to be 88...\n";
    myStack.update(88);
    std::cout << "Now it should be 88: " << myStack.get() << std::endl;
    std::cout << "==Grabbing index out of bounds from stack size...\n";
    std::cout << "Should be 99: " << myStack.get(150) << std::endl;
    std::cout << "==Testing edge case of loop-around...\n";
    std::cout << "Array slot size-1 :: Should be 50: " << myStack.get(50) << std::endl;
    std::cout << "Array slot 0 :: Should be 49: " << myStack.get(49) << std::endl;

    std::cout << "==Testing empty list...(will return garbage, that's ok)" << std::endl;
    std::cout << "Get top of stack from empty list: " << empty_stack.get() << std::endl;
    std::cout << "Get non-added number from stack (50): " << empty_stack.get(50) << std::endl;
    std::cout << "Get index outside of stack size (150): " << empty_stack.get(150) << std::endl;
}