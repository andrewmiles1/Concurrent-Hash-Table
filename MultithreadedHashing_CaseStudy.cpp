// MultithreadedHashing_CaseStudy.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include "LinkedList.h"
#include "HashTable.h"
#include "Tester_LinkedList.h"
#include <string>

int parse_key(std::string str){
    return int(str[0]) * str.length();
}

int main()
{
    //test linked list add last and size:
    //TestLinkedList();

    HashTable<std::string, int> my_table(&parse_key);
    my_table.addItem("Andrew", 38);
    my_table.displayDiagnostic();
    std::cout << "Is Andrew in the table: " << my_table.search("Andrew") << std::endl;
    std::cout << "Is Lauren in the table: " << my_table.search("Lauren") << std::endl;
}



// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file
