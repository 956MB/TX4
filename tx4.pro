
QT += core gui widgets multimedia

win32:QT += winextras

include($$PWD/QGoodWindow/QGoodWindow.pri)

CONFIG += c++11

SOURCES += \
    main.cpp \
    phot.cpp

HEADERS += \
    phot.h

TRANSLATIONS += /locale/tx4_en.ts \
                /locale/tx4_fi.ts \
                /locale/tx4_ko.ts

qgoodwindow {
SOURCES += \
    captionbutton.cpp \
    iconwidget.cpp \
    titlebar.cpp \
    titlewidget.cpp

HEADERS += \
    captionbutton.h \
    iconwidget.h \
    titlebar.h \
    titlewidget.h

RESOURCES += \
    res.qrc
}
