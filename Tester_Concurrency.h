#include <iostream>
#include <thread>
#include <random>
#include "HashTable.h"
#include <string>



// int parse_string_key(std::string str){
//     int sum = 0;
//     for(char letter : str){
//         sum += int(letter);
//     }
//     return sum;
// }

void TestConcurrency(){
    std::cout << "===========Concurrency testing===========\n";
    //CONCURRENCY TESTING:
    std::default_random_engine rand_num_eng(time(0));
    int items_in_table = 26;//keep at 26 to just have alphabet in table.
    int threads_count = 5;
    int tasks_per_thread = 100;
    //create hash table of 100 string,int items
    HashTable<std::string, int> test_table(parse_string_key);
    std::vector<std::thread> threads;

    std::cout << "Test table contains: \n";
    for(int i = 0; i < items_in_table; i++){
        test_table.update(std::to_string(char(i+65)), i);//65... the alphabet
        std::cout << (char(i+65)) << " ";
    }
    std::cout << "\n";
    test_table.displayDiagnostic();

    // //create a large list of tasks, preferrably 1000 or so
    // //create vector of lists:
    // std::vector<std::vector<std::string>> task_lists;
    // //fill tasks lists with tasks.
    // //tasks are strings with task data, in the form of:
    // // [task type]:[key]:[value]...
    // // task type being: update, addition (adding two key's values), and new.
    // //   UPDATE  updates keys in key range 65 to items_in_table
    // //   ADDITION  takes 2 numbers from specified keys and saves them to key. (type:key:key1:key2)
    // //   NEW  adds a new item into the hash table, with a key that's "a[rand letter]" 
    // for(int i = 0; i < threads_count; i++){//each task list for threads
    //     std::vector<std::string> tasks;
    //     for(int k = 0; k < tasks_per_thread; k++){//each task in list
    //         std::string new_task;
    //         //create random tasks for threads to do
    //         std::uniform_real_distribution<> task_type(1,4);
    //         std::uniform_real_distribution<> key_range(65, 65+items_in_table);
    //         std::uniform_real_distribution<> value_range(1, 100);
    //         switch(int(task_type(rand_num_eng))){
    //             case 1://UPDATE TASK
    //                 //update something in list (that already exists)
    //                 new_task = "update:";
    //                 new_task += (std::to_string(int(key_range(rand_num_eng))) + ":");
    //                 new_task += std::to_string(int(value_range(rand_num_eng)));
    //                 tasks.push_back(new_task);
    //                 std::cout << new_task << std::endl;
    //                 break;
                
    //             case 2://ADDITION TASK
    //                 //add two other keys and put result into specified key.
    //                 new_task = "addition:";
    //                 //key to save result to:
    //                 new_task += std::to_string(int(key_range(rand_num_eng))) + ":";
    //                 //key1 to add from:
    //                 new_task += std::to_string(int(key_range(rand_num_eng))) + ":";
    //                 //key 2 to add from:
    //                 new_task += std::to_string(int(key_range(rand_num_eng)));
    //                 //add to list:
    //                 tasks.push_back(new_task);
    //                 break;

    //             case 3://NEW TASK
    //                 //add new key to list
    //                 new_task = "new:";
    //                 //key to add:
    //                 new_task += ("a" + std::to_string(int(key_range(rand_num_eng))));
    //                 //value to add:
    //                 new_task += (":" + std::to_string(int(value_range(rand_num_eng))));
    //                 //add to list
    //                 tasks.push_back(new_task);
    //                 break;
    //         }
    //         task_lists.push_back(tasks);
    //     }
    // }

    std::uniform_real_distribution<> key_range(65, 65+items_in_table);
    std::uniform_real_distribution<> value_range(1, 100);

    auto complete_tasks = [](int task_count, std::uniform_int_distribution<> key_range,
     std::default_random_engine engine, std::uniform_int_distribution<> value_range, HashTable<std::string, int> hash_table){
            //do a bunch of tasks
            for(int i = 0; i < task_count; i++){
                std::string key;
                int new_data;
                key = char(int(key_range(engine)));
                new_data = int(value_range(engine));
                hash_table.update(key, new_data);
            }
    };

    //create a bunch of threads to fulfill tasks, I don't know how many.
    for(int i = 0; i < threads_count; i++){
        threads.push_back(std::thread(complete_tasks, std::ref(tasks_per_thread),
         std::ref(key_range), std::ref(rand_num_eng), std::ref(value_range), std::ref(test_table)));
    }
    for(auto it = threads.begin(); it != threads.end(); it++){
        it->join();//join each thread until they're done.
    }
}