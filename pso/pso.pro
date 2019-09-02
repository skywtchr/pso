TEMPLATE = app
CONFIG += console c++11
CONFIG -= app_bundle
CONFIG -= qt

SOURCES += \
        consolelogger.cpp \
        main.cpp \
        particle.cpp \
        swarm.cpp

HEADERS += \
    consolelogger.h \
    ilog.h \
    particle.h \
    swarm.h
