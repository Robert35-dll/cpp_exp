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

#### Adding files to the project

### Creating Custom Components

### Signal/Slot Communication
