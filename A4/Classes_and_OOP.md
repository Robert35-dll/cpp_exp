# Classes and OOP

Here are some basic notes about creating and using classes in C++.
All code examples are primarily thought to use the stack memory pros and cons of which will also be covered at the end.

## File Structure of a Class

Functionally classes work in the same way as in any other language.
However C++ allows to split class declaration and implementation into two files: the header `.h` and the source `.cpp` files respectively.

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

## Inheritance

Just as in any other language inheritance is specified in class' definition.
However in C++ you can specify an access modifier to control members accessibility defined in the base class:

```c++
class Ancestor
{
// Access only withing ancestor
private:
    int age;

// Access only withing ancestor and any descendant
protected:
    int id;

// Access withing and outside of ancestor
// Access withing and outside of descendant depends on modifier
public:
    char name[10];
};

// Remaining original modifiers
class DescendantPublic : public Ancestor
{
    // age  -> no access
    // id   -> access withing this and further descendants only
    // name -> access withing and outside of this descendant
};

// Making all accessible members protected
class DescendantProtected : protected Ancestor
{
    // age  -> no access
    // id   -> access withing this and further descendants only
    // name -> access withing this and further descendants only
};

// Making all accessible members private
class DescendantPrivate : private Ancestor
{
    // age  -> no access
    // id   -> access withing this descendant only
    // name -> access withing this descendant only
};
```

To treat all these descendants in the same way (*e.g. to use them as parameters or store in the same container*) pointers should be used:

```c++
// For this example all classes have been split into separate files
#include "Ancestor.h"
#include "DescendantPublic.h"
#include "DescendantProtected.h"
#include "DescendantPrivate.h"

// Smart pointers are quite convenient to use here
#include <memory>
#include <vector>

using namespace std;

// Initializing pointers to single instance of each object
shared_ptr<DescendantPublic>    dPub = make_shared<DescendantPublic>();
shared_ptr<DescendantProtected> dPro = make_shared<DescendantProtected>();
shared_ptr<DescendantPrivate>   dPri = make_shared<DescendantPrivate>();

// Defining a vector to store all descendants
vector<shared_ptr<Ancestor>> population;
// and filling it with pointers to those
population.push_back(dPub);
population.push_back(dPro);
population.push_back(dPri);
```

**Keep in mind** that if any method is reimplemented by descendants and is called from such container, consider either:

- Casting the container element (*pointer*) to descendant class' one or
- Specifying virtual methods.

Without one of those options calling any method by dereferencing a pointer will lead to execution of its base method (*the one implemented by* `Ancestor`).

### Virtual Methods

In order to stress a polymorphic behaviour of descendants it's common to put `virtual` and `override` keywords to their methods:

- `virtual` stays for "*there may be a descendant that implements this method too. Check that implementation first.*"
- `override` stays for "*this method is inherited from the ancestor class and there's another implementation of it.*"

```c++
class Ancestor
{
public:
    // This method is meant to be reimplemented by descendants
    // If there're no other implementations, run this one instead
    virtual void think() { cout << "Ooga Booga!" << endl; }
};

class Descendant : public Ancestor
{
public:
    // This method comes from the ancestor but
    // may have another implementation
    void think() override { cout << "damn, thats huge W" << endl; }
};
```

It's worth noticing that a method can be either virtual or static (*or none of both* `:D`).

Another good hint is given by [this cppreference](https://en.cppreference.com/w/cpp/language/virtual.html):

> A useful guideline is that the destructor of any base class must be public and virtual or protected and non-virtual, whenever delete expressions are involved, e.g. when implicitly used in std::unique_ptr(since C++11).

While deriving from a class and referencing ancestors via pointers to that base class there's a risk to call the base' desctructor.
Since descendants may allocate extra memory for their members this will not be freed by destroying base automatically.
Therefore destructor of a base class should always either:
- be declared as virtual and overridden by descendants or
- be able to free all memory allocated by descendants

### Virtual Classes

A virtual method can also be forced to be overridden.
In this case a that method will be declared as 'pure virtual' and its class itself as 'virtual' or 'abstract'.
This is analog to static or abstract/static classes in C# and Java which cannot be instantiated by definition:

```c++
class Ancestor
{
public:
    // This method can be reimplemented by descendants
    // but doesn't have to
    virtual void think() { cout << "Ooga Booga!" << endl; }
    
    // This method has to be reimplemented by descendants
    virtual void eat()=0;
}
```

### Multiple Inheritance

In C++ descendants are allowed to have multiple ancestors at once:

```c++
class Dad
{
public:
    int age;
};

class Mom
{
public:
    char name[10];
};

class Child : public Dad, public Mom
{
    // age  -> access withing and outside of this descendant
    // name -> access withing and outside of this descendant
}
```

Sometimes ancestors may have their own ancestors as well.
These might be inherited by descendants too, if allowed by all ancestors in-between:

```c++
// First order ancestors
class Grandpa
{
private:
    float height;
};

class Grandma
{
protected:
    char eyeColor[5];
};

// Second order ancestors / descendants of the first ancestors
// Inheriting virtually to avoid double instances of any ancestor
// for further descendants
class Dad : public virtual Grandpa, public virtual Grandma
{
public:
    int age;
};

// Inheriting virtually to avoid double instances of any ancestor
// for further descendants
class Mom : public virtual Grandpa, public virtual Grandma
{
public:
    char name[10];
};

// Final descendant
// Inheriting normally since no further descendants are in sight
class Child : public Dad, public Mom
{
    // height   -> no access
    // eyeColor -> access withing this and further descendants only
    // age      -> access withing and outside of this descendant
    // name     -> access withing and outside of this descendant
}
```

While using multiple inheritance it's crucial to specify virtual inheritance from farther ancestors (*Grandpa and Grandpa in above example*).
Such virtual inheritance ensures members' unambiguity withing a single descendant's instance.
The whole inheritance tree would look like this:

```
Grandma <+> Grandpa    // single eyeColor property from common Grandma
      /     \
    Mom     Dad        // single age and name properties from Dad and Mom
      \     /
       Child           // ^^^ inherited properties ^^^
```

Without virtual inheritance a program would need to memorize base classes for each subclass separately:

```
Grandma Grandpa Grandma Grandpa    //! double eyeColor property from both Grandmas !
     \   /           \   /
      Mom             Dad          // single age and name properties from Dad and Mom
          \         /
             Child                 // ^^^ inherited properties ^^^
```

This means that `Child` has `Dad::eyeColor` and `Mom::eyeColor` members at the same time which invalidates `Child::eyeColor`.
This pattern is often referred as the "diamond problem" or the "Deadly Diamond of Death."

### Friend Members

As an alternative to access modifiers `friend` keyword can be used to allow certain functions and classes access any member of a certain class.
There're two limitations of such 'friendship':

- `friend` status cannot be inherited
- `friend` status allows forward access only

```c++
class Mate
{
    // Allowing StrangeFunction to access private members
    friend void* StrangeFunction(Mate &mate);
    // Allowing Stranger class to access private members
    // Note: Nate cannot access Stranger's private members
    friend class Stranger;

private:
    // These are accessible for Stranger
    int phoneNumber;
    float location[2];
};

// Some strange funciton with explicit access to all Mate's members
void* StrangeFunction(Mate &mate)
{
    mate.location[0] = rand();
    mate.location[1] = rand();

    return nullptr;
}

// Some Stranger class with explicit access to all Mate's members
class Stranger
{
private:
    // This is unaccessible for Mate
    char name[10];

public:
    void scam(Mate &mate)
    {
        cout << "Exploiting phone number '"
             << mate.phoneNumber
             << "' (｀∀´)Ψ"
        << endl;
    }
};
```

## Stack vs Heap

This topic is meant to be covered in further updates but since it directly touches instantiation of classes it is noticeable here as well.

There're two types of memory space you can use to store and operate your variables:

- Stack - for short-term or function execution's data (_generally limited but fast_)
- Heap - for long-term and program-shared data (_potentially unlimited but slow_)

Another significant difference between both types is the allocation process.
Stack memory is allocated automatically by the program while heap memory has to be operated manually (_e.g. allocating and freeing memory space_).

In order to define the type of memory space for a certain object you can write the following:

```c++
#include "C.h"

int main()
{
    // Creating an object in stack memory of main()
    C stackC = C();

    // Creating an object in heap memory
    C *heapC = new C();

    // At the end all defined object will be destroyed automatically 
    return 1;
}
```

### Destructor Method

Even though object will be destroyed automatically at the end of a program this doesn't include its internal objects allocated to heap.
Therefore you have to implement a custom destructor and free used memory manually like:

```c++
#pragma once

class C
{
    private:
        int Count;
        int* pCount;

    public:
        // Constructor
        C(int count_)
            : Count(count_)
        {
            pCount = new int;
            *pCount = Count;
        }
        // Destructor
        ~C()
        {
            delete pCount;
        }
}
```