#-------------------------------------------------
#
# Project created by QtCreator 2018-02-11T11:42:04
#
#-------------------------------------------------

QT       += core gui network

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = OEAgentControl
TEMPLATE = app

# The following define makes your compiler emit warnings if you use
# any feature of Qt which has been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS
QMAKE_LFLAGS_WINDOWS = /SUBSYSTEM:WINDOWS,5.01

win32:RC_ICONS += icons/agentlogo.ico

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

include(../../3rdparty/qtservice/src/qtservice.pri)

INCLUDEPATH += ../../common/

SOURCES += \
        main.cpp \
    guicontroller.cpp \
    ../../common/agentcontrolclient.cpp

HEADERS += \
    ../../common/message.h \
    ../../common/agentcontrolclient.h \
    guicontroller.h

RESOURCES += \
    res.qrc
