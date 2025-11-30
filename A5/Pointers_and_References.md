# Pointers and References

Here are some basic notes about using pointers and references in C++.

## Computer Memory in a Nutshell

Before talking about pointers it's crucial to understand, how a computer memorize things in general.
To efficiently store and operate data computers put it into certain memory cells (_typically 1 byte small_) with unique addresses.
Depending on the size of the data multiple cells can be reserved to store its values like this:

```c++
// The whole memory available
[
    // The first memory cell
    [int]   // address - 0d213a70
    // + several next cells to store the whole int

    // The second memory cell
    [float] // address - 0d213a74
    // + several next cells to store the whole float

    // and so on...
]
```

Before executing a program an operating system reserves some free memory (_basically a bunch of those memory cells_) to provide space for variables, functions, their results as well as for objects and data structures used withing that program.
Since all of those variables and objects have to be stored in memory (_either stack or heap_), all of them have to be assigned to a certain memory cell (_or multiple cells_) with a unique address. Therefore all initialized variables can be accessed by that address.
Such address is stored in a pointer variable.

## Pointers

Pointers are nothing more than variables that store memory addresses of other variables (_probably also pointers :3_) as follows:

```c++
// Initializing an int variable
int age = 14;

// Initializing an int pointer variable
int* pAge = &age;
// another way to create pointer named p
// int *p = &age;

cout << age << endl;        // Output: 14
cout << pAge << endl;       // Possible output: 0x5ffecc (address of age)

cout << *pAge << endl;      // Output: 14 (pointed value of pAge)
cout << &pAge << endl;      // Possible output: 0x5ffec0 (address of pAge)
```

Since pointers are variables they also have their own addresses :3
If some pointer is used but neither is initialized nor points to an allocated memory, there is a fatal error which crashes the program.
To prevent such errors you can do the following:

```c++
// 1. Use default 'nullptr' value for non-initialized pointers
int* pEmpty = nullptr;

// some logic

// 2. Validate pointers before using them
if (pEmpty == nullptr)
{
    // further logic
}
```

Another thing to consider is that the pointer refers to the right value.
If the pointed value had been overwritten or the pointer itself hadn't been initialized at least as `nullptr`, an _undefined behavior_ would acure which potentially would also lead to a crash.

Additionally you can lock pointers and their linked values by using `const` key word in multiple ways:

```c++
// Standard usage
int a = 14;
int* pA = &a;

// Locking linked value
const int* cpA = &a;
*cpA = 0;                       // Error: expression must be modifiable value
cpA = nullptr;

// Locking pointer
int* const pcA = &a;
*pcA = 0;
pcA = nullptr;                  // Error: expression must be modifiable value

// Locking both linked value and pointer
const int* const cpcA = &a;
*cpcA = 0;                      // Error: expression must be modifiable value
cpcA = nullptr;                 // Error: expression must be modifiable value
```

## References

A reference is practically a constant pointer that is automatically dereferenced upon every usage.
Therefore they are functionally equal to pointers but require less typing:

```c++
void AddToValue(int x)
{
    x++;                    // The value of x' copy is changed
}                           // not of original x!

void AddToPointer(int *x)
{
    *x++;                   // x is dereferenced manually and 
}                           // its value is changed directly

void AddToReference(int &x)
{
    x++;                    // x is dereferenced automatically and
}                           // its value is changed directly

int a = 0;

AddToValue(a);              // 0 -> 0 because change refers to the function's scope
AddToPointer(&a);           // 0 -> 1 because change refers to the actual value

// Calling by reference requires only the name of a variable (no addresses)
AddToReference(a);          // 1 -> 2 because change refers to the actual value again
```

Similar to pointers you can also prevent the referenced value from any modification like:

```c++
void AddToReference(const int &x)
{
    x++;                    // Error: expression must be modifiable value
}
```