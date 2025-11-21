# Classes and OOP

Here are some basic notes about creating and using classes in C++.
All code examples are primarily thought to use the stack memory pros and cons of which will also be covered at the end.

## File Structure of a Class

Functionally classes work in the same way as in any other language. However C++ allows to split class declaration and implementation into two files: the header `.h` and the source `.cpp` files respectively.

An `.h` header file represents the interface of a class and should not contain any unnecessary `#include`s since it might significantly affect build time and performance.

A `.cpp` source file represents the implementation of its header. If any library included in `.h` file is directly used in the `.cpp` file, it has to be included there as well.

## Creating a Class

To create a class in C++ you have to create two files of the following structure:

`C.h`
```c++
// Very important line to avoid multiple includes
#pragma once

#include <string>

class C
{
    private:
        int Count;
    
    public:
        C()
            : Count(0)
        {}
        C(int count_)
            : Count(count)
        {}

        void F(string line);
}
```

`C.cpp`
```c++
// Including the header located in the same directory
#include "C.h"
// or in another one with relative or absolute path
// #include "path_to_header_file"

#include <string>

void C::F(string line)
{
    // Method's implementation code
}
```

### Constructor Method

Every object (_instance of a non-static class_) is created by calling a class' constructor which can be implemented in several ways:

```c++
class C
{
    private:
        int Count;
        bool IsActive;
    
    public:
        // This variant
        C() { Count = 0; }
        // is equal to this one
        C()
            : Count(0)
        {}

        // but can also be combined with it 
        C(int count_)
            : Count(count_)
        {
            IsActive = true;
        }
}
```

Implementation of a constructor can be done directly in the `.h` file.

### Default Parameters

Sometimes it's useful to define a default value for a certain argument to spare some typing time.
If you want to do so, you have to define such values either in the declaration or in the implementation of your method as follows:

`C.h`
```c++
#pragma once
#include <string>

class C
{
    private:
        int Count;
        bool IsAlive;
    
    public:
        C()
            : Count(0)
        {}
        C(int count_)
            : Count(count)
        {}

        // Option 1: Default parameter in header
        void F(string line = "hello");
        
        // Option 2: Default parameter in source
        // This way you have to define an overload w/o arguments!
        void G()
        void G(int x /*= 0*/)
}
```

`C.cpp`
```c++
#include "C.h"

#include <string>

// Option 1: Default parameter in header
// You can note the default parameter like this
void C::F(string line /*= "hello"*/)
{
    // Method's implementation code
}

// Option 2: Default parameter in source
// You can simply call the other method with preset parameter
void C::G()
{
    C::G(0);
}

void C::G(int x = 0)
{
    // Method's implementation code
}
```

### `#pragma once` and Include Guards

Multiple `#include`s of the same class cause definition/implementation conflicts and are not welcome in C++.
In order to avoid such problem there're two options to put at the `#include` section:

In `C.h` you would typically use the `#pragma once` like:
```c++
#pragma once

class C {}
```

In code written for older compilers you'd like to use an _include guard_ like:
```c++
#ifndef _C_
#define _C_

class C {}

#endif
```

### Static Members

Sometimes you might want to have a field or method related to the class rather than to an instance.
If so you'd like to define a static member of a class like:

`C.h`
```c++
#pragma once
#include <string>

class C
{
    private:
        // Static variables have to be always initialized/implemented in source files
        static int ClassCount;          
        static void IncClassCount();

        int Count;
    
    public:
        C()
            : Count(0)
        { IncClassCount(); }
        C(int count_)
            : Count(count)
        { IncClassCount(); }

        void F(string line);
}

```

`C.cpp`
```c++
#include "C.h"

#include <string>

int C::ClassCount = 0;

void C::IncClassCount()
{
    // Here only static members are allowed!
    ClassCount++;
}
```

## Stack vs Heap

cSen Device1; // Definition in Stack
cSen Device1 = new cSen() // Definition in Heap

### Destructor Method

~cSen() // At deletion of an object, also in .h files possible