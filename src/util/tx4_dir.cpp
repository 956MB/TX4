
#include "tx4_dir.h"

tx4_dir::tx4_dir(const bool &load, const bool &force_dir, const QString &dir, QObject* parent) : QObject(parent) {
	if (load) {
		loadTeslaDrive(force_dir, dir);
	}
}

tx4_dir::~tx4_dir() {}

bool tx4_dir::loadTeslaDrive(bool force_dir, QString dir) {
	if (force_dir) {
		s_drivePathPrefix = dir;
	} else {
		s_drivePathPrefix = QFileDialog::getExistingDirectory(
			nullptr,
			tx4_dir::tr(CAPTION),
			ROOT,
			QFileDialog::ShowDirsOnly | QFileDialog::DontResolveSymlinks);
	}

	QDir driveRoot(s_drivePathPrefix);

	if (driveRoot.exists() && driveRoot.dirName() == CAM_FOLDER) {

		QDir savedDir(s_drivePathPrefix + "/" + SAVED_FOLDER);
		if (!savedDir.exists() && savedDir.dirName() == SAVED_FOLDER) { emit &tx4_dir::err_savedClipsFolder; return false; } else { d_savedClipsDir = savedDir; }
		QDir sentryDir(s_drivePathPrefix + "/" + SENTRY_FOLDER);
		if (!sentryDir.exists() && sentryDir.dirName() == SENTRY_FOLDER) { emit &tx4_dir::err_sentryClipsFolder; return false; } else { d_sentryClipsDir = sentryDir; }

		bool savedClipsSuccess = loopClipsDir(savedEvents, d_savedClipsDir, true);
		if (!savedClipsSuccess) { emit &tx4_dir::err_savedClipsFolderEmpty; return false; }
		bool sentryClipsSuccess = loopClipsDir(sentryEvents, d_sentryClipsDir, false);
		if (!sentryClipsSuccess) { emit &tx4_dir::err_sentryClipsFolderEmpty; return false; }

		return true;
	} else {
		emit &tx4_dir::err_teslaCamFolder;
		return false;
	}
}

bool tx4_dir::loopClipsDir(QList<tx4_event*> &eventList, QDir useDir, bool saved) {
	eventList.clear();

	QFileInfoList dirContents = useDir.entryInfoList(QDir::Dirs | QDir::NoSymLinks | QDir::NoDot | QDir::NoDotDot, QDir::Name);
	if (dirContents.isEmpty()) { return false; }

	QFileInfo eventFI;
	foreach (eventFI, dirContents) {
		QDir eventDir(eventFI.absoluteFilePath());
		tx4_event *_event = new tx4_event(eventDir, (saved ? "Saved" : "Sentry"));
		formDisplayStrings(_event);
		eventList.append(_event);
	}

	return true;
}

void tx4_dir::formDisplayStrings(tx4_event *_event) {
	QString clipCountString = QString::number(_event->i_ClipCount) + QString("x") + QString("4");
	QString s_dateString = _event->d_eventDir.dirName().split("_")[0];
	QString s_sizeString = Util::humanSize(_event->i_Size);
	QString timeString = Util::format_duration(_event->i_TotalClipLength);

	_event->s_countDisplay = clipCountString;
	_event->s_dateDisplay = s_dateString;
	_event->s_sizeDisplay = s_sizeString;
	_event->s_lengthDisplay = timeString;
}
