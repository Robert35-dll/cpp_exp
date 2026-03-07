#pragma once

#include <QObject>
#include <QQmlEngine>

class Calculator : public QObject
{
    Q_OBJECT
    QML_ELEMENT

    float  displayedNumber;
    float  reservedNumber;
    int     decimalPower;

    float (*applyOperand)(float, float);

    static float add     (float a, float b) { return a + b; }
    static float subtract(float a, float b) { return a - b; }
    static float multiply(float a, float b) { return a * b; }
    static float divide  (float a, float b) { return a / b; }

public:
    explicit Calculator(QObject *parent = nullptr)
        : QObject{parent},
        displayedNumber(0),
        reservedNumber(0),
        decimalPower(0)
    {}

    Q_INVOKABLE void addDigit(int newDigit);
    Q_INVOKABLE void setOperand(QString newOperand);
    Q_INVOKABLE void calculate();

    Q_INVOKABLE void clear(bool isReset /*= false*/);

signals:
    void displayedNumberChanged(float newNumber);
    void errorOccurred();
};
