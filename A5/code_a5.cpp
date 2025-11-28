#include <iostream>

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

int main()
{
    // A5.1
    cout << "[*] A5.1\n |" << endl;
    TestSwapping();
    cout << " |" << endl;

    // A5.2
    cout << "[*] A5.1\n |" << endl;
    TestArrayOutputs();
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