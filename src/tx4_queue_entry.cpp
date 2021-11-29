
#include "tx4_queue_entry.h"
#include <qboxlayout.h>
#include <QStackedLayout>

tx4_queue_entry::tx4_queue_entry(const QString &text, tx4_event_preview &preview, QWidget *parent)
	: QWidget(parent)
	, textContent(text)
	, eventPreview(&preview) {

	previewCurrentStylesheet = eventPreview->styleSheet();
	previewHoverStylesheet = eventPreview->queueHoverStyle_SelectMode;
	barCurrentStylesheet = eventPreview->previewInfoBar->styleSheet();
	barHoverStylesheet = eventPreview->queue_barStyleHover;
	selectIdxCurrentStylesheet = eventPreview->l_selectIdxLabel->styleSheet();
	selectIdxHoverStylesheet = eventPreview->queue_selectIdxLabelStyle;

	//connect(eventPreview, &tx4_event_preview::selectedEnter, this, &tx4_queue_entry::on_selectedEnter);
	//connect(eventPreview, &tx4_event_preview::selectedLeave, this, &tx4_queue_entry::on_selectedLeave);

	this->setAttribute(Qt::WA_StyledBackground); // <--- this attribute solves issue of background color not being drawn on custom widget, no need for reimplementing paintEvent, yet.
	this->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Expanding);
	this->setStyleSheet(blankStyle);

	initContents();
}

tx4_queue_entry::~tx4_queue_entry() {}

void tx4_queue_entry::initContents() {
	QHBoxLayout *h_contentsLayout = new QHBoxLayout(this);
	Util::setLayoutZero(h_contentsLayout);

	entryLabel = new tx4_label(textContent, 10, queueLabelStyleNormal, QFont::Medium, Qt::AlignCenter);
	h_contentsLayout->addWidget(entryLabel);

	this->setLayout(h_contentsLayout);
}

void tx4_queue_entry::enterEvent(QEvent *e) {
    on_selectedEnter();
    QWidget::enterEvent(e);
}

void tx4_queue_entry::leaveEvent(QEvent *e) {
    on_selectedLeave();
    QWidget::leaveEvent(e);
}

void tx4_queue_entry::on_selectedEnter() {
	entryLabel->setStyleSheet(queueLabelStyleHover);
	eventPreview->setOwnStylesheet(previewHoverStylesheet, barHoverStylesheet, selectIdxHoverStylesheet);
	if (eventPreview->metaInfo != NULL) { eventPreview->metaInfo->metaInfoBar->setHoverStyle(eventPreview->metaDataActive, eventPreview->previewInfoBar->queue_barStyleHoverTop); }
	eventPreview->previewInfoBar->setTextStylesheet(selectIdxHoverStylesheet);
}
void tx4_queue_entry::on_selectedLeave() {
	entryLabel->setStyleSheet(queueLabelStyleNormal);
	eventPreview->setOwnStylesheet(previewCurrentStylesheet, barCurrentStylesheet, selectIdxCurrentStylesheet);
	if (eventPreview->metaInfo != NULL) { eventPreview->metaInfo->metaInfoBar->setStyleSheet(eventPreview->previewInfoBar->barStyleHover_SelectModeTop); }
	eventPreview->previewInfoBar->setTextStylesheet(selectIdxCurrentStylesheet);
}