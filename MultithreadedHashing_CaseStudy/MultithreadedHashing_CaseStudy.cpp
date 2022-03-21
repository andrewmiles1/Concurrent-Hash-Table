// MultithreadedHashing_CaseStudy.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include "LinkedList.h"

int main()
{
    //test linked list add last and size:
    LinkedList<int> test_list;
    test_list.addLast(5);
    test_list.addLast(4);
    test_list.addLast(8);
    test_list.addLast(4);
    test_list.addLast(5);
    test_list.addLast(6);
    std::cout << test_list.size() << std::endl;
    test_list.clear();
    std::cout << test_list.size() << std::endl;

    std::cout << "Iterator testing:" << std::endl;
    //test iterator:
    test_list.addLast(1);
    test_list.addLast(2);
    test_list.addLast(3);
    test_list.addLast(4);
    test_list.addLast(5);
    test_list.addLast(6);
    LinkedList<int>::LinkedListIterator it = test_list.begin();
    for (it = test_list.begin(); it != test_list.end(); ++it) {
        std::cout << *it << std::endl;
    }
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
