TEMPLATE = app
CONFIG += console c++11
CONFIG -= app_bundle
CONFIG -= qt

SOURCES += \
        main.cpp \
    docparser.cpp \
    queryprocessor.cpp \
    userinterface.cpp \
    hashtable.cpp \
    indexinterface.cpp \
    htindex.cpp

HEADERS += \
    docparser.h \
    queryprocessor.h \
    userinterface.h \
    avltree.h \
    hashtable.h \
    indexinterface.h \
    htindex.h
