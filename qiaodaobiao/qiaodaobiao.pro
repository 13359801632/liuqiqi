#-------------------------------------------------
#
# Project created by QtCreator 2020-02-06T16:35:20
#
#-------------------------------------------------

QT       += core gui sql

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = qiaodaobiao
TEMPLATE = app


SOURCES += main.cpp\
        widget.cpp \
    person.cpp \
    denglu.cpp

HEADERS  += widget.h \
    person.h \
    denglu.h

FORMS    += widget.ui \
    person.ui \
    denglu.ui

RESOURCES += \
    qwe.qrc \
    resource/qwe.qrc
