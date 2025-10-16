# Basics of C++

To get started with programming in C++  

## Creating C++ Programs

To write the first program in any text editor consider completing following steps:

1. Install C++ compiler
   - `gcc/g++` for Linux
   - `MinGW` for Windows
   - `Clang` for Mac
2. Create `.cpp` file with `int main() { return 0; }` function
3. Compile with chosen compiler (_probably via CLI_)
4. Run the executable

To make life easier steps `3` and `4` can be automated by an IDE of your choice (_see related features and tutorials_).

## Writing C++ Code

### Including a library:

Similar to many other languages including a library into code is usually placed at the top of a file like:

```c++
#include <abc>      // System library (also static library)
#include "abc.h"    // Path to the library file (used for dynamic libraries)

#include <std>      // A standard library with most basic functions
#include <iostream> // Library to get CLI inputs

// pi po bakudan

// To use a function of the library
// you have to write library's name with double colon first
std::cout << "Done with pi po bakudan" << std::endl;
```

Sometimes you can simplify referring that library using namespaces like following:

```c++
using namespace std;

// pi po bakudan

cout << "pi po bakudan'ed again" << endl;
```

_Note: Be aware of namespaces since some libraries may define functions with the same name._

### CLI Input and Output

To give user an output line the `std` library may be used as follows:

```c++
#include <std>

// int main() and so on...

std::cout << "Done with pi po bakudan" << std::endl;
```

To retrieve an input from user there're several options:

```c++
#include <std>

// int main() and so on...

// Waiting for any input (only the first letter is returned)
std::cin.get();

// or wait just for [Enter] key (no return value)

std::cin.ignore();

// or get a whole line
string line;
std::getline(std::cin, line);
```

If you execute your programs via CLI, it may be useful to pause the window after script executed. The way you do this depends on your OS:

```c++
// Method for Linux
std::cin.ignore();

// Alternative for Windows (requires cstdlib.h)
system("pause");
```

### Data Types and Bounds

In C++ there're all well-known data types (_+ a bit more_):

| Type | Bounds | Usage |
|:----:|:-----:|:-----:|
| `bool` | { false; true } or { 0; any number } | Representing a logical statement |
| `short` | [ -32768; 32767 ] | Storing small `int`s |
| `int` | [ -2147483648; 2147483647 ] | Storing medium-sized `int`s |
| `long` | [ -2147483648; 2147483647 ] | Storing huge `int`s |
| `float` | [ 1.17549e-38; 3.40282e+38 ] | Storing normal decimals |
| `double` | [ 2.22507e-308; 1.79769e+308 ] | Storing precise decimals |
| `long double` | [ 3.3621e-4932; 1.18973e+4932 ] | Storing exact decimals |
| `signed char` | [ -128; 127 ] | Storing very small `int`s |
| `unsigned char` | [ 0; 255 ] | Storing very small `int`s, single letter or character (_UTF-8_) |
| `char` | [ -128; 127 ] or [ 0; 255 ] | Depending on compiler either as `signed char` or as `unsigned char` |
| `wchar_t` | [ 0; 65535 ] or [ 0; 4.294.967.295 ] | Storing `int`s, single letter or character (_UTF-16 or UTF-32_) |

Unsigned `int`s and `long`s have their ranges shifter to the positive side, e.g. `unsigned int`'s range is [ 0; 4294967295 ].

To check limits of a certain data type check these functions of `limits` static library:

- `limits::digits()` - Amount of bits a data type reserves
- `limits::max()` - upper bounds of a data type
- `limits::min()` - lower bounds of a data type
- `limits::is_signed()` - whether a datatype may store negative values or not