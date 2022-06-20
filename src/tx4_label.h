#ifndef TX4_LABEL_H
#define TX4_LABEL_H

#include <QtWidgets>
#include <QLabel>
#include "./util/tx4_util.h"
#include "./tx4_defines.h"

class tx4_label : public QLabel {
	Q_OBJECT

	public:
		explicit tx4_label(const QString &text, const int &size, const QString &style, const QFont::Weight &weight, const Qt::AlignmentFlag &alignH = Qt::AlignHCenter, const Qt::AlignmentFlag &alignV = Qt::AlignVCenter, const QString &font = "Gotham", const int &spacing = 0, const QString &tooltip = "", QWidget *parent = nullptr);
		virtual ~tx4_label(); // Segoe UI / Gotham

	public:
		QString labelText;
		void setLabelText(QString newText);
		void setLabelSize(int newSize);
		void setLabelStyle(QString newStyle);
		void setLabelWeight(QFont::Weight weight);
		void setLabelAlignment(Qt::AlignmentFlag alignH, Qt::AlignmentFlag alignV);

};

class tx4_selectable_label : public tx4_label {
	Q_OBJECT

	public:
		explicit tx4_selectable_label(const QString &text, const int &size, const QString &style, const QFont::Weight &weight, const Qt::AlignmentFlag &alignH = Qt::AlignHCenter, const Qt::AlignmentFlag &alignV = Qt::AlignVCenter, const QString &font = "Gotham", const int &spacing = 0, const QString &tooltip = "", QWidget *parent = nullptr);
		virtual ~tx4_selectable_label(); // Segoe UI / Gotham

	public:
		bool b_labelActive;
		bool b_labelHovered;
		bool b_labelSelected;
		void setLabelActive(bool active);

	protected:
		virtual void enterEvent(QEvent *e);
		virtual void leaveEvent(QEvent *e);
		virtual void mouseReleaseEvent(QMouseEvent *e);
};

class tx4_key_value_label : public QWidget {
	Q_OBJECT

	public:
		explicit tx4_key_value_label(const QString &key, const QString &value, const int &size, const QFont::Weight &weight, const Qt::AlignmentFlag &align, const bool &mouseEvents = false, const QString &font = "Gotham", QWidget *parent = nullptr);
		virtual ~tx4_key_value_label();

	public:
		QString keyText;
		QString valueText;
		QString keyStyle;
		QString valueStyle;
		tx4_label* l_keyLabel;
		tx4_label* l_valueLabel;
		bool m_acceptMouseEvents;
		//QString keyLabelStyle = "background-color: none; color: #ffffff;";
		//QString valueLabelNormalStyle = "background-color: none; color: #909090;";
		//QString valueLabelHoveredStyle = "background-color: none; color: #8b8b8b;";
		//QString valueLabelPressedStyle = "background-color: none; color: #666666;";

		void setKeyLabelText(QString newText);
		void setValueLabelText(QString newText);
		void setKeyLabelColor(QString newStyle);
		void setValueLabelColor(QString newStyle);

	protected:
		//bool event(QEvent *e) override;
		virtual void enterEvent(QEvent *e);
		virtual void leaveEvent(QEvent *e);
		virtual void mousePressEvent(QMouseEvent *e);
		virtual void mouseReleaseEvent(QMouseEvent *e);

	private:
		bool m_pressed;

		void initLayout();

};

#endif // TX4_LABEL_H