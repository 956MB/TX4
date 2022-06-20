
#include "tx4_list_item.h"
#include <qboxlayout.h>
#include <qdebug.h>
#include <QStackedLayout>
#include <algorithm>
#include <random>

tx4_list_item::tx4_list_item(const tx4_event* event, const QString &thumbnail, const int &index, const int &displayIndex, QWidget *parent)
	: QWidget(parent)
	, i_eventIndex(index)
	, i_displayIndex(displayIndex)
	, w_smallPreviewLabel(new QLabel)
	, l_itemLabels(QList<tx4_label*> ())
{

	b_selectModeActive = true;
	b_listItemActive = true;
	b_listItemHovered = false;
	b_listItemSelected = false;
	b_previewPixmapSet = false;
	selectIndex = -1;

	s_dateString = event->s_dateDisplay;
	//s_locString = event->s_countDisplay;
	s_sizeString = event->s_sizeDisplay;
	s_lengthString = event->s_lengthDisplay;
	s_timestampString = event->s_metaDataTimestampString;
	s_cityString = event->s_metaDataCityString;
	s_latString = event->s_metaDataLatString;
	s_lonString = event->s_metaDataLonString;
	s_reasonString = event->s_metaDataReasonString;
	//s_cameraString = event->s_metaDataCameraString;

	l_infoTextList << s_dateString
				   << s_cityString
				   << s_reasonString
				   << s_sizeString
				   << s_lengthString;

	this->setAttribute(Qt::WA_StyledBackground); // <--- this attribute solves issue of background color not being drawn on custom widget, no need for reimplementing paintEvent, yet.
	this->setFixedHeight(LIST_ITEM_H);
	this->setStyleSheet(S_LIST_ITEM_EMPTY);
	this->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Fixed);

	//createThumbnailPixmap(thumbnail);
	initContents(thumbnail);
	//repaintItem();
}

tx4_list_item::~tx4_list_item() {}

void tx4_list_item::initContents(QString thumbMat) {
	QStackedLayout *s_stackLayout = new QStackedLayout(this);
	s_stackLayout->setStackingMode(QStackedLayout::StackAll);
	Util::setLayoutZero(s_stackLayout);

	w_itemBackground = new QLabel;
	w_itemBackground->setBackgroundRole(QPalette::Base);
	w_itemBackground->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
	w_itemBackground->setStyleSheet(S_LIST_ITEM_EMPTY);

	QWidget *w_contentContainer = new QWidget;
	QHBoxLayout *h_contentContainerLayout = new QHBoxLayout(w_contentContainer);
	Util::setLayoutZero(h_contentContainerLayout);
	//h_contentContainerLayout->setAlignment(Qt::AlignLeading);

	w_listButton = new tx4_list_button(ButtonState::Enabled, ICONS_PLUS, ICONS_MINUS, "", i_displayIndex);
	QObject::connect(w_listButton, &tx4_list_button::clicked, this, &tx4_list_item::on_buttonClicked);
	h_contentContainerLayout->addWidget(w_listButton);

	if (!b_previewPixmapSet) {
		//QPixmap p_previewPixmap = QPixmap::fromImage(QImage((unsigned char*) thumbMat.data, thumbMat.cols, thumbMat.rows, QImage::Format_BGR888));
		QPixmap p_previewPixmap(thumbMat);

		w_smallPreviewLabel->setFixedWidth(83);
		w_smallPreviewLabel->setBackgroundRole(QPalette::Base);
		w_smallPreviewLabel->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Ignored);
		w_smallPreviewLabel->setAlignment(Qt::AlignHCenter | Qt::AlignVCenter);
		w_smallPreviewLabel->setScaledContents(true);
		w_smallPreviewLabel->setStyleSheet(S_LIST_ITEM_CONTENT_NORMAL);
		w_smallPreviewLabel->setPixmap(p_previewPixmap);

		h_contentContainerLayout->addWidget(w_smallPreviewLabel);
		b_previewPixmapSet = true;
	}

	// Text container right
	QWidget *w_textContentContainer = new QWidget;
	QHBoxLayout *v_textContentLayout = new QHBoxLayout(w_textContentContainer);
	Util::setLayoutZero(v_textContentLayout);
	v_textContentLayout->setContentsMargins(45,0,45,0);

	for (int i = 0; i < l_infoTextList.count(); i++) {
		QWidget *w_textContainer = new QWidget;
		QHBoxLayout *h_textLayout = new QHBoxLayout(w_textContainer);
		Util::setLayoutZero(h_textLayout);
		h_textLayout->setAlignment(Qt::AlignLeading);

		QString useStr = Util::limitString(l_infoTextList[i], 21);
		tx4_label *w_infoText = new tx4_label(useStr, 13, S_LIST_ITEM_TEXT_EMPTY, QFont::Medium, Qt::AlignLeading, Qt::AlignVCenter);
		w_infoText->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);

		h_textLayout->addWidget(w_infoText);
		if (i == 1) { w_infoText->setToolTip(QString(s_latString + ", " + s_lonString)); }
		if (i == 2) {
			w_infoText->setLabelText(Util::reasonMap(l_infoTextList[i]));
			w_infoText->setToolTip(l_infoTextList[i]);
		}
		l_itemLabels.append(w_infoText);
		v_textContentLayout->addWidget(w_textContainer);
	}

	h_contentContainerLayout->addWidget(w_textContentContainer);
	s_stackLayout->addWidget(w_contentContainer);
	s_stackLayout->addWidget(w_itemBackground);

	this->setLayout(s_stackLayout);
}

//void tx4_list_item::repaintItem() {
//	if (b_listItemActive) {
//		QPixmap backgroundTarget = QPixmap(w_itemBackground->size());
//		backgroundTarget.fill(Qt::transparent);
//		QPainter backgroundPainter(&backgroundTarget);
//
//		// Bottom right corner removed from thumbnail
//		//QPixmap pixmapTarget = QPixmap(w_smallPreviewLabel->size());
//		//pixmapTarget.fill(Qt::transparent);
//		//QPainter pixmapPainter(&pixmapTarget);
//
//		QPainterPath usePathBG;
//		//QPainterPath usePathBG, cornerPathBG, usePathPIX, cornerPathPIX;
//		QColor fillColor = QColor(0, 0, 0);
//		if (b_listItemSelected) { fillColor = QColor(30, 30, 30); }
//		if (b_listItemHovered) { fillColor = QColor(17, 17, 17); }
//		QPoint bg_bR = w_itemBackground->rect().bottomRight();
//		//QPoint pix_bR = w_smallPreviewLabel->rect().bottomRight();
//
//		backgroundPainter.setCompositionMode(QPainter::CompositionMode_Source);
//		backgroundPainter.setRenderHints(QPainter::Antialiasing | QPainter::SmoothPixmapTransform);
//		//usePathBG.setFillRule(Qt::WindingFill);
//		//cornerPathBG.setFillRule(Qt::WindingFill);
//
//		// Bottom right corner removed from list item
//		//usePathBG.addRect(0, 0, w_itemBackground->width(), w_itemBackground->height());
//		//cornerPathBG.moveTo(bg_bR.x() + 1 - CORNER_ANGLE, bg_bR.y() + 1);
//		//cornerPathBG.lineTo(bg_bR.x() + 1, bg_bR.y() + 1);
//		//cornerPathBG.lineTo(bg_bR.x() + 1, bg_bR.y() + 1 - CORNER_ANGLE);
//		//cornerPathBG.lineTo(bg_bR.x() + 1 - CORNER_ANGLE, bg_bR.y() + 1);
//		//usePathBG = usePathBG.subtracted(cornerPathBG);
//		//backgroundPainter.fillPath(cornerPathBG, fillColor);
//		//backgroundPainter.setClipPath(cornerPathBG);
//
//		// List item rounded corners
//		usePathBG.addRoundedRect(QRectF(w_itemBackground->x(), w_itemBackground->y(), w_itemBackground->width(), w_itemBackground->height()), 10, 10);
//		//usePathBG = usePathBG.subtracted(usePathBG);
//		backgroundPainter.fillPath(usePathBG, fillColor);
//		//backgroundPainter.setClipPath(usePathBG);
//		//backgroundPainter.drawPath(usePathBG);
//		backgroundPainter.drawPath( usePathBG.simplified() );
//
//		//w_itemBackground->setMask(backgroundTarget.createMaskFromColor(fillColor));
//
//		// TODO: what the fuck man, thumbnail pixmap corner remove not working?
//		
//		//pixmapPainter.setCompositionMode(QPainter::CompositionMode_Source);
//		//pixmapPainter.setRenderHints(QPainter::Antialiasing | QPainter::SmoothPixmapTransform);
//		//cornerPathPIX.setFillRule(Qt::WindingFill);
//		//usePathPIX.addRect(0, 0, w_smallPreviewLabel->width(), w_smallPreviewLabel->height());
//		//cornerPathPIX.moveTo(pix_bR.x() + 1 - CORNER_ANGLE, pix_bR.y() + 1);
//		//cornerPathPIX.lineTo(pix_bR.x() + 1, pix_bR.y() + 1);
//		//cornerPathPIX.lineTo(pix_bR.x() + 1, pix_bR.y() + 1 - CORNER_ANGLE);
//		//cornerPathPIX.lineTo(pix_bR.x() + 1 - CORNER_ANGLE, pix_bR.y() + 1);
//		//usePathPIX = usePathPIX.subtracted(cornerPathPIX);
//		//pixmapPainter.fillPath(cornerPathPIX, fillColor);
//		//pixmapPainter.setClipPath(cornerPathPIX);
//		////pixmapPainter.drawPixmap(w_smallPreviewLabel->rect(), p_smallPreviewPixmap);
//		////pixmapPainter.drawImage(w_smallPreviewLabel->rect(), p_smallPreviewPixmap.toImage());
//		//w_smallPreviewLabel->setMask(pixmapTarget.createMaskFromColor(fillColor));
//		////w_smallPreviewLabel->setPixmap(pixmapTarget);
//		//cornerPath.moveTo(tL.x() + BORDER_W, tL.y() + BORDER_W);							// AS
//		//cornerPath.lineTo(tR.x() + 1 - BORDER_W, tR.y() + BORDER_W);						// BS
//		//cornerPath.lineTo(bR.x() + 1 - BORDER_W, bR.y() + 2 - CORNER_ANGLE - BORDER_W);	// CS
//		//cornerPath.lineTo(bR.x() + 2 - CORNER_ANGLE - BORDER_W, bR.y() + 1 - BORDER_W);	// DS
//		//cornerPath.lineTo(bL.x() + BORDER_W, bL.y() + 1 - BORDER_W);						// ES
//		//cornerPath.lineTo(tL.x() + BORDER_W, tL.y() + BORDER_W);							// AS
//		//usePath = usePath.subtracted(cornerPath);
//		//painter.drawPath(usePath);
//		//painter.drawImage(w_smallPreviewLabel->rect(), p_smallPreviewPixmap.toImage());
//		//w_smallPreviewLabel->setPixmap(backgroundTarget);
//	}
//}

void tx4_list_item::repaintItem() {
	if (b_listItemActive) {
		//QPainter p(this);
		//QPainterPath path;

		//QColor fillColor = QColor(0, 0, 0);
		//if (b_listItemSelected) { fillColor = QColor(40, 40, 40); }
		//if (b_listItemHovered) { fillColor = QColor(22, 22, 22); }

		//p.setCompositionMode(QPainter::CompositionMode_Source);
		//p.setRenderHints(QPainter::Antialiasing | QPainter::SmoothPixmapTransform);
		//path.addRoundedRect(QRectF(0, 0,  w_itemBackground->width(),  w_itemBackground->height()), 5, 5);
		//p.fillPath(path, fillColor);
		//p.drawPath(path);
	}
}

//void tx4_list_item::createThumbnailPixmap(cv::Mat thumbMat) {
//	//p_smallPreviewPixmap = QPixmap::fromImage(QImage((unsigned char*) thumbMat.data, 83, LIST_ITEM_H, QImage::Format_BGR888));
//	p_smallPreviewPixmap = QPixmap::fromImage(QImage((unsigned char*) thumbMat.data, thumbMat.cols, thumbMat.rows, QImage::Format_BGR888));
//}

void tx4_list_item::enterEvent(QEvent *e) {
    if (b_listItemActive) {
		setHoverStyles(true, S_LIST_ITEM_HOVER, true, ButtonState::Hovered);
        QWidget::enterEvent(e);
    }
}
void tx4_list_item::leaveEvent(QEvent *e) {
    if (b_listItemActive) {
		setHoverStyles(false, S_LIST_ITEM_NORMAL, false, ButtonState::Enabled);
        QWidget::leaveEvent(e);
    }
}

// SLOTS:
void tx4_list_item::on_buttonClicked() {
	if (b_listItemSelected) {
		deselectItem();
	} else {
		selectItem();
	}
}

void tx4_list_item::selectItem() {
	setSelectStyles(true, S_LIST_ITEM_SELECTED, ButtonState::Selected);
	emit select(i_eventIndex);
}
void tx4_list_item::deselectItem() {
	setSelectStyles(false, S_LIST_ITEM_HOVER, ButtonState::Hovered);
	emit deselect(i_eventIndex);
}

void tx4_list_item::setHoverStyles(bool hovered, QString backgroundStyle, bool parentHoverd, ButtonState buttonState) {
	b_listItemHovered = hovered;
	if (!b_listItemSelected) {
		w_itemBackground->setStyleSheet(backgroundStyle);
		w_listButton->b_parentHovered = parentHoverd;
		w_listButton->setButtonState((w_listButton->s_state == ButtonState::Selected ? ButtonState::Selected : buttonState));
		setLabelStyles((b_listItemHovered ? S_LIST_ITEM_TEXT_HOVER : S_LIST_ITEM_TEXT_NORMAL));
		//repaintItem();
	}
}
void tx4_list_item::setSelectStyles(bool selected, QString backgroundStyle, ButtonState buttonState) {
	b_listItemSelected = selected;
	w_itemBackground->setStyleSheet(backgroundStyle);
	w_listButton->setButtonState(buttonState);
	setLabelStyles((selected ? S_LIST_ITEM_TEXT_SELECTED : S_LIST_ITEM_TEXT_NORMAL));
	//repaintItem();
}
void tx4_list_item::setLabelStyles(QString style) {
	for (auto &label : l_itemLabels) {
		label->setLabelStyle(style);
	}
}