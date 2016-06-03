#-------------------------------------------------
#
# Project created by QtCreator 2016-05-23T16:00:46
#
#-------------------------------------------------

QT       += core gui sql webkit

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = aies
TEMPLATE = app

target.path = /home/pi

INSTALLS += target

SOURCES += main.cpp\
        fihm.cpp \
    cbdd.cpp \
    ccapteur.cpp

HEADERS  += fihm.h \
    cbdd.h \
    ccapteur.h

FORMS    += fihm.ui

LIBS += -L/usr/local/lib -lwiringPi

