#-------------------------------------------------
#
# Project created by QtCreator 2012-04-10T20:45:52
# on a PPC in Wales uk.. so leets have fun aabd add credidz.. et all
#
#-------------------------------------------------

QT       += core gui script network

TARGET = fgx-installer
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    releases/releaseswidget.cpp \
    info/machineinfowidget.cpp \
    releases/releaseeditdialog.cpp \
    xobjects/xsettings.cpp \
    xobjects/servercall.cpp \
    xwidgets/xstatusbar.cpp \
    aircraft/aircrafttreewidget.cpp \
    download/downloadmanagerwidget.cpp

HEADERS  += mainwindow.h \
    releases/releaseswidget.h \
    info/machineinfowidget.h \
    releases/releaseeditdialog.h \
    xobjects/xsettings.h \
    xobjects/servercall.h \
    xwidgets/xstatusbar.h \
    aircraft/aircrafttreewidget.h \
    download/downloadmanagerwidget.h

RESOURCES += \
    resource/icons.qrc
