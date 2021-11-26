
#include "tx4_event_preview.h"
#include <qboxlayout.h>
#include <qdebug.h>
#include <QStackedLayout>

tx4_event_preview::tx4_event_preview(const QString &date, const QString &loc, const QString &size, const QString &length, const QString &timestamp, const QString &city, const QString &lat, const QString &lon, const QString &reason, const QString &camera, const QString &loc_style, const int &index, QWidget *parent)
	: QWidget(parent)
	, contentLabel(new QLabel)
	, previewIndex(index) {

	selectModeActive = true;
	metaDataActive = false;
	previewActive = true;
	previewHovered = false;
	previewSelected = false;
	clipCount = 4;
	selectIndex = -1;

	metaInfo = NULL;

	s_dateString = date;
	s_locString = loc;
	s_sizeString = size;
	s_lengthString = length;
	s_locStyle = loc_style;
	s_timestampString = timestamp;
	s_cityString = city;
	s_latString = lat;
	s_lonString = lon;
	s_reasonString = reason;
	s_cameraString = camera;

	this->setAttribute(Qt::WA_StyledBackground); // <--- this attribute solves issue of background color not being drawn on custom widget, no need for reimplementing paintEvent, yet.
	//this->setMinimumHeight(PREVIEW_H);
	this->setMinimumSize(PREVIEW_W, PREVIEW_H);
	this->setFixedSize(PREVIEW_W, PREVIEW_H);
	this->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
	this->setStyleSheet(normalStyle);

	initContents();
	//initPalette();
}

tx4_event_preview::~tx4_event_preview() {}

void tx4_event_preview::paintEvent(QPaintEvent *) {
    QStyleOption opt;
    opt.init(this);
    QPainter p(this);
    style()->drawPrimitive(QStyle::PE_Widget, &opt, &p, this);
}

void tx4_event_preview::setSelectModeState(bool active) {
	selectModeActive = active;
	metaDataActive = false;
	w_metaDataScreen->setVisible(metaDataActive);
	w_contentContainer->setVisible(true);

	if (!selectModeActive) {
		previewSelected = false;
		this->setStyleSheet(normalStyle);
		previewInfoBar->setStyleSheet(previewInfoBar->barStyleNormal);
		if (metaInfo != NULL) { metaInfo->metaInfoBar->setStyleSheet(previewInfoBar->barStyleNormal); }
	}
}

void tx4_event_preview::setSelectIdx(int idx) {
	selectIndex = idx;
	l_selectIdxLabel->setLabelText(QString::number(selectIndex));
}


void tx4_event_preview::initContents() {
	QStackedLayout *s_stackLayout = new QStackedLayout(this);
	s_stackLayout->setStackingMode(QStackedLayout::StackAll);
	Util::setLayoutZero(s_stackLayout);

	w_contentContainer = new QWidget;
	QVBoxLayout *v_contentsLayout = new QVBoxLayout(w_contentContainer);
	Util::setLayoutZero(v_contentsLayout);

	w_metaDataScreen = new QWidget;
	w_metaDataScreen->setStyleSheet(metaDataScreenStyle);
	QVBoxLayout *v_metaDataLayout = new QVBoxLayout(w_metaDataScreen);
	Util::setLayoutZero(v_metaDataLayout);

	w_selectIdxScreen = new QWidget;
	w_selectIdxScreen->setStyleSheet(selectIdxScreenStyle);
	QVBoxLayout *v_selectIdxLayout = new QVBoxLayout(w_selectIdxScreen);
	Util::setLayoutZero(v_selectIdxLayout);
	v_selectIdxLayout->setContentsMargins(0, 10, 10, 0);
	QWidget *w_selectIdxContainerTop = new QWidget;
	w_selectIdxContainerTop->setStyleSheet(selectIdxScreenStyle);
	QHBoxLayout *v_selectIdxContainerTopLayout = new QHBoxLayout(w_selectIdxContainerTop);
	Util::setLayoutZero(v_selectIdxContainerTopLayout);
	l_selectIdxLabel = new tx4_label("-1", 10, selectIdxLabelStyle, QFont::Medium, Qt::AlignCenter, "Anonymous Pro");
	v_selectIdxContainerTopLayout->addStretch();
	v_selectIdxContainerTopLayout->addWidget(l_selectIdxLabel);
	v_selectIdxLayout->addWidget(w_selectIdxContainerTop);
	v_selectIdxLayout->addStretch();

	//metaInfo = new tx4_meta_info("\"2021-10-12T17:55:04\"", "\"Northfield\"", "\"41.2781\"", "\"-81.5432\"", "\"user_interaction_honk\"", "\"0\"");
	//v_metaDataLayout->addWidget(metaInfo);

	//contentImage = new QImage("C:/Users/infga/Downloads/ppyslu8nukz71.png");
	//contentPixmap = QPixmap::fromImage(*contentImage);
	//contentLabel->setBackgroundRole(QPalette::Base);
 //   contentLabel->setSizePolicy(QSizePolicy::Ignored, QSizePolicy::Ignored);
	//contentLabel->setAlignment(Qt::AlignHCenter | Qt::AlignVCenter);
 //   contentLabel->setScaledContents(true);
	//contentLabel->setStyleSheet(contentStyleNormal);
	//contentLabel->setPixmap(contentPixmap);

	w_contentScreen = new QWidget;
	w_contentScreen->setFixedSize(PREVIEW_W, PREVIEW_H);
	w_contentScreen->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
	w_contentScreen->setStyleSheet(normalStyle);
	QVBoxLayout *v_contentLayout = new QVBoxLayout(w_contentScreen);
	Util::setLayoutZero(v_contentLayout);
	v_contentLayout->addStretch();
	v_contentLayout->addWidget(new tx4_label(tx4_event_preview::tr("THUMB UNAVAILABLE"), 10, thumbUnavailableLabelStyle, QFont::Medium, Qt::AlignCenter, "Anonymous Pro"));
	v_contentLayout->addSpacerItem(new QSpacerItem(0, 5, QSizePolicy::Expanding, QSizePolicy::Fixed));
	v_contentLayout->addStretch();
	previewInfoBar = new tx4_preview_bar(s_dateString, s_locString, s_sizeString, s_lengthString, s_locStyle, "event.json", false);

	v_contentsLayout->addWidget(w_contentScreen);
	//v_contentsLayout->addWidget(contentLabel);
	v_contentsLayout->addWidget(previewInfoBar);
	//v_contentsLayout->addSpacerItem(new QSpacerItem(0 , NAV_W , QSizePolicy::Expanding , QSizePolicy::Expanding));

	//QWidget *w_checkContainer = new QWidget;
	//w_checkContainer->setStyleSheet(blankStyle);
	//QVBoxLayout *v_checkLayout = new QVBoxLayout(w_checkContainer);
	//Util::setLayoutZero(v_checkLayout);
	//QWidget *w_checkTop = new QWidget;
	//w_checkTop->setStyleSheet(blankStyle);
	//QHBoxLayout *h_checkTopLayout = new QHBoxLayout(w_checkTop);
	//Util::setLayoutZero(h_checkTopLayout);
	//h_checkTopLayout->setContentsMargins(9, 9, 9, 9);

	//checkbox = new tx4_checkbox;
	//h_checkTopLayout->addStretch();
	//h_checkTopLayout->addWidget(checkbox);
	//checkbox->setCheckboxState(false);
	//checkbox->setVisible(false);

	//v_checkLayout->addWidget(w_checkTop);
	//v_checkLayout->addStretch();

	s_stackLayout->addWidget(w_metaDataScreen);
	s_stackLayout->addWidget(w_selectIdxScreen);
	s_stackLayout->addWidget(w_contentContainer);
	w_metaDataScreen->setVisible(metaDataActive);
	w_selectIdxScreen->setVisible(false);

	this->setLayout(s_stackLayout);
}


void tx4_event_preview::enterEvent(QEvent *e) {
    if (previewActive && !previewSelected) {
        previewHovered = true;

		if (selectModeActive) {
			//this->setStyleSheet(hoverStyle_SelectMode);
			this->setStyleSheet(hoverStyle);
			//previewInfoBar->setStyleSheet(previewInfoBar->barStyleHover_SelectMode);
			previewInfoBar->setStyleSheet(previewInfoBar->barStyleHover);
			//if (metaInfo != NULL) { metaInfo->metaInfoBar->setStyleSheet(previewInfoBar->barStyleHover_SelectMode); }
			if (metaInfo != NULL) { metaInfo->metaInfoBar->setHoverStyle(metaDataActive); }
		} else {
			this->setStyleSheet(hoverStyle);
			previewInfoBar->setStyleSheet(previewInfoBar->barStyleHover);
			//if (metaInfo != NULL) { metaInfo->metaInfoBar->setStyleSheet(previewInfoBar->barStyleHover); }
			if (metaInfo != NULL) { metaInfo->metaInfoBar->setHoverStyle(metaDataActive); }
		}
		//contentLabel->setStyleSheet(contentStyleHover);
		//checkbox->setCheckboxState(false);
		//checkbox->setVisible(true);

        QWidget::enterEvent(e);
    }
}
void tx4_event_preview::leaveEvent(QEvent *e) {
    if (previewActive && !previewSelected) {
        previewHovered = false;
		this->setStyleSheet(normalStyle);
		previewInfoBar->setStyleSheet(previewInfoBar->barStyleNormal);
		if (metaInfo != NULL) { metaInfo->metaInfoBar->setStyleSheet(previewInfoBar->barStyleNormal); }
		//if (metaInfo != NULL) { metaInfo->metaInfoBar->setHoverStyle(metaDataActive); }
		//contentLabel->setStyleSheet(contentStyleNormal);
		//checkbox->setCheckboxState(false);
		//checkbox->setVisible(false);
			
        QWidget::leaveEvent(e);
    }
}
void tx4_event_preview::mouseReleaseEvent(QMouseEvent *e) {
    if (previewActive) {
		if (e->button() == Qt::RightButton) {
			rightClick();
		} else {
			leftClick();
			//qDebug() << "left clickssscpdsjmfsomg";
		}

		QWidget::mouseReleaseEvent(e);
	}
}


void tx4_event_preview::leftClick() {
	if (previewActive && selectModeActive) {
		if (previewSelected) {
			previewSelected = false;
			this->setStyleSheet(normalStyle);
			previewInfoBar->setStyleSheet(previewInfoBar->barStyleNormal);
			if (metaInfo != NULL) { metaInfo->metaInfoBar->setStyleSheet(previewInfoBar->barStyleNormal); }
			w_selectIdxScreen->setVisible(false);
			emit deselect(previewIndex);
		} else {
			previewSelected = true;
			this->setStyleSheet(hoverStyle_SelectMode);
			previewInfoBar->setStyleSheet(previewInfoBar->barStyleHover_SelectMode);
			//if (metaInfo != NULL) { metaInfo->metaInfoBar->setStyleSheet(previewInfoBar->barStyleHover_SelectMode); }
			if (metaInfo != NULL) { metaInfo->metaInfoBar->setSelectedStyle(metaDataActive); }
			//if (metaInfo != NULL) { metaInfo->metaInfoBar->setHoverStyle(metaDataActive); }
			w_selectIdxScreen->setVisible(true);
			emit select(previewIndex);
		}
	} else if (previewActive && !selectModeActive) {
		//metaDataActive = !metaDataActive;
		//if (metaDataActive) {
		//	addCreateMetaInfo();
		//} else {
		//	removeMetaInfo();
		//}
		//w_metaDataScreen->setVisible(metaDataActive);
		//w_contentContainer->setVisible(!metaDataActive);
	}
}
void tx4_event_preview::rightClick() {
	if (previewActive) {
		metaDataActive = !metaDataActive;
		if (metaDataActive) {
			addCreateMetaInfo();
			if (metaInfo != NULL && previewSelected) { metaInfo->metaInfoBar->setSelectedStyle(metaDataActive); }
		} else {
			removeMetaInfo();
			if (previewSelected) { previewInfoBar->setStyleSheet(previewInfoBar->barStyleHover_SelectMode); }
		}
		w_metaDataScreen->setVisible(metaDataActive);
		w_contentContainer->setVisible(!metaDataActive);
	}
}


void tx4_event_preview::addCreateMetaInfo() {
	if (metaInfo == NULL) {
		metaInfo = new tx4_meta_info(s_timestampString, s_cityString, s_latString, s_lonString, s_reasonString, s_cameraString);
		w_metaDataScreen->layout()->addWidget(metaInfo);
	}
}
void tx4_event_preview::removeMetaInfo() {
	if (metaInfo != NULL) {
		w_metaDataScreen->layout()->removeWidget(metaInfo);
		metaInfo = NULL;
		//delete metaInfo;
	}
}