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
		QString barStyleHover = "background-color: rgba(70,70,70,245); border-left: 3px solid rgba(255,255,255,50); border-top: 0px solid rgba(255,255,255,50); border-right: 3px solid rgba(255,255,255,50); border-bottom: 3px solid rgba(255,255,255,50); outline: none;";
		QString barStyleHoverTop = "background-color: rgba(70,70,70,245); border-left: 3px solid rgba(255,255,255,50); border-top: 3px solid rgba(255,255,255,50); border-right: 3px solid rgba(255,255,255,50); border-bottom: 0px solid rgba(255,255,255,50); outline: none;";
		QString barStyleHover_SelectMode = "background-color: rgba(70,70,70,255); border-left: 3px solid rgba(255,255,255,160); border-top: 0px solid rgba(255,255,255,160); border-right: 3px solid rgba(255,255,255,160); border-bottom: 3px solid rgba(255,255,255,160); outline: none;";
		QString barStyleHover_SelectModeTop = "background-color: rgba(70,70,70,255); border-left: 3px solid rgba(255,255,255,160); border-top: 3px solid rgba(255,255,255,160); border-right: 3px solid rgba(255,255,255,160); border-bottom: 0px solid rgba(255,255,255,160); outline: none;";
		QString barTextStyle = "background-color: none; border: none; outline: none; color: rgba(255,255,255,220)";
		QString braceStyle = "background-color: none; border: none; outline: none; color: rgba(255,255,255,120)";

		void setHoverStyle(bool top);
		void setSelectedStyle(bool top);

};

#endif // TX4_PREVIEW_BAR_H