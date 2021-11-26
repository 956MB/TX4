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

class tx4_shortcuts : public QWidget {
	Q_OBJECT

	public:
		explicit tx4_shortcuts(QWidget *parent = nullptr);
		~tx4_shortcuts();

	signals:
		void signal_esc();
		void signal_selectMode();

};

#endif // TX4_SHORTCUTS_H