TEMPLATE = app
CONFIG += console c++11
CONFIG -= app_bundle
CONFIG -= qt

SOURCES += \
        main.cpp \
    docparser.cpp \
    queryprocessor.cpp \
    userinterface.cpp

HEADERS += \
    index.h \
    indexhandler.h \
    docparser.h \
    queryprocessor.h \
    userinterface.h \
    avltree.h
