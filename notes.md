### New vs Malloc
- malloc(): It is a C library function that can also be used in C++, while the “new” operator is specific for C++ only. 
- Both malloc() and new are used to allocate the memory dynamically in heap. But “new” does call the constructor of a class whereas “malloc()” does not.

### Delete vs Free
- free() is a C library function that can also be used in C++, while “delete” is a C++ keyword.
- free() frees memory but doesn’t call Destructor of a class whereas “delete” frees the memory and also calls the Destructor of the class.
- 