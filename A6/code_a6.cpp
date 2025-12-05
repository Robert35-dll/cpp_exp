#include <iostream>
#include <vector>
#include <limits>
#include <memory>
#include "../A4/A4.3/SimpleCLI.h"

using namespace std;

// A6.1 Functions

void TestFunctionPointer(SimpleCLI* const);
float Add(float, float);
float Substract(float, float);
float Multiply(float, float);
float Devide(float, float);

// A6.2 Functions
void TestSmartPointers(SimpleCLI* const);
bool CheckPointer(int, const shared_ptr<int>&, SimpleCLI* const);
bool CheckPointer(int, const unique_ptr<int>&, SimpleCLI* const);
bool CheckPointer(int, const weak_ptr<int>&, SimpleCLI* const);

int main()
{
    // Creating a CLI tool for custom I/O
    SimpleCLI* const cli = new SimpleCLI();

    // A6.1
    // cout << "[*] A6.1\n |" << endl;
    // TestFunctionPointer(cli);
    // cout << " |" << endl;
    
    // A6.1
    cout << "[*] A6.1\n |" << endl;
    TestSmartPointers(cli);
    cout << " |" << endl;

    delete cli;
    return 0;
}

#pragma region [A6.1]

/**
 * @brief Demonastrates usage of a function pointer.
 * @param cli: A CLI-Tool to retrieve user inputs.
 */
void TestFunctionPointer(SimpleCLI* const cli)
{
    vector<string> options = {
        "Add",
        "Substract",
        "Multiply",
        "Devide"
    };
    cli->SetOptions(options);

    int operationChoice = cli->GetOptionChoice();

    float(*operationFunc)(float, float);

    switch (operationChoice)
    {
        case 1:
        {
            operationFunc = Add;
            break;
        }
        case 2:
        {
            operationFunc = Substract;
            break;
        }
        case 3:
        {
            operationFunc = Multiply;
            break;
        }
        case 4:
        {
            operationFunc = Devide;
            break;
        }
        default:
        {
            cli->LogMessage("Exiting the program...", false, true);
            return;
        }
    }

    float a = cli->GetFloatInput("Please enter the first number", true);
    float b = cli->GetFloatInput("Please enter the second number", true);

    float result = operationFunc(a, b);

    cli->LogMessage("Result: " + to_string(result), false, true);
}

/**
 * @brief Adds to decimal numbers together.
 * @param a: The first number.
 * @param b: The second number.
 * @retval The sum of given numbers.
 */
float Add(float a, float b)
{
    return a + b;
}

/**
 * @brief Substracts one decimal number from another.
 * @param a: The number to substract from.
 * @param b: The number to substract by.
 * @retval The difference between given numbers.
 */
float Substract(float a, float b)
{
    return a - b;
}

/**
 * @brief Multiplies to decimal numbers together.
 * @param a: The first number.
 * @param b: The second number.
 * @retval The product of given numbers.
 */
float Multiply(float a, float b)
{
    return a * b;
}

/**
 * @brief Devides one decimal number by another.
 * @note If the second number is zero,
 * an `inf` value is returned instead.
 * @param a: The number to devide.
 * @param b: The number to devide by (first quotient).
 * @retval The second quotient of given first number.
 */
float Devide(float a, float b)
{
    return b != 0
        ? a / b
        : numeric_limits<float>::infinity();
}

#pragma endregion [A6.1]
#pragma region [A6.2]

void TestSmartPointers(SimpleCLI* const cli)
{
    cli->LogMessage("Checking single shared pointer:", false, true);
    int *heapInt = new int(1);
    shared_ptr<int> sp1 = shared_ptr<int>(heapInt);
    bool spResult = CheckPointer(0, sp1, cli);
    
    cli->LogMessage("Checking multiple shared pointers:", false, true);
    shared_ptr<int> sp2 = shared_ptr<int>(new int(1));
    shared_ptr<int> sp3 = sp2;
    spResult = CheckPointer(0, sp2, cli);

    cli->LogMessage("Checking unique pointer:", false, true);
    unique_ptr<int> up1 = unique_ptr<int>(new int(2));
    unique_ptr<int> up2;
    up1.swap(up2);
    bool upResult = CheckPointer(0, up2, cli);

    cli->LogMessage("Checking weak pointers:", false, true);
    weak_ptr<int> wp1 = weak_ptr<int>(sp2);
    bool wpResult = CheckPointer(0, wp1, cli);
    weak_ptr<int> wp2 = weak_ptr<int>(sp2);
    wpResult = CheckPointer(0, wp2, cli);
}

bool CheckPointer(int count_help, const shared_ptr<int> &p, SimpleCLI* const cli)
{
    if (p == nullptr)
    {
        cli->LogError("Invalid shared pointer!");
        return false;
    }

    cli->LogMessage("Shared pointer value: " + to_string(*p), false);
    cli->LogMessage("Shared pointer references: " + to_string(p.use_count()));

    return true;
}

bool CheckPointer(int count_help, const unique_ptr<int> &p, SimpleCLI* const cli)
{
    if (p == nullptr)
    {
        cli->LogError("Invalid unique pointer!");
        return false;
    }

    cli->LogMessage("Unique pointer value: " + to_string(*p), false);
    cli->LogMessage("Unique pointer references: 1 :D");

    return true;
}

bool CheckPointer(int count_help, const weak_ptr<int> &p, SimpleCLI* const cli)
{
    if (p.expired())
    {
        cli->LogError("Invalid weak pointer!");
        return false;
    }

    cli->LogMessage("Weak pointer value: " + to_string(*(p.lock())), false);
    cli->LogMessage("Weak pointer references: " + to_string(p.use_count()));

    return true;
}

#pragma endregion [A6.2]