#ifndef TX4_TOOLBAR_BUTTON_H
#define TX4_TOOLBAR_BUTTON_H

#include <qpushbutton.h>
#include "tx4_label.h"
#include "tx4_util.h"

class tx4_toolbar_button : public QWidget {
	Q_OBJECT

	public:
		tx4_toolbar_button(const QString &text, const bool &enabled, const QString &tooltip, const QString &extraLeft = "*", const QString &extraRight = "*", const int &lrpadding = 18, QWidget *parent = nullptr);
		~tx4_toolbar_button();

		bool s_enabled;

		void setButtonState(bool state);
		void setButtonText(QString text);

	signals:
		void clicked();

	protected:
		//bool event(QEvent *e) override;
		virtual void enterEvent(QEvent *e);
		virtual void leaveEvent(QEvent *e);
		virtual void mousePressEvent(QMouseEvent *e);
		virtual void mouseReleaseEvent(QMouseEvent *e);

	private:
		tx4_label *buttonLabel;
		QString buttonText;
		QString extraTextLeft;
		QString extraTextRight;
		int padding;
		bool m_pressed;

		QString extraLabelStyle = "background-color: none; border: none; outline: none; color: rgba(255,255,255,70);";
		QString buttonLabelStyle = "background-color: none; border: none; outline: none; color: white;";
		QString buttonLabelStyleDisabled = "background-color: none; border: none; outline: none; color: rgba(255,255,255,100);";
		QString toolbarButtonStyleNormal = "background-color: rgba(255,255,255,35); border: none; outline: none;";
		QString toolbarButtonStyleHover = "background-color: rgba(255,255,255,45); border: 1px solid rgba(255,255,255,200); outline: none;";
		QString toolbarButtonStylePress = "background-color: rgba(255,255,255,35); border: 1px solid rgba(255,255,255,170); outline: none;";
		QString toolbarButtonStyleDisabled = "background-color: rgba(255,255,255,10); border: none; outline: none;";
		
		void initContents();
};

#endif // TX4_TOOLBAR_BUTTON_H