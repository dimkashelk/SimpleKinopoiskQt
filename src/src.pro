QT       += core gui sql

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    cinemacard.cpp \
    cinemagenrecard.cpp \
    clickableqtextedit.cpp \
    clickedqlabel.cpp \
    main.cpp \
    mainwindow.cpp \
    newscard.cpp \
    soapoperacard.cpp

HEADERS += \
    cinemacard.h \
    cinemagenrecard.h \
    clickableqtextedit.h \
    clickedqlabel.h \
    mainwindow.h \
    newscard.h \
    soapoperacard.h

FORMS += \
    cinemacard.ui \
    cinemagenrecard.ui \
    mainwindow.ui \
    newscard.ui \
    soapoperacard.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

DISTFILES += \
    home.png
