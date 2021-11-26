
#ifndef TX4_H
#define TX4_H

#include <QGoodWindow>
#include <qdebug.h>
#include "tx4_util.h"
#include "tx4_events_section.h"
#include "tx4_shortcuts.h"
#include "tx4_toolbar.h"
#include "tx4_dir.h"

#define START_W 1200
#define START_H 775
#define MIN_W 500
#define MIN_H 300

#ifdef Q_OS_WIN
#include <QtWinExtras>
#endif

#ifdef QGOODWINDOW
#include "titlebar.h"
#endif

inline qreal pixelRatio() {
#ifdef QGOODWINDOW
	QScreen *screen = QApplication::primaryScreen();

#ifdef Q_OS_MAC
	qreal pixel_ratio = screen->devicePixelRatio();
#else
	qreal pixel_ratio = screen->logicalDotsPerInch() / qreal(96);
#endif

#else
	qreal pixel_ratio = qreal(1);
#endif
	return pixel_ratio;
}

class tx4 : public QGoodWindow {
	Q_OBJECT

	public:
		explicit tx4(QWidget *parent = nullptr);
		~tx4();

	signals:
		void startWork();
		void stopWork();

	protected:
		//void closeEvent(QCloseEvent *event);
		virtual bool nativeEvent(const QByteArray &eventType , void *message , long *result);
		virtual bool event(QEvent *event);

	private:
		QWidget *w_screensContainer;
		QWidget *w_mainContainer;
		QFrame *outerFrame;
		QFrame *innerFrame;
		tx4_shortcuts *o_shortcutManager;

		tx4_dir* o_tx4Dir;
		QList<tx4_event_preview*> selectedEvents;
		tx4_toolbar *w_toolbar;
		tx4_events_section *w_recentSection;
		tx4_events_section *w_savedSection;
		tx4_events_section *w_sentrySection;
		//tx4_recents *w_recentsSection;
		//tx4_events *w_eventsSection;
		bool m_selectMode;
		bool m_eventsLoaded;

		//bool workerstarted;
		//tx4_worker *worker;

		int window_w;
		QString m_title;
		bool m_dark;
		QString m_color_str;
		QString m_frame_style;

	#ifdef QGOODWINDOW
		TitleBar *title_bar;
	#endif

		void initWindowConfig();
		void initMainContainer();
		void initToolbar();
		void initShortcuts();

	private slots:
		void on_selectModeSignal();
		void on_eventSelectChange(tx4_event_preview *pselect);
		void on_eventDeselectChange(tx4_event_preview *pdeselect);
		void on_eventsLoadSignal();

		void on_teslaCamFolderError();
		void on_savedClipsFolderError();
		void on_sentryClipsFolderError();

};

#endif // TX4_H
