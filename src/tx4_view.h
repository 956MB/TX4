#ifndef TX4_VIEW_H
#define TX4_VIEW_H

#include <QWidget>
#include "tx4_label.h"
#include "tx4_util.h"
#include "tx4_toolbar_button.h"
#include "tx4_event_preview.h"
#include "tx4_event.h"
#include "tx4_control_bar.h"

#define VIEW_MIN_W 304
#define VIEW_MIN_H 171

class tx4_view : public QWidget {
	Q_OBJECT

	public:
		explicit tx4_view(QWidget* parent = nullptr);
		~tx4_view();

	//protected:
	//	virtual void resizeEvent(QResizeEvent *event) Q_DECL_OVERRIDE;
		//virtual int heightForWidth (int w) const Q_DECL_OVERRIDE { return w*9/16; };

	private:
		QWidget *w_clipWidget;
		QWidget *w_controlsWidget;
		tx4_control_bar *w_controlBar;

		QString viewerScreenStyle = "background-color: grey; border: none; outline: none;";
		QString blankStyle = "background-color: none; border: none; outline: none;";
		QString containerStyle = "background-color: black; border: none; outline: none;";
		QString blueStyle = "background-color: blue; border: none; outline: none;";

		void initContents();

};


class AspectRatioWidget : public QWidget {
	Q_OBJECT

	public:
		AspectRatioWidget(QWidget *widget, float width, float height, QWidget *parent = 0);
		void resizeEvent(QResizeEvent *event);

	private:
		QBoxLayout *layout;
		float arWidth; // aspect ratio width
		float arHeight; // aspect ratio height

};

#endif // TX4_VIEW_H