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
    avlindex.cpp

HEADERS += \
    index.h \
    indexhandler.h \
    docparser.h \
    queryprocessor.h \
    userinterface.h \
    avltree.h \
    hashtable.h \
    indexinterface.h \
    avlindex.h
