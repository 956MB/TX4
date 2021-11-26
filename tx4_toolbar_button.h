#ifndef TX4_TOOLBAR_BUTTON_H
#define TX4_TOOLBAR_BUTTON_H

#include <qpushbutton.h>
#include "tx4_label.h"
#include "tx4_util.h"

class tx4_toolbar_button : public QWidget {
	Q_OBJECT

	public:
		tx4_toolbar_button(const QString &text, const bool &enabled, const QString &tooltip, QWidget *parent = nullptr);
		~tx4_toolbar_button();

		void setButtonState(bool state);

	signals:
		void clicked();

	protected:
		//bool event(QEvent *e) override;
		virtual void enterEvent(QEvent *e);
		virtual void leaveEvent(QEvent *e);
		//virtual void mousePressEvent(QMouseEvent *e);
		virtual void mouseReleaseEvent(QMouseEvent *e);

	private:
		tx4_label *buttonLabel;
		bool s_enabled;
		QString buttonText;

		QString extraLabelStyle = "background-color: none; border: none; outline: none; color: rgba(255,255,255,70);";
		QString buttonLabelStyle = "background-color: none; border: none; outline: none; color: white;";
		QString buttonLabelStyleDisabled = "background-color: none; border: none; outline: none; color: rgba(255,255,255,100);";
		QString toolbarButtonStyleNormal = "background-color: rgba(255,255,255,35); border: none; outline: none;";
		QString toolbarButtonStyleHover = "background-color: rgba(255,255,255,50); border: 2px solid white; outline: none;";
		QString toolbarButtonStyleDisabled = "background-color: rgba(255,255,255,10); border: none; outline: none;";
		
		void initContents();
};

#endif // TX4_TOOLBAR_BUTTON_H