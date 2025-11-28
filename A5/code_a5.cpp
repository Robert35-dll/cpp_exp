#include <iostream>

using namespace std;

// A5.1 Functions
void TestSwapping();
void SwapWithReference(int &, int &);
void SwapWithPointer(int*, int*);

int main()
{
    // A5.1
    cout << "[*] A5.1\n |" << endl;
    TestSwapping();

    return 0;
}

void TestSwapping()
{
    int a = 0;
    int b = 1;

    cout << " |-> Initial value of a: " << a << endl;
    cout << " |-> Initial value of b: " << b << endl;

    SwapWithReference(a, b);

    cout << " |-> Swapped value of a: " << a << endl;
    cout << " |-> Swapped value of b: " << b << endl;

    cout << " |-> Initial value of a: " << a << endl;
    cout << " |-> Initial value of b: " << b << endl;

    SwapWithPointer(&a, &b);

    cout << " |-> Swapped value of a: " << a << endl;
    cout << " |-> Swapped value of b: " << b << endl;
}

void SwapWithReference(int &a, int &b)
{
    int c = a;
    a = b;
    b = c;
}

void SwapWithPointer(int *a, int *b)
{
    int c = *a;
    *a = *b;
    *b = c;
}