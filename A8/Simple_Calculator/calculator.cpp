#include "calculator.h"

#include <map>

/**
 * @brief Appends a digit to current input.
 * @param newDigit - The digit to append.
 */
void Calculator::addDigit(int newDigit)
{
    // If there's a number on display
    // but no operation's set
    // -> reset the input
    if (this->displayedNumber != 0 &&
        this->reservedNumber != 0 &&
        this->applyOperand == nullptr)
    {
        this->clear(true);
    }

    // If input is decimal
    // -> add the digit to the end of the decimal part
    if (this->decimalPower != 0)
    {
        this->displayedNumber += static_cast<float>(newDigit) / this->decimalPower;
        this->decimalPower *= 10;
    }
    // Otherwise -> add to the end of the integer part
    else
    {
        this->displayedNumber *= 10;
        this->displayedNumber += newDigit;
    }

    emit displayedNumberChanged(this->displayedNumber);
}

/**
 * @brief Sets the next operand to apply to calculation.
 * @param newOperand - The operand's code to set.
 *        Possible values are: `+`, `-`, `*`, `/`, `+/-` and `,` (comma).
 */
void Calculator::setOperand(QString newOperand)
{
    // Translating QString into char
    std::map<QString, char> codesMap = {
        { "+", '+' },
        { "-", '-' },
        { "*", '*' },
        { "/", '/' },
        { ",", ',' },
        { "+/-", '!' }
    };

    char operandCode;
    try { operandCode = codesMap.at(newOperand); }
    catch (std::out_of_range) {}

    // Starting adding decimals
    if (operandCode == ',' &&
        this->decimalPower == 0)
    {
        this->decimalPower = 10;
        return;
    }

    // Inverting the input
    if (operandCode == '!')
    {
        this->displayedNumber *= -1;
        emit displayedNumberChanged(this->displayedNumber);
        return;
    }

    // Performing previously set operand
    if (this->applyOperand != nullptr &&
        this->displayedNumber != 0)
    {
        this->calculate();
    }

    // Setting new operand
    switch (operandCode)
    {
        case '+':
        {
            this->applyOperand = Calculator::add;
            break;
        }
        case '-':
        {
            this->applyOperand = Calculator::subtract;
            break;
        }
        case '*':
        {
            this->applyOperand = Calculator::multiply;
            break;
        }
        case '/':
        {
            this->applyOperand = Calculator::divide;
            break;
        }
        default: this->applyOperand = nullptr;
    }

    // Saving the input
    this->reservedNumber = this->displayedNumber;
    // and reseting the display
    this->displayedNumber = 0;
    emit displayedNumberChanged(this->displayedNumber);

    this->decimalPower = 0;
}

/**
 * @brief Applies the last set operand to the two last inputs.
 * @note If trying to devide by 0, an errorOccurred signal is emitted.
 */
void Calculator::calculate()
{
    // If no operand has been set
    // -> do nothing :)
    if (this->applyOperand == nullptr)
    {
        return;
    }
    // If try to divide by 0
    // -> throw an error >:(
    if (this->applyOperand == &Calculator::divide &&
        this->displayedNumber == 0)
    {
        emit errorOccurred();
        return;
    }

    // Otherwise
    // -> perform the operation
    this->displayedNumber = this->applyOperand(this->reservedNumber, this->displayedNumber);
    // -> display the result
    emit displayedNumberChanged(this->displayedNumber);
    // -> and reset the inputs
    this->applyOperand = nullptr;
    this->decimalPower = 0;
}

/**
 * @brief Sets the displayed number to 0
 *        and optionally resets the operand with previous input.
 * @param isReset - Whether to reset the operand with previous input or not.
 */
void Calculator::clear(bool isReset)
{
    // If reseting
    // -> clear inputs
    if (isReset)
    {
        this->reservedNumber = 0;
        this->applyOperand = nullptr;
    }

    // Reseting the display
    this->displayedNumber = 0;
    emit displayedNumberChanged(this->displayedNumber);

    this->decimalPower = 0;
}
