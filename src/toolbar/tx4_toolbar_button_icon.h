#ifndef TX4_TOOLBAR_BUTTON_ICON_H
#define TX4_TOOLBAR_BUTTON_ICON_H

#include <qpushbutton.h>
#include "../tx4_label.h"
#include "tx4_toolbar_button.h"
#include "../util/tx4_util.h"
#include "../tx4_defines.h"

class tx4_toolbar_button_icon : public QWidget {
	Q_OBJECT

	public:
		tx4_toolbar_button_icon(const QString &icon, const ButtonState &state, const QString &tooltip, const int &index, const bool &useText = false, QWidget *parent = nullptr);
		virtual ~tx4_toolbar_button_icon();

		ButtonState s_state;
		bool b_buttonDisabled;

		void setButtonState(ButtonState state);
		void updateInnerText(int text);
		void repaintIconPixmap(bool disabled);

	signals:
		void clicked(int idx);

	protected:
		//bool event(QEvent *e) override;
		virtual void enterEvent(QEvent *e);
		virtual void leaveEvent(QEvent *e);
		virtual void mousePressEvent(QMouseEvent *e);
		virtual void mouseReleaseEvent(QMouseEvent *e);

	private:
		tx4_label *l_buttonInnerLabel;
		QWidget *w_innerLabel;
		QLabel *w_buttonIcon;
		QPixmap p_iconPixmap;
		QString s_buttonIcon;
		QString s_buttonInnerText;
		int i_buttonIndex;
		bool b_pressed;
		bool b_useText;
		bool b_iconPixmapSet;
		
		void initContents();
};

#endif // TX4_TOOLBAR_BUTTON_ICON_H