#pragma once

#include "LinkedList.h"
#include <iostream>

void TestLinkedList() {

	std::cout << "~~~~~~~~~~~~~Testing LinkedList from andrewmiles1~~~~~~~~~~~~~" << std::endl;
	std::cout << "\n--Initilization, adding to and clearing the list" << std::endl;
	std::cout << "Adding 4 numbers..." << std::endl;
	//Initialization, adding, clearing
	LinkedList<int> test_list1;
	test_list1.addLast(0);
	test_list1.addLast(1);
	test_list1.addLast(2);
	test_list1.addLast(3);

	std::cout << "List contains: ";
	for (LinkedList<int>::Iterator it = test_list1.begin(); it != test_list1.end(); it++) {
		std::cout << *it << " ";
	}

	std::cout << "\n\nClearing list..." << std::endl;
	test_list1.clear();
	std::cout << "List contains " << test_list1.size() << " items." << std::endl;

}
