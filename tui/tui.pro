QT       += core gui xml

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11

# The following define makes your compiler emit warnings if you use
# any Qt feature that has been marked deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    components.cpp \
    curvecharttest.cpp \
    main.cpp \
    mainwindow.cpp \
    navigationtest.cpp \
    progressbartest.cpp \
    siderbartest.cpp \
    treeviewtest.cpp \
    treeviewtest.cpp

HEADERS += \
    components.h \
    curvecharttest.h \
    mainwindow.h \
    navigationtest.h \
    progressbartest.h \
    siderbartest.h \
    treeviewtest.h

FORMS += \
    components.ui \
    curvecharttest.ui \
    mainwindow.ui \
    navigationtest.ui \
    progressbartest.ui \
    siderbartest.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    res.qrc

#CONFIG += release
#MOC_DIR = temp/moc
#RCC_DIR = temp/rcc
#UI_DIR = temp/ui
#OBJECTS_DIR = temp/obj
#DESTDIR = bin

include(curvechart/curvechart.pri)
include(polygon/cpolygon.pri)
include(ultrasound/ultrasound.pri)
include(keyboard/keyboard.pri)
include(progressbar/progressbar.pri)
include(siderbar/siderbar.pri)
include(navigation/navigation.pri)
include(treeview/treeview.pri)
include(msgnotify/msgnotify.pri)
include(component/component.pri)
include(expander/expander.pri)
