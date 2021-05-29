# build dir
BUILD_DIR = build_$$QT_VERSION
BUILD_PATH = $$PWD/$$BUILD_DIR
OUT_PATH = $$BUILD_PATH/$$TARGET

CONFIG(debug, debug|release) {
    BUILD_TYPE = debug
} else {
    BUILD_TYPE = release
}

DESTDIR = $$BUILD_PATH/bin
OBJECTS_DIR = $$OUT_PATH/$$BUILD_TYPE/.obj
MOC_DIR = $$OUT_PATH/$$BUILD_TYPE/.moc
RCC_DIR = $$OUT_PATH/$$BUILD_TYPE/.rcc
UI_DIR = $$OUT_PATH/$$BUILD_TYPE/.ui

# QT5 applciation icon
contains(QT_MAJOR_VERSION, 5){
    RC_ICONS = "res/img/logo.ico"
}

message(Host is $$QMAKE_HOST.arch)

message($$qtLibraryTarget($$TARGET))

message($$QMAKESPEC)

contains(QMAKESPEC, msvc) {
    message(--> msvc)
}

contains(QMAKESPEC, mingw) {
    message(--> mingw)
}

contains(QMAKE_HOST.os,Windows) {
    message($$QMAKE_HOST.os)
    contains(QT_ARCH, i386) {
        PLAT_FORM = x86
    } else {
        PLAT_FORM = x64
    }

    message($$PLAT_FORM)

    VERSION = 0.1.0.0
    QMAKE_TARGET_PRODUCT = $${TARGET}_$$PLAT_FORM
    QMAKE_TARGET_COMPANY = MK CO., LTD.
    QMAKE_TARGET_DESCRIPTION = $${TARGET}_V$${VERSION}
    QMAKE_TARGET_COPYRIGHT = Copyright 2020-2030 The MK Ltd.
    CONFIG += skip_target_version_ext
}else{
    message($$QMAKE_HOST.os)
}
