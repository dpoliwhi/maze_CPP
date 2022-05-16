QT       += core gui printsupport

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    ../s21_calc_cpp/Controller/s21_controller.cpp \
    ../s21_calc_cpp/Model/s21_model.cpp \
    ../s21_calc_cpp/View/dialog_plot.cpp \
    ../s21_calc_cpp/View/main.cpp \
    ../s21_calc_cpp/View/calculator.cpp \
    ../s21_calc_cpp/View/plot.cpp \
    ../s21_calc_cpp/qcustomplot.cpp \
    ../s21_calc_cpp/View/substitute_x.cpp

HEADERS += \
    ../s21_calc_cpp/Controller/s21_controller.h \
    ../s21_calc_cpp/Model/s21_model.h \
    ../s21_calc_cpp/View/calculator.h \
    ../s21_calc_cpp/View/dialog_plot.h \
    ../s21_calc_cpp/View/plot.h \
    ../s21_calc_cpp/qcustomplot.h \
    ../s21_calc_cpp/View/substitute_x.h

FORMS += \
    ../s21_calc_cpp/View/calculator.ui \
    ../s21_calc_cpp/View/dialog_plot.ui \
    ../s21_calc_cpp/View/plot.ui \
    ../s21_calc_cpp/View/substitute_x.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

DISTFILES += \
    s21.png

#ICON = s21calc.icns
