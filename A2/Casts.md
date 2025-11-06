# Type Casting

Here are some useful hints about casting variables (_especially strings to numbers_).

## Number to Number

To convert one number type to another, you can use either a C-style or a C++-style casting.

### C-style Cast

The C-style cast syntax is commonly used in most other languages:

```c++
// Initializing an int variable
int a = 10;

// and converting it to a float for division
float b = (float)a / 3;
```

However this option is quite unwelcome (_almost completely avoided_) across C++ community because of its implicit distinguishing between different casting processes and compile time type-restriction. See [this topic on Stack Overflow](https://stackoverflow.com/a/26269263) for more details.

### C++-style Cast

In C++ there're a quite more methods to convert a variable to another type (_including super and inherited classes_):

| Cast Function | Syntax | Use Case |
|:-------------:|:-------|:---------|
| Static Cast | `static_cast<type>(variable)` | Number casting, inheritance upcasting |
| Dynamic Cast | `dynamic_cast<type*>(variable*)` | Inheritance downcasting (_might return null pointer!_) |
| Const Cast | `const_cast<type*>(&variable)` | Addition/Removal of `const` or `volatile` qualifiers |
| Reinterpret Cast | `reinterpret_cast<type*>(&variable)` | Converting to unrelated (_pointer_) types, e.g. int -> void |
