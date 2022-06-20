#ifndef TX4_PREVIEW_BAR_H
#define TX4_PREVIEW_BAR_H

#include <QtWidgets>
#include <QLabel>
#include "tx4_label.h"
#include "./util/tx4_util.h"
#include "./tx4_defines.h"

class tx4_preview_bar : public QWidget {
	Q_OBJECT

	public:
		explicit tx4_preview_bar(const QString &date, const QString &loc, const QString &size, const QString &length, const QString &meta, const bool &top, QWidget *parent = nullptr);
		virtual ~tx4_preview_bar();

	public:
		tx4_label *dateText;
		tx4_label *locText;
		tx4_label *sizeText;
		tx4_label *lengthText;
		tx4_label *topText;

		void setHoverStyle(bool top, QString topStyle);
		void setSelectedStyle(bool top);
		void setTextStylesheet(QString setStyle);
};

#endif // TX4_PREVIEW_BAR_H