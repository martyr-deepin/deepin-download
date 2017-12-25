#-------------------------------------------------
#
# Project created by QtCreator 2017-11-06T09:51:23
#
#-------------------------------------------------

QT += core
QT += widgets
QT += gui
QT += network
QT += x11extras
QT += dbus
QT += svg
QT += sql



#greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = deepin-download
TEMPLATE = app
RESOURCES = deepin_download.qrc
CONFIG += link_pkgconfig
CONFIG += c++11
PKGCONFIG += dtkwidget
PKGCONFIG += xcb xcb-util

QMAKE_CXXFLAGS += -g
LIBS += -lX11 -lXext -lXtst
# The following define makes your compiler emit warnings if you use
# any feature of Qt which as been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
#DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

##########################################################################################################

SOURCES += \
        main.cpp \
        mainwindow.cpp \
    downlistview.cpp \
    base64.cpp \
    aria2crpcmsg.cpp \
    gcjsonrpc.cpp \
    newdown.cpp \
    gcmenubar.cpp \
    gctoolbar.cpp \
    gcsystemtrayicon.cpp \
    gcstatusbar.cpp \
    gcslidebar.cpp \
    sqlitefunt.cpp \
    configdlg.cpp \
    aboutdlg.cpp \
    mwm.cpp \
    gctooltips.cpp \
    gcthread.cpp \
    interfaceadaptor.cpp \
    utils.cpp \
    slideitem.cpp \
    slidebar.cpp \
    toolbar.cpp


HEADERS += \
        mainwindow.h \
    downrecord.h \
    downlistview.h \
    base64.h \
    aria2crpcmsg.h \
    gcjsonrpc.h \
    optionstruct.h \
    newdown.h \
    gcmenubar.h \
    gctoolbar.h \
    gcsystemtrayicon.h \
    gcstatusbar.h \
    gcslidebar.h \
    sqlitefunt.h \
    configdlg.h \
    aboutdlg.h \
    mwm.h \
    gctooltips.h \
    gcthread.h \
    interfaceadaptor.h \
    utils.h \
    slideitem.h \
    slidebar.h \
    toolbar.h

##########################################################################################################

#多国语言翻译

TRANSLATIONS += translations/deepin-download.ts

##########################################################################################################

#安装桌面快捷方式 、图标

isEmpty(PREFIX){
    PREFIX = /usr
}

target.path = $${PREFIX}/bin

icon.path = $$PREFIX/share/icons/hicolor/scalable/apps

icon.files = $$PWD/Resources/images/deepin-download.svg

#安装desktop文件

desktop.path = $$PREFIX/share/applications

desktop.files = $$PWD/deepin-download.desktop

translations.path = $${PREFIX}/share/$${TARGET}/translations
translations.files = $$PWD/translations/*.qm

# Automating generation .qm files from .ts files
!system(python $$PWD/tool/translate_generation.py $$PWD): error("Failed to generate translation")


INSTALLS += target icon desktop translations
