
#include "tx4_event.h"
#include <qboxlayout.h>
#include <qdebug.h>

tx4_event::tx4_event(QDir &pass_dir, QWidget *parent)
	: QWidget(parent)
	, d_eventDir(pass_dir) {

	m_tempPlayer = new QMediaPlayer;
	connect(m_tempPlayer, &QMediaPlayer::mediaStatusChanged, this, &tx4_event::onMediaStatusChanged);
	//connect(m_tempPlayer, &QMediaPlayer::durationChanged, this, &tx4_event::GetMetaData);
	//connect(m_tempPlayer, &QMediaPlayer::durationChanged, this, [&](qint64 dur) {
	//	i_eventFolder_TotalClipLength += dur;
	//	emit durationValueUpdated();
	//});

	s_Name = d_eventDir.dirName();
	s_Date = "";
	i_Size = 0;
	i_ClipCount = 0;
	i_ClipCountMerged = 0;
	i_TotalClipLength = 0;
	i_LeftClipCount = 0;
	i_FrontClipCount = 0;
	i_RightClipCount = 0;
	i_BackClipCount = 0;
	jsonPresent = false;
	s_countDisplay = "";
	s_dateDisplay = "";
	s_sizeDisplay = "";
	s_lengthDisplay = "";
	s_metaDataTimestampString = "";
	s_metaDataCityString = "";
	s_metaDataLatString = "";
	s_metaDataLonString = "";
	s_metaDataReasonString = "";
	s_metaDataCameraString = "";

	calculateClips();
	parseEventJson();
}

tx4_event::~tx4_event() {}


void tx4_event::splitBaseName(QString basename) {
	if (basename[20] == ("l")) { i_LeftClipCount += 1; i_ClipCount += 1; }
	if (basename[20] == ("f")) { i_FrontClipCount += 1; }
	if (basename[20] == ("r")) { i_RightClipCount += 1; }
	if (basename[20] == ("b")) { i_BackClipCount += 1; }
}
void tx4_event::calculateClips() {
	//QDirIterator eventDirIt(d_eventDir.absolutePath(), {"*.mp4", "*.wav"}, QDir::Files | QDir::NoSymLinks | QDir::NoDotAndDotDot);
	QFileInfoList eventDirContents = d_eventDir.entryInfoList({"*.mp4"}, QDir::Files | QDir::NoSymLinks | QDir::NoDotAndDotDot, QDir::Time);

	if (!eventDirContents.isEmpty()) {
		qint64 sizeCount = 0;
		QFileInfo file;

		foreach (file, eventDirContents) {
			if (file.isFile()) {
				m_tempPlayer->setMedia(QUrl::fromLocalFile(file.absoluteFilePath()));
				// TODO: waiting for every duration change connection is SLOW, also throwing many null reference pointer stub errors. need to find another way of getting media meta data SYNCHRONOUSLY and quick
				//QEventLoop loop;
				//loop.connect(this, SIGNAL(durationValueUpdated()), &loop, SLOT(quit()));
				//loop.exec();
				
				splitBaseName(file.baseName());
				sizeCount += file.size();
			}
		}

		i_Size = sizeCount;
	}
}
void tx4_event::parseEventJson() {
	QFile eventJsonFile(d_eventDir.absolutePath() + eventJsonFile);

	if (eventJsonFile.exists()) {
		if (eventJsonFile.open(QIODevice::ReadOnly)) {
			QByteArray bytes = eventJsonFile.readAll();
			eventJsonFile.close();

			QJsonParseError jsonError;
			QJsonDocument document = QJsonDocument::fromJson( bytes, &jsonError );
			if( jsonError.error != QJsonParseError::NoError ) {
				return;
			}
			QJsonObject jsonObj = document.object();

			auto timestamp = jsonObj.take("timestamp").toString();
			auto city = jsonObj.take("city").toString();
			auto est_lat = jsonObj.take("est_lat").toString();
			auto est_lon = jsonObj.take("est_lon").toString();
			auto reason = jsonObj.take("reason").toString();
			auto camera = jsonObj.take("camera").toString();
			s_metaDataTimestampString = timestamp;
			s_metaDataCityString = city;
			s_metaDataLatString = est_lat;
			s_metaDataLonString = est_lon;
			s_metaDataReasonString = reason;
			s_metaDataCameraString = camera;
		}
	}
}


// SLOTS: {
	void tx4_event::onMediaStatusChanged(QMediaPlayer::MediaStatus status) {
		if (status == QMediaPlayer::LoadedMedia) {
			GetMetaData();
		}
	}

	void tx4_event::GetMetaData() {
		QStringList metadatalist = m_tempPlayer->availableMetaData();
		int list_size = metadatalist.size();
		//qDebug() << player->isMetaDataAvailable() << list_size;

		//QString metadata_key = metadatalist.at(1);
		//QVariant var_data = player->metaData(metadata_key);
		QString metadata_key;
		QVariant var_data;
		//i_eventFolder_TotalClipLength += var_data.toInt();

		for (int indx = 0; indx < list_size; indx++) {
			metadata_key = metadatalist.at(indx);
			var_data = m_tempPlayer->metaData(metadata_key);

			if (metadata_key == "Duration") {
				i_TotalClipLength += var_data.toInt();
				//emit durationValueUpdated();
				return;
			}
		}
	}
// }