#ifndef TX4_EVENT_H
#define TX4_EVENT_H

#include <QWidget>
#include <QMediaPlayer>
#include "tx4_util.h"
#include "tx4_event_preview.h"

#define CLIP_LEN 59000 // TODO: temp duration value for all clips, because of qmediaplkayer metadata problem, 59000ms = 59s

class tx4_event : public QWidget {
	Q_OBJECT

	public:
		explicit tx4_event(QDir &pass_dir, QWidget* parent = nullptr);
		~tx4_event();

	//signals:
	//	void durationValueUpdated();

	public:
		//QMediaPlayer *m_tempPlayer;

		int selectIndex;
		QDir d_eventDir;
		QString s_Name;
		QString s_Date; // needs to be date formetted
		qint64 i_Size;
		int i_ClipCount;
		int i_ClipCountMerged;
		qint64 i_TotalClipLength;
		int i_LeftClipCount;
		int i_FrontClipCount;
		int i_RightClipCount;
		int i_BackClipCount;

		bool jsonPresent;
		QString s_countDisplay;
		QString s_dateDisplay;
		QString s_sizeDisplay;
		QString s_lengthDisplay;
		QString s_metaDataTimestampString;
		QString s_metaDataCityString;
		QString s_metaDataLatString;
		QString s_metaDataLonString;
		QString s_metaDataReasonString;
		QString s_metaDataCameraString;

		void setSelectIdx(int idx);

	private:
		QString eventJsonFile = "/event.json";

		void splitBaseName(QString basename);
		void calculateClips();
		void parseEventJson();
		void GetMetaData();

	//private slots:
	//	void onMediaStatusChanged(QMediaPlayer::MediaStatus status);
		
};

#endif // TX4_EVENT_H