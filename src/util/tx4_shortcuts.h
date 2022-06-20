#ifndef TX4_SHORTCUTS_H
#define TX4_SHORTCUTS_H
//
#include <QtCore>
#include <QtGui>
#include <QtWidgets>
#include <QObject>
#ifdef Q_OS_WIN
#include <QtWinExtras>
#endif

class tx4_shortcuts_main;
class tx4_shortcuts_viewer;

class tx4_shortcuts : public QObject {
	Q_OBJECT

	friend class tx4_shortcuts_main;
	friend class tx4_shortcuts_viewer;

	public:
		explicit tx4_shortcuts(QWidget *parent = nullptr);
		virtual ~tx4_shortcuts();

		bool b_shortCutsSet;

	signals:
		void shortcutNum1();
		void shortcutNum2();
		void shortcutNum3();
		void shortcutNum4();
		void shortcutEsc();
		void shortcutOpen();
		void shortcutLoad();
		void shortcutPlayPause();
		void shortcutSkipBack();
		void shortcutSkipBackInterval();
		void shortcutSkipForward();
		void shortcutSkipForwardInterval();
		void shortcutFullscreenViewer();
		void shortcutNavigateNextEvent();
		void shortcutNavigatePreviousEvent();

	private:
		QWidget *w_parentWidget;
};

class tx4_shortcuts_main : public tx4_shortcuts {
	Q_OBJECT

	public:
		tx4_shortcuts_main(QWidget *parent = nullptr);
		virtual ~tx4_shortcuts_main();
};

class tx4_shortcuts_viewer : public tx4_shortcuts {
	Q_OBJECT

	public:
		tx4_shortcuts_viewer(QWidget *parent = nullptr);
		virtual ~tx4_shortcuts_viewer();
};

#endif // TX4_SHORTCUTS_H