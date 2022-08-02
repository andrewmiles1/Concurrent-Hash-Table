#include <iostream>
#include <thread>
#include <random>
#include "HashTable.h"
#include <string>

using namespace andrewmiles2;

const int ITEMS_IN_TABLE = 50;//keep at 26 to just have alphabet in table.
const int THREAD_COUNT = 5;
const int TASKS_PER_THREAD = 1000;


int parse_key(int num){

    return num;
}

void TestConcurrency(){
    std::cout << "===========Concurrency testing===========\n";
    //CONCURRENCY TESTING:

    //create hash table of 100 string,int items
    HashTable<int, int> test_table([](int num){return num;});
    std::vector<std::thread> threads;

    std::cout << "Test table contains: \n";
    for(int i = 0; i < ITEMS_IN_TABLE; i++){
        test_table.update(i, 50);//65... the alphabet
        std::cout << i << ":" << test_table.get(i) << std::endl;
    }
    std::cout << "\n";
    test_table.displayDiagnostic();


    auto complete_tasks = [](int task_count, HashTable<int, int>& hash_table, int id){
            std::uniform_real_distribution<> key_range(0, ITEMS_IN_TABLE);
            std::uniform_real_distribution<> value_range(1, 100);
            std::default_random_engine rand_num_eng(time(0));

            for(int i = 0; i < task_count; i++){
                int rand_key = int(key_range(rand_num_eng));
                int rand_value = int(value_range(rand_num_eng));
                std::string str = std::to_string(id) +"-"+ std::to_string(rand_key) + "::" + std::to_string(rand_value) + "\n";
                std::cout << str;
                hash_table.update(rand_key, rand_value);
            }
            
            //do a bunch of tasks
            std::cout << "Thread completed.\n";
    };

    //create a bunch of threads to fulfill tasks, I don't know how many.
    for(int i = 0; i < THREAD_COUNT; i++){
        threads.push_back(std::thread(complete_tasks, TASKS_PER_THREAD, std::ref(test_table), i));
    }
    for(auto it = threads.begin(); it != threads.end(); it++){
        if(true)
            it->join();//join each thread until they're done.
    }
    std::cout << "Test table contains: \n";
    for(int i = 0; i < ITEMS_IN_TABLE; i++){
        std::cout << i << ":" << test_table.get(i) << " ";
    }
    std::cout << std::endl;
    //display diagnostic
    test_table.displayDiagnostic();
}
