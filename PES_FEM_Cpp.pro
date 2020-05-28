TEMPLATE = app
CONFIG += console c++11
CONFIG -= app_bundle
CONFIG -= qt

SOURCES += \
        aux_functions.cpp \
        boundaryconditions.cpp \
        domain.cpp \
        element.cpp \
        elementq2.cpp \
        elementt1.cpp \
        main.cpp \
        node.cpp \
        point.cpp \
        quaddata.cpp \
        quadpoint.cpp \
        systemofequations.cpp

HEADERS += \
    aux_functions.h \
    boundaryconditions.h \
    domain.h \
    element.h \
    elementq2.h \
    elementt1.h \
    node.h \
    point.h \
    quaddata.h \
    quadpoint.h \
    systemofequations.h
