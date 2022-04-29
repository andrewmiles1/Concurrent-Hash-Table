#pragma once

#include "LinkedList.h"
#include <iostream>

using namespace andrewmiles2;

//normal case, large case, shouldn't work (opt), edge case

void TestLinkedList() {

	std::cout << "~~~~~~~~~~~~~Testing LinkedList from andrewmiles1~~~~~~~~~~~~~" << std::endl;

	//--Adding to and clearing the list testing
	std::cout << "\n--Initilization, adding to and clearing the list" << std::endl;
	std::cout << "Adding 4 numbers..." << std::endl;

	LinkedList<int> test_list1;
	test_list1.addFirst(1);
	test_list1.addFirst(0);
	test_list1.addLast(2);
	test_list1.addLast(3);

	std::cout << "Iterating with .at() function:\n";
	for(int i = 0; i < test_list1.size(); i++){
		std::cout << test_list1.at(i) << ", ";
	}
	std::cout << std::endl;


	std::cout << "List contains: ";
	for (LinkedList<int>::Iterator it = test_list1.begin(); it != test_list1.end(); it++) {
		std::cout << *it << " ";
	}

	std::cout << "Clearing list..." << std::endl;
	test_list1.clear();
	std::cout << "List contains " << test_list1.size() << " items." << std::endl;

	std::cout << "Adding 10,000 items to list..." << std::endl;
	for(int i = 0; i < 5000; i++){
		test_list1.addLast(i);
	}
	for(int i = 0; i < 5000; i++){
		test_list1.addFirst(i);
	}
	std::cout << "List contains " << test_list1.size() << " items." << std::endl;

	std::cout << "Clearing large list..." << std::endl;
	test_list1.clear();
	std::cout << "List contains " << test_list1.size() << " items." << std::endl;

	std::cout << "Clearing an empty list..." << std::endl;
	test_list1.clear();
	std::cout << "List contains " << test_list1.size() << " items." << std::endl;

	std::cout << "\n--Search and Single removal testing--" << std::endl;
	std::cout << "Populating list with 100 numbers..." << std::endl;
	for(int i = 0; i < 100; i++){
		test_list1.addLast(i);
	}

	std::cout << "Removing 55, 33, and 77..." << std::endl;
	test_list1.remove(55);
	test_list1.remove(33);
	test_list1.remove(77);
	std::cout << "Removing last 2 numbers..." << std::endl;
	test_list1.removeLast();
	test_list1.removeLast();
	std::cout << "List contains: " << std::endl;
	for(int i : test_list1){
		std::cout << i << " ";
	}
	std::cout << std::endl << "Searching for 22 should return true: " << test_list1.find(22) << std::endl;
	std::cout << "Clearing list and removing 55 and last from empty list..." << std::endl;
	test_list1.clear();
	test_list1.removeLast();
	std::cout << "Trying to remove 55 from empty list should return NULL: " << test_list1.remove(55) << std::endl;
	std::cout << "Trying to find 22 from empty list should return false: " << test_list1.find(22) << std::endl;

}
