#------------------------------------------------- 
# 
# Project created by Script 
# 
#------------------------------------------------- 

QT += widgets 

TARGET = astarte
TEMPLATE = lib 

CONFIG += c++11 

DEFINES += ASTARTE_LIBRARY 

include(../build_plugins.pri) 

SOURCES += \
   astarte.cpp\
   form.cpp

HEADERS += \
   astarte_global.h \
   astarte.h \
   form.h

RESOURCES += \
    res.qrc

FORMS += \
    form.ui

