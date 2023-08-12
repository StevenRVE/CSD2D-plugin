### New vs Malloc
- malloc(): It is a C library function that can also be used in C++, while the “new” operator is specific for C++ only. 
- Both malloc() and new are used to allocate the memory dynamically in heap. But “new” does call the constructor of a class whereas “malloc()” does not.

### Delete vs Free
- free() is a C library function that can also be used in C++, while “delete” is a C++ keyword.
- free() frees memory but doesn’t call Destructor of a class whereas “delete” frees the memory and also calls the Destructor of the class.

### Dry/Wet for Delay plugin
y(n) = dry * x(n) + wet * [x(n-D) + fb*y(n-D)] from Will C. Pirkle's Designing Audio Effect Plugins in C++ pg. 214

### Interpolation recommendation Jan Janssen
``` 
result = (currentValue * alpha) + ( previousValue * (1-alpha)) 
```
Where alpha is a value between 0 and 1. The closer to 1, the more weight the current value has. The closer to 0, the more weight the previous value has.

TODO:
- improve interpolation
- improve drive algorithm
- improve GUI
- add on/off button
- add bypass button
- add presets/programs
