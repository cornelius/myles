QT += core gui webkitwidgets widgets

TARGET = Myles
TEMPLATE = app

SOURCES += main.cpp mainwindow.cpp \
    bucketlist.cpp \
    webserver.cpp \
    bucketlistitem.cpp \
    model.cpp

HEADERS += mainwindow.h \
    bucketlist.h \
    webserver.h \
    bucketlistitem.h \
    model.h

RESOURCES += \
    myles.qrc
