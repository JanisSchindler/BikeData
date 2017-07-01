#-------------------------------------------------
#
# Project created by QtCreator 2017-07-01T15:14:34
#
#-------------------------------------------------

QT       += core gui xml

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = BikeData
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    Model/rider.cpp \
    Model/tour.cpp

HEADERS  += mainwindow.h \
    Model/tour.h \
    Model/rider.h \
    Model/ipersistence.h \
    Model/imodelelement.h

FORMS    += mainwindow.ui
