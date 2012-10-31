#-------------------------------------------------
#
# Project created by QtCreator 2012-10-29T17:25:05
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = TextLocoViewer
TEMPLATE = app

LIBS += /usr/local/lib/libopencv_core.so

SOURCES += main.cpp\
        tileviewer.cpp\
        handler.cpp \
    lcmthread.cpp \
    clickablegraphicsview.cpp

HEADERS  += tileviewer.h\
        handler.h \
    lcmthread.h \
    clickablegraphicsview.h

FORMS    += tileviewer.ui

INCLUDEPATH += /usr/local/include

unix {
   CONFIG += link_pkgconfig
   PKGCONFIG += lcm
   PKGCONFIG += opencv
}
