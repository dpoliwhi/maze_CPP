QT       += core gui

include(../QtGifImage/src/gifimage/qtgifimage.pri)

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets opengl openglwidgets

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    ../Controller/facade.cpp \
    ../Model/actions.cpp \
    ../Model/interface.cpp \
    ../Model/matrix.cpp \
    ../Model/object.cpp \
    ../main.cpp \
    ../View/mainwindow.cpp \
    ../OpenGL/opengl_widget.cpp \
    ../Settings/settings.cpp

HEADERS += \
    ../Controller/facade.h \
    ../Model/actions.h \
    ../Model/interface.h \
    ../Model/matrix.h \
    ../Model/object.h \
    ../View/mainwindow.h \
    ../OpenGL/opengl_widget.h \
    ../Settings/settings.h

FORMS += \
    ../View/mainwindow.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

DISTFILES += \
    ../Configurations/settings.conf \
    ../Objects/CUB.obj

RESOURCES += \
    ../Resources/icons.qrc \
    ../Resources/settings.qrc \
    ../Resources/shaders.qrc

DEFINES += HOME_DIR=\\\"$(HOME)/Applications/3DViewer/\\\"


ICON = ../Resources/AnyConv.com__premium-icon-3d-modeling-3112437.icns
