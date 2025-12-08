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
float Divide(float, float);

// A6.2 Functions
void TestSmartPointers(SimpleCLI* const);
bool CheckPointer(const shared_ptr<int>&, SimpleCLI* const, int = 0);
bool CheckPointer(const unique_ptr<int>&, SimpleCLI* const, int = 0);
bool CheckPointer(const weak_ptr<int>&, SimpleCLI* const, int = 0);

int main()
{
    // Creating a CLI tool for custom I/O
    SimpleCLI* const cli = new SimpleCLI();

    // A6.1
    // cout << "[*] A6.1\n |" << endl;
    // TestFunctionPointer(cli);
    // cout << " |" << endl;
    
    // A6.1
    cout << "[*] A6.2\n |" << endl;
    TestSmartPointers(cli);
    cout << " |" << endl;

    delete cli;
    return 0;
}

#pragma region [A6.1]

/**
 * @brief Demonstrates usage of a function pointer.
 * @param cli: A CLI-Tool to retrieve user inputs.
 */
void TestFunctionPointer(SimpleCLI* const cli)
{
    vector<string> options = {
        "Add",
        "Substract",
        "Multiply",
        "Divide"
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
            operationFunc = Divide;
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
 * @brief Divides one decimal number by another.
 * @note If the second number is zero,
 * an `inf` value is returned instead.
 * @param a: The number to divide.
 * @param b: The number to divide by (first quotient).
 * @retval The second quotient of given first number.
 */
float Divide(float a, float b)
{
    return b != 0
        ? a / b
        : numeric_limits<float>::infinity();
}

#pragma endregion [A6.1]
#pragma region [A6.2]

void TestSmartPointers(SimpleCLI* const cli)
{
    cli->LogMessage("Checking shared pointers:", false, true);
    // Initializing a test value
    int *heapInt = new int(1);

    // Creating the first shared_ptr
    shared_ptr<int> sp1 = make_shared<int>();
    sp1.reset(heapInt);

    // Creating the second shared_ptr bound to the same test value
    shared_ptr<int> sp2(sp1);

    // Creating another separate shared_ptr with the same value
    //*Note: This implies creating a complete separate variable/object 
    shared_ptr<int> sp3 = make_shared<int>(*heapInt);

    // Modifying the test value
    //*Note: This should be visible by dereferencing two first shared pointers 
    *heapInt = 2;
    
    // Logging all three shared pointers
    cli->LogMessage("\b1st> Shared Pointer:", false);
    bool spResult = CheckPointer(sp1, cli);
    cli->LogMessage("\b2nd> Shared Pointer:", false);
    spResult = CheckPointer(sp2, cli);
    cli->LogMessage("\b3rd> Shared Pointer:", false);
    spResult = CheckPointer(sp3, cli);

    cli->LogMessage("Checking unique pointers:", false, true);
    // Creating two unique pointers and assigning values to them
    unique_ptr<int> up1 = unique_ptr<int>(new int(0));
    unique_ptr<int> up2;
    up1.swap(up2);

    // Logging both unique pointers
    cli->LogMessage("\b1st> Unique Pointer:", false);
    bool upResult = CheckPointer(up1, cli);
    cli->LogMessage("\b2nd> Unique Pointer:", false);
    upResult = CheckPointer(up2, cli);
    
    cli->LogMessage("Checking weak pointers:", false, true);
    // Creating the first weak_ptr to the first shared_ptr (value = 2)
    weak_ptr<int> wp1 = weak_ptr<int>(sp1);
    
    // Creating the second weak_ptr to the third shared_ptr (value = 1)
    weak_ptr<int> wp2 = weak_ptr<int>(sp3);
    
    // Logging both weak pointers
    cli->LogMessage("\b1st> Weak Pointer:", false);
    bool wpResult = CheckPointer(wp1, cli, 1);
    cli->LogMessage("\b2nd> Weak Pointer:", false);
    wpResult = CheckPointer(wp2, cli, 1);
}

bool CheckPointer(const shared_ptr<int> &p,
                  SimpleCLI* const cli,
                  int count_help /*= 0*/)
{
    if (p == nullptr)
    {
        cli->LogError("Invalid shared pointer!");
        return false;
    }

    cli->LogMessage("Shared pointer value: " + to_string(*p), false);
    cli->LogMessage("Shared pointer references: " +
                    to_string(p.use_count()));

    return true;
}

bool CheckPointer(const unique_ptr<int> &p,
                  SimpleCLI* const cli,
                  int count_help /*= 0*/)
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

bool CheckPointer(const weak_ptr<int> &p,
                  SimpleCLI* const cli,
                  int count_help /*= 0*/)
{
    if (p.expired())
    {
        cli->LogError("Invalid weak pointer!");
        return false;
    }

    cli->LogMessage("Weak pointer value: " + to_string(*(p.lock())), false);
    cli->LogMessage("Shared pointer references: " + to_string(p.use_count())
                    + " (+" + to_string(count_help)
                    + " weak pointer references)");

    return true;
}

#pragma endregion [A6.2]