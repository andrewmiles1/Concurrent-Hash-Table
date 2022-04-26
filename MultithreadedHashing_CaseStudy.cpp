#include <iostream>
#include "LinkedList.h"
#include "HashTable.h"
#include "Tester_LinkedList.h"
#include "Tester_HashTable.h"
#include "Tester_Stack.h"
#include <string>
#include "Stack.h"
#include <random>


int main()
{
    //TestHashTable();
    //TestLinkedList();
    //TestStack();

    std::cout << "===========Concurrency testing===========\n";
    //CONCURRENCY TESTING:
    std::default_random_engine rand_num_eng(time(0));
    int items_in_table = 26;//keep at 26 to just have alphabet in table.
    int threads_count = 5;
    int tasks_per_thread = 100;
    //create hash table of 100 string,int items
    HashTable<std::string, int> test_table(parse_string_key);

    std::cout << "Test table contains: \n";
    for(int i = 0; i < items_in_table; i++){
        test_table.update(std::to_string(char(i+65)), i);//65... the alphabet
        std::cout << (char(i+65)) << " ";
    }
    std::cout << "\n";
    test_table.displayDiagnostic();

    //create a large list of tasks, preferrably 1000 or so
    //create vector of lists:
    std::vector<vector<std::string>> task_lists;
    //fill tasks lists with tasks.
    //tasks are strings with task data, in the form of:
    // [task type]:[key]:[value]...
    // task type being: update, addition (adding two key's values), and new.
    //   UPDATE  updates keys in key range 65 to items_in_table
    //   ADDITION  takes 2 numbers from specified keys and saves them to key. (type:key:key1:key2)
    //   NEW  adds a new item into the hash table, with a key that's "a[rand letter]" 
    for(int i = 0; i < threads_count; i++){//each task list for threads
        vector<std::string> tasks;
        for(int k = 0; k < tasks_per_thread; k++){//each task in list
            std::string new_task;
            //create random tasks for threads to do
            std::uniform_real_distribution<> task_type(1,4);
            std::uniform_real_distribution<> key_range(65, 65+items_in_table);
            std::uniform_real_distribution<> value_range(1, 100);
            switch(int(task_type(rand_num_eng))){
                case 1://UPDATE TASK
                    //update something in list (that already exists)
                    new_task = "update:";
                    new_task += (std::to_string(int(key_range(rand_num_eng))) + ":");
                    new_task += std::to_string(int(value_range(rand_num_eng)));
                    tasks.push_back(new_task);
                    std::cout << new_task << std::endl;
                    break;
                
                case 2://ADDITION TASK
                    //add two other keys and put result into specified key.
                    new_task = "addition:";
                    //key to save result to:
                    new_task += std::to_string(int(key_range(rand_num_eng))) + ":";
                    //key1 to add from:
                    new_task += std::to_string(int(key_range(rand_num_eng))) + ":";
                    //key 2 to add from:
                    new_task += std::to_string(int(key_range(rand_num_eng)));
                    //add to list:
                    tasks.push_back(new_task);
                    break;

                case 3://NEW TASK
                    //add new key to list
                    new_task = "new:";
                    //key to add:
                    new_task += ("a" + std::to_string(int(key_range(rand_num_eng))));
                    //value to add:
                    new_task += (":" + std::to_string(int(value_range(rand_num_eng))));
                    //add to list
                    tasks.push_back(new_task);
                    break;
            }
            task_lists.push_back(tasks);
        }
    }

    //display all tasks created:
    for(auto list : task_lists){
        for(auto task : list){
            std::cout << task << " ";
        }
        std::cout << "\n";
    }

    auto complete_tasks = [](vector<std::string> tasks){

    };

    //create a bunch of threads to fulfill tasks, I don't know how many.


}