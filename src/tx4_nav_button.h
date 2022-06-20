#ifndef TX4_NAV_BUTTON_H
#define TX4_NAV_BUTTON_H

#include <qpushbutton.h>
#include "tx4_label.h"
#include "./util/tx4_util.h"
#include "./tx4_defines.h"

class tx4_nav_button : public QPushButton {
	Q_OBJECT

	public:
		tx4_nav_button(const QString &text, const bool &enabled, const QString &tooltip, const bool &left, QWidget *parent = nullptr);
		virtual ~tx4_nav_button();

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
		
		void initContents();
};

#endif // TX4_NAV_BUTTON_H