#include "calculator.h"

#include <QString>
#include <QDebug>

void Calculator::addDigit(int newDigit)
{
    // If input is decimal
    // -> add the digit to the end of the decimal part
    if (this->decimalPower != 0) {
        this->displayedNumber += static_cast<float>(newDigit) / this->decimalPower;
        this->decimalPower *= 10;
    } else {
        // Otherwise -> add to the end of the integer part
        this->displayedNumber *= 10;
        this->displayedNumber += newDigit;
    }

    emit displayedNumberChanged(this->displayedNumber);
}

void Calculator::setOperand(QString newOperand)
{
    std::map<QString, char> translate = {
        { "+", '+' },
        { "-", '-' },
        { "*", '*' },
        { "/", '/' },
        { ",", ',' },
        { "+/-", '!' }
    };

    char operandCode;
    try { operandCode = translate.at(newOperand); }
    catch (std::out_of_range) {}

    if (operandCode == ',' &&
        this->decimalPower == 0)
    {
        this->decimalPower = 10;
        return;
    }

    if (operandCode == '!')
    {
        this->displayedNumber *= -1;
        emit displayedNumberChanged(this->displayedNumber);
        return;
    }

    if (this->applyOperand != nullptr &&
        this->displayedNumber != 0)
    {
        this->calculate();
    }

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

    this->reservedNumber = this->displayedNumber;
    this->displayedNumber = 0;
    emit displayedNumberChanged(this->displayedNumber);

    this->decimalPower = 1;
}

void Calculator::calculate()
{
    qDebug() << this->calculationResult;
    if (this->applyOperand == nullptr) {
        return;
    }
    if (this->applyOperand == &Calculator::divide &&
        this->displayedNumber == 0) {
        emit errorOccurred();
        return;
    }

    this->displayedNumber = this->applyOperand(this->reservedNumber, this->displayedNumber);
    emit displayedNumberChanged(this->displayedNumber);

    this->applyOperand = nullptr;
    this->decimalPower = 0;
}

void Calculator::clear(bool isReset)
{
    if (isReset)
    {
        this->reservedNumber = 0;
        this->applyOperand = nullptr;
    }

    this->displayedNumber = 0;
    emit displayedNumberChanged(this->displayedNumber);

    this->decimalPower = 0;
}
