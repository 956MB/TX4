#ifndef TX4_DIR_H
#define TX4_DIR_H

#include <QFileDialog>
#include <QDir>
#include "tx4_util.h"
#include "../tx4_event.h"
#include "../tx4_defines.h"

class tx4_dir : public QObject {
	Q_OBJECT

	public:
		explicit tx4_dir(const bool &load = false, const bool &force_dir = true, const QString &dir = TESLA_DRIVE, QObject* parent = nullptr);
		virtual ~tx4_dir();

		QList<tx4_event*> savedEvents;
		QList<tx4_event*> sentryEvents;
		bool loadTeslaDrive(bool force_dir = true, QString dir = TESLA_DRIVE);

	signals:
		void err_teslaCamFolder();
		void err_savedClipsFolder();
		void err_sentryClipsFolder();
		void err_savedClipsFolderEmpty();
		void err_sentryClipsFolderEmpty();

	private:
		QString s_drivePathPrefix;
		QDir d_savedClipsDir;
		QDir d_sentryClipsDir;

		bool loopClipsDir(QList<tx4_event*> &eventList, QDir useDir, bool saved);
		void formDisplayStrings(tx4_event *_event);
};

#endif // TX4_DIR_H