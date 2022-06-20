
#include "tx4_event_preview.h"
#include <qboxlayout.h>
#include <qdebug.h>
#include <QStackedLayout>
#include <algorithm>
#include <random>

tx4_event_preview::tx4_event_preview(const QString &date, const QString &loc, const QString &size, const QString &length, const QString &timestamp, const QString &city, const QString &lat, const QString &lon, const QString &reason, const QString &camera, const QString &loc_style, const QString &thumbnail, const int &index, QWidget *parent)
	: QWidget(parent)
	, w_contentLabel(new QLabel)
	, i_sectionIndex(index)
	, i_saveWindowW(0)
	, b_previewGrayscaled(false)
{

	b_selectModeActive = true;
	b_thumbnailPixmapSet = false;
	b_previewActive = true;
	b_previewHovered = false;
	b_previewSelected = false;
	b_metaDataActive = false;
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

	//effect = new QGraphicsDropShadowEffect;
	//effect->setBlurRadius(25);
	//effect->setXOffset(0);
	//effect->setYOffset(0);
	//effect->setColor(Qt::black);

	//m_ratio = (double)16/9;
	//setRatio((double)16/9);

	this->setAttribute(Qt::WA_StyledBackground); // <--- this attribute solves issue of background color not being drawn on custom widget, no need for reimplementing paintEvent, yet.
	this->setMinimumWidth(PREVIEW_W);
	this->setMinimumHeight(PREVIEW_H);
	//this->setMinimumSize(PREVIEW_W, PREVIEW_H);
	//this->setFixedSize(PREVIEW_W, PREVIEW_H);
	//QSizePolicy qsp(QSizePolicy::Expanding, QSizePolicy::Expanding);
	//qsp.setHeightForWidth(true);
	//this->setSizePolicy(qsp);
	this->setStyleSheet(S_EVENT_PREVIEW_NORMAL);
	//this->setGraphicsEffect(effect);

	//createThumbnailPixmap(thumbnail);
	initContents();
	repaintPreview(b_previewGrayscaled, PreviewState::Normal);
}

tx4_event_preview::~tx4_event_preview() {}

void tx4_event_preview::resizePreview(int window_w) {
	i_saveWindowW = window_w;

	this->setFixedSize(PREVIEW_W, PREVIEW_H);
	int new_w = ((i_saveWindowW - (80+36))/4);
	int new_h = new_w * 9/16;
	new_w = new_w >= PREVIEW_W ? new_w : PREVIEW_W;
	new_h = new_h >= PREVIEW_H ? new_h : PREVIEW_H;
	
	this->setFixedSize(new_w, new_h);
	repaintPreview(b_previewGrayscaled, (b_previewSelected ? PreviewState::Selected : PreviewState::Normal));
}

void tx4_event_preview::repaintPreview(bool grayscale, PreviewState state) {
	if (b_thumbnailPixmapSet) {
		QPixmap target = QPixmap(w_contentLabel->size());
		target.fill(Qt::transparent);
		QPainter painter(&target);
		QPainterPath usePath, cornerPath, borderUsePath, borderSubPath;
		Qt::GlobalColor borderColor = (state == PreviewState::Selected ? Qt::white : Qt::gray);

		QPoint tL = w_contentLabel->rect().topLeft();
		QPoint tR = w_contentLabel->rect().topRight();
		QPoint bL = w_contentLabel->rect().bottomLeft();
		QPoint bR = w_contentLabel->rect().bottomRight();

		painter.setCompositionMode(QPainter::CompositionMode_Source);
		painter.setRenderHints(QPainter::Antialiasing | QPainter::SmoothPixmapTransform);
		usePath.setFillRule(Qt::WindingFill);
		usePath.addRect(0, 0, w_contentLabel->width(), w_contentLabel->height());
		borderUsePath.setFillRule(Qt::WindingFill);
		borderUsePath.addRect(0, 0, w_contentLabel->width(), w_contentLabel->height());

		// PreviewState::Hovered:		PreviewState::Selected:
		// AH-----------------BH		AS--------------------BS
		// |--------------------\		|----------------------|
		// |---------------------\		|----------------------|
		// |-------------------- CH		|-------------------- CS
		// |----------------------|		|---------------------/
		// |----------------------|		|--------------------/
		// EH--------------------DH		ES-----------------DS

		if (state == PreviewState::Normal) {
			cornerPath.moveTo(tR.x() + 1 - CORNER_ANGLE, tR.y());
			cornerPath.lineTo(tR.x() + 1, tR.y());
			cornerPath.lineTo(tR.x() + 1, tR.y() + CORNER_ANGLE);
			cornerPath.lineTo(tR.x() + 1 - CORNER_ANGLE, tR.y());
			usePath = usePath.subtracted(cornerPath);
		}
		if (state == PreviewState::Hovered) {
			borderSubPath.moveTo(tL.x() + BORDER_W, tL.y() + BORDER_W);							// AH
			borderSubPath.lineTo(tR.x() + 2 - CORNER_ANGLE - BORDER_W, tR.y() + BORDER_W);		// BH
			borderSubPath.lineTo(tR.x() + 1 - BORDER_W, tR.y() - 1 + CORNER_ANGLE + BORDER_W);	// CH
			borderSubPath.lineTo(bR.x() + 1 - BORDER_W, bR.y() + 1 - BORDER_W);					// DH
			borderSubPath.lineTo(bL.x() + BORDER_W, bL.y() + 1 - BORDER_W);						// EH
			borderSubPath.lineTo(tL.x() + BORDER_W, tL.y() + BORDER_W);							// AH
			borderUsePath = borderUsePath.subtracted(borderSubPath);
			cornerPath.moveTo(tR.x() + 1 - CORNER_ANGLE, tR.y());
			cornerPath.lineTo(tR.x() + 1, tR.y());
			cornerPath.lineTo(tR.x() + 1, tR.y() + CORNER_ANGLE);
			cornerPath.lineTo(tR.x() + 1 - CORNER_ANGLE, tR.y());
			usePath = usePath.subtracted(cornerPath);
		}
		if (state == PreviewState::Selected) {
			borderSubPath.moveTo(tL.x() + BORDER_W, tL.y() + BORDER_W);							// AS
			borderSubPath.lineTo(tR.x() + 1 - BORDER_W, tR.y() + BORDER_W);						// BS
			borderSubPath.lineTo(bR.x() + 1 - BORDER_W, bR.y() + 2 - CORNER_ANGLE - BORDER_W);	// CS
			borderSubPath.lineTo(bR.x() + 2 - CORNER_ANGLE - BORDER_W, bR.y() + 1 - BORDER_W);	// DS
			borderSubPath.lineTo(bL.x() + BORDER_W, bL.y() + 1 - BORDER_W);						// ES
			borderSubPath.lineTo(tL.x() + BORDER_W, tL.y() + BORDER_W);							// AS
			borderUsePath = borderUsePath.subtracted(borderSubPath);
			cornerPath.moveTo(bR.x() + 1 - CORNER_ANGLE, bR.y() + 1);
			cornerPath.lineTo(bR.x() + 1, bR.y() + 1);
			cornerPath.lineTo(bR.x() + 1, bR.y() + 1 - CORNER_ANGLE);
			cornerPath.lineTo(bR.x() + 1 - CORNER_ANGLE, bR.y() + 1);
			usePath = usePath.subtracted(cornerPath);
		}

		painter.fillPath(usePath, QColor(15, 15, 15));
		painter.setClipPath(usePath);
		painter.setOpacity(grayscale ? 0.5 : 1.0 );

		if (!b_metaDataActive) {
			painter.drawImage(w_contentLabel->rect(), p_thumbnailPixmap.toImage());
		}
		if (state == PreviewState::Selected || state == PreviewState::Hovered) {
			painter.strokePath(borderUsePath.simplified(), QPen(Qt::black, 1));
			painter.fillPath(borderUsePath, borderColor);
		}

		w_contentLabel->setPixmap(target);
	}
}

void tx4_event_preview::createThumbnailPixmap(cv::Mat thumbMat) {
	p_thumbnailPixmap = QPixmap::fromImage(QImage((unsigned char*) thumbMat.data, thumbMat.cols, thumbMat.rows, QImage::Format_BGR888));
}

//void tx4_event_preview::setSelectModeState(bool active) {
//	w_contentContainer->setVisible(true);
//
//	if (!b_selectModeActive) {
//		b_previewSelected = false;
//		//w_borderOverlayOuter->setStyleSheet(S_EVENT_PREVIEW_NORMAL);
//	}
//}

void tx4_event_preview::setSelectIdx(int idx) {
	selectIndex = idx;
}

void tx4_event_preview::setOwnStylesheet(QString parentSS, QString barSS, QString selectIdxSS, QString metaSS) {
	//w_borderOverlayOuter->setStyleSheet(parentSS);
	//w_contentScreen->setStyleSheet(parentSS);
	//previewInfoBar->setStyleSheet(barSS);
	//l_selectIdxLabel->setStyleSheet(selectIdxSS);
}


void tx4_event_preview::initContents() {
	QStackedLayout *s_stackLayout = new QStackedLayout(this);
	s_stackLayout->setStackingMode(QStackedLayout::StackAll);
	Util::setLayoutZero(s_stackLayout);

	w_contentContainer = new QWidget;
	QVBoxLayout *v_contentsLayout = new QVBoxLayout(w_contentContainer);
	Util::setLayoutZero(v_contentsLayout);

	w_metaDataScreen = new QWidget;
	w_metaDataScreen->setStyleSheet(S_META_DATA_SCREEN);
	QVBoxLayout *v_metaDataLayout = new QVBoxLayout(w_metaDataScreen);
	Util::setLayoutZero(v_metaDataLayout);

	//metaInfo = new tx4_meta_info("\"2021-10-12T17:55:04\"", "\"Northfield\"", "\"41.2781\"", "\"-81.5432\"", "\"user_interaction_honk\"", "\"0\"");
	//v_metaDataLayout->addWidget(metaInfo);

	w_contentStack = new QWidget;
	w_contentStack->setStyleSheet(S_EVENT_PREVIEW_NORMAL);
	QStackedLayout *s_contentStackLayout = new QStackedLayout(w_contentStack);
	s_contentStackLayout->setStackingMode(QStackedLayout::StackAll);
	Util::setLayoutZero(s_contentStackLayout);
	//s_contentStackLayout->setContentsMargins(20, 0, 20, 0);

	//w_borderOverlayOuter = new QWidget;
	//w_borderOverlayOuter->setStyleSheet(borderOverlayStyleNormal);
	//w_borderOverlayInner = new QWidget;
	//w_borderOverlayInner->setStyleSheet(borderInnerStyle);
	//s_contentStackLayout->addWidget(w_borderOverlayOuter); // TODO: STILL FOR SOME REASON FIRST WIDGET PUT IN STACKEDLAYOUT IS ON TOP
	//s_contentStackLayout->addWidget(w_borderOverlayInner);
	//w_borderOverlayInner->setVisible(false);

	if (!b_thumbnailPixmapSet) {
		w_contentLabel->setBackgroundRole(QPalette::Base);
		w_contentLabel->setSizePolicy(QSizePolicy::Ignored, QSizePolicy::Ignored);
		w_contentLabel->setAlignment(Qt::AlignHCenter | Qt::AlignVCenter);
		w_contentLabel->setScaledContents(true);
		w_contentLabel->setStyleSheet(S_EVENT_PREVIEW_CONTENT_NORMAL);
		w_contentLabel->setPixmap(p_thumbnailPixmap);

		s_contentStackLayout->addWidget(w_contentLabel);
	//	v_contentLayout->addWidget(new tx4_label("THUMBNAIL EJ TILLGANGLIG", 12, S_THUMB_UNAVAILABLE_LABEL, QFont::Medium, Qt::AlignCenter));
		b_thumbnailPixmapSet = true;
	}
	
	v_contentsLayout->addWidget(w_contentStack);
	s_stackLayout->addWidget(w_metaDataScreen);
	s_stackLayout->addWidget(w_contentContainer);
	w_metaDataScreen->setVisible(b_metaDataActive);

	this->setLayout(s_stackLayout);
}


void tx4_event_preview::enterEvent(QEvent *e) {
    if (b_previewActive) {
        b_previewHovered = true;
		if (!b_previewSelected) {
			//setOwnStylesheet(borderOverlayStyleHover);
			//w_borderOverlayInner->setVisible(true);
			repaintPreview(false, PreviewState::Hovered);
		}
		//effect->setColor(QColor(255, 255, 255, 35));

        QWidget::enterEvent(e);
    }
}
void tx4_event_preview::leaveEvent(QEvent *e) {
    if (b_previewActive) {
        b_previewHovered = false;

		if (!b_previewSelected) {
			//setOwnStylesheet(borderOverlayStyleNormal);
			//w_borderOverlayInner->setVisible(false);
			repaintPreview(b_previewGrayscaled, PreviewState::Normal);
		}
		//effect->setColor(Qt::black);
			
        QWidget::leaveEvent(e);
    }
}
void tx4_event_preview::mouseReleaseEvent(QMouseEvent *e) {
    if (b_previewActive) {
		if (e->button() == Qt::RightButton) {
			rightClick();
		} else {
			leftClick();
		}

		QWidget::mouseReleaseEvent(e);
	}
}


void tx4_event_preview::leftClick() {
	if (b_previewActive && b_selectModeActive) {
		if (b_previewSelected) {
			deselectPreview();
		} else {
			selectPreview();
		}
	}
}
void tx4_event_preview::rightClick() {
	if (b_previewActive) {
		b_metaDataActive = !b_metaDataActive;
		if (b_metaDataActive) {
			createMetaInfo();
		} else {
			removeMetaInfo();
		}
		w_metaDataScreen->setVisible(b_metaDataActive);
		//w_contentContainer->setVisible(!metaDataActive);
		repaintPreview(false, (b_previewSelected ? PreviewState::Selected : PreviewState::Hovered));
	}
}


void tx4_event_preview::selectPreview() {
	b_previewSelected = true;
	//setOwnStylesheet(borderOverlayStyleSelected);
	//w_borderOverlayInner->setVisible(true);
	repaintPreview(false, PreviewState::Selected);
	emit select(i_sectionIndex);
}
void tx4_event_preview::deselectPreview() {
	b_previewSelected = false;
	//setOwnStylesheet(borderOverlayStyleNormal);
	//w_borderOverlayInner->setVisible(false);
	repaintPreview(false, (b_previewHovered ? PreviewState::Hovered : PreviewState::Normal));
	emit deselect(i_sectionIndex);
}


void tx4_event_preview::createMetaInfo() {
	if (metaInfo == NULL) {
		metaInfo = new tx4_meta_info(s_timestampString, s_cityString, s_latString, s_lonString, s_reasonString, s_cameraString);
		w_metaDataScreen->layout()->addWidget(metaInfo);
	}
}
void tx4_event_preview::removeMetaInfo() {
	if (metaInfo != NULL) {
		w_metaDataScreen->layout()->removeWidget(metaInfo);
		metaInfo = NULL;
		delete metaInfo;
	}
}