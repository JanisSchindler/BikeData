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
    Model/tour.cpp \
    Model/manager.cpp \
    Model/imodelelement.cpp \
    UI/riders.cpp \
    UI/tours.cpp \
    UI/idqwidgetlistitem.cpp \
    Model/duration.cpp

HEADERS  += mainwindow.h \
    Model/tour.h \
    Model/rider.h \
    Model/ipersistence.h \
    Model/imodelelement.h \
    Model/manager.h \
    UI/riders.h \
    UI/tours.h \
    UI/idqwidgetlistitem.h \
    Model/duration.h

FORMS    += mainwindow.ui \
    riders.ui \
    tours.ui
