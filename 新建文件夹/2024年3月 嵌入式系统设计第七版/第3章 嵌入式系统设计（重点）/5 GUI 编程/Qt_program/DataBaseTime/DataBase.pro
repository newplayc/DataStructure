#-------------------------------------------------
#
# Project created by QtCreator 2019-03-22T00:12:13
#
#-------------------------------------------------

QT       += core gui
QT += sql
greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = DataBase
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    sqliteset.cpp

HEADERS  += mainwindow.h \
    sqliteset.h

FORMS    += mainwindow.ui
