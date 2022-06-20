#ifndef TX4_TOOLBAR_BUTTON_H
#define TX4_TOOLBAR_BUTTON_H

#include <qpushbutton.h>
#include "../tx4_label.h"
#include "../util/tx4_util.h"
#include "../tx4_defines.h"

class tx4_toolbar_button : public QWidget {
	Q_OBJECT

	public:
		tx4_toolbar_button(const QString &text, const ButtonState &state, const QString &tooltip, const int &index, const int &lrpadding = 19, QWidget *parent = nullptr);
		virtual ~tx4_toolbar_button();

		ButtonState s_state;

		void setButtonState(ButtonState state);
		void setButtonText(QString text);
		void updateInnerText(int text);

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
		QWidget *innerButton;
		tx4_label *buttonLabel;
		QString buttonText;
		QString s_buttonInnerText;
		int padding;
		int i_buttonIndex;
		bool m_pressed;
		
		void initContents();
};

#endif // TX4_TOOLBAR_BUTTON_H