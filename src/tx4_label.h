#ifndef TX4_LABEL_H
#define TX4_LABEL_H

#include <QtWidgets>
#include <QLabel>
#include "tx4_util.h"

class tx4_label : public QLabel {
	Q_OBJECT

	public:
		explicit tx4_label(const QString &text, const int &size, const QString &style, const QFont::Weight &weight, const Qt::AlignmentFlag &align, const QString &font = "Anonymous Pro", QWidget *parent = nullptr);
		~tx4_label();

	public:
		QString labelText;
		void setLabelText(QString newText);
		void setLabelColor(QString newStyle);

};

class tx4_key_value_label : public QWidget {
	Q_OBJECT

	public:
		explicit tx4_key_value_label(const QString &key, const QString &value, const int &size, const QString &key_style, const QString &value_style, const QFont::Weight &weight, const Qt::AlignmentFlag &align, const QString &font = "Anonymous Pro", QWidget *parent = nullptr);
		~tx4_key_value_label();

	public:
		QString keyText;
		QString valueText;
		QString keyStyle;
		QString valueStyle;
		tx4_label* l_keyLabel;
		tx4_label* l_valueLabel;

		void setKeyLabelText(QString newText);
		void setValueLabelText(QString newText);
		void setKeyLabelColor(QString newStyle);
		void setValueLabelColor(QString newStyle);

	private:
		QString labelStyle = "background-color: none; color: rgba(255,255,255,255);";
		QString braceStyle = "background-color: none; color: rgba(255,255,255,78);";

		void initLayout();

};

#endif // TX4_LABEL_H