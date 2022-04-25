#pragma once

#include <iostream>
#include "HashTable.h"
#include <string>

int parse_string_key(std::string str){
    int sum = 0;
    for(char letter : str){
        sum += int(letter);
    }
    return sum;
}

void TestHashTable(){
    //constructor and update testing
    std::cout << "=================HashTable Testing================" << std::endl;
    std::cout << "==Constructor and Update testing:"
    HashTable<std::string, int> my_table(&parse_string_key, MULTIPLICATION);
    my_table.update("Andrew", 38);
    my_table.displayDiagnostic();
    std::cout << "Is Andrew in the table: " << my_table.search("Andrew") << std::endl;
    std::cout << "Is Lauren in the table: " << my_table.search("Lauren") << std::endl;
    for(int i = 0; i < 100; i++){
        my_table.update(std::to_string(i+64), i);
    }
    my_table.displayDiagnostic();
}