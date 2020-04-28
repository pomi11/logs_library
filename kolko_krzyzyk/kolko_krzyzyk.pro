#-------------------------------------------------
#
# Project created by QtCreator 2018-11-12T14:58:33
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = kolko_krzyzyk
TEMPLATE = app

# The following define makes your compiler emit warnings if you use
# any feature of Qt which has been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

CONFIG += c++11

SOURCES += \
    gamecontroller.cpp \
        main.cpp \
        mainwindow.cpp \
    maindraw.cpp \
    obiekt.cpp \
    objects.cpp

HEADERS += \
    gamecontroller.h \
        mainwindow.h \
    maindraw.h \
    obiekt.h \
    objects.h

FORMS += \
        mainwindow.ui

LIBS += -lOpengl32
# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

win32:CONFIG(release, debug|release): LIBS += -L$$PWD/../../../C++/logs_library/debug_win/release/ -llogs_library
else:win32:CONFIG(debug, debug|release): LIBS += -L$$PWD/../../../C++/logs_library/debug_win/debug/ -llogs_library
else:unix: LIBS += -L$$PWD/../../../C++/logs_library/debug_win/ -llogs_library

INCLUDEPATH += $$PWD/include
DEPENDPATH += $$PWD/include
