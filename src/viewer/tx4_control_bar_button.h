#ifndef TX4_CONTROL_BAR_BUTTON_H
#define TX4_CONTROL_BAR_BUTTON_H

#include <qpushbutton.h>
#include "../tx4_label.h"
#include "../util/tx4_util.h"
#include "../tx4_defines.h"

class tx4_control_bar_button : public QWidget {
	Q_OBJECT

	friend class tx4_control_bar_button_toggle;

	public:
		tx4_control_bar_button(const QString &icon, const ButtonState &state, const QString &tooltip, const int &index, const bool &shrink = false, QWidget *parent = nullptr);
		virtual ~tx4_control_bar_button();

		ButtonState s_state;
		bool b_buttonDisabled;

		void setButtonState(ButtonState state);
		void updateButtonIcon(QString newIcon);
		void repaintIconPixmap();

	signals:
		void clicked(int idx);

	protected:
		virtual void mousePressEvent(QMouseEvent *e);
		virtual void mouseReleaseEvent(QMouseEvent *e);

	private:
		QLabel *w_buttonIcon;
		QPixmap p_iconPixmap;
		QString s_buttonIcon;
		int i_buttonIndex;
		bool b_pressed;
		bool b_iconShrink;
		bool b_iconPixmapSet;
		
		void initContents();
};

class tx4_control_bar_button_toggle : public tx4_control_bar_button {
	Q_OBJECT

	public:
		tx4_control_bar_button_toggle(const QString &icon1 , const QString &icon2 , const ButtonState &state , const QString &tooltip, const int &index, const bool &shrink = false);
		virtual ~tx4_control_bar_button_toggle();

	protected:
		//virtual void mousePressEvent(QMouseEvent *e);
		virtual void mouseReleaseEvent(QMouseEvent *e);

	private:
		QString s_icon1;
		QString s_icon2;
		QString s_useIcon;
		bool b_buttonToggled;

		void toggleButton();
};

#endif // TX4_CONTROL_BAR_BUTTON_H