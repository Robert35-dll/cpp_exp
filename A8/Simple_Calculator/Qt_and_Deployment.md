`Hello 👋/ᐠ｡ᆺ｡ᐟ\`

# Qt Framework and Deployment

Here are some basic notes about developing apps with Qt framework.
For deployment (*creating binaries for end users*) I used GitHub Actions since I don't want to deal with conflicting compiler versions on my machine :3

## Basics of Qt

For better convenience I personally recommend using QtCreator IDE while working on Qt-Projects.
Alternatively you may want to set up extensions for your editor.

It's worth noting that Qt has to be downloaded and installed manually.
Qt has an [online installer](https://doc.qt.io/qt-6/qt-online-installation.html) which is available for registered users.
Another option (*for Linux users*) is to install Qt via CLI (*e.g. via* `sudo pacman -S qt`).
However Qt insists to stick to its online installer which may provide a smoother and safer installation process.

Once you've installed your Qt version you should set up your IDE.
QtCreator should automatically recognize the right place of Qt binaries.
If that's not the case:
1. Go to `Edit` -> `Preferences` -> `Kits` -> `QtVersions`
2. `Add` your version (*default paths on Linux are* `/usr/bin/qmake6` *or* `/usr/bin/qmake-qt5`)

Afterwards you should be able to create Qt-projects.
While there're many project options the *Qt Quick Application* is the one to be chosen for a desktop app.

### Project Setup

The project is generally set by a `CMakeLists.txt` file using `cmake` syntax.
For older versions of Qt/QtCreator this might be a `project.pro` file using `qmake` syntax.
In both cases the files should be created automatically by the IDE and in most cases will be managed by those as well.
It's still worth to take a look at some basic changes may be performed.

#### Setting Parameters

A custom macro parameter can be specified by `add_compile_definitions(<macro_name>[=macro_value])` in `CMakeLists.txt`.
This works similar to adding `-D<macro_name>[=macro_value]` to the compile command.
Such parameters are available withing the whole program by e.g. `#ifdef <macro_name>` and `#if <macro_value> [= value]`.

In case you're developing for x86 and ARM platforms at the same time you might want to add an option to the Qt project via `option(<name> <description> <value>)`.
These can also be added and toggled in project settings of QtCreator.

#### Adding files to the project

Extra files with class' or UI definitions added to a project are specified in `CMakeLists.txt` as `qt_add_qml_module()`'s parameters.
Assets and resource files are listed as parameters of `qt_add_resources()`.

If you prefer to keep your source files grouped with their headers in separate folders, you should include those directories too:

```cmake
target_include_directories(app<project_name> PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}<path_to_dir_from_project_root>
)
```

### Creating Custom QML-Components

Generally a QML-Component is a C++-class wrapped with some QML-related base classes and macros.
Such classes look like this:

```c++
#pragma once

#include <QQmlEngine>
#include <QObject>

class C : public QObject
{
    Q_OBJECT
    QML_ELEMENT

    // A QML-wrapper for exposing properties (optional)
    Q_PROPERTY(int prop READ getProp WRITE setProp NOTIFY propChanged)

    int private_prop;

public:
    C(QObject *parent = nullptr)
     : QObject(parent)
    {}

    // Such method can be called directly in QML-code
    Q_INVOKABLE int getProp() { return private_prop; }
    Q_INVOKABLE void setProp(int newProp) { this->private_prop = newProp; }
}
```

The usage of `Q_PROPERTY` macro is optional since its parameters has to be defined explicilty anyway `¯\_(ツ)_/¯`

After a class is defined, you should register it as a QML-type in `main.cpp`:

```c++
#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QQmlContext>
#include <QQuickStyle>

#include "./C/C.h"

int main(int argc, char *argv[]) {
    // Qt App's and QML engine's definitions
    
    qmlRegisterType<C>("CComponent", 1, 0, "C");

    engine.loadFromModule(<app_name>, "Main");
    return app.exec();
}
```

After that you can finally import your component directly into UI:

```qml
import CComponent 1.0

Item {
    C {}
}
```

### Signal/Slot Communication
