BUILD_DIR = build_$$QT_VERSION
BUILD_PATH = $$PWD/../$$BUILD_DIR
OUT_PATH = $$BUILD_PATH/$$TARGET

TARGET = $$qtLibraryTarget($$TARGET)
message($$TARGET)

CONFIG(debug, debug|release) {
    BUILD_TYPE = debug
} else {
    BUILD_TYPE = release
}

DESTDIR = $$BUILD_PATH/bin/plugins
OBJECTS_DIR = $$OUT_PATH/$$BUILD_TYPE/.obj
MOC_DIR = $$OUT_PATH/$$BUILD_TYPE/.moc
RCC_DIR = $$OUT_PATH/$$BUILD_TYPE/.rcc
UI_DIR = $$OUT_PATH/$$BUILD_TYPE/.ui

contains(QMAKE_HOST.os,Windows) {
    contains(QT_ARCH, i386) {
        PLAT_FORM = x86
    } else {
        PLAT_FORM = x64
    }

    VERSION = 0.1.0.0
    QMAKE_TARGET_PRODUCT = $${TARGET}_$$PLAT_FORM
    QMAKE_TARGET_COMPANY = MK CO., LTD.
    QMAKE_TARGET_DESCRIPTION = $${TARGET}_V$${VERSION}
    QMAKE_TARGET_COPYRIGHT = Copyright 2020-2030 The MK Ltd.
    CONFIG += skip_target_version_ext
}else{

}
