cmake_minimum_required(VERSION 3.10)

# set the project name
project(ConcurrentHasshTableTests)

# add the executable
add_executable(MT-HashTableTests MultiThreadedHashTable_Tests.cpp)