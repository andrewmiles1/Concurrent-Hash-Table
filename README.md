# Concurrent Hash Table in C++
## Introdcution
This is a Hash Table library that is multi-thread safe. It still has a bit to go as far as optimization, but at it's current version 1.0, it is thread safe and tested. It uses a custom Linked List library for collision resolution, it hashes with the division method, and currently uses C++11 features for memory management (although I need to change that for better optimization.)

## Planned Features
- Choice between division and multiplication hash functions
- revert back to usage of `new` and `delete` for optimization purposes
- Automatic conversion from key type to int for hashing instead of requiring a function at constructor
