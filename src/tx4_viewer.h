#ifndef TX4_VIEWER_H
#define TX4_VIEWER_H

#include <QWidget>
#include "tx4_label.h"
#include "tx4_util.h"
#include "tx4_toolbar_button.h"
#include "tx4_event_preview.h"
#include "tx4_event.h"
#include "tx4_view.h"
#include "tx4_control_bar.h"

#define VIEW_MIN_W 304
#define VIEW_MIN_H 171

class tx4_viewer : public QWidget {
	Q_OBJECT

	public:
		explicit tx4_viewer(QWidget* parent = nullptr);
		~tx4_viewer();

	private:
		QWidget *w_viewsContainer;
		tx4_control_bar *w_controlBar;

		QString viewerScreenStyle = "background-color: black; border: none; outline: none;";
		QString blankStyle = "background-color: none; border: none; outline: none;";
		QString outerContainerStyle = "background-color: #141414; border: none; outline: none;";
		QString horContainerStyle = "background-color: black; border: none; outline: none;";
		QString viewStyle = "background-color: grey; border: none; outline: none;";
		QString greenStyle = "background-color: green; border: none; outline: none;";
		QString controlBarBodyStyle = "background-color: rgba(255,255,255,15); border: none; outline: none;";

		void initContents();
		void initViews();
		void initControlBar();

};

#endif // TX4_VIEWER_H