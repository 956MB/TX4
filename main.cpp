

#include "tx4.h"
#include <QApplication>
#include <iostream>
#include <qdebug.h>
#include <QTranslator>

int main(int argc, char *argv[]) {
    QApplication::setAttribute(Qt::AA_EnableHighDpiScaling);
    QApplication a(argc, argv);
    
    QTranslator translator;
    //translator.load(":/locale/tx4_ko.ts");
    if (translator.load(":/locale/tx4_ko")) {
        a.installTranslator(&translator);
    }
    //if (translator.load(QLocale(), QLatin1String("tx4"), QLatin1String("_"), QLatin1String(":/locale"))) {
    //    a.installTranslator(&translator);
    //}

	QString appStylesheet =
            //"QToolTip { background-color: #292929; background-clip: border; color:white; padding:3px; border-width:2px; border-color: #292929; border-style:solid; border-radius:3px }"
            "QScrollBar:horizontal"
            "{"
            "    height: 12px;"
            "    margin: 5px 0px 5px 0px;"
            "    border: 1px transparent #2A2929;"
            "    border-radius: 5px;"
            "    background-color: none;    /* #2A2929; */"
            "}"
            "QScrollBar::handle:horizontal"
            "{"
            "    background-color: rgba(255,255,255,60);      /* #605F5F; */"
            "    min-width: 2px;"
            "    border-radius: 5px;"
            "}"
            "QScrollBar::add-line:horizontal"
            "{"
            "    margin: 0px 3px 0px 3px;"
            "    border-image: url(:/qss_icons/rc/right_arrow_disabled.png);"
            "    width: 10px;"
            "    height: 10px;"
            "    subcontrol-position: right;"
            "    subcontrol-origin: margin;"
            "}"
            "QScrollBar::sub-line:horizontal"
            "{"
            "    margin: 0px 3px 0px 3px;"
            "    border-image: url(:/qss_icons/rc/left_arrow_disabled.png);"
            "    height: 10px;"
            "    width: 10px;"
            "    subcontrol-position: left;"
            "    subcontrol-origin: margin;"
            "}"
            "QScrollBar::add-line:horizontal:hover,QScrollBar::add-line:horizontal:on"
            "{"
            "    border-image: url(:/qss_icons/rc/right_arrow.png);"
            "    height: 10px;"
            "    width: 10px;"
            "    subcontrol-position: right;"
            "    subcontrol-origin: margin;"
            "}"
            "QScrollBar::sub-line:horizontal:hover, QScrollBar::sub-line:horizontal:on"
            "{"
            "    border-image: url(:/qss_icons/rc/left_arrow.png);"
            "    height: 10px;"
            "    width: 10px;"
            "    subcontrol-position: left;"
            "    subcontrol-origin: margin;"
            "}"
            "QScrollBar::up-arrow:horizontal, QScrollBar::down-arrow:horizontal"
            "{"
            "    background: none;"
            "}"
            "QScrollBar::add-page:horizontal, QScrollBar::sub-page:horizontal"
            "{"
            "    background: none;"
            "}"
            "QScrollBar:vertical"
            "{"
            "    background-color: #2A2929;"
            "    width: 15px;"
            "    margin: 15px 3px 15px 3px;"
            "    border: 1px transparent #2A2929;"
            "    border-radius: 4px;"
            "}"
            "QScrollBar::handle:vertical"
            "{"
            "    background-color: red;         /* #605F5F; */"
            "    min-height: 5px;"
            "    border-radius: 4px;"
            "}"
            "QScrollBar::sub-line:vertical"
            "{"
            "    margin: 3px 0px 3px 0px;"
            "    border-image: url(:/qss_icons/rc/up_arrow_disabled.png);"
            "    height: 10px;"
            "    width: 10px;"
            "    subcontrol-position: top;"
            "    subcontrol-origin: margin;"
            "}"
            "QScrollBar::add-line:vertical"
            "{"
            "    margin: 3px 0px 3px 0px;"
            "    border-image: url(:/qss_icons/rc/down_arrow_disabled.png);"
            "    height: 10px;"
            "    width: 10px;"
            "    subcontrol-position: bottom;"
            "    subcontrol-origin: margin;"
            "}"
            "QScrollBar::sub-line:vertical:hover,QScrollBar::sub-line:vertical:on"
            "{"
            "    border-image: url(:/qss_icons/rc/up_arrow.png);"
            "    height: 10px;"
            "    width: 10px;"
            "    subcontrol-position: top;"
            "    subcontrol-origin: margin;"
            "}"
            "QScrollBar::add-line:vertical:hover, QScrollBar::add-line:vertical:on"
            "{"
            "    border-image: url(:/qss_icons/rc/down_arrow.png);"
            "    height: 10px;"
            "    width: 10px;"
            "    subcontrol-position: bottom;"
            "    subcontrol-origin: margin;"
            "}"
            "QScrollBar::up-arrow:vertical, QScrollBar::down-arrow:vertical"
            "{"
            "    background: none;"
            "}"
            "QScrollBar::add-page:vertical, QScrollBar::sub-page:vertical"
            "{"
            "    background: none;"
            "}";
	//a.setStyleSheet("QToolTip { background-color: #292929; background-clip: border; color:white; padding:3px; border-width:2px; border-color: #292929; border-style:solid; border-radius:3px }");
	a.setStyleSheet(appStylesheet);

    tx4 w;
	w.show();

	return a.exec();
}
