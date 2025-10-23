# Arrays and Containers

Here are some basic notes about usage of arrays, containers and structs in C++.

## C-native Structures

These structures are quite low-level options of common ones used in other languages.
Use them, if you're sure what you're doing. Otherwise go to [C-Structures](#c-structures).

### C-Arrays

Just like an array in any other compiled language - static, not resizable.

```c
int test = 1;

// "Reserving" 10 values (all set to 0)
int numbers1[10];
// Assigning values directly
int numbers2[2] = { 23 };
// Assigning values alternatively by a variable
int numbers3[3] = { test };

// The size of an array is set automatically
int numbers4[] = { 1, 2, 3 };

// There're ofc multi-dimensional arrays as well
int table[10][10] = { 2 };
```

However there's a tricky (_actually dangerous_) feature hiding behind the lines. 
Most (OOP) languages (_including C++_) strongly restrict accessing arrays elements by its bounds (_0 to arrays' length - 1_). If you try to overcome these bounds, you get some kind of `IndexOutOfBoundsException`. C is kind of not designed to check these by default:

```c
// Creating an array of length 3
int numbers[3] = { 1 };
// so the last element is stored at index 2
numbers[2] = 2;

// however...

// This is a valid operation :3
int numbers[3] = 3;
for (int i = 0; i < 4; i++) {
    // The values should differ by 1
    cout << "cArray[" << i << "]: " << numbers1[i] << endl;
    // and their addresses by 4 (standard int's size)
    cout << "cArray Address[" << i << "]: " << &numbers1[i] << endl;
}
```

In the above code a value has been written to a memory space not associated with the `numbers` array at all.
Such failures can lead to so called _segmentation faults_ (_accessing memory not reserved by a whole program_) and unexpected behavior, which is the most difficult to debug.

### C-Strings

Strings in C are represented as `char` arrays with trailing `\0` element.

```c
// Normal char array
char myString[6] = { 'b','a','k','u','d','a','n' };
// CString
char myCString[7] = { 'b','a','k','u','d','a','n','\0' };
```

The `<cstring>` header file provides lots of functions to work with these.
There're also many of extensions of _cstrings_ made by different companies and frameworks.

### Unions

Unions are specific C structs that combine multiple values into a single type.

```c
union newUnion {
    // Only one field can be assigned automatically
    unsigned int __int16 ui16 = 0;
    unsigned int __int32 ui32;
}
```

There're some key features unions have:
- All fields are stored in **the same** memory segment
- The size of the segment is set to fit the biggest field of a union

Since by writing into a smaller field the bigger one will be changed as well, unions are most likely to be avoided nowadays.

## C++ Structures

These are practically extending the usage and increase safety of previous [C-native structures](#c-native-structures) by providing decent amount of additional manipulation methods.

### STL Arrays

Just like [C-Array](#c-arrays) but with `IndexOutOfBoundsException`:

```c++
#include <array>

// Creating a C++ array
std::array<int, 10> stlArray;
// Iterating through it (specific size_t type)
for (size_t i = 0; i < stlArray.size(); i++) {
    stlArray[i] = i;
    // Alternatively (also safer)
    stlArray.at(i) = i;
}

// Alternatively getting the size of an array
const size_t maxsize = stlArray.max_size();
```

### Custom Data Types

In C++ there's a feature that allows you to rename certain data types or define a new one:

```c++
// Renaming an existing data type
typedef unsigned int uint;
// Creating a "new" one
typedef int[100] int_array;

// Purely renaming a data type (will give cursed errors, not preferred)
#define MY_UINT unsigned int
```

### Structs

Just like [unions](#unions) in C but w/o _memory sparing complex_ xD

```c++
// Defining a struct as high as possible
// to let compiler know as early as possible
struct shoe {
    unsigned short usSize = 0;
    string brand = "notSpecified";
    eZipper zipper = notSet;
    string colorName = "notSpecified";
}

shoe shoe1;
shoe shoe2;

// Comparing bare structs is performed bitwise
cout << shoe1 < shoe2 << endl;

// Overwriting comparison operator (also overloading)
bool operator < (const shoe &a, const shoe &b) {
    return a.UsSize < b.UsSize;
}
```

Structs are typically used to combine values into a single variable without defining any methods to modify them (_otherwise it would be a class_).

### Enums

Enums are practically a stricter form of structs (_also available in C_):

```c++
// Enums cannot be changed after declaration
enum eZipper {
    // They also can contain only data types
    Simple = 3,
    Modern = 1,
    Western = 0
}
```

Enums are the perfect choice for cases, when a static option has to be used.

### STL Vectors

Vectors provide a decent flexibility of managing and iterating over a series of values.
Other languages name vectors something like _Collections_ or _Lists_.
There're lots of methods a vector has to offer:

```c++
#include <vector>

// Defining a simple vector
std::vector<double> drunk;

// Adding a new element to the end
drunk.push_back(1.0);
// Adding a new element at certain index
drunk.insert(drunk.begin() + 1, 2.0);

// Removing an element at the end
drunk.pop_back();
// Remove an element at index 1
drunk.erase(drunk.begin() + 1);
// Remove all elements
drunk.clear();

// Access elements
drunk[0];
drunk.front();
drunk.back();

// Access element at the beginning of a vector
drunk.begin();
// Access element behind the end of a vector
drunk.end();

// Getting the vector's size (for iterations)
drunk.size();

// Reserving memory for another 1000 elements
drunk.reserve(1000);
// Shrinking the vector (possible data loss after 500th element)
drunk.resize(500);
// Shrinking the vector (no data loss)
drunk.shrink_to_fit();

// Iterating through a vector (just like an array)
for (size_t i = 0; i < drunk.size(); i++) {}

// or with an iterator
vector<float>::iterator i;
for (i = drunk.begin(); i != drunk.end(); i++) {}

// Alternative iterator
for (auto &a : drunk) {}

// Additionally swapping the whole vector
std::vector<double> eaten;
drunk.swap(eaten);
```

Keep in mind, that an iterator represents an address of a vector's element (_a pointer_).