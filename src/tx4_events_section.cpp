
#include "tx4_events_section.h"
#include <qboxlayout.h>
#include <qdebug.h>

tx4_events_section::tx4_events_section(const QString &title, QWidget *parent)
	: QWidget(parent)
	, previews(QList<tx4_event_preview*> ())
	, events(QList<tx4_event*> ())
	, selectedPreviews(QList<tx4_event_preview*> ())
	, selectedEvents(QList<tx4_event*> ())
	, sectionTitle(title) {

	i_scrollValue = 0;
	selectModeActive = false;
	selectAllClicked = false;
	eventsLoaded = false;
	i_selectedCount = 0;
	i_selectedSize = 0;
	i_selectedLength = 0;
	i_totalEvents = 4; // TODO: bug related to widgets not being visible in hor scroll: amount of events that need to be present in layout before adding new ones needs to be >= the amount of new ones, less and they overlap and dont work right, more and theyre all removed and new ones are added ffine, DONT KNOW WHY. maybe? remove scoll container from scroll area and readd it? or update the widget in scroll area after updating hor layout with new widgets?
	s_totalSize = "2.11 GB";
	s_totalLength = "0:15:39";

	this->setAttribute(Qt::WA_StyledBackground); // <--- this attribute solves issue of background color not being drawn on custom widget, no need for reimplementing paintEvent, yet.
	//this->setFixedHeight(RECENTS_H);
	this->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Fixed);
	this->setStyleSheet(sectionStyle);

	initContents();
	//initPalette();
	initEmptyState(false);
}

tx4_events_section::~tx4_events_section() {}


void tx4_events_section::initContents() {
	QVBoxLayout *v_contentsLayout = new QVBoxLayout(this);
	Util::setLayoutZero(v_contentsLayout);
	v_contentsLayout->setSpacing(16);
	v_contentsLayout->setContentsMargins(0,16,0,16);

	QWidget *titleContainer = new QWidget;
	titleContainer->setFixedHeight(24);
	titleContainer->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Fixed);
	titleContainer->setStyleSheet(titleBarStyle);
	QHBoxLayout *h_titleContainerLayout = new QHBoxLayout(titleContainer);
	Util::setLayoutZero(h_titleContainerLayout);
	h_titleContainerLayout->setContentsMargins(24,0,24,0);
	w_rightContainer = new QWidget;
	w_rightContainer->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
	QHBoxLayout *h_rightContainerLayout = new QHBoxLayout(w_rightContainer);
	Util::setLayoutZero(h_rightContainerLayout);
	//h_titleContainerLayout->setSpacing(15);
	//QWidget *w_titlew = new QWidget;
	//w_titlew->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
	//w_titlew->setFixedWidth(120);
	//QHBoxLayout *h_titleWLayout = new QHBoxLayout(w_titlew);
	//Util::setLayoutZero(h_titleWLayout);
	l_sectionTitle = new tx4_label(sectionTitle, 10, titleLabelStyle, QFont::Medium, Qt::AlignLeft);
	//h_titleWLayout->addWidget(l_sectionTitle);
	//h_titleWLayout->addStretch();

	b_returnButton = new tx4_toolbar_button(tx4_events_section::tr("RETURN") + QString(" (R)"), false, "");
	b_selectDeselectAllButton = new tx4_toolbar_button(tx4_events_section::tr("SELECT ALL") + QString(" (S)"), false, "");
	
	QObject::connect(b_returnButton, &tx4_toolbar_button::clicked, this, &tx4_events_section::on_returnClick);
	QObject::connect(b_selectDeselectAllButton, &tx4_toolbar_button::clicked, this, &tx4_events_section::on_selectDeselectAll);

	l_countSubitle = new tx4_label(QString::number(i_totalEvents) + tx4_events_section::tr(" EVENTS"), 10, subLabelStyle, QFont::Medium, Qt::AlignLeft);
	l_sizeSubitle = new tx4_label(s_totalSize, 10, subLabelStyle, QFont::Medium, Qt::AlignLeft, Qt::AlignTop);
	l_lengthSubitle = new tx4_label(s_totalLength, 10, subLabelStyle, QFont::Medium, Qt::AlignLeft);
	h_rightContainerLayout->addWidget(l_countSubitle);
	h_rightContainerLayout->addSpacerItem(new QSpacerItem(20, 0, QSizePolicy::Fixed, QSizePolicy::Expanding));
	//h_rightContainerLayout->addWidget(new tx4_label("[", 10, subLabelBraceStyle, QFont::Medium, Qt::AlignCenter));
	h_rightContainerLayout->addWidget(l_sizeSubitle);
	h_rightContainerLayout->addSpacerItem(new QSpacerItem(20, 0, QSizePolicy::Fixed, QSizePolicy::Expanding));
	//h_rightContainerLayout->addWidget(new tx4_label("]", 10, subLabelBraceStyle, QFont::Medium, Qt::AlignCenter));
	//h_rightContainerLayout->addSpacerItem(new QSpacerItem(5, 0, QSizePolicy::Fixed, QSizePolicy::Expanding));
	//h_rightContainerLayout->addWidget(new tx4_label("[", 10, subLabelBraceStyle, QFont::Medium, Qt::AlignCenter));
	h_rightContainerLayout->addWidget(l_lengthSubitle);
	//h_rightContainerLayout->addWidget(new tx4_label("]", 10, subLabelBraceStyle, QFont::Medium, Qt::AlignCenter));

	h_titleContainerLayout->addWidget(l_sectionTitle);
	h_titleContainerLayout->addSpacerItem(new QSpacerItem(24, 0, QSizePolicy::Fixed, QSizePolicy::Expanding));
	h_titleContainerLayout->addWidget(w_rightContainer);
	h_titleContainerLayout->addStretch();
	h_titleContainerLayout->addWidget(b_selectDeselectAllButton);
	h_titleContainerLayout->addSpacerItem(new QSpacerItem(1, 0, QSizePolicy::Fixed, QSizePolicy::Expanding));
	h_titleContainerLayout->addWidget(b_returnButton);
	b_selectDeselectAllButton->setVisible(false);
	b_returnButton->setVisible(false);

	w_sectionScroll = new QWidget;
	w_sectionScroll->setStyleSheet(scrollAreaStyle);
	w_sectionScroll->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Fixed);
	QHBoxLayout *h_recentsScrollLayout = new QHBoxLayout(w_sectionScroll);
	Util::setLayoutZero(h_recentsScrollLayout);
	h_recentsScrollLayout->setSpacing(10);

	// TODO:
	for (int i = 0; i < i_totalEvents; i++) {
		tx4_event_preview *preview = new tx4_event_preview("", "", "", "", "", "", "","", "", "", titleLabelStyle, i);
		h_recentsScrollLayout->addWidget(preview);
		previews.append(preview);
		//QObject::connect(preview, &tx4_event_preview::select, this, &tx4_events_section::on_updateSelect);
		//QObject::connect(preview, &tx4_event_preview::deselect, this, &tx4_events_section::on_updateDeselect);
    }
	h_recentsScrollLayout->addStretch();

	// horizontal preview scroll
	w_scrollContainer = new QWidget;
	w_scrollContainer->setFixedHeight(PREVIEW_H);
	w_scrollContainer->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Fixed);
	w_scrollContainer->setStyleSheet(scrollAreaStyle);
	QHBoxLayout *h_scrollContainerLayout = new QHBoxLayout(w_scrollContainer);
	Util::setLayoutZero(h_scrollContainerLayout);
	h_scrollContainerLayout->setContentsMargins(10, 0, 10, 0);

	QWidget *buttonholder = new QWidget;
	buttonholder->setStyleSheet(buttonHolderStyle);
	buttonholder->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Fixed);
	QHBoxLayout *h_buttonholderLayout = new QHBoxLayout(buttonholder);
	Util::setLayoutZero(h_buttonholderLayout);
	//h_buttonholderLayout->setContentsMargins(20, 0, 20, 0);
	b_navButtonLeft = new tx4_nav_button("", true, "", true);
	b_navButtonRight = new tx4_nav_button("", true, "", false);
	QObject::connect(b_navButtonLeft, &tx4_nav_button::buttonClicked, this, &tx4_events_section::on_navLeftClick);
	QObject::connect(b_navButtonRight, &tx4_nav_button::buttonClicked, this, &tx4_events_section::on_navRightClick);

	scrollarea = new QScrollArea();
	scrollarea->verticalScrollBar()->setEnabled(false);
	scrollarea->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
	scrollarea->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
	scrollarea->setStyleSheet(scrollAreaStyle);
	scrollarea->setWidget(w_sectionScroll);
	scrollarea->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Fixed);

	 //empty state message
	w_emptyState = new QWidget;
	w_emptyState->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
	w_emptyState->setStyleSheet(emptyStateStyle);
	QHBoxLayout *h_emptyStateLayout = new QHBoxLayout(w_emptyState);
	Util::setLayoutZero(h_emptyStateLayout);
	h_emptyStateLayout->setContentsMargins(20, 0, 20, 0);
	l_emptyState = new tx4_label(tx4_events_section::tr("NO EVENTS LOADED"), 10, subLabelStyleOff, QFont::Medium, Qt::AlignLeft);
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
	//h_buttonholderLayout->addSpacerItem(new QSpacerItem(16, 0, QSizePolicy::Fixed, QSizePolicy::Expanding));
	h_buttonholderLayout->addWidget(b_navButtonLeft);
	h_buttonholderLayout->addWidget(w_scrollContainer);
	//h_buttonholderLayout->addStretch();
	h_buttonholderLayout->addWidget(b_navButtonRight);
	//h_buttonholderLayout->addSpacerItem(new QSpacerItem(16, 0, QSizePolicy::Fixed, QSizePolicy::Expanding));
	s_emptyStateStackLayout->addWidget(w_emptyState);
	s_emptyStateStackLayout->addWidget(buttonholder);
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

void tx4_events_section::setNavButtonStates(bool style_left, bool style_right, bool enable_left, bool enable_right) {
	b_navButtonLeft->setButtonState(style_left);
	b_navButtonRight->setButtonState(style_right);
	b_navButtonLeft->setVisible(enable_left);
	b_navButtonRight->setVisible(enable_right);
}
void tx4_events_section::setSelectDeselectButtonState(bool state, bool visible) {
	b_selectDeselectAllButton->setButtonState(state);
	b_selectDeselectAllButton->setVisible(visible);
}
void tx4_events_section::setReturnButtonState(bool state, bool visible) {
	b_returnButton->setButtonState(state);
	b_returnButton->setVisible(visible);
}


// TODO: public select/deselect for all
void tx4_events_section::selectAll() {
	deselectAll();

	if (eventsLoaded && !previews.isEmpty()) {
		for (int i = 0; i < previews.count(); i++) {
			if (!previews[i]->previewSelected) {
				previews[i]->selectPreview();
			}
		}

		if (b_selectDeselectAllButton->s_enabled) { b_selectDeselectAllButton->setButtonText(tx4_events_section::tr("DESELECT ALL") + QString(" (D)")); }
	}
}
void tx4_events_section::deselectAll() {
	if (eventsLoaded && !previews.isEmpty()) {
		for (int i = 0; i < previews.count(); i++) {
			if (previews[i]->previewSelected) {
				previews[i]->deselectPreview();
			}
		}

		if (b_selectDeselectAllButton->s_enabled) { b_selectDeselectAllButton->setButtonText(tx4_events_section::tr("SELECT ALL") + QString(" (S)")); }
	}
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
			goLeft(SCROLL_DIFF);
		}
	}
	void tx4_events_section::scrollRight() {
		if (scrollarea->rect().contains(scrollarea->mapFromGlobal(QCursor::pos()))) {
			goRight(SCROLL_DIFF);
		}
	}
	void tx4_events_section::on_navLeftClick() {
		goLeft(CLICK_SCROLL_DIFF);
	}
	void tx4_events_section::on_navRightClick() {
		goRight(CLICK_SCROLL_DIFF);
	}
	void tx4_events_section::goLeft(const int &amount) {
		if (i_scrollValue > scrollarea->horizontalScrollBar()->minimum()) {
			i_scrollValue = i_scrollValue-amount;
			scrollarea->horizontalScrollBar()->setValue(i_scrollValue);
		} else {
			setReturnButtonState(false, true);
		}
	}
	void tx4_events_section::goRight(const int &amount) {
		if (i_scrollValue < scrollarea->horizontalScrollBar()->maximum()) {
			i_scrollValue = i_scrollValue+amount;
			scrollarea->horizontalScrollBar()->setValue(i_scrollValue);
			setReturnButtonState(true, true);
		}
	}
	void tx4_events_section::on_returnClick() {
		i_scrollValue = 0;
		scrollarea->horizontalScrollBar()->setValue(i_scrollValue);
		setReturnButtonState(false, true);
	}
	void tx4_events_section::on_selectDeselectAll() {
		if (!selectAllClicked) {
			selectAllClicked = true;
			on_selectAll();
		} else {
			selectAllClicked = false;
			on_deselectAll();
		}
	}
	void tx4_events_section::on_selectAll() {
		selectAll();
	}
	void tx4_events_section::on_deselectAll() {
		deselectAll();
	}
// }


void tx4_events_section::populateEvents(QList<tx4_event*> pop_events) {
	auto *hbox = qobject_cast<QHBoxLayout*>(w_sectionScroll->layout());
	Util::clearLayout(hbox);
	//delete w_sectionScroll->layout();//delete the first layout
	previews.clear();
	events.clear();
	int count = pop_events.count();
	i_totalEvents = count;
	qint64 sizeCount = 0;
	qint64 timeCount = 0;
	//QHBoxLayout *h_recentsScrollLayout = new QHBoxLayout(w_sectionScroll);
	//Util::setLayoutZero(h_recentsScrollLayout);
	//h_recentsScrollLayout->setSpacing(10);

	for (int i = 0; i < i_totalEvents; i++) {
		tx4_event_preview *preview = new tx4_event_preview(pop_events[i]->s_dateDisplay, pop_events[i]->s_countDisplay, pop_events[i]->s_sizeDisplay, pop_events[i]->s_lengthDisplay, pop_events[i]->s_metaDataTimestampString, pop_events[i]->s_metaDataCityString, pop_events[i]->s_metaDataLatString, pop_events[i]->s_metaDataLonString, pop_events[i]->s_metaDataReasonString, pop_events[i]->s_metaDataCameraString, titleLabelStyle, i);
		//tx4_event_preview *preview = new tx4_event_preview("2021_08_22", "12x4", "21.75MB", "09:13", titleLabelStyle, i);
		//preview->setParent(w_sectionScroll);
		hbox->addWidget(preview);
		//h_recentsScrollLayout->addWidget(preview);
		preview->show();
		previews.append(preview);
		events.append(pop_events[i]);
		QObject::connect(preview, &tx4_event_preview::select, this, &tx4_events_section::on_updateSelect);
		QObject::connect(preview, &tx4_event_preview::deselect, this, &tx4_events_section::on_updateDeselect);

		sizeCount += pop_events[i]->i_Size;
		timeCount += pop_events[i]->i_TotalClipLength;
    }
	hbox->addStretch();
	w_sectionScroll->setLayout(hbox);
	//qDebug() << "hbox::EMPTY?? " << hbox->isEmpty();

	QString titleEventsString = QString::number(i_totalEvents) + tx4_events_section::tr(" EVENTS");
	QString titleSizeString = Util::humanSize(sizeCount);
	QString titleTimeString = Util::format_duration(timeCount);
	s_totalSize = titleSizeString;
	s_totalLength = titleTimeString;
	l_countSubitle->setLabelText(titleEventsString);
	l_sizeSubitle->setLabelAlignment(Qt::AlignLeft, Qt::AlignTop);
	l_sizeSubitle->setLabelText(s_totalSize);
	l_lengthSubitle->setLabelText(s_totalLength);
}
void tx4_events_section::resetSubtitle() {
	selectModeActive = false;
	QString formDeselect = QString::number(i_totalEvents) + tx4_events_section::tr(" EVENTS");
	l_countSubitle->setText(formDeselect);
	l_sizeSubitle->setLabelAlignment(Qt::AlignLeft, Qt::AlignVCenter);
	l_sizeSubitle->setText(s_totalSize);
	l_sizeSubitle->setStyleSheet(subLabelStyle);
	l_lengthSubitle->setText(s_totalLength);
	l_lengthSubitle->setStyleSheet(subLabelStyle);
}


// SLOTS : {
	void tx4_events_section::on_updateSelect(int idx) {
		if (!selectModeActive) {
			selectModeActive = true;
			i_selectedCount += 1;
			i_selectedSize += events[idx]->i_Size;
			i_selectedLength += events[idx]->i_TotalClipLength;
			QString formSelect = QString::number(i_selectedCount) + QString("/") + QString::number(i_totalEvents) + tx4_events_section::tr(" SELECTED");
			l_countSubitle->setText(formSelect);
			l_sizeSubitle->setLabelAlignment(Qt::AlignLeft, Qt::AlignTop);
			l_sizeSubitle->setLabelText(Util::humanSize(i_selectedSize) + "*");
			l_sizeSubitle->setStyleSheet(subLabelStyleOff);
			l_lengthSubitle->setLabelAlignment(Qt::AlignLeft, Qt::AlignTop);
			l_lengthSubitle->setLabelText(Util::format_duration(i_selectedLength) + "*");
			l_lengthSubitle->setStyleSheet(subLabelStyleOff);

			selectedPreviews.append(previews[idx]);
			selectedEvents.append(events[idx]);
			emit eventSelect(events[idx], previews[idx]);
			return;
		}

		i_selectedCount += 1;
		i_selectedSize += events[idx]->i_Size;
		i_selectedLength += events[idx]->i_TotalClipLength;
		QString formSelect = QString::number(i_selectedCount) + QString("/") + QString::number(i_totalEvents) + tx4_events_section::tr(" SELECTED");
		l_countSubitle->setText(formSelect);
		l_sizeSubitle->setLabelAlignment(Qt::AlignLeft, Qt::AlignTop);
		l_sizeSubitle->setLabelText(Util::humanSize(i_selectedSize) + "*");
		l_lengthSubitle->setLabelAlignment(Qt::AlignLeft, Qt::AlignTop);
		l_lengthSubitle->setLabelText(Util::format_duration(i_selectedLength) + "*");

		selectedPreviews.append(previews[idx]);
		selectedEvents.append(events[idx]);
		emit eventSelect(events[idx], previews[idx]);
	}
	void tx4_events_section::on_updateDeselect(int idx) {
		i_selectedCount -= 1;
		i_selectedSize -= events[idx]->i_Size;
		i_selectedLength -= events[idx]->i_TotalClipLength;
		QString formDeselect = QString::number(i_selectedCount) + QString("/") + QString::number(i_totalEvents) + tx4_events_section::tr(" SELECTED");
		l_countSubitle->setText(formDeselect);
		l_sizeSubitle->setLabelAlignment(Qt::AlignLeft, Qt::AlignTop);
		l_sizeSubitle->setLabelText(Util::humanSize(i_selectedSize) + "*");
		l_lengthSubitle->setLabelAlignment(Qt::AlignLeft, Qt::AlignTop);
		l_lengthSubitle->setLabelText(Util::format_duration(i_selectedLength) + "*");

		if (i_selectedCount <= 0) {
			resetSubtitle();
		}

		if (i_selectedCount >= 0) {
			selectedPreviews.removeAt(i_selectedCount);
			selectedEvents.removeAt(i_selectedCount);
			emit eventDeselect(events[idx], previews[idx]);
		}
	}
// }