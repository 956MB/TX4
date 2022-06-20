
#include "tx4_viewer.h"

tx4_viewer::tx4_viewer(QList<tx4_event*> events, QWidget *parent)
	: QWidget(parent)
	, l_loadedEvents(events)
	, n_currentEventIndex(0)
	, n_currentLayoutIndex(0)
	, n_currentSelectedView(0) // TODO: May want to give tx4 the reference of the selected view index, because if we close the events viewer screen, the selected index returns to 0 (Front). Do we want it always to start at 0 (Front), or keep on whatever it was last on like Right, even if its whole new events being loaded. ???
{
	o_currentEvent = l_loadedEvents[n_currentEventIndex];
	e_selectedLayout = layouts[n_currentLayoutIndex].first;

	this->setAttribute(Qt::WA_StyledBackground); // <--- this attribute solves issue of background color not being drawn on custom widget, no need for reimplementing paintEvent, yet.
	//this->setFixedHeight(TOOLBAR_H);
	this->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
	this->setStyleSheet(S_VIEWER_SCREEN);

	initContents();
	initShortcuts();
}

tx4_viewer::~tx4_viewer() {}

void tx4_viewer::initContents() {
	QVBoxLayout *v_contentsLayout = new QVBoxLayout(this);
	Util::setLayoutZero(v_contentsLayout);
	//v_contentsLayout->setContentsMargins(OUTER_MARGIN,0,OUTER_MARGIN,0);

	initInfoBar();
	initViews();
	initControlBar();

	v_contentsLayout->addWidget(w_infoBar);
	v_contentsLayout->addWidget(w_innerViewsContainer);
	v_contentsLayout->addWidget(w_controlBar);

	this->setLayout(v_contentsLayout);
}

void tx4_viewer::initShortcuts() {
	o_shortcutManager = new tx4_shortcuts_viewer(this);

	QObject::connect(o_shortcutManager, &tx4_shortcuts::shortcutPlayPause, this, [=]{ qDebug() << "shortcutPlayPause::here"; });
	QObject::connect(o_shortcutManager, &tx4_shortcuts::shortcutSkipBack, this, [=]{ qDebug() << "shortcutSkipBack::here"; });
	QObject::connect(o_shortcutManager, &tx4_shortcuts::shortcutSkipForward, this, [=]{ qDebug() << "shortcutSkipForward::here"; });
	QObject::connect(o_shortcutManager, &tx4_shortcuts::shortcutSkipBackInterval, this, [=]{ qDebug() << "shortcutSkipBackInterval::here"; });
	QObject::connect(o_shortcutManager, &tx4_shortcuts::shortcutSkipForwardInterval, this, [=]{ qDebug() << "shortcutSkipForwardInterval::here"; });
}

void tx4_viewer::initInfoBar() {
	auto dt = QDateTime::fromString(o_currentEvent->s_metaDataTimestampString, Qt::ISODate);
	w_infoBar = new tx4_info_bar(o_currentEvent->s_eventType, o_currentEvent->s_metaDataReasonString, o_currentEvent->s_metaDataCityString, dt.toString("dddd, MMMM d, yyyy"), dt.toString("h:mm a"), {"", o_currentEvent->s_metaDataReasonString, QString(o_currentEvent->s_metaDataLatString + ", " + o_currentEvent->s_metaDataLonString), "", ""});
}
void tx4_viewer::initViews() {
	w_innerViewsContainer = new QWidget;
	QBoxLayout *h_innerContainerLayout = new QBoxLayout(QBoxLayout::LeftToRight, w_innerViewsContainer);
	//QHBoxLayout *h_innerContainerLayout = new QHBoxLayout(w_innerViewsContainer);
	Util::setLayoutZero(h_innerContainerLayout);
	w_innerViewsContainer->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);

	initViewsLayout();

	b_prevButton = new tx4_control_bar_button(ICONS_BAR, ButtonState::Enabled, "", 3);
	b_prevButton->setFixedWidth(30);
	b_nextButton = new tx4_control_bar_button(ICONS_BAR, ButtonState::Enabled, "", 3);
	b_nextButton->setFixedWidth(30);
	Util::setWidgetsSizePolicy(QSizePolicy::Fixed, QSizePolicy::Expanding, {b_prevButton, b_nextButton});

	QObject::connect(b_prevButton, &tx4_control_bar_button::clicked, this, [=]{ goNextEvent(-1); });
	QObject::connect(b_nextButton, &tx4_control_bar_button::clicked, this, [=]{ goNextEvent(1); });

	setButtonStates(ButtonState::Hidden, (l_loadedEvents.count() <= 1 ? ButtonState::Hidden: ButtonState::Enabled));

	h_innerContainerLayout->addWidget(b_prevButton);
	h_innerContainerLayout->addWidget(w_viewsLayout);
	h_innerContainerLayout->addWidget(b_nextButton);
}
void tx4_viewer::initViewsLayout() {
	switch (e_selectedLayout) {
		case ViewsLayout::L3:   w_viewsLayout = new tx4_views_layout_L3(o_currentEvent, n_currentSelectedView);   break;
		case ViewsLayout::L4:   w_viewsLayout = new tx4_views_layout_L4(o_currentEvent, n_currentSelectedView);   break;
		case ViewsLayout::L13V: w_viewsLayout = new tx4_views_layout_L13V(o_currentEvent, n_currentSelectedView); break;
	}

	QObject::connect(w_viewsLayout, &tx4_views_layout::selectedViewChange, this, &tx4_viewer::on_selectedViewChangeSignal);
}
void tx4_viewer::initControlBar() {
	w_controlBar = new tx4_control_bar();
	QObject::connect(w_controlBar, &tx4_control_bar::cycleLayout, this, &tx4_viewer::on_cycleLoadoutSignal);
}

void tx4_viewer::goNextEvent(int incr) {
	Util::cycleListBoth(n_currentEventIndex, incr, l_loadedEvents.count());

	if (n_currentEventIndex == 0)														{ setButtonStates(ButtonState::Hidden, ButtonState::Enabled); }
	if ((0 < n_currentEventIndex) && (n_currentEventIndex < l_loadedEvents.count()-1))	{ setButtonStates(ButtonState::Enabled, ButtonState::Enabled); }
	if (n_currentEventIndex == l_loadedEvents.count()-1)								{ setButtonStates(ButtonState::Enabled, ButtonState::Hidden); }

	o_currentEvent = l_loadedEvents[n_currentEventIndex];

	auto dt = QDateTime::fromString(o_currentEvent->s_metaDataTimestampString, Qt::ISODate);
	w_infoBar->updateInfo(o_currentEvent->s_eventType, o_currentEvent->s_metaDataReasonString, o_currentEvent->s_metaDataCityString, dt.toString("dddd, MMMM d, yyyy"), dt.toString("h:mm a"), {"", o_currentEvent->s_metaDataReasonString, QString(o_currentEvent->s_metaDataLatString + ", " + o_currentEvent->s_metaDataLonString), "", ""});
	// update viewslayout here
	w_controlBar->resetControlBar();
}

void tx4_viewer::setButtonStates(ButtonState prevState, ButtonState nextState) {
	b_prevButton->setButtonState(prevState);
	b_nextButton->setButtonState(nextState);
}

void tx4_viewer::resizeInnerViews() {
	w_viewsLayout->resizeLayoutViews();
}


// SLOTS
void tx4_viewer::on_cycleLoadoutSignal() {
	Util::cycleList(n_currentLayoutIndex, layouts.count());
	e_selectedLayout = layouts[n_currentLayoutIndex].first;
	
	// update views layout widget (w_viewsLayout)
	auto *h_innerViewsContainerLayout = qobject_cast<QBoxLayout*>(w_innerViewsContainer->layout());
	h_innerViewsContainerLayout->removeWidget(w_viewsLayout);
	Util::deleteAndCleanup(w_viewsLayout);
	initViewsLayout();
	h_innerViewsContainerLayout->insertWidget(1, w_viewsLayout);

	w_controlBar->updateLayoutIcon(layouts[n_currentLayoutIndex].second);

	// TODO: for some reason calling resizeInnerViews() or signaling back to tx4 doesnt make L13V views resize, even when calling it after everything is reset and updated
	resizeInnerViews();
}
void tx4_viewer::on_selectedViewChangeSignal(int selectedIndex) {
	n_currentSelectedView = selectedIndex;
}