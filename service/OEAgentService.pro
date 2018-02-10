QT += core
QT -= gui
QT += network

CONFIG += c++11

#QMAKE_LFLAGS *= /MACHINE:X64

LIBS     += -lws2_32
LIBS     += -liphlpapi

TARGET = OE-Agent
CONFIG += console
CONFIG -= app_bundle

TEMPLATE = app

SOURCES += main.cpp \
    configurationmanager.cpp \
    configuration.cpp \
    exception.cpp \
    commonexceptions.cpp \
    engine.cpp \
    metricdata.cpp \
    winperformancedataprovider.cpp \
    upload/oddeyeclient.cpp \
    upload/sendcontroller.cpp \
    logger.cpp \
    upload/basicoddeyeclient.cpp \
    upload/oddeyecacheuploader.cpp \
    pinger.cpp \
    application.cpp \
    imetricscategorychecker.cpp \
    imetricchecker.cpp \
    metricsgroupchecker.cpp \
    basicmetricchecker.cpp \
    checkers/performanceounterhecker.cpp \
    winperformancemetricschecker.cpp \
    checkers/scriptsmetricschecker.cpp \
    checkers/system_cpu_stats.cpp \
    checkers/system_disk_stats.cpp \
    checkers/system_memory_stats.cpp \
    checkers/system_network_stats.cpp \
    checkers/system_tcp_stats.cpp \
    checkers/oddeyeselfcheck.cpp \
    agentinitializer.cpp \
    cservicecontroller.cpp

include(../3rdparty/qtservice/src/qtservice.pri)

HEADERS += \
    configurationmanager.h \
    configuration.h \
    exception.h \
    commonexceptions.h \
    engine.h \
    metricdata.h \
    macros.h \
    winperformancedataprovider.h \
    upload/oddeyeclient.h \
    upload/sendcontroller.h \
    logger.h \
    upload/basicoddeyeclient.h \
    upload/oddeyecacheuploader.h \
    pinger.h \
    winpdhexception.h \
    application.h \
    imetricscategorychecker.h \
    imetricchecker.h \
    metricsgroupchecker.h \
    basicmetricchecker.h \
    checkers/performanceounterhecker.h \
    winperformancemetricschecker.h \
    checkers/scriptsmetricschecker.h \
    checkers/system_cpu_stats.h \
    checkers/system_disk_stats.h \
    checkers/system_memory_stats.h \
    checkers/system_network_stats.h \
    checkers/system_tcp_stats.h \
    checkers/oddeyeselfcheck.h \
    agentinitializer.h \
    cservicecontroller.h
