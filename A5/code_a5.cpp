#include <iostream>

using namespace std;

// A5.1 Functions
void TestSwapping();
void SwapInts(int &, int &);
void SwapInts(int*, int*);

int main()
{
    // A5.1
    cout << "[*] A5.1\n |" << endl;
    TestSwapping();
    cout << " |" << endl;

    return 0;
}

#pragma region [A5.1]

void TestSwapping()
{
    int a = 0;
    int b = 1;

    cout << " |-> Initial value of a: " << a << endl;
    cout << " |-> Initial value of b: " << b << endl;

    SwapInts(a, b);

    cout << " |-< Swapped value of a: " << a << endl;
    cout << " |-< Swapped value of b: " << b << endl;
    cout << " |" << endl;

    cout << " |-> Initial value of a: " << a << endl;
    cout << " |-> Initial value of b: " << b << endl;

    SwapInts(&a, &b);

    cout << " |-< Swapped value of a: " << a << endl;
    cout << " |-< Swapped value of b: " << b << endl;
}

void SwapInts(int &a, int &b)
{
    int c = a;
    a = b;
    b = c;
}

void SwapInts(int *a, int *b)
{
    int c = *a;
    *a = *b;
    *b = c;
}

#pragma endregion [A5.1]