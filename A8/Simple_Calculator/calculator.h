#pragma once

#include <QObject>
#include <QQmlEngine>

class Calculator : public QObject
{
    Q_OBJECT
    QML_ELEMENT

    double  displayedNumber;
    double  calculationResult;
    int     decimalPower;

    double (*applyOperand)(double, double);

    static double add     (double a, double b) { return a + b; }
    static double subtract(double a, double b) { return a - b; }
    static double multiply(double a, double b) { return a * b; }
    static double divide  (double a, double b) { return a / b; }

public:
    explicit Calculator(QObject *parent = nullptr)
        : QObject{parent},
        displayedNumber(0),
        calculationResult(0),
        decimalPower(0)
    {}

    Q_INVOKABLE void addDigit(int newDigit);
    Q_INVOKABLE void setOperand(QString newOperand);
    Q_INVOKABLE void calculate();

    Q_INVOKABLE void clear(bool isReset /*= false*/);

signals:
    void displayedNumberChanged(double newNumber);
    void errorOccurred();
};
