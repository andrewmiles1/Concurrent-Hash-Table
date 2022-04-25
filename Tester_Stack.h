#pragma once

#include <iostream>
#include "Stack.h"

void TestStack(){
        Stack<int> myStack(100);
    for(int i = 150-1; i >= 0; i--){
        myStack.push(i);
    }
    std::cout << myStack.get(60) << std::endl;
}