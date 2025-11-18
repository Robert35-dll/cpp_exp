#include "SimpleCLI.h"

#include <iostream>
#include <string>
#include <vector>

using namespace std;

/**
 * @brief Checks, whether the given choice is in valid range
 *        of menu options' vector.
 * @param choice: The chosen option.
 * @retval True, if choice lies withing menu's range, false otherwise.
 */
bool SimpleCLI::IsValidChoice(int choice)
{
    return -1 < choice && choice < (int)MenuOptions.size();
}

/**
 * @brief Asks for input of a certain menu option.
 * @note This displays all available options and keeps asking
 *       until a valid one is provided.
 * @retval The chosen option as `int`.
 */
int SimpleCLI::GetOptionChoice()
{
    int choice = 0;
    while (true)
    {
        LogWarning("Choose an option", true, true);

        for (size_t i = 0; i < MenuOptions.size(); i++)
        {
            cout << "[" << i + 1 << "] - " << MenuOptions[i] << endl;
        }
        cout << "[-1] - Exit the program" << endl;
        cout << LineIndicator << endl;
    
        choice = GetIntInput("Enter a respective number", true);

        if (choice == -1 || IsValidChoice(choice - 1))
        {
            break;
        }

        LogError("Please enter a valid option from the list >:(", true);
    }
    cout << LineIndicator << endl;

    return choice;
}

/**
 * @brief Retrieves an `int` number from the user.
 * @note This function keeps asking for input until a convertible string
 *       is provided.
 * @param requestLine: The line to request an input with.
 * @param isSigned: Whether the number can be negative or not.
 * @retval An `int` number provided by user.
 */
int SimpleCLI::GetIntInput(string requestLine, bool isSigned /*= false*/)
{
    // Defining required input variables
    string rawInput;
    int numberInput;

    while (true) {
        // Asking for input
        cout << InputIndicator << " " << requestLine << ": ";
        cin >> rawInput;

        // Trying to convert the input to int,
        // if succeeded -> break the loop,
        // if failed -> skip the iteration
        try {
            numberInput = stoi(rawInput);
            if (!isSigned && numberInput < 0) {
                throw range_error("Please enter a positive number.");
            }
        } catch (invalid_argument) {
            LogError("Please enter a number!", true);
            continue;
        } catch (range_error) {
            LogError("Please enter a positive number!", true);
            continue;
        }

        break;
    }

    return numberInput;
}

/**
 * @brief Retrieves a text from the user.
 * @note This function keeps asking for input until a non-empty string
 *       is provided.
 * @param requestLine: The line to request an input with.
 * @retval A `string` line provided by user.
 */
string SimpleCLI::GetStringInput(string requestLine)
{
    // Defining required input variable
    string rawInput;

    while (true) {
        // Asking for input
        cout << InputIndicator << " " << requestLine << ": ";
        cin >> rawInput;

        // Validating the string,
        // if succeeded -> break the loop,
        // if failed -> iterate again
        if (rawInput.length() >= 1 && rawInput.at(0) != ' ') {
            break;
        }

        LogError("Invalid input! Please try again.", true);
    }

    return rawInput;
}

/**
 * @brief Adds an option to the menu.
 * @note If provided index is out of menu's range,
 *       no option will be added.
 * @param newOption: The option to add.
 * @param index: The position of the option to insert into the menu.
 */
void SimpleCLI::AddOption(string newOption, int index /*= -1*/)
{
    if (-1 > index || index >= (int)MenuOptions.size())
    {
        LogError("Cannot add option at invalid index >:(");
        return;
    }

    if (index != -1)
    {
        MenuOptions.insert(MenuOptions.begin() + index, newOption);
    }
    else
    {
        MenuOptions.push_back(newOption);
    }
}

/**
 * @brief Sets menu options to the given list.
 * @param newOptions: The list of new options to set.
 */
void SimpleCLI::SetOptions(vector<string> newOptions)
{
    ClearOptions();

    for (string option : newOptions)
    {
        MenuOptions.push_back(option);
    }
    
    MenuOptions.shrink_to_fit();
}

/**
 * @brief Removes an option from the menu.
 * @param option: The option to remove.
 */
void SimpleCLI::RemoveOption(string option)
{
    for (size_t i = 0; i < MenuOptions.size(); i++)
    {
        if (MenuOptions.at(i) == option)
        {
            MenuOptions.erase(MenuOptions.begin() + i);
            return;
        }
    }

    LogWarning("Option '" + option + "' is not on the list :/");
}

/**
 * @brief Removes an option from the menu.
 * @param index: The position of the option to remove.
 */
void SimpleCLI::RemoveOption(int index /*= -1*/)
{
    if (-1 > index || index >= (int)MenuOptions.size())
    {
        LogError("Cannot remove option at invalid index >:(");
        return;
    }
    
    if (index != -1)
    {
        MenuOptions.erase(MenuOptions.begin() + index);
    }
    else
    {
        MenuOptions.pop_back();
    }
}

/**
 * @brief Removes all options from the menu.
 */
void SimpleCLI::ClearOptions()
{
    MenuOptions.clear();
}

/**
 * @brief Formats and outputs a message.
 * @param description: The text of a message to display.
 * @param hasBlankLine: Whether to put a blank line under the message.
 * @param isUrgent: Whether to use special mark for the output.
 */
void SimpleCLI::LogMessage(string description,
                           bool hasBlankLine /*= false*/,
                           bool isUrgent /*= false*/)
{
    string indicator = isUrgent
        ? OutputIndicator
        : ExecutionDebug;

    cout << indicator << " " << description << endl;
    if (hasBlankLine)
    {
        cout << LineIndicator << endl;
    }
}

/**
 * @brief Formats and outputs a message as a warning.
 * @param description: The text of a message to display.
 * @param hasBlankLine: Whether to put a blank line under the message.
 * @param isUrgent: Whether to use special mark for the output.
 */
void SimpleCLI::LogWarning(string description,
                           bool hasBlankLine /*= false*/,
                           bool isUrgent /*= false*/)
{
    string indicator = isUrgent
        ? WarningIndicator
        : ExecutionWarning;

    cout << indicator << " " << description << endl;
    if (hasBlankLine)
    {
        cout << LineIndicator << endl;
    }

}

/**
 * @brief Formats and outputs a message as an error.
 * @param description: The text of a message to display.
 * @param hasBlankLine: Whether to put a blank line under the message.
 * @param isUrgent: Whether to use special mark for the output.
 */
void SimpleCLI::LogError(string description,
                         bool hasBlankLine /*= false*/,
                         bool isUrgent /*= false*/)
{
    string indicator = isUrgent
        ? ErrorIndicator
        : ExecutionError;

    cout << indicator << " " << description << endl;
    if (hasBlankLine)
    {
        cout << LineIndicator << endl;
    }
}