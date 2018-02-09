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
    engineinitializer.cpp \
    checkers/system_cpu_stats_checker.cpp \
    checkers/system_memory_stats_checker.cpp \
    winperformancedataprovider.cpp \
    upload/oddeyeclient.cpp \
    upload/sendcontroller.cpp \
    logger.cpp \
    upload/basicoddeyeclient.cpp \
    upload/oddeyecacheuploader.cpp \
    pinger.cpp \
    application.cpp \
    checkers/system_disk_stats_checker.cpp \
    checkers/system_network_stats_checker.cpp \
    checkers/system_tcp_stats_checker.cpp \
    imetricscategorychecker.cpp \
    imetricchecker.cpp \
    metricsgroupchecker.cpp \
    basicmetricchecker.cpp \
    checkers/performanceounterhecker.cpp \
    winperformancemetricschecker.cpp

include(../3rdparty/qtservice/src/qtservice.pri)

HEADERS += \
    configurationmanager.h \
    configuration.h \
    exception.h \
    commonexceptions.h \
    engine.h \
    metricdata.h \
    engineinitializer.h \
    checkers/system_cpu_stats_checker.h \
    macros.h \
    checkers/system_memory_stats_checker.h \
    winperformancedataprovider.h \
    upload/oddeyeclient.h \
    upload/sendcontroller.h \
    logger.h \
    upload/basicoddeyeclient.h \
    upload/oddeyecacheuploader.h \
    pinger.h \
    winpdhexception.h \
    application.h \
    checkers/system_disk_stats_checker.h \
    checkers/system_network_stats_checker.h \
    checkers/system_tcp_stats_checker.h \
    imetricscategorychecker.h \
    imetricchecker.h \
    metricsgroupchecker.h \
    basicmetricchecker.h \
    checkers/performanceounterhecker.h \
    winperformancemetricschecker.h
