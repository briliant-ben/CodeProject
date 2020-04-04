#-------------------------------------------------
#
# Project created by QtCreator 2020-02-22T13:17:19
#
#-------------------------------------------------

QT       += core gui serialport

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = RTK-WDT
TEMPLATE = app

# The following define makes your compiler emit warnings if you use
# any feature of Qt which has been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS
DEFINES += QUAZIP_STATIC

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

CONFIG += c++11
QMAKE_LFLAGS = -static

INCLUDEPATH += $$PWD/inc
#LIBS += -L$$PWD/lib/ -lquazip

SOURCES += \
    src/main.cpp \
    src/mainwindow.cpp \
    src/packagedialog.cpp \
    src/scriptworker.cpp \
    src/serialcom.cpp \
    src/serialconsole.cpp \
    src/seriallog.cpp \

HEADERS += \
    inc/mainwindow.h \
    inc/packagedialog.h \
    inc/scriptworker.h \
    inc/serialcom.h \
    inc/serialconsole.h \
    inc/seriallog.h \

FORMS += \
    ui/mainwindow.ui \
    ui/packagedialog.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    resource.qrc

RC_ICONS = $$PWD/rc/RTK-WDT.ico

DISTFILES += \

win32: LIBS += -L$$PWD/lib/ -lquazip

INCLUDEPATH += $$PWD/.
DEPENDPATH += $$PWD/.

win32:!win32-g++: PRE_TARGETDEPS += $$PWD/lib/quazip.lib
else:win32-g++: PRE_TARGETDEPS += $$PWD/lib/libquazip.a

win32: LIBS += -L$$PWD/lib/ -lzlib1

INCLUDEPATH += $$PWD/.
DEPENDPATH += $$PWD/.

win32:!win32-g++: PRE_TARGETDEPS += $$PWD/lib/zlib1.lib
else:win32-g++: PRE_TARGETDEPS += $$PWD/lib/libzlib1.a
