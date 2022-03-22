#include <iostream>
#include "DataPoint.h"
#include "LinkedList.h"

int old_main() {
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
    LinkedList<int>::Iterator it = test_list.begin();
    for(it = test_list.begin(); it != test_list.end(); ++it){
        std::cout << *it << std::endl;
    }

    return 0;
    
}

