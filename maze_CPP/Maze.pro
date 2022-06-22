QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    Controller/facade.cpp \
    Model/interface.cpp \
    Model/Maze/openMaze.cpp \
    Model/Maze/mazeData.cpp \
    Model/Maze/generateMaze.cpp \
    Model/Cave/caveData.cpp \
    Model/Cave/openCave.cpp \
    Model/Cave/generateCave.cpp \
    PaintWidget/paintwidgetcave.cpp \
    PaintWidget/paintwidget.cpp \
    View/mainwindow.cpp \
    main.cpp \


HEADERS += \
    Controller/facade.h \
    Model/interface.h \
    Model/Maze/openMaze.h \
    Model/Maze/mazeData.h \
    Model/Maze/generateMaze.h \
    Model/Cave/caveData.h \
    Model/Cave/openCave.h \
    Model/Cave/generateCave.h \
    PaintWidget/paintwidgetcave.h \
    PaintWidget/paintwidget.h \
    View/mainwindow.h \

FORMS += \
    View/mainwindow.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    View/icons.qrc

DEFINES += HOME_DIR=\\\"$(HOME)/Applications/Maze/\\\"

ICON = maze.icns
