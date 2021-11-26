
#include "tx4_events_section.h"
#include <qboxlayout.h>
#include <qdebug.h>

tx4_events_section::tx4_events_section(const QString &title, QWidget *parent)
	: QWidget(parent)
	, previews(QList<tx4_event_preview*> ())
	, selectedPreviews(QList<tx4_event_preview*> ())
	, sectionTitle(title) {

	scrollValue = 0;
	selectModeActive = false;
	eventsLoaded = false;
	selectedCount = 0;
	totalEvents = 4; // TODO: bug related to widgets not being visible in hor scroll: amount of events that need to be present in layout before adding new ones needs to be >= the amount of new ones, less and they overlap and dont work right, more and theyre all removed and new ones are added ffine, DONT KNOW WHY. maybe? remove scoll container from scroll area and readd it? or update the widget in scroll area after updating hor layout with new widgets?
	totalSize = "2.11 GB";
	totalLength = "0:15:39";

	this->setAttribute(Qt::WA_StyledBackground); // <--- this attribute solves issue of background color not being drawn on custom widget, no need for reimplementing paintEvent, yet.
	//this->setFixedHeight(RECENTS_H);
	this->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
	this->setStyleSheet(sectionStyle);

	initContents();
	//initPalette();
	initEmptyState(false);
}

tx4_events_section::~tx4_events_section() {}


void tx4_events_section::initContents() {
	//QVBoxLayout *v_contentsLayout = new QVBoxLayout(this);
	//v_contentsLayout->setSpacing(16);
	//v_contentsLayout->setContentsMargins(0,16,0,16);

	////QWidget *titleContainer = new QWidget;
	////titleContainer->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Fixed);
	////QHBoxLayout *h_titleContainerLayout = new QHBoxLayout(titleContainer);
	////h_titleContainerLayout->setContentsMargins(20,3,20,3);
	////w_rightContainer = new QWidget;
	////w_rightContainer->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
	////QHBoxLayout *h_rightContainerLayout = new QHBoxLayout(w_rightContainer);
	////l_sectionTitle = new tx4_label(sectionTitle, 10, titleLabelStyle, QFont::Medium, Qt::AlignLeft, "Anonymous Pro");
	////l_countSubitle = new tx4_label(QString::number(totalEvents) + tx4_events_section::tr(" EVENTS"), 10, subLabelStyle, QFont::Medium, Qt::AlignLeft, "Anonymous Pro");
	////l_sizeSubitle = new tx4_label(totalSize, 10, subLabelStyle, QFont::Medium, Qt::AlignLeft, "Anonymous Pro");
	////l_lengthSubitle = new tx4_label(totalLength, 10, subLabelStyle, QFont::Medium, Qt::AlignLeft, "Anonymous Pro");
	////h_rightContainerLayout->addWidget(l_countSubitle);
	////h_rightContainerLayout->addSpacerItem(new QSpacerItem(15, 0, QSizePolicy::Fixed, QSizePolicy::Expanding));
	////h_rightContainerLayout->addWidget(new tx4_label("[", 10, subLabelBraceStyle, QFont::Medium, Qt::AlignCenter, "Anonymous Pro"));
	////h_rightContainerLayout->addWidget(l_sizeSubitle);
	////h_rightContainerLayout->addWidget(new tx4_label("]", 10, subLabelBraceStyle, QFont::Medium, Qt::AlignCenter, "Anonymous Pro"));
	////h_rightContainerLayout->addSpacerItem(new QSpacerItem(15, 0, QSizePolicy::Fixed, QSizePolicy::Expanding));
	////h_rightContainerLayout->addWidget(new tx4_label("[", 10, subLabelBraceStyle, QFont::Medium, Qt::AlignCenter, "Anonymous Pro"));
	////h_rightContainerLayout->addWidget(l_lengthSubitle);
	////h_rightContainerLayout->addWidget(new tx4_label("]", 10, subLabelBraceStyle, QFont::Medium, Qt::AlignCenter, "Anonymous Pro"));

	////h_titleContainerLayout->addWidget(l_sectionTitle);
	////h_titleContainerLayout->addStretch();
	////h_titleContainerLayout->addWidget(w_rightContainer);

	//w_sectionScroll = new QWidget;
	//w_sectionScroll->setStyleSheet(scrollAreaStyle);
	//w_sectionScroll->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Fixed);
	//QHBoxLayout *h_recentsScrollLayout = new QHBoxLayout(w_sectionScroll);
	//Util::setLayoutZero(h_recentsScrollLayout);
	//h_recentsScrollLayout->setSpacing(10);

	//// TODO:
	//for (int i = 0; i < totalEvents; i++) {
	//	tx4_event_preview *preview = new tx4_event_preview("2021_08_22", "12x4", "21.75MB", "09:13", titleLabelStyle, i, this);
	//	h_recentsScrollLayout->addWidget(preview);
	//	previews.append(preview);
	//	connect(preview, &tx4_event_preview::select, this, &tx4_events_section::on_updateSelect);
	//	connect(preview, &tx4_event_preview::deselect, this, &tx4_events_section::on_updateDeselect);
 //   }
	////h_recentsScrollLayout->addSpacerItem(new QSpacerItem(20, 0, QSizePolicy::Fixed, QSizePolicy::Expanding));
	//h_recentsScrollLayout->addStretch();

	//w_scrollContainer = new QWidget;
	//w_scrollContainer->setFixedHeight(PREVIEW_H);
	//w_scrollContainer->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Fixed);
	//w_scrollContainer->setStyleSheet(titleBarStyle);
	//QHBoxLayout *h_scrollContainerLayout = new QHBoxLayout(w_scrollContainer);
	//Util::setLayoutZero(h_scrollContainerLayout);
	//h_scrollContainerLayout->setContentsMargins(20, 0, 20, 0);
	//scrollarea = new QScrollArea();
	//scrollarea->verticalScrollBar()->setEnabled(false);
	//scrollarea->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
	//scrollarea->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
	//scrollarea->setStyleSheet(scrollAreaStyle);
	//scrollarea->setWidget(w_sectionScroll);

	//h_scrollContainerLayout->addWidget(scrollarea);
	////v_contentsLayout->addWidget(titleContainer);
	//v_contentsLayout->addWidget(w_scrollContainer);

	//this->setLayout(v_contentsLayout);





























	QVBoxLayout *v_contentsLayout = new QVBoxLayout(this);
	Util::setLayoutZero(v_contentsLayout);
	v_contentsLayout->setSpacing(16);
	v_contentsLayout->setContentsMargins(0,16,0,16);

	QWidget *titleContainer = new QWidget;
	titleContainer->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Fixed);
	titleContainer->setStyleSheet(titleBarStyle);
	QHBoxLayout *h_titleContainerLayout = new QHBoxLayout(titleContainer);
	Util::setLayoutZero(h_titleContainerLayout);
	h_titleContainerLayout->setContentsMargins(20,3,20,3);
	w_rightContainer = new QWidget;
	w_rightContainer->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
	QHBoxLayout *h_rightContainerLayout = new QHBoxLayout(w_rightContainer);
	Util::setLayoutZero(h_rightContainerLayout);
	//h_titleContainerLayout->setSpacing(15);
	l_sectionTitle = new tx4_label(sectionTitle, 10, titleLabelStyle, QFont::Medium, Qt::AlignLeft, "Anonymous Pro");
	l_countSubitle = new tx4_label(QString::number(totalEvents) + tx4_events_section::tr(" EVENTS"), 10, subLabelStyle, QFont::Medium, Qt::AlignLeft, "Anonymous Pro");
	l_sizeSubitle = new tx4_label(totalSize, 10, subLabelStyle, QFont::Medium, Qt::AlignLeft, "Anonymous Pro");
	l_lengthSubitle = new tx4_label(totalLength, 10, subLabelStyle, QFont::Medium, Qt::AlignLeft, "Anonymous Pro");
	h_rightContainerLayout->addWidget(l_countSubitle);
	h_rightContainerLayout->addSpacerItem(new QSpacerItem(15, 0, QSizePolicy::Fixed, QSizePolicy::Expanding));
	h_rightContainerLayout->addWidget(new tx4_label("[", 10, subLabelBraceStyle, QFont::Medium, Qt::AlignCenter, "Anonymous Pro"));
	h_rightContainerLayout->addWidget(l_sizeSubitle);
	h_rightContainerLayout->addWidget(new tx4_label("]", 10, subLabelBraceStyle, QFont::Medium, Qt::AlignCenter, "Anonymous Pro"));
	h_rightContainerLayout->addSpacerItem(new QSpacerItem(15, 0, QSizePolicy::Fixed, QSizePolicy::Expanding));
	h_rightContainerLayout->addWidget(new tx4_label("[", 10, subLabelBraceStyle, QFont::Medium, Qt::AlignCenter, "Anonymous Pro"));
	h_rightContainerLayout->addWidget(l_lengthSubitle);
	h_rightContainerLayout->addWidget(new tx4_label("]", 10, subLabelBraceStyle, QFont::Medium, Qt::AlignCenter, "Anonymous Pro"));

	h_titleContainerLayout->addWidget(l_sectionTitle);
	h_titleContainerLayout->addStretch();
	h_titleContainerLayout->addWidget(w_rightContainer);

	w_sectionScroll = new QWidget;
	w_sectionScroll->setStyleSheet(scrollAreaStyle);
	w_sectionScroll->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Fixed);
	QHBoxLayout *h_recentsScrollLayout = new QHBoxLayout(w_sectionScroll);
	Util::setLayoutZero(h_recentsScrollLayout);
	h_recentsScrollLayout->setSpacing(10);

	// TODO:
	for (int i = 0; i < totalEvents; i++) {
		tx4_event_preview *preview = new tx4_event_preview("", "", "", "", "", "", "","", "", "", titleLabelStyle, i);
		h_recentsScrollLayout->addWidget(preview);
		previews.append(preview);
		connect(preview, &tx4_event_preview::select, this, &tx4_events_section::on_updateSelect);
		connect(preview, &tx4_event_preview::deselect, this, &tx4_events_section::on_updateDeselect);
    }
	h_recentsScrollLayout->addStretch();

	// horizontal preview scroll
	w_scrollContainer = new QWidget;
	w_scrollContainer->setFixedHeight(PREVIEW_H);
	w_scrollContainer->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Fixed);
	w_scrollContainer->setStyleSheet(titleBarStyle);
	QHBoxLayout *h_scrollContainerLayout = new QHBoxLayout(w_scrollContainer);
	Util::setLayoutZero(h_scrollContainerLayout);
	h_scrollContainerLayout->setContentsMargins(20, 0, 20, 0);
	scrollarea = new QScrollArea();
	scrollarea->verticalScrollBar()->setEnabled(false);
	scrollarea->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
	scrollarea->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
	scrollarea->setStyleSheet(scrollAreaStyle);
	scrollarea->setWidget(w_sectionScroll);

	 //empty state message
	w_emptyState = new QWidget;
	w_emptyState->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
	w_emptyState->setStyleSheet(emptyStateStyle);
	QHBoxLayout *h_emptyStateLayout = new QHBoxLayout(w_emptyState);
	Util::setLayoutZero(h_emptyStateLayout);
	h_emptyStateLayout->setContentsMargins(20, 0, 20, 0);
	l_emptyState = new tx4_label(tx4_events_section::tr("NO EVENTS LOADED"), 10, subLabelStyleOff, QFont::Medium, Qt::AlignLeft, "Anonymous Pro");
	h_emptyStateLayout->addSpacerItem(new QSpacerItem(20, 0, QSizePolicy::Fixed, QSizePolicy::Expanding));
	h_emptyStateLayout->addStretch();
	h_emptyStateLayout->addWidget(l_emptyState);
	h_emptyStateLayout->addStretch();
	h_emptyStateLayout->addSpacerItem(new QSpacerItem(20, 0, QSizePolicy::Fixed, QSizePolicy::Expanding));
	QWidget *emptyStateStack = new QWidget;
	emptyStateStack->setFixedHeight(PREVIEW_H);
	emptyStateStack->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Fixed);
	emptyStateStack->setStyleSheet(emptyStateStyle);
	QStackedLayout *s_emptyStateStackLayout = new QStackedLayout(emptyStateStack);
	s_emptyStateStackLayout->setStackingMode(QStackedLayout::StackAll);
	Util::setLayoutZero(s_emptyStateStackLayout);
	s_emptyStateStackLayout->setContentsMargins(20, 0, 20, 0);

	h_scrollContainerLayout->addWidget(scrollarea);
	s_emptyStateStackLayout->addWidget(w_emptyState);
	s_emptyStateStackLayout->addWidget(w_scrollContainer);
	v_contentsLayout->addWidget(titleContainer);
	v_contentsLayout->addWidget(emptyStateStack);

	this->setLayout(v_contentsLayout);
}
void tx4_events_section::initEmptyState(bool active) {
	w_emptyState->setVisible(!active);
	w_rightContainer->setVisible(active);
	w_scrollContainer->setVisible(active);
}
void tx4_events_section::initPalette() {
	QPalette p(palette());
	p.setColor(QPalette::Base, Qt::lightGray);
	this->setPalette(p);
}

void tx4_events_section::toggleEventsLoaded(bool active) {
	eventsLoaded = active;
	initEmptyState(eventsLoaded);
}


// SCROLLWHEEL EVENTS: {
	void tx4_events_section::wheelEvent(QWheelEvent* event) {
		if(event->angleDelta().y() > 0) { // up Wheel
			scrollLeft();
		} else if (event->angleDelta().y() < 0) { //down Wheel
			scrollRight();
		}
	}
	void tx4_events_section::scrollLeft() {
		if (scrollarea->rect().contains(scrollarea->mapFromGlobal(QCursor::pos()))) {
			if (scrollValue > scrollarea->horizontalScrollBar()->minimum()) {
				scrollValue = scrollValue-SCROLL_DIFF;
				scrollarea->horizontalScrollBar()->setValue(scrollValue);
			}
		}
	}
	void tx4_events_section::scrollRight() {
		if (scrollarea->rect().contains(scrollarea->mapFromGlobal(QCursor::pos()))) {
			if (scrollValue < scrollarea->horizontalScrollBar()->maximum()) {
				scrollValue = scrollValue+SCROLL_DIFF;
				scrollarea->horizontalScrollBar()->setValue(scrollValue);
			}
		}
	}
// }

void tx4_events_section::clearLayout(QLayout *layout) {
    if (layout == NULL)
        return;
    QLayoutItem *item;
    while((item = layout->takeAt(0))) {
        if (item->layout()) {
            clearLayout(item->layout());
            delete item->layout();
        }
        if (item->widget()) {
           delete item->widget();
        }
        delete item;
    }
}
void tx4_events_section::populateEvents(QList<tx4_event*> events) {
	auto *hbox = qobject_cast<QHBoxLayout*>(w_sectionScroll->layout());
	clearLayout(hbox);
	//delete w_sectionScroll->layout();//delete the first layout
	previews.clear();
	int count = events.count();
	totalEvents = count;
	qint64 sizeCount = 0;
	qint64 timeCount = 0;
	//QHBoxLayout *h_recentsScrollLayout = new QHBoxLayout(w_sectionScroll);
	//Util::setLayoutZero(h_recentsScrollLayout);
	//h_recentsScrollLayout->setSpacing(10);

	for (int i = 0; i < totalEvents; i++) {
		tx4_event_preview *preview = new tx4_event_preview(events[i]->s_dateDisplay, events[i]->s_countDisplay, events[i]->s_sizeDisplay, events[i]->s_lengthDisplay, events[i]->s_metaDataTimestampString, events[i]->s_metaDataCityString, events[i]->s_metaDataLatString, events[i]->s_metaDataLonString, events[i]->s_metaDataReasonString, events[i]->s_metaDataCameraString, titleLabelStyle, i);
		//tx4_event_preview *preview = new tx4_event_preview("2021_08_22", "12x4", "21.75MB", "09:13", titleLabelStyle, i);
		//preview->setParent(w_sectionScroll);
		hbox->addWidget(preview);
		//h_recentsScrollLayout->addWidget(preview);
		preview->show();
		previews.append(preview);
		connect(preview, &tx4_event_preview::select, this, &tx4_events_section::on_updateSelect);
		connect(preview, &tx4_event_preview::deselect, this, &tx4_events_section::on_updateDeselect);

		sizeCount += events[i]->i_Size;
		timeCount += events[i]->i_TotalClipLength;
    }
	hbox->addStretch();
	w_sectionScroll->setLayout(hbox);
	qDebug() << "hbox::EMPTY?? " << hbox->isEmpty();

	QString titleEventsString = QString::number(totalEvents) + tx4_events_section::tr(" EVENTS");
	QString titleSizeString = Util::humanSize(sizeCount);
	QString titleTimeString = Util::format_duration(timeCount);
	l_countSubitle->setLabelText(titleEventsString);
	l_sizeSubitle->setLabelText(titleSizeString);
	l_lengthSubitle->setLabelText(titleTimeString);
}
void tx4_events_section::resetSubtitle() {
	selectModeActive = false;
	QString formDeselect = QString::number(totalEvents) + tx4_events_section::tr(" EVENTS");
	l_countSubitle->setText(formDeselect);
	l_sizeSubitle->setStyleSheet(subLabelStyle);
	l_lengthSubitle->setStyleSheet(subLabelStyle);
}


// SLOTS : {
	void tx4_events_section::on_updateSelect(int idx) {
		if (!selectModeActive) {
			selectModeActive = true;
			selectedCount += 1;
			QString formSelect = QString::number(selectedCount) + QString("/") + QString::number(totalEvents) + tx4_events_section::tr(" SELECTED");
			l_countSubitle->setText(formSelect);
			l_sizeSubitle->setStyleSheet(subLabelStyleOff);
			l_lengthSubitle->setStyleSheet(subLabelStyleOff);

			selectedPreviews.append(previews[idx]);
			emit eventSelect(previews[idx]);
			return;
		}

		selectedCount += 1;
		QString formSelect = QString::number(selectedCount) + QString("/") + QString::number(totalEvents) + tx4_events_section::tr(" SELECTED");
		l_countSubitle->setText(formSelect);

		selectedPreviews.append(previews[idx]);
		emit eventSelect(previews[idx]);
	}
	void tx4_events_section::on_updateDeselect(int idx) {
		selectedCount -= 1;
		QString formDeselect = QString::number(selectedCount) + QString("/") + QString::number(totalEvents) + tx4_events_section::tr(" SELECTED");
		l_countSubitle->setText(formDeselect);

		if (selectedCount <= 0) {
			resetSubtitle();
		}

		if (selectedCount >= 0) {
			selectedPreviews.removeAt(selectedCount);
			emit eventDeselect(previews[idx]);
		}
	}
// }