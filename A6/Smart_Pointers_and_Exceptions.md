# Smart Pointers and Exceptions

Here are some basic notes about using function, smart pointers, plain and `std` exceptions.

## Function Pointers

As the name says these point to a certain function which is similar e.g. to `Delegate` type in C#.
Just as in other languages you have to precisely describe function's signature (input/output types) for such pointers in order to use them:

```c++
// Generic function pointer's declaration
// <output_type> (*<ptr_name>)(<input_types>)

// Defining a pointer to a function:
// 1. returning int ptr and taking a string
int* (*strToIntFunc)(string);

// 2.returning void and taking a pointer to a float
void (*floatToVoidFunc)(float*);

// 3. returning a void pointer and taking a pointer to an array of int pointers
void* (*notEnoughPtrsFunc)(int* (*)[]));
```

Therefore function pointers are more useful with functions of the same signature e.g. those needed for a simple calculator.
Furthermore *class' methods have to be static* in order to use a pointer to such as withing as well as outside a class.

After a function pointer variable is initialized it can be called as a normal function:

```c++
// Declaring some functions
int add(int a, int b) { return a + b; }
int sub(int a, int b) { return a - b; }

// Initializing a function pointer
int (*calculate)(int, int);
// and a result variable
int result;

// Setting one function to calculate the result
calculate = add;
result = calculate(2, 2);       // result = 4 (maybe 5)

// Than swapping it with another
calculate = sub;
result = calculate(1, 1);       // result = 0 (for sure)
```
