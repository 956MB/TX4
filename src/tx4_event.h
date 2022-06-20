#ifndef TX4_EVENT_H
#define TX4_EVENT_H

#include <QWidget>
#include "./util/tx4_util.h"
#include "tx4_event_preview.h"
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc.hpp>
#include "./tx4_defines.h"

class tx4_event : public QWidget {
	Q_OBJECT

	public:
		explicit tx4_event(const QDir &pass_dir, const QString &type, QWidget* parent = nullptr);
		virtual ~tx4_event();

	public:
		QString s_eventType;
		int selectIndex;
		int i_inPage;
		QDir d_eventDir;
		QString s_yearS;
		QString s_Name;
		QString s_Date; // needs to be date formetted
		qint64 i_Size;
		int i_ClipCount;
		int i_ClipCountMerged;
		qint64 i_TotalClipLength;
		QList<QFileInfo> l_frontClips;
		QList<QFileInfo> l_backClips;
		QList<QFileInfo> l_leftClips;
		QList<QFileInfo> l_rightClips;

		bool b_jsonPresent;
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
		
		//cv::Mat *mat_thumbFrame;
		QString s_thumbnailPath;

		void setSelectIdx(int idx);

	private:
		bool b_thumbnailSet;
		int randomThumb;
		//cv::VideoCapture *cap;

		void splitBaseName(QFileInfo file);
		void calculateClips();
		void parseEventJson();
		//void getOpenCVData(QFileInfo file, int rand);
		void setThumbnailPath();

	//private slots:
	//	void onMediaStatusChanged(QMediaPlayer::MediaStatus status);
		
};

#endif // TX4_EVENT_H