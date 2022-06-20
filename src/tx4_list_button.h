#ifndef TX4_LIST_BUTTON_H
#define TX4_LIST_BUTTON_H

#include <qpushbutton.h>
#include "tx4_label.h"
#include "tx4_event.h"
#include "./toolbar/tx4_toolbar_button.h"
#include "./util/tx4_util.h"
#include "./tx4_defines.h"

class tx4_list_button : public QWidget {
	Q_OBJECT

	public:
		tx4_list_button(const ButtonState &state, const QString &iconSelect, const QString &iconDeselect, const QString &tooltip, const int &index, QWidget *parent = nullptr);
		virtual ~tx4_list_button();

		ButtonState s_state;
		bool b_buttonDisabled;
		bool b_parentHovered;

		void setButtonState(ButtonState state);
		//void updateInnerText(int text);
		//void repaintIconPixmap(bool disabled);

	signals:
		void clicked(int idx);

	protected:
		//bool event(QEvent *e) override;
		virtual void enterEvent(QEvent *e);
		virtual void leaveEvent(QEvent *e);
		virtual void mousePressEvent(QMouseEvent *e);
		virtual void mouseReleaseEvent(QMouseEvent *e);

	private:
		QStackedWidget *w_iconsStackWidget;
		QLabel *w_buttonIconSelect;
		QLabel *w_buttonIconDeselect;
		tx4_label *w_buttonInnerText;
		QString s_buttonIconSelect;
		QString s_buttonIconDeselect;
		QString s_buttonInnerText;
		int i_buttonIndex;
		bool b_pressed;
		bool b_useText;
		bool b_iconPixmapsSet;
		
		void initContents();
};

#endif // TX4_LIST_BUTTON_H