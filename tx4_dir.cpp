
#include "tx4_dir.h"

tx4_dir::tx4_dir(const bool &load, const bool &force_dir, const QString &dir, QWidget* parent) : QWidget(parent) {
	if (load) {
		loadTeslaDrive(force_dir, dir);
	}
}

tx4_dir::~tx4_dir() {}

bool tx4_dir::loadTeslaDrive(bool force_dir, QString dir) {
	if (force_dir) {
		s_drivePathPrefix = dir;
	} else {
		s_drivePathPrefix = QFileDialog::getExistingDirectory(this, tx4_dir::tr("Select root of \"TESLACAM\" drive..."),
												 "./",
												 QFileDialog::ShowDirsOnly
												 | QFileDialog::DontResolveSymlinks);
	}

	QDir driveRoot(s_drivePathPrefix);

	if (driveRoot.exists()) {
		if (driveRoot.dirName() != s_teslaCamFolder) { emit &tx4_dir::no_teslaCamFolder; return false; } else { d_driveRootDir = driveRoot; }

		QDir savedDir(s_drivePathPrefix + s_savedClipsFolder);
		QDir sentryDir(s_drivePathPrefix + s_sentryClipsFolder);
		if (!savedDir.exists()) { emit &tx4_dir::no_savedClipsFolder; return false; } else { d_savedClipsDir = savedDir; }
		if (!sentryDir.exists()) { emit &tx4_dir::no_sentryClipsFolder; return false; } else { d_sentryClipsDir = sentryDir; }

		bool savedClipsSuccess = loopClipsDir(d_savedClipsDir, true);
		bool sentryClipsSuccess = loopClipsDir(d_sentryClipsDir, false);
		if (!savedClipsSuccess) { emit &tx4_dir::no_savedClipsFolder; return false; }
		if (!sentryClipsSuccess) { emit &tx4_dir::no_sentryClipsFolder; return false; }

			 return true;
	} else { return false; }
}

bool tx4_dir::loopClipsDir(QDir useDir, bool saved) {
	QFileInfoList dirContents = useDir.entryInfoList(QDir::Dirs | QDir::NoSymLinks | QDir::NoDot | QDir::NoDotDot, QDir::Time);

	if (dirContents.isEmpty()) { return false; }
	//qDebug() << useDir.dirName() << " dirContents:: " << dirContents.count();

	QFileInfo eventFI;
	foreach (eventFI, dirContents) {
		QDir eventDir(eventFI.absoluteFilePath());
		//qDebug() << eventDir.dirName();

		if (saved) {
			tx4_event *savedEvent = new tx4_event(eventDir);
			formDisplayStrings(savedEvent);
			savedEvents.append(savedEvent);
		} else {
			tx4_event *sentryEvent = new tx4_event(eventDir);
			formDisplayStrings(sentryEvent);
			sentryEvents.append(sentryEvent);
		}

		//return true;
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
