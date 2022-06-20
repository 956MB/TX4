
#ifndef TX4_H
#define TX4_H

#include <QGoodWindow>
#include <qdebug.h>
#include "./util/tx4_util.h"
#include "./util/tx4_shortcuts.h"
#include "./toolbar/tx4_toolbar.h"
#include "./util/tx4_dir.h"
#include "./viewer/tx4_viewer.h"
#include "tx4_events_page.h"
#include "tx4_page_actions.h"
#include "./tx4_defines.h"

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
		virtual ~tx4();

	signals:
		void startWork();
		void stopWork();

	protected:
		//void closeEvent(QCloseEvent *event);
		virtual bool nativeEvent(const QByteArray &eventType , void *message , long *result);
		virtual bool event(QEvent *event);

	private:
		QStackedWidget *w_screensContainer;
		QWidget *w_mainScreen;
		tx4_viewer *w_viewerScreen;
		QFrame *f_outerFrame;
		QFrame *f_innerFrame;
		tx4_shortcuts *o_shortcutManager;

		tx4_dir* o_tx4Dir;
		QList<tx4_event*> l_selectedEvents;
		QList<tx4_event_preview*> l_selectedPreviews;
		tx4_toolbar *w_toolbar;
		QStackedWidget *w_pagesStackWidget;
		tx4_events_page *w_recentPage;
		tx4_events_page *w_savedPage;
		tx4_events_page *w_sentryPage;
		tx4_events_page *w_favoritesPage;
		bool m_selectMode;
		bool m_eventsLoaded;
		bool m_eventViewerOpen;

		//bool workerstarted;
		//tx4_worker *worker;

		int window_w;
		QString m_title;
		bool m_dark;
		bool m_groupsInitialized;
		QString m_color_str;
		QString m_frame_style;

	#ifdef QGOODWINDOW
	    CaptionButton *backbtn;
		TitleBar *title_bar;
	#endif

		void initWindowConfig();
		void initMainScreen();
		void initViewerScreen();
		//void initToolbar();
		void initShortcuts();
		void resizeSectionContents(int window_w);

	private slots:
		void on_manualResizeSignal();
		void on_pageSelectSignal(int idx);
		void on_eventSelectChange(tx4_event *eselect);
		void on_eventDeselectChange(tx4_event *edeselect);
		void on_eventsOpenSignal();
		void on_eventsLoadSignal();

		void on_teslaCamFolderError();
		void on_savedClipsFolderError();
		void on_sentryClipsFolderError();
		void on_savedClipsFolderEmptyError();
		void on_sentryClipsFolderEmptyError();

		void on_handleCloseEvents();

};

#endif // TX4_H
