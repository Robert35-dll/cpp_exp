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

## Smart Pointers

The following theory has been compiled from many pages about smart pointers on [cppreference.com](https://en.cppreference.com/book/intro/smart_pointers)
Check those for extensive knowledge and a deeper dive into the topic.

Smart pointers are basically wrappers for raw pointers.
These have two significant advantages:
1. A smart pointer is destroyed automatically upon leaving the scope where it has been defined.
2. The value a smart pointer refers to is destroyed when its owners count (amount of smart pointers to that object owning it) reaches 0.

However it's still possible to manually delete the pointed value and therefore make all its smart pointers invalid at once :3

The underlying structure of smart pointers is rather simple and consists of:
1. A pointer to the actual value.
2. A pointer to control block:
    2.1. Either a pointer or the value itself
    2.2. Deleter (*to remove pointers or delete the value*)
    2.3. Allocator (*to add pointers*)
    2.4. Owners count (*amount of assigned shared pointers*)
    2.5. Reference count (*amount of assigned weak pointers*)

The very first smart pointer was `auto_ptr`.
It served similar purpose as `unique_ptr` does now and was replaced by the last with release of C++11.
With the new C++11 standard there are three kinds of smart pointers currently used: [`unique_ptr`](#uniqueptr), [`shared_ptr`](#sharedptr), [`weak_ptr`](#weakptr).

### `unique_ptr`

A unique pointer is kind of smart pointers that allows at most 1 ownership per value.

```c++
#include <memory>
using namespace std;

// Initializing a unique pointer
unique_ptr<int> u1(new int(42));
unique_ptr<int> u2;

// Extracting the stored pointer
int *iPtr = u1.release();   // u1 = nullptr

// Replacing the stored pointer
u2.reset(iPtr);             // only works with raw pointers :(

// Swapping pointed values
u1.swap(u2);                // also works with raw pointers :)
```

**Keep in mind** that `reset()` deletes held value first and then assigns the new one.

### `shared_ptr`

A shared pointer is kind of smart pointers that doesn't restrict amount of ownerships per value.
This may be the trickiest among smart pointers.

```c++
#include <memory>
using namespace std;

// Defining couple of shared pointers:
// 1. Shortly
shared_ptr<int> s1;         // s1 = nullptr
shared_ptr<int> s2(s1);     // s2 = s1 = nullptr

// 2. In a long way (see note after this code block)
shared_ptr<int> s3 = shared_ptr<int>(new int(0));
shared_ptr<int> s4 = make_shared<int>(new int(0));

// Resetting the stored pointer
s1.reset(new int(42));      // only works with raw pointers :(

// Swapping pointed values
s2.swap(s4);                // also works with raw pointers :)

// Getting amount of ownerships of pointed value
int ownersCount = s1.use_count();
```

#### `make_shared()` vs `shared_ptr()`

As mentioned at the very beginning the control block of a smart pointer can hold either a pointer to the value or the value itself.
The key difference is amount of necessary memory allocations performed while creating a shared pointer.
It's easier/faster to allocate whole memory once and to put everything into control block than do each step separately.
The choice between both is performed by using one of both creation methods of shared pointers:

```c++
#include <memory>
using namespace std;

// Option 1: Using constructor -> allocating memory in two steps
shared_ptr<int> sp1(new int(0));

// is equivalent to:
shared_ptr<int> sp1 = shared_ptr<int>(new int(0));

// is equivalent to:
int* iPtr = new int(0);     // -> allocating an int
shared_ptr<int> sp1(iPtr);  // -> allocating a shared pointer

// Option 2: Using make_shared -> allocating memory at once
shared_ptr<int> sp2 = make_shared<int>(new int(0));
```

#### Dumb way to crash

Even though the control block of shared pointers counts ownerships automatically, it's limited to pointers it knows.
Therefore there is a dumb way to crash a program using shared pointers:

```c++
#include <memory>
using namespace std;

// 1. Initializing the value to reference
int* iPtr = new int(42);

// 2. Creating a shared pointer to the target value
shared_ptr<int> s1(iPtr);

// 3, Creating another shared pointer to the same target
//    w/o referencing the first shared pointer
shared_ptr<int> s2(iPtr);

// 4, Exiting the scope of one shared pointer

// 5. Exiting the scope of another shared pointer
// -> ERROR: double free()
```

To avoid this try to initialize values within pointers' constructors or stick to creating pointers from already existing.

#### The trickiest part

It is possible to specify the pointed value (*the one stored in the variable's part*) while keeping ownership of another one (*stored in the control block*).
Due to lack of experience I'm not going to touch such use cases or make any assumptions at this point.
If you wish to go into the rabbit hole of shared pointers, check (8) of [this cppreference](https://en.cppreference.com/w/cpp/memory/shared_ptr/shared_ptr.html) or code example of [this cppreference](https://en.cppreference.com/w/cpp/memory/shared_ptr/get.html).

### `weak_ptr`

A weak pointer is a kind of smart pointers that doesn't own any value at all but only references one.

```c++
#include <memory>
using namespace std;

// Initializing a shared pointer
shared_ptr<int> s1(new int(42));    // s1.use_count() = 1

// Initializing couple of weak pointers
weak_ptr<int> w1(s1);               // s1.use_count() = 1
weak_ptr<int> w2;

// Releasing the stored reference
w2.reset();

// Swapping referenced values
w1.swap(w2);                        // only works with weak pointers :(

// Getting owners count of referenced value
int ownersCount = w2.use_count();   // = s1.use_count() = 1

// Checking, if the referenced object has been deleted
bool isValid = w2.expired();        // = false

// Creating a shared pointer from the weak
shared_ptr<int> temp = w2.lock();   // s1.use_count() = 2
// and accessing the referenced value
int val = *temp;
```

Weak pointers are useful for accessing values w/o forcing the program to keep them the whole time.
This also prevents circular references that may occur by using shared pointers.

## Exceptions

Exceptions work quite the same way as in any other language.
Once an exception occurs or is trown intentionally it's being passed to the underlying layer of stack memory until it reaches one of the following:
1. A defined try-catch block that is specified to handle the occured exception.
2. The `main()` w/o catch block where it'll lead to crash of the program.

### Plain Exceptions

In C++ value of any type can be thrown as an exception and be direcly used in the catch part of a try-catch block:

```c++
#include <iostream>
#include <string>
using namespace std;

try {
    throw "smth went wrong \\@o@/";
}
catch (string errMsg) {
    cout << "Oh no:" << errMsg << endl;
}
```

### `STL` Exceptions

There're many predefined exception types provided by `STL` listed on [this cppreference](https://en.cppreference.com/w/cpp/error.html#Exception_categories).
These work in the exact same way as plain exceptions with an additional inheritance from `exception` base class:

```c++
#include <iostream>
#include <string>
using namespace std;

try {
    throw runtime_exception("smth ran wrong x.x");
}
catch (const runtime_exception& runEx) {
    // All exceptions have a what() explanation method
    cout << "Oh no:" << runEx.what() << endl;
}
```

#### Custom exceptions

A custom exception class may be necessary, if this is actively used in the code.
However the only difference to predefined ones is going to be the overriden `what()` method, if no other extentions are planned:

```c++
#include <exception>
#include <string>
using namespace std;

class CustomException : public exception {
private:
    string errMsg;

public:
    CustomException(string errMsg_ = "Custom exception w/o info.")
        : errMsg(errMsg_)
    {};

    const char* what() {
        return errMsg.c_str();
    }
}
```

In most of the cases a plain string exception does the same job just as good ¯\_(ツ)_/¯
