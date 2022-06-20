
#include "tx4_event.h"
#include <qdebug.h>
//#include <opencv2/core/core.hpp>
//#include <opencv2/highgui/highgui.hpp>
//#include <opencv2/imgproc.hpp>
#include <iostream>

tx4_event::tx4_event(const QDir &pass_dir, const QString &type, QWidget *parent)
	: QWidget(parent)
	, s_eventType(type)
	, d_eventDir(pass_dir)
	, l_frontClips(QList<QFileInfo> ())
	, l_backClips(QList<QFileInfo> ())
	, l_leftClips(QList<QFileInfo> ())
	, l_rightClips(QList<QFileInfo> ())
	, b_thumbnailSet(false)
	, s_thumbnailPath("")
{

	i_inPage = (type == "Saved" ? 1 : 2);
	selectIndex = -1;
	s_Name = d_eventDir.dirName();
	s_Date = "";
	i_Size = 0;
	i_ClipCount = 0;
	i_ClipCountMerged = 0;
	i_TotalClipLength = 0;
	b_jsonPresent = false;
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

	std::random_device rd; // obtain a random number from hardware
	std::mt19937 gen(rd()); // seed the generator
	std::uniform_int_distribution<> distr(0, 3); // define the range
	randomThumb = distr(gen);

	setThumbnailPath();
	parseEventJson();
	calculateClips();
}

tx4_event::~tx4_event() {}


void tx4_event::setSelectIdx(int idx) {
	selectIndex = idx;
}

void tx4_event::splitBaseName(QFileInfo file) {
	QString basename = file.baseName();

	if (basename[20] == ("l")) {
		l_leftClips.append(file);
		i_ClipCount += 1;
		//getOpenCVData(file, 0);
	}
	if (basename[20] == ("f")) {
		l_frontClips.append(file);
		//getOpenCVData(file, 1);
	}
	if (basename[20] == ("r")) {
		l_rightClips.append(file);
		//getOpenCVData(file, 2);
	}
	if (basename[20] == ("b")) {
		l_backClips.append(file);
		//getOpenCVData(file, 3);
	}
}

void tx4_event::calculateClips() {
	QFileInfoList eventDirContents = d_eventDir.entryInfoList({"*.mp4"}, QDir::Files | QDir::NoSymLinks | QDir::NoDotAndDotDot, QDir::Name);

	if (!eventDirContents.isEmpty()) {
		qint64 sizeCount = 0;
		QFileInfo file;

		foreach (file, eventDirContents) {
			if (file.isFile()) {
				splitBaseName(file);
				sizeCount += file.size();
				i_TotalClipLength += CLIP_LEN; // TODO: using default clip length of 59 seconds becuase i cant calculate lengths yet (ross's default clip length is 59 seconds for all of them it seems anyway)
			}
		}

		i_TotalClipLength = i_TotalClipLength/4;
		i_Size = sizeCount;
	}
}
void tx4_event::parseEventJson() {
	QFile eventJsonFile(d_eventDir.absolutePath() + EVENT_JSON);

	if (eventJsonFile.exists()) {
		if (eventJsonFile.open(QIODevice::ReadOnly)) {
			QByteArray bytes = eventJsonFile.readAll();
			eventJsonFile.close();

			QJsonParseError jsonError{};
			if( jsonError.error != QJsonParseError::NoError ) { return; }
			QJsonDocument document = QJsonDocument::fromJson( bytes, &jsonError );
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

void tx4_event::setThumbnailPath() {
	QString thumbPath = d_eventDir.absolutePath() + "/" + THUMB_PNG;
	QFileInfo check_file(thumbPath);

	if (check_file.exists() && check_file.isFile()) {
        s_thumbnailPath = thumbPath;
    }

	b_thumbnailSet = true;
}

//void tx4_event::getOpenCVData(QFileInfo file, int rand) {
//	if (!b_thumbnailSet && rand == randomThumb) {
//		cap = new cv::VideoCapture(file.absoluteFilePath().toStdString()); // video
//		if (!cap->isOpened()) { std::cout << "*ERROR* Cannot open the video file" << std::endl; }
//
//		//double fps = cap->get(cv::CAP_PROP_FPS); // fps
//		//double fcount = cap->get(cv::CAP_PROP_FRAME_COUNT); // mat_thumbFrame count
//		//i_TotalClipLength = (int)(fcount/fps); // calculate clip length for every individual clip instead of default 59s len
//
//		//cv::Mat mat_thumbFrame;
//		mat_thumbFrame = new cv::Mat();
//		bool bSuccess = cap->read(*mat_thumbFrame); // first mat_thumbFrame
//		if (!bSuccess) { std::cout << "*ERROR* Cannot read the frame from video file" << std::endl; }
//
//		//size_t sizeInBytes = mat_thumbFrame->step[0] * mat_thumbFrame->rows;
//		//qDebug() << "frame size: " << sizeInBytes;
//
//		//s_selectedThumbnail = QPixmap::fromImage(QImage((unsigned char*) mat_thumbFrame->data, mat_thumbFrame->cols, mat_thumbFrame->rows, QImage::Format_BGR888));
//		b_thumbnailSet = true;
//
//		delete cap;
//		//delete mat_thumbFrame;
//	}
//}