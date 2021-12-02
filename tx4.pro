
QT += core gui widgets multimedia

win32:QT += winextras

TARGET = tx4

include($$PWD/QGoodWindow/QGoodWindow.pri)

CONFIG += c++17

SOURCES += \
    /src/main.cpp \
    /src/phot.cpp

HEADERS += \
    /src/phot.h

TRANSLATIONS += /locale/tx4_en.ts \
                /locale/tx4_fi.ts \
                /locale/tx4_ko.ts

qgoodwindow {
SOURCES += \
    /src/captionbutton.cpp \
    /src/iconwidget.cpp \
    /src/titlebar.cpp \
    /src/titlewidget.cpp

HEADERS += \
    /src/captionbutton.h \
    /src/iconwidget.h \
    /src/titlebar.h \
    /src/titlewidget.h

RESOURCES += \
    res.qrc
}
