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
void PrintPolynom(float *, int);
void PrintCoefficient(float, bool);

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
    cout << "[^]" << endl;

    return 0;
}

#pragma region [A5.1]

/**
 * @brief Demonstrates swapping values by pointers and references.
 */
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

/**
 * @brief Swaps two integers passed by references using a swap variable.
 * @param&a: The reference of the first integer.
 * @param &b: The reference of the second integer.
 */
void SwapInts(int &a, int &b)
{
    int c = a;
    a = b;
    b = c;
}

/**
 * @brief Swaps two integers passed by pointers using a swap variable.
 * @param &a: The pointer to the first integer.
 * @param &b: The pointer to the second integer.
 */
void SwapInts(int *a, int *b)
{
    int c = *a;
    *a = *b;
    *b = c;
}

#pragma endregion [A5.1]
#pragma region [A5.2]

/**
 * @brief Demonstrates methods to output values of an array.
 */
void TestArrayOutputs()
{
    int arrSize = 5;
    int arr[arrSize];
    FillArray(arr, arrSize, 0, 9);

    cout << "[<] Array output with two pointers:" << endl;
    PrintArray(arr, &(arr[arrSize - 1]));
    cout << " |" << endl;

    cout << "[<] Array output with one pointer and array size:" << endl;
    PrintArray(arr, arrSize);
}

/**
 * @brief Fills an array with random values in the given range.
 * @note The generation method was inspired by a guide from W3Schools:
 *       https://www.w3schools.com/cpp/cpp_howto_random_number.asp
 * @param *arrStart: The pointer to an array to fill.
 * @param arrSize: The size of an array. 
 * @param min: The minimum value of the range.
 * @param max: The maximum value of the range.
 */
void FillArray(int *arrStart, int arrSize, int min = 0, int max = 1)
{
    // Updating randomizer's seed
    srand(time(0));
    for (int i = 0; i < arrSize; i++)
    {
        // and filling random numbers (see @note above)
        *(arrStart + i) = rand() % (max - min + 1) + min;
    }
}

/**
 * @brief Outputs the values of an array.
 * @param *arrStart: The pointer to the first element of the array.
 * @param *arrEnd: The pointer to the last element of the array.
 */
void PrintArray(int *arrStart, int *arrEnd)
{
    //* Note: int    = 4 bytes
    //*       int*   = 8 bytes (typically on x64 OS)
    //*
    //*       int++  = +1
    //*       int*++ = +0x000004 (+4 bytes for int specifically)
    for (int *i = arrStart; i != arrEnd + 1; i++)
    {
        cout << "[" << i - arrStart  + 1 << "]-< " << *i;
        cout << " - (" << i << ")" << endl;
    }
}

/**
 * @brief Outputs the values of an array.
 * @param *arrStart: The pointer to the first element of the array.
 * @param arrLength: The amount of elements in the array.
 */
void PrintArray(int *arr, int arrLength)
{
    for (int i = 0; i < arrLength; i++)
    {
        cout << "[" << i + 1 << "]-< " << arr[i] << endl;
    }
}

#pragma endregion [A5.2]
#pragma region [A5.3]

/**
 * @brief Demonstrates a method to solve a quadratic equation.
 * @note Solutions can be either real or complex numbers.
 */
void SolveQuadraticEquation()
{
    float a = 3;
    float b = -2;
    float c = 1;

    float termsCoeffs[] = {a, b, c};
    PrintPolynom(termsCoeffs, 3);

    float x1 = 0.0;
    float x2 = 0.0;

    cout << "[<] Equation roots:" << endl;

    bool hasRealSolution = RootSquad(a, b, c, &x1, &x2);
    if (hasRealSolution)
    {
        cout << " |-< " << x1 << endl;
        cout << " |-< " << x2 << endl;
    }
    else
    {
        cout << " |-< " << x1 << " - " << x2 << "i" << endl;
        cout << " |-< " << x1 << " + " << x2 << "i" << endl;
    }
}

/**
 * @brief Calculates roots of a quadratic equation in form f(x) = 0.
 * @note For any term that isn't present in the equation
 *       a `0` should be passed for its coefficient.
 * @param a_IN: The coefficient for x^2 term. 
 * @param b_IN: The coefficient for x term.
 * @param c_IN: The free coefficient.
 * @param *d_OUT: The first (smaller) root of the equation,
 * if solution is real, or the `Re` term of the complex solution
 * in form `Re + Im * i`.
 * @param *e_OUT: The second (bigger) root of the equation,
 * if solution is real, or the `Im` term of the complex solution
 * in form `Re + Im * i`.
 * @retval True if roots are real numbers, false otherwise.
 */
bool RootSquad(float a_IN, float b_IN, float c_IN, float *d_OUT, float *e_OUT)
{
    float disc = b_IN * b_IN - 4 * a_IN * c_IN;
    float discrSqrt;

    // If distance between roots is negative ->
    // calculate imaginary coefficients
    if (disc < 0)
    {
        discrSqrt = sqrt(-disc);

        *d_OUT = -b_IN     / (2 * a_IN);
        *e_OUT = discrSqrt / (2 * a_IN);

        return false;
    }

    // Otherwise -> calculate real coefficients
    discrSqrt = sqrt(disc);

    *d_OUT = (-b_IN - discrSqrt) / (2 * a_IN);
    *e_OUT = (-b_IN + discrSqrt) / (2 * a_IN);

    return true;
}

/**
 * @brief Outputs a polynomial function in form ax^n + bx^(n-1) + ... + cx + d.
 * @note For any term that isn't present in the equation
 *       a `0` should be passed for its coefficient.
 * @param *termsCoeffs: The coefficients to each term of the function.
 * @param termsCoeffsAmount: The amount of terms coefficients.
 */
void PrintPolynom(float *termsCoeffs, int termsCoeffsAmount)
{
    cout << "[>] Equation: ";

    // A flag to notice the start of output
    bool isFirstTerm = true;

    for (int i = 0; i < termsCoeffsAmount; i++)
    {
        // If coefficient is 0 -> don't print anything
        if (termsCoeffs[i] == 0)
        {
            continue;
        }

        // For any other coefficient:
        // Step 1 - Print coefficients with their signs separately
        PrintCoefficient(termsCoeffs[i], isFirstTerm);

        // Step 2 - If a coefficient isn't the last one -> print the x term
        if (i == termsCoeffsAmount - 1)
        {
            break;
        }

        cout << "x";

        // Step 3 - If a coefficient isn't the last or the second last ->
        // print the term's power
        if (i < termsCoeffsAmount - 2)
        {
            cout << "^" << termsCoeffsAmount - 1 - i;
        }

        cout << " ";
        isFirstTerm = false;
    }
    cout << " = 0" << endl;
}

/**
 * @brief Outputs a single coefficient of a polynomial.
 * @param coeff: The coefficient to output.
 * @param isFirst: Whether it's the very first coefficient or not.
 */
void PrintCoefficient(float coeff, bool isFirst)
{
    if (isFirst)
    {
        cout << coeff;
        return;
    }

    if (coeff > 0)
    {
        cout << "+ " << coeff;
    }
    else
    {
        cout << "- " << -coeff;
    }
}

#pragma endregion [A5.3]