#-------------------------------------------------
#
# Project created by QtCreator 2018-09-07T00:25:14
#
#-------------------------------------------------

QT          += core gui
QT          += sql
QT          += core gui network
QT          += network

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = ARK
TEMPLATE = app

# The following define makes your compiler emit warnings if you use
# any feature of Qt which has been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0


SOURCES += \
        main.cpp \
        mainwindow.cpp \
    newdoc.cpp \
    archivesdoc.cpp \
    outbound.cpp \
    inventory.cpp \
    statistical.cpp \
    usermanagement.cpp \
    organizationmangement.cpp \
    fileexport.cpp \
    cd.cpp \
    mysqlite.cpp \
    server.cpp \
    serverthread.cpp \
    mysocket.cpp

HEADERS += \
        mainwindow.h \
    newdoc.h \
    archivesdoc.h \
    outbound.h \
    inventory.h \
    statistical.h \
    usermanagement.h \
    organizationmangement.h \
    fileexport.h \
    cd.h \
    mysqlite.h \
    server.h \
    serverthread.h \
    mysocket.h

FORMS += \
        mainwindow.ui \
    newdoc.ui \
    archivesdoc.ui \
    outbound.ui \
    inventory.ui \
    statistical.ui \
    usermanagement.ui \
    organizationmangement.ui \
    fileexport.ui \
    cd.ui

DISTFILES += \
    ico.rc
RC_FILE += ico.rc


