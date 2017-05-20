#-------------------------------------------------
#
# Project created by QtCreator 2017-04-18T02:33:43
#
#-------------------------------------------------

QT       += core gui
QT       += serialport

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = ARINC_825
TEMPLATE = app

# The following define makes your compiler emit warnings if you use
# any feature of Qt which as been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0


SOURCES += main.cpp\
        mainwindow.cpp \
    serialconfigbox.cpp \
    receivebox.cpp \
    arinc_msg_composer.cpp \
    transmitbox.cpp \
    socket.cpp \
    profile.cpp

HEADERS  += mainwindow.h \
    a825.h \
    serialconfigbox.h \
    receivebox.h \
    arinc_msg_composer.h \
    transmitbox.h \
    socket.h \
    profile.h

FORMS    += mainwindow.ui \
    serialconfigbox.ui \
    receivebox.ui \
    arinc_msg_composer.ui \
    transmitbox.ui

DISTFILES += \
    profile.json
