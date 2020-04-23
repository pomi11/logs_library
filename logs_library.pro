QT -= gui
QT += network
TEMPLATE = lib
DEFINES += LOGS_LIBRARY_LIBRARY

CONFIG += c++11

# The following define makes your compiler emit warnings if you use
# any Qt feature that has been marked deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    directserver.cpp \
    file_struct.cpp \
    iconnector.cpp \
    log.cpp \
    logs.cpp \
    sys_info.cpp

HEADERS += \
    directserver.h \
    file_struct.h \
    iconnector.h \
    log.h \
    logs.h \
    logs_library_global.h \
    logs_library.h \
    sys_info.h

TRANSLATIONS += \
    logs_library_pl_PL.ts

# Default rules for deployment.
unix {
    target.path = /usr/lib
}
!isEmpty(target.path): INSTALLS += target
LIBS += -lpsapi

win32:CONFIG(release, debug|release): LIBS += -L$$PWD/../build-logs_library-Nienazwany-Debug/release/ -llogs_library
else:win32:CONFIG(debug, debug|release): LIBS += -L$$PWD/../build-logs_library-Nienazwany-Debug/debug/ -llogs_library
else:unix: LIBS += -L$$PWD/../build-logs_library-Nienazwany-Debug/ -llogs_library

INCLUDEPATH += $$PWD/../
DEPENDPATH += $$PWD/../
