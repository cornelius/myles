QT += core gui webkit

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = Myles
TEMPLATE = app

SOURCES += main.cpp mainwindow.cpp \
    bucketlist.cpp \
    webserver.cpp

HEADERS += mainwindow.h \
    bucketlist.h \
    webserver.h
