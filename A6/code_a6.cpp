#include <iostream>
#include <vector>
#include <limits>
#include "../A4/A4.3/SimpleCLI.h"

using namespace std;

// A6.1 Functions

void TestFunctionPointer(SimpleCLI* const cli);
float Add(float, float);
float Substract(float, float);
float Multiply(float, float);
float Devide(float, float);

int main()
{
    SimpleCLI* const cli = new SimpleCLI();

    // A6.1
    cout << "[*] A6.1\n |" << endl;
    TestFunctionPointer(cli);
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

float Add(float a, float b)
{
    return a + b;
}

float Substract(float a, float b)
{
    return a - b;
}

float Multiply(float a, float b)
{
    return a * b;
}

float Devide(float a, float b)
{
    return b != 0
        ? a / b
        : numeric_limits<float>::infinity();
}

#pragma endregion [A6.1]