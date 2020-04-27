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
    src/directserver.cpp \
    src/FILE_STRUCT.cpp \
    src/iconnector.cpp \
    src/LOG.cpp \
    src/logs.cpp \
    src/sys_info.cpp \
    src/watcher.cpp

HEADERS += \
    include/FILE_STRUCT.h \
    include/iconnector.h \
    include/LOG.h \
    include/logs.h \
    include/logs_library_global.h \
    include/logs_library.h \
    include/sys_info.h \
    include/watcher.h \
    include/directserver.h

TRANSLATIONS += \
    logs_library_pl_PL.ts

# Default rules for deployment.
unix {
    target.path = /usr/lib
}
!isEmpty(target.path): INSTALLS += target

win32:CONFIG(release, debug|release): LIBS += -lpsapi
else:win32:CONFIG(debug, debug|release): LIBS += -lpsapi

INCLUDEPATH += $$PWD/../include
DEPENDPATH += $$PWD/../include
