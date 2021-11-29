#ifndef TX4_PREVIEW_BAR_H
#define TX4_PREVIEW_BAR_H

#include <QtWidgets>
#include <QLabel>
#include "tx4_label.h"
#include "tx4_util.h"

#define BAR_H 25

class tx4_preview_bar : public QWidget {
	Q_OBJECT

	public:
		explicit tx4_preview_bar(const QString &date, const QString &loc, const QString &size, const QString &length, const QString &loc_style, const QString &meta, const bool &top, QWidget *parent = nullptr);
		~tx4_preview_bar();

	public:
		tx4_label *dateText;
		tx4_label *locText;
		tx4_label *sizeText;
		tx4_label *lengthText;
		tx4_label *topText;

		QString barStyleNormal = "background-color: rgba(70,70,70,245); border: none; outline: none;";
		QString barStyleHover = "background-color: rgba(70,70,70,245); border-left: 2px solid #8f8f8f; border-top: 0px solid #8f8f8f; border-right: 2px solid #8f8f8f; border-bottom: 2px solid #8f8f8f; outline: none;";
		QString barStyleHoverTop = "background-color: rgba(70,70,70,245); border-left: 2px solid #8f8f8f; border-top: 2px solid #8f8f8f; border-right: 2px solid #8f8f8f; border-bottom: 0px solid #8f8f8f; outline: none;";
		QString queue_barStyleHoverTop = "background-color: rgba(70,70,70,245); border-left: 2px solid #f6ed19; border-top: 2px solid #f6ed19; border-right: 2px solid #f6ed19; border-bottom: 0px solid #f6ed19; outline: none;";
		QString barStyleHover_SelectMode = "background-color: rgba(70,70,70,255); border-left: 2px solid #f6f6f6; border-top: 0px solid #f6f6f6; border-right: 2px solid #f6f6f6; border-bottom: 2px solid #f6f6f6; outline: none;";
		QString barStyleHover_SelectModeTop = "background-color: rgba(70,70,70,255); border-left: 2px solid #f6f6f6; border-top: 2px solid #f6f6f6; border-right: 2px solid #f6f6f6; border-bottom: 0px solid #f6f6f6; outline: none;";
		QString barTextStyle = "background-color: none; border: none; outline: none; color: rgba(255,255,255,220)";
		QString braceStyle = "background-color: none; border: none; outline: none; color: rgba(255,255,255,120)";

		void setHoverStyle(bool top, QString topStyle);
		void setSelectedStyle(bool top);
		void setTextStylesheet(QString setStyle);

};

#endif // TX4_PREVIEW_BAR_H