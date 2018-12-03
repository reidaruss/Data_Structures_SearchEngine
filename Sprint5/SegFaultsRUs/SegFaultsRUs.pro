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
    htindex.cpp \
    avlindex.cpp \
    indexinterface.cpp \
    persistedindex.cpp


HEADERS += \
    docparser.h \
    queryprocessor.h \
    userinterface.h \
    avltree.h \
    hashtable.h \
    indexinterface.h \
    htindex.h \
    avlindex.h \
    persistedindex.h \
    english_stem.h \
    indexing/common_lang_constants.h \
    indexing/string_util.h \
    utilities/debug_logic.h \
    utilities/safe_math.h \
    utilities/utilities.h

