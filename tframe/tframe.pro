QT       += core gui

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
    aboutdialog.cpp \
    caboutdialog.cpp \
    centerwindow.cpp \
    csettingdialog.cpp \
    floatwindow.cpp \
    main.cpp \
    mainwindow.cpp \
    settingdialog.cpp \
    settingmenu.cpp \
    thememenu.cpp

HEADERS += \
    aboutdialog.h \
    caboutdialog.h \
    centerwindow.h \
    csettingdialog.h \
    floatwindow.h \
    mainwindow.h \
    settingdialog.h \
    settingmenu.h \
    thememenu.h

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

include(core/core.pri)

RESOURCES += \
    res.qrc

DEPENDPATH += .
INCLUDEPATH += .

# build dir
BuildDir =build_$$QT_VERSION

CONFIG(debug, debug|release) {
    DESTDIR = $$PWD/$$BuildDir/debug
    OBJECTS_DIR = $$PWD/$$BuildDir/debug/.obj
    MOC_DIR = $$PWD/$$BuildDir/debug/.moc
    RCC_DIR = $$PWD/$$BuildDir/debug/.rcc
    UI_DIR = $$PWD/$$BuildDir/debug/.ui
} else {
    DESTDIR = $$PWD/$$BuildDir/release
    OBJECTS_DIR = $$PWD/$$BuildDir/release/.obj
    MOC_DIR = $$PWD/$$BuildDir/release/.moc
    RCC_DIR = $$PWD/$$BuildDir/release/.rcc
    UI_DIR = $$PWD/$$BuildDir/release/.ui
}

## QT4.8 applciation icon
#contains(QT_MAJOR_VERSION, 4){
#    win32{
#        RC_FILE = logo.rc
#    }
#}

# QT5 applciation icon
contains(QT_MAJOR_VERSION, 5){
    RC_ICONS = "res/logo.ico"
}
