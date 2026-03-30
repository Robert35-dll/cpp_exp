#include <QGuiApplication>
#include <QQmlApplicationEngine>

#include "calculator.h"

int main(int argc, char *argv[])
{
    QGuiApplication app(argc, argv);

    qmlRegisterType<Calculator>("CalculatorComponent", 1, 0, "Calculator");

    QQmlApplicationEngine engine;
    QObject::connect(
        &engine,
        &QQmlApplicationEngine::objectCreationFailed,
        &app,
        []() { QCoreApplication::exit(-1); },
        Qt::QueuedConnection);
    engine.loadFromModule("Simple_Calculator", "Main");

    return app.exec();
}
