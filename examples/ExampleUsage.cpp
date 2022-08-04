#include <iostream>
#include "../include/HashTable.h"

int main() {
    andrewmiles2::HashTable<int, int> squares_table([](int num) {return num; });

    squares_table.update(1, 1);
    squares_table.update(2, 4);
    squares_table.update(3, 9);
    squares_table.update(4, 16);
    squares_table.update(5, 25);
    squares_table.update(6, 36);
    squares_table.update(7, 49);
    squares_table.update(8, 64);
    squares_table.update(9, 81);
    squares_table.update(10, 100);
    squares_table.update(11, 121);
    squares_table.update(12, 144);


    for (int i = 0; i < squares_table.getSize(); i++) {
        std::cout << i << " squared is " << squares_table.get(i) << std::endl;
    }

    return 0;
    
}

