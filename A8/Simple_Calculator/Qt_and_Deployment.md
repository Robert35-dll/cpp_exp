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

In other words event-driven communication or sender-observer pattern.
Qt offers this powerful mechanism out of the box for nearly any inter-component connection (*e.g. frontend to backend*).
This can be used for similar connections within single classes as well.
Therefore any class derived from `QObject` **and** mentioning the `Q_OBJECT` macro can define its signals and slots for such purposes:

```c++
#pragma once

#include <QQmlEngine>
#include <QObject>

class C : public QObject
{
    Q_OBJECT
    QML_ELEMENT

public:
    C(QObject *parent = nullptr)
     : QObject(parent)
    {}

// These events can be listened from other components
signals:
    void propChanged(int newProp);

// These methods can be attached to signals from other components
slots:
    void DoSmth(float someValue);
}
```

It's worth noting that both signals and slots don't have to have any return values.
Since signals are emitted to start their slots' execution (*without checking if they're actually executable*) a return value doesn't make any practical sense.
Eventhough slots are effectively regular methods, their return values don't impact anything in case a slot is executed automatically by Qt itself after certain signal is fired.

#### Connecting with C++

To assign slots to signals the `QObject::connect` method is used on the backend side:

```c++
#include "C.h"
#include <QObject>

int main()
{
    C c1, c2;

    // Connecting two objects to each other
    QObject::connect(&c1, &C::propChanged,  // First the sender + signal
                     &c2, &C::DoSmth);      // Then the receiver + slot
}
```

Slot argument can be substituted with a static method or a lambda expression just as good:

```c++
    // Attaching a static method to a signal
    QObject::connect(&c1, &C::propChanged,
                     &c2, &C::SomeStaticFunc);

    // Attaching a custom lambda expression to a signal
    // Note: assuming this happens within a class
    QObject::connect(&c1, &C::propChanged,
                     this, [=](int newProp) { /* some logic */ };
                     );
```

#### Connecting with QML

To assign some logic to signals in QML you can simply define a function for required parameters (*optional*):

```qml
import CComponent 1.0

Item {
    C {
        // It won't fail anything, if you'll forget the signal's signature /ᐠ｡ᆺ｡ᐟ\
        onPropChanged: function() {
            // do some stuff
        }
    }
}
```

## Deployment

Once the project is ready to be delivered to the user you have to think about distributing it as an ordinary app.
This is already done by QtCreator when building a project for a test run but you can also build manually with `cmale` like this from the project root:

```bash
cmake -S <source_path> -B <build_path>
cmake --build <build_path>
```

Yes, the content of the build directory is already the app you can roll out.
Thanks to `cmake` the binary file is created for the host machine automatically (`.exe` *and* `plain binaries` *will match the OS*).

The only issue with those folders is that they might not contain the required Qt core libraries.
There're couple of tools for a workaround: [`windeployqt`](#deploying-for-windows) and [`linuxdeployqt`](#deploying-for-linux).
Alternatively you can seek for the required `.dll` files in your Qt-root and copy them into the build directory `:3`

If you want to compress the project down to a single executable, you have to add compiled Qt libraries yourself to it which will:
1. Take a while
2. Increase the size of the end file dramatically

It's quite common to stick to the folder option though.

### Deploying for Windows

With `windeployqt` you can easily prepare a release of your project.
Qt has written an [extensive documentation](https://doc.qt.io/qt-6/windows-deployment.html) about this tool but essential is the following command:

```bash
windeployqt --qmldir <path-to-app-qml-files> <path-to-app-binary>
```

After using it you should have a ready to deliver release directory.

### Deploying for Linux

There's similar tool called [`linuxdeployqt`](https://github.com/probonopd/linuxdeployqt) for Linux systems.
To use `linuxdeployqt` execute a similar command:

```bash
linuxdeployqt <path-to-app-binary> -qmldir=<path>
```

[However](https://github.com/probonopd/linuxdeployqt?tab=readme-ov-file#a-note-on-binary-compatibility):

> `linuxdeployqt` refuses to work on systems any newer than
the oldest currently still-supported Ubuntu LTS release,
because we want to encourage developers to build applications
in a way that makes them possible to run
on all still-supported distribution releases.

which literally means that you might have to switch to an older Linux version to use `linuxdeployqt`.
For this sake there're GitHub Actions that allow to build for both Windows and Linux at once.

### GitHub Workflows

Workflows are kind of routine scripts executed upon certain git events.
Their execution can be monitored at the dedicated 'Actions' tab on the website.
There're many ready to use routines defined as actions you can add to your workflow.
To build a Qt project you'll need these actions:
1. Checkout - `actions/checkout@v6`
2. Qt Installer - `jurplel/install-qt-action@v3`
3. Artifact Uploader - `actions/upload-artifact@v4`

as well as couple of building scripts including `cmake`, [`windeployqt`](#deploying-for-windows) and [`linuxdeployqt`](#deploying-for-linux) commands from above.

The workflow `.yml` file must be stored at `./.github/workflows/` directory.
A single workflow file is built like this:

```yml
name: <workflow-name>
# A list of triggering events
on:
  push:
    branches:
      - <branch-name>
  pull_request:
    paths:
      - <paths_to_triggering_files_or_directories>

# A step by step description of the workflow
jobs:
  <job_name>:
    runs-on: <target_system>

    steps:
      # An Action Step
      - name: <step_name>
        uses: <action_link>
        
      # A Script Step
      - name: <step_name>
        [shell: pwsh]
        run: |
          <command_to_run>
```

An example workflow for this project is stored at [`./.github/workflows/build_calculator.yml`](../../.github/workflows/build_calculator.yml)

See [the official syntax reference](https://docs.github.com/en/actions/reference/workflows-and-actions/workflow-syntax) for more options.
