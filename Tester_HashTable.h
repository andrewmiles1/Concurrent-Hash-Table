#pragma once

#include <iostream>
#include "HashTable.h"
#include <string>
using namespace andrewmiles2;

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
    std::cout << "==Constructor and Update testing" << std::endl;
    HashTable<std::string, int> test_table(&parse_string_key, MULTIPLICATION);
    HashTable<std::string, int> empty_table(&parse_string_key, MULTIPLICATION);
    test_table.update("Andrew", 38);
    test_table.displayDiagnostic();
    std::cout << "Is Andrew in the table: " << test_table.search("Andrew") << std::endl;
    std::cout << "Andrew's number: " << test_table.get("Andrew") << std::endl;
    std::cout << "Is Lauren in the table: " << test_table.search("Lauren") << std::endl;
    std::cout << "Adding 100 strings to table..." << std::endl;
    for(int i = 0; i < 100; i++){
        test_table.update(std::to_string(i+64), i);
    }
    test_table.displayDiagnostic();

    std::cout << "==Diagnostic of empty table:" << std::endl;
    empty_table.displayDiagnostic();

    std::cout << "==Search in an empty table:" << std::endl;
    std::cout << "is Fake in the table: " << empty_table.search("Fake") << std::endl;
}