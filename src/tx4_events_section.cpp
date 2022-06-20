
#include "tx4_events_section.h"
#include <qboxlayout.h>
#include <qdebug.h>

tx4_events_section::tx4_events_section(const GroupLayout &layout, QWidget *parent)
	: QWidget(parent)
	, l_listItems(QList<tx4_list_item*> ())
	, l_previews(QList<tx4_event_preview*> ())
	, l_events(QList<tx4_event*> ())
	, l_selectedEvents(QList<tx4_event*> ())
	, i_totaslSizeNum(0)
	, i_totaslLengthNum(0)
	, gl_sectionLayout(layout)
{

	i_scrollValue = 0;
	selectAllClicked = false;
	b_eventsLoaded = false;
	i_selectedCount = 0;
	i_selectedSize = 0;
	i_selectedLength = 0;
	i_totalEvents = 4; // TODO: bug related to widgets not being visible in hor scroll: amount of events that need to be present in layout before adding new ones needs to be >= the amount of new ones, less and they overlap and dont work right, more and theyre all removed and new ones are added ffine, DONT KNOW WHY. maybe? remove scoll container from scroll area and readd it? or update the widget in scroll area after updating hor layout with new widgets?
	s_totalSizeDisplay = "0.00 GB";
	s_totalLengthDisplay = "0:00:00";

	this->setAttribute(Qt::WA_StyledBackground); // <--- this attribute solves issue of background color not being drawn on custom widget, no need for reimplementing paintEvent, yet.
	//this->setFixedHeight(RECENTS_H);
	//this->setMinimumHeight(SECTION_H);
	this->setSizePolicy(QSizePolicy::Ignored, QSizePolicy::Fixed);
	this->setStyleSheet(S_EVENTS_SECTION_BODY);

	initContents();
	//initPalette();
	initEmptyState(false);
}

tx4_events_section::~tx4_events_section() {}


void tx4_events_section::initContents() {
	QVBoxLayout *v_contentsLayout = new QVBoxLayout(this);
	Util::setLayoutZero(v_contentsLayout);
	//v_contentsLayout->setSpacing(0);
	//v_contentsLayout->setContentsMargins(0,0,0,0);

	w_sectionContents = new QWidget;
	w_sectionContents->setStyleSheet(S_EVENTS_SECTION_SCROLL_BODY);

	if (gl_sectionLayout == GroupLayout::Grid) {
		w_sectionContents->setSizePolicy(QSizePolicy::Ignored, QSizePolicy::Fixed);
		w_sectionContents->setMinimumWidth((PREVIEW_W * 4) + (OUTER_MARGIN*2) + 36);
		QHBoxLayout *h_contentsLayout = new QHBoxLayout(w_sectionContents);
		Util::setLayoutZero(h_contentsLayout);
		h_contentsLayout->setSpacing(12);
		h_contentsLayout->setContentsMargins(OUTER_MARGIN,0,OUTER_MARGIN,0);
		h_contentsLayout->setAlignment(Qt::AlignLeading);
	} else if (gl_sectionLayout == GroupLayout::List) {
		w_sectionContents->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Fixed);
		QVBoxLayout *v_contentsLayout = new QVBoxLayout(w_sectionContents);
		Util::setLayoutZero(v_contentsLayout);
		v_contentsLayout->setSpacing(4);
		v_contentsLayout->setContentsMargins(OUTER_MARGIN,0,OUTER_MARGIN,0);
		v_contentsLayout->setAlignment(Qt::AlignTop);
	}

	 //empty state message
	w_emptyState = new QWidget;
	QWidget *emptyStateStack = new QWidget;
	Util::setWidgetsSizePolicy(QSizePolicy::Expanding, QSizePolicy::Preferred, {w_emptyState, emptyStateStack});

	w_emptyState->setStyleSheet(S_EVENTS_SECTION_EMPTY_STATE);
	QHBoxLayout *h_emptyStateLayout = new QHBoxLayout(w_emptyState);
	Util::setLayoutZero(h_emptyStateLayout);
	h_emptyStateLayout->setContentsMargins(20, 0, 20, 0);
	l_emptyState = new tx4_label(tx4_events_section::tr("NO EVENTS LOADED"), 10, S_SUB_LABEL_OFF, QFont::Medium, Qt::AlignLeft);
	h_emptyStateLayout->addSpacerItem(new QSpacerItem(20, 0, QSizePolicy::Fixed, QSizePolicy::Expanding));
	h_emptyStateLayout->addStretch();
	h_emptyStateLayout->addWidget(l_emptyState);
	h_emptyStateLayout->addStretch();
	h_emptyStateLayout->addSpacerItem(new QSpacerItem(20, 0, QSizePolicy::Fixed, QSizePolicy::Expanding));
	emptyStateStack->setStyleSheet(S_EVENTS_SECTION_EMPTY_STATE);
	QStackedLayout *s_emptyStateStackLayout = new QStackedLayout(emptyStateStack);
	s_emptyStateStackLayout->setStackingMode(QStackedLayout::StackAll);
	Util::setLayoutZero(s_emptyStateStackLayout);
	s_emptyStateStackLayout->setContentsMargins(20, 0, 20, 0);

	//h_scrollContainerLayout->addWidget(scrollarea);
	s_emptyStateStackLayout->addWidget(w_emptyState);
	s_emptyStateStackLayout->addWidget(w_sectionContents);
	//v_contentsLayout->addWidget(titleContainer);
	v_contentsLayout->addWidget(emptyStateStack);

	this->setLayout(v_contentsLayout);
}
void tx4_events_section::initEmptyState(bool active) {
	w_emptyState->setVisible(!active);
	//w_rightContainer->setVisible(active);
	w_sectionContents->setVisible(active);
}
void tx4_events_section::initPalette() {
	QPalette p(palette());
	p.setColor(QPalette::Base, Qt::lightGray);
	this->setPalette(p);
}

void tx4_events_section::toggleEventsLoaded(bool active) {
	b_eventsLoaded = active;
	initEmptyState(b_eventsLoaded);
}

void tx4_events_section::resizeEventPreviews(int window_w) {
	if (gl_sectionLayout == GroupLayout::Grid) {
		if (b_eventsLoaded && i_totalEvents >= 1) {
			for (int i = 0; i < i_totalEvents; i++) {
				l_previews.at(i)->resizePreview(window_w);
			}
		}
	}
}

void tx4_events_section::populateEvents(QList<tx4_event*> pop_events, int indexOffset) {
	auto *sectionLayout = qobject_cast<QLayout*>(w_sectionContents->layout());
	Util::clearLayout(sectionLayout);

	l_events.clear();
	int count = pop_events.count();
	i_totalEvents = count;
	qint64 sizeCount = 0;
	qint64 timeCount = 0;

	if (gl_sectionLayout == GroupLayout::Grid) {
		populateGrid(sizeCount, timeCount, sectionLayout, pop_events, indexOffset);
	} else if (gl_sectionLayout == GroupLayout::List) {
		populateList(sizeCount, timeCount, sectionLayout, pop_events, indexOffset);
	}
	
	w_sectionContents->setLayout(sectionLayout);
	i_totaslSizeNum += sizeCount;
	i_totaslLengthNum += sizeCount;

	QString titleSizeString = Util::humanSize(sizeCount);
	QString titleTimeString = Util::format_duration(timeCount);
	s_totalSizeDisplay = titleSizeString;
	s_totalLengthDisplay = titleTimeString;
	emit infoUpdate(i_selectedCount, i_totalEvents, s_totalSizeDisplay, s_totalLengthDisplay);
}

void tx4_events_section::populateGrid(qint64 &sizeCount, qint64 &timeCount, QLayout *addLayout, QList<tx4_event*> events, int indexOffset) {
	l_previews.clear();

	for (int i = 0; i < i_totalEvents; i++) {
		tx4_event *event = events[i];
		tx4_event_preview *preview = new tx4_event_preview(event->s_dateDisplay, event->s_countDisplay, event->s_sizeDisplay, event->s_lengthDisplay, event->s_metaDataTimestampString, event->s_metaDataCityString, event->s_metaDataLatString, event->s_metaDataLonString, event->s_metaDataReasonString, event->s_metaDataCameraString, S_TITLE_LABEL, event->s_thumbnailPath, i+indexOffset);

		addLayout->addWidget(preview);
		preview->show();
		l_previews.append(preview);
		l_events.append(event);
		QObject::connect(preview, &tx4_event_preview::select, this, &tx4_events_section::on_updateSelect);
		QObject::connect(preview, &tx4_event_preview::deselect, this, &tx4_events_section::on_updateDeselect);

		sizeCount += event->i_Size;
		timeCount += event->i_TotalClipLength;
		//Util::deleteAndCleanup(event->mat_thumbFrame);
    }
}
void tx4_events_section::populateList(qint64 &sizeCount, qint64 &timeCount, QLayout *addLayout, QList<tx4_event*> events, int indexOffset) {
	l_listItems.clear();

	for (int i = 0; i < i_totalEvents; i++) {
		tx4_event *event = events[i];
		tx4_list_item *listItem = new tx4_list_item(event, event->s_thumbnailPath, i, i+indexOffset);
	
		addLayout->addWidget(listItem);
		listItem->show();
		l_listItems.append(listItem);
		l_events.append(event);
		QObject::connect(listItem, &tx4_list_item::select, this, &tx4_events_section::on_updateSelect);
		QObject::connect(listItem, &tx4_list_item::deselect, this, &tx4_events_section::on_updateDeselect);

		sizeCount += event->i_Size;
		timeCount += event->i_TotalClipLength;
		//Util::deleteAndCleanup(event->mat_thumbFrame);
	}
}

void tx4_events_section::manualInfoUpdate() {
	emit infoUpdate(i_selectedCount, i_totalEvents, s_totalSizeDisplay, s_totalLengthDisplay);
}

void tx4_events_section::setPreviewGrayscales(bool set) {
	if (gl_sectionLayout == GroupLayout::Grid) { 
		for (auto &preview: l_previews) {
			if (!preview->b_previewSelected) {
				preview->b_previewGrayscaled = set;
				preview->repaintPreview(set, (preview->b_previewHovered == true ? PreviewState::Hovered : PreviewState::Normal));
			}
		}
	}
}


// SLOTS :

void tx4_events_section::on_updateSelect(int idx) {
	i_selectedCount += 1;
	i_selectedSize += l_events[idx]->i_Size;
	i_selectedLength += l_events[idx]->i_TotalClipLength;
	l_selectedEvents.append(l_events[idx]);

	emit eventSelect(l_events[idx]);
	emit infoUpdate(i_selectedCount, i_totalEvents, Util::humanSize(i_selectedSize), Util::format_duration(i_selectedLength));
	setPreviewGrayscales(true);
}
void tx4_events_section::on_updateDeselect(int idx) {
	i_selectedCount -= 1;
	i_selectedSize -= l_events[idx]->i_Size;
	i_selectedLength -= l_events[idx]->i_TotalClipLength;

	//if (i_selectedCount <= 0) {
	//	resetSubtitle();
	//}

	if (i_selectedCount >= 0) {
		l_selectedEvents.removeAt(i_selectedCount);
		emit eventDeselect(l_events[idx]);
		setPreviewGrayscales(true);
	}

	if (i_selectedCount >= 1) {
		emit infoUpdate(i_selectedCount, i_totalEvents, Util::humanSize(i_selectedSize), Util::format_duration(i_selectedLength));
	} else {
		emit infoUpdate(i_selectedCount, i_totalEvents, s_totalSizeDisplay, s_totalLengthDisplay);
		setPreviewGrayscales(false);
	}
}