TEMPLATE = app
CONFIG += console c++11
CONFIG -= app_bundle
CONFIG -= qt

SOURCES += \
        consolelogger.cpp \
        domain.cpp \
        main.cpp \
        objectivefunction.cpp \
        particle.cpp \
        particlefactors.cpp \
        ranlux24numbersgenerator.cpp \
        swarm.cpp \
        swarmconfig.cpp \
        velocitylimit.cpp

HEADERS += \
    consolelogger.h \
    domain.h \
    ilog.h \
    irandomnumbersgenerator.h \
    objectivefunction.h \
    particle.h \
    particlefactors.h \
    ranlux24numbersgenerator.h \
    swarm.h \
    swarmconfig.h \
    velocitylimit.h
