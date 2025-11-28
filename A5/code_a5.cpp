#include <iostream>
#include <cmath>

using namespace std;

// A5.1 Functions
void TestSwapping();
void SwapInts(int &, int &);
void SwapInts(int*, int*);

// A5.2 Functions
void TestArrayOutputs();
void FillArray(int*, int, int, int);
void PrintArray(int*, int*);
void PrintArray(int*, int);

// A5.3 Functions
void SolveQuadraticEquation();
bool RootSquad(float, float, float, float*, float*);

int main()
{
    // A5.1
    cout << "[*] A5.1\n |" << endl;
    TestSwapping();
    cout << " |" << endl;

    // A5.2
    cout << "[*] A5.2\n |" << endl;
    TestArrayOutputs();
    cout << " |" << endl;

    // A5.3
    cout << "[*] A5.3\n |" << endl;
    SolveQuadraticEquation();
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
#pragma region [A5.2]

void TestArrayOutputs()
{
    int arrSize = 5;
    int arr[arrSize];
    FillArray(arr, arrSize, 0, 10);
    
    cout << "[<] Array output with two pointers:" << endl;
    PrintArray(arr, &(arr[arrSize - 1]));
    cout << " |" << endl;
    cout << "[<] Array output with one pointer and array size:" << endl;
    PrintArray(arr, arrSize);
}

void FillArray(int *arrStart, int arrSize, int min = 0, int max = 1)
{
    srand(time(0));
    for (int i = 0; i < arrSize; i++)
    {
        *(arrStart + i) = rand() % (max - min + 1) + min;
    }
}

void PrintArray(int *arrStart, int *arrEnd)
{
    for (int *i = arrStart; i <= arrEnd; i++)
    {
        cout << "[" << i - arrStart  + 1 << "]-< " << *i << endl;
    }
}

void PrintArray(int *arr, int arrLength)
{
    for (int i = 0; i < arrLength; i++)
    {
        cout << "[" << i + 1 << "]-< " << arr[i] << endl;
    }
}

#pragma endregion [A5.2]
#pragma region [A5.3]

void SolveQuadraticEquation()
{
    float a = 1;
    float b = 1;
    float c = -1;

    cout << "[>] Equation: " << a << "x^2 + (" << b << ")x + (" << c << ")" << endl;

    float x1 = 0.0;
    float x2 = 0.0;

    RootSquad(a, b, c, &x1, &x2);

    cout << "[<] Equation roots: " << x1 << "; " << x2 << endl;
}

bool RootSquad(float a_IN, float b_IN, float c_IN, float *d_OUT, float *e_OUT)
{
    float disc = b_IN * b_IN - 4 * a_IN * c_IN;
    if (disc < 0)
    {
        return false;
    }

    float discrSqrt = sqrt(disc);

    *d_OUT = (-b_IN - discrSqrt) / (2 * a_IN);
    *e_OUT = (-b_IN + discrSqrt) / (2 * a_IN);

    return true;
}

#pragma endregion [A5.3]