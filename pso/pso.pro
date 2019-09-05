TEMPLATE = app
CONFIG += console c++11
CONFIG -= app_bundle
CONFIG -= qt

SOURCES += \
        consolelogger.cpp \
        main.cpp \
        objectivefunction.cpp \
        particle.cpp \
        particlefactors.cpp \
        randomnumbersgenerator.cpp \
        swarm.cpp \
        swarmconfig.cpp

HEADERS += \
    consolelogger.h \
    ilog.h \
    objectivefunction.h \
    particle.h \
    particlefactors.h \
    randomnumbersgenerator.h \
    swarm.h \
    swarmconfig.h
