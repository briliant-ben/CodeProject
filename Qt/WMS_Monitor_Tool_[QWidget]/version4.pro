#-------------------------------------------------
#
# Project created by QtCreator 2017-04-16T14:00:59
#
#-------------------------------------------------

QT       += core gui sql axcontainer printsupport webenginewidgets
QT       += charts

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = version4
TEMPLATE = app

# The following define makes your compiler emit warnings if you use
# any feature of Qt which as been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0


SOURCES += main.cpp\
    entity/coupling.cpp \
    entity/location.cpp \
    entity/staff.cpp \
    entity/storageinoutcheck.cpp \
    dao/basedao.cpp \
    window/loginwindow.cpp \
    window/mainwindow.cpp \
    window/personnelwindow.cpp \
    window/registerwindow.cpp \
    window/tabpersonnelwindow.cpp \
    dao/staffdao.cpp \
    window/tabstafflogwindow.cpp \
    dao/stafflogdao.cpp \
    window/tabstoragestockwindow.cpp \
    window/tabstoragestreamwindow.cpp \
    window/tabstoragelogwindow.cpp \
    dao/couplingdao.cpp \
    dao/locationdao.cpp \
    dao/storagestreamdao.cpp \
    window/streamrecordwindow.cpp \
    window/tabmonitoragvwindow.cpp \
    window/systemconfigurewindow.cpp \
    window/tabstatisticone.cpp \
    window/tabreportformwindow.cpp \
    window/feedbackwindow.cpp \
    window/tabdispatchwindow.cpp

HEADERS  += \
    entity/coupling.h \
    entity/location.h \
    entity/staff.h \
    entity/storageinoutcheck.h \
    dao/basedao.h \
    window/loginwindow.h \
    window/mainwindow.h \
    window/personnelwindow.h \
    window/registerwindow.h \
    window/tabpersonnelwindow.h \
    dao/staffdao.h \
    window/tabstafflogwindow.h \
    dao/stafflogdao.h \
    window/tabstoragestockwindow.h \
    window/tabstoragestreamwindow.h \
    window/tabstoragelogwindow.h \
    dao/couplingdao.h \
    dao/locationdao.h \
    dao/storagestreamdao.h \
    window/streamrecordwindow.h \
    window/tabmonitoragvwindow.h \
    window/systemconfigurewindow.h \
    window/tabstatisticone.h \
    window/tabreportformwindow.h \
    window/feedbackwindow.h \
    window/tabdispatchwindow.h

FORMS    += \
    window/loginwindow.ui \
    window/mainwindow.ui \
    window/personnelwindow.ui \
    window/registerwindow.ui \
    window/tabpersonnelwindow.ui \
    window/tabstafflogwindow.ui \
    window/tabstoragestockwindow.ui \
    window/tabstoragestreamwindow.ui \
    window/tabstoragelogwindow.ui \
    window/streamrecordwindow.ui \
    window/tabmonitoragvwindow.ui \
    window/systemconfigurewindow.ui \
    window/tabstatisticone.ui \
    window/tabreportformwindow.ui \
    window/feedbackwindow.ui \
    window/tabdispatchwindow.ui

RESOURCES += \
    resource.qrc
