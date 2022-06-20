#ifndef TX4_VIEW_H
#define TX4_VIEW_H

#include <QWidget>
#include <QMediaPlayer>
#include <QtMultimedia/QMediaPlaylist>
#include <QVideoWidget>
#include "../tx4_label.h"
#include "../util/tx4_util.h"
#include "../toolbar/tx4_toolbar_button.h"
#include "../tx4_event_preview.h"
#include "../tx4_event.h"
#include "tx4_control_bar.h"
#include "../tx4_defines.h"

class tx4_view : public QWidget {
	Q_OBJECT

	public:
		explicit tx4_view(QList<QFileInfo> clips, const QString &text, const int &index, const bool &selected = false, const bool &selectable = false, const bool &clickable = false, QWidget* parent = nullptr);
		virtual ~tx4_view();

		int i_viewIndex;
		void setViewState(bool selected);
		// void setFlipedVideo(bool flipped);

	protected:
		//virtual void mousePressEvent(QMouseEvent *e);
		virtual void mouseReleaseEvent(QMouseEvent *e);

	signals:
		void clicked();
		void selected();

	private:
		QMediaPlaylist *clipPlaylist;
		QMediaPlayer *w_player;
		QVideoWidget *w_playerVideoWidget;
		QList<QFileInfo> l_clipsList;
		QWidget *w_controlsWidget;
		QString s_viewText;
		tx4_label *l_viewLabel;
		bool b_controlsShown;
		bool b_viewSelectable;
		bool b_viewSelected;
		bool b_viewClickable;

		void initContents();
		void initPlayer();
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