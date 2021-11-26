#ifndef TX4_NAV_BUTTON_H
#define TX4_NAV_BUTTON_H

#include <qpushbutton.h>
#include "tx4_label.h"
#include "tx4_util.h"

class tx4_nav_button : public QPushButton {
	Q_OBJECT

	public:
		tx4_nav_button(const QString &text, const bool &enabled, const QString &tooltip, const bool &left, QWidget *parent = nullptr);
		~tx4_nav_button();

		void setButtonState(bool state);

	signals:
		void buttonClicked();

	protected:
		//bool event(QEvent *e) override;
		virtual void enterEvent(QEvent *e);
		virtual void leaveEvent(QEvent *e);
		//virtual void mousePressEvent(QMouseEvent *e);
		virtual void mouseReleaseEvent(QMouseEvent *e);

	private:
		//tx4_label *buttonLabel;
		bool s_enabled;
		QString buttonText;
		//QWidget *buttonBar;
		QIcon *normalIcon;
		QIcon *hoverIcon;
		QIcon *rightIcon;

		QString extraLabelStyle = "background-color: none; border: none; outline: none; color: rgba(255,255,255,70);";
		QString buttonLabelStyle = "background-color: none; border: none; outline: none; color: white;";
		QString buttonLabelStyleDisabled = "background-color: none; border: none; outline: none; color: rgba(255,255,255,100);";
		QString barStyleNormal = "background-color: rgba(255,255,255,50); border: none; outline: none;";
		QString navButtonStyleNormal = "background-color: #222222; border: none; outline: none;";
		QString navButtonStyleHover = "background-color: #4e4e4e; border: none; outline: none;";
		QString navButtonStyleDisabled = "background-color: #222222; border: none; outline: none;";
		
		void initContents();
};

#endif // TX4_NAV_BUTTON_H