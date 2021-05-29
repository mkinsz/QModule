include(gtest_dependency.pri)

TEMPLATE = app
CONFIG += console c++11
CONFIG -= app_bundle
CONFIG += thread
CONFIG += qt core gui

HEADERS += \
        runnable.h \
        thread.h \
        threadpool.h \
        tst_runnable.h \
        tst_test.h

SOURCES += \
        main.cpp \
        thread.cpp \
        threadpool.cpp \
        tst_test.cpp
