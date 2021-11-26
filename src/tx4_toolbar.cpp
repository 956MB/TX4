
#include "tx4_toolbar.h"

tx4_toolbar::tx4_toolbar(const bool &loaded, const bool &auto_load, QWidget *parent)
	: QWidget(parent) {

	scrollValue = 0;
	eventQueueCount = 0;
	eventQueueClipsCount = 0;
	eventsLoaded = loaded;
	autoLoad = auto_load;

	this->setAttribute(Qt::WA_StyledBackground); // <--- this attribute solves issue of background color not being drawn on custom widget, no need for reimplementing paintEvent, yet.
	this->setFixedHeight(TOOLBAR_H);
	this->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Fixed);
	this->setStyleSheet(toolbarBodyStyle);

	initContents();
}

tx4_toolbar::~tx4_toolbar() {}

void tx4_toolbar::initContents() {
	QHBoxLayout *h_mainLayout = new QHBoxLayout(this);
	Util::setLayoutZero(h_mainLayout);
	//h_mainLayout->setSpacing(20);
	//h_mainLayout->setContentsMargins(0,0,0,0);

	b_openButton = new tx4_toolbar_button(tx4_toolbar::tr("VIEW EVENTS"), false, "");
	b_loadEventsButton = new tx4_toolbar_button(tx4_toolbar::tr("LOAD DIR"), !eventsLoaded, "");
	connect(b_openButton, &tx4_toolbar_button::clicked, this, [=]{ emit eventsOpen(); });
	connect(b_loadEventsButton, &tx4_toolbar_button::clicked, this, [=]{ emit eventsLoad(); });
	//QWidget *infoContainer = new QWidget;
	//infoContainer->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Fixed);
	//QHBoxLayout *h_infoContainerLayout = new QHBoxLayout(infoContainer);
	//Util::setLayoutZero(h_infoContainerLayout);
	//h_infoContainerLayout->setContentsMargins(20,3,20,3);

	QWidget *eventQueueContainer = new QWidget;
	eventQueueContainer->setFixedHeight(23);
	eventQueueContainer->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Fixed);
	QHBoxLayout *h_eventQueueContainerLayout = new QHBoxLayout(eventQueueContainer);
	Util::setLayoutZero(h_eventQueueContainerLayout);
	h_eventQueueContainerLayout->setContentsMargins(20,0,20,0);
	//h_eventQueueContainerLayout->setSpacing(5);
	l_selectedEventsTitle = new tx4_label(tx4_toolbar::tr("EVENT QUEUE: "), 9, titleLabelStyleZeroDisabled, QFont::DemiBold, Qt::AlignLeft, "Anonymous Pro");
	l_selectedEventsTitle->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Expanding);

	QWidget *queueContainer = new QWidget;
	queueContainer->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
	QHBoxLayout *h_queueContainerLayout = new QHBoxLayout(queueContainer);
	Util::setLayoutZero(h_queueContainerLayout);
	l_queueTitle = new tx4_label("--", 10, queueLabelStyleDisabled, QFont::Medium, Qt::AlignLeft, "Anonymous Pro");
	l_queueTitle->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Expanding);
	l_queueTitle->setContentsMargins(10,0,10,0);
	h_queueContainerLayout->addWidget(l_queueTitle);
	h_queueContainerLayout->addStretch();

	QWidget *scrollContainer = new QWidget;
	scrollContainer->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
	QHBoxLayout *h_scrollContainerLayout = new QHBoxLayout(scrollContainer);
	Util::setLayoutZero(h_scrollContainerLayout);
	queueScrollarea = new QScrollArea();
	queueScrollarea->verticalScrollBar()->setEnabled(false);
	queueScrollarea->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
	queueScrollarea->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
	queueScrollarea->setWidgetResizable(true);
	queueScrollarea->setStyleSheet(scrollAreaStyle);
	queueScrollarea->setWidget(queueContainer);
	h_scrollContainerLayout->addWidget(queueScrollarea);

	QWidget *loadedContainer = new QWidget;
	loadedContainer->setStyleSheet(blankStyle);
	loadedContainer->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Expanding);
	QHBoxLayout *h_loadedContainerLayout = new QHBoxLayout(loadedContainer);
	Util::setLayoutZero(h_loadedContainerLayout);

	l_eventsLoadedTitle = new tx4_key_value_label(tx4_toolbar::tr("DIR LOADED"), eventsLoaded ? tx4_toolbar::tr("true") : tx4_toolbar::tr("false"), 9, titleLabelStyle, eventsLoaded ? loadedTrueLabelStyle : loadedFalseLabelStyle, QFont::Medium, Qt::AlignLeft, "Anonymous Pro");
	l_eventsLoadedTitle->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Expanding);
	l_autoLoadTitle = new tx4_key_value_label(tx4_toolbar::tr("AUTO LOAD"), autoLoad ? tx4_toolbar::tr("true") : tx4_toolbar::tr("false"), 9, titleLabelStyle, autoLoad ? loadedTrueLabelStyle : loadedFalseLabelStyle, QFont::Medium, Qt::AlignLeft, "Anonymous Pro");
	l_autoLoadTitle->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Expanding);

	h_loadedContainerLayout->addWidget(l_eventsLoadedTitle);
	h_loadedContainerLayout->addSpacerItem(new QSpacerItem(5, 0, QSizePolicy::Fixed, QSizePolicy::Expanding));
	h_loadedContainerLayout->addWidget(l_autoLoadTitle);

	h_eventQueueContainerLayout->addWidget(l_selectedEventsTitle);
	h_eventQueueContainerLayout->addSpacerItem(new QSpacerItem(20, 0, QSizePolicy::Fixed, QSizePolicy::Expanding));
	h_eventQueueContainerLayout->addWidget(scrollContainer);
	//h_eventQueueContainerLayout->addStretch();
	h_eventQueueContainerLayout->addSpacerItem(new QSpacerItem(20, 0, QSizePolicy::Fixed, QSizePolicy::Expanding));
	h_eventQueueContainerLayout->addWidget(loadedContainer);
	//l_selectedEventsTitle->setVisible(false);
	//l_queueTitle->setVisible(false);

	h_mainLayout->addSpacerItem(new QSpacerItem(20, 0, QSizePolicy::Fixed, QSizePolicy::Expanding));
	h_mainLayout->addWidget(b_openButton);
	h_mainLayout->addSpacerItem(new QSpacerItem(1, 0, QSizePolicy::Fixed, QSizePolicy::Expanding));
	h_mainLayout->addWidget(b_loadEventsButton);
	h_mainLayout->addSpacerItem(new QSpacerItem(20, 0, QSizePolicy::Fixed, QSizePolicy::Expanding));
	//h_mainLayout->addSpacerItem(new QSpacerItem(20, 0, QSizePolicy::Fixed, QSizePolicy::Expanding));
	h_mainLayout->addWidget(eventQueueContainer);

	this->setLayout(h_mainLayout);
}


// SCROLLWHEEL EVENTS: {
	void tx4_toolbar::wheelEvent(QWheelEvent* event) {
		if(event->angleDelta().y() > 0) { // up Wheel
			scrollLeft();
		} else if (event->angleDelta().y() < 0) { //down Wheel
			scrollRight();
		}
	}

	void tx4_toolbar::scrollLeft() {
		if (queueScrollarea->rect().contains(queueScrollarea->mapFromGlobal(QCursor::pos()))) {
			if (scrollValue > queueScrollarea->horizontalScrollBar()->minimum()) {
				scrollValue = scrollValue-SCROLL_DIFF;
				queueScrollarea->horizontalScrollBar()->setValue(scrollValue);
			}
		}
	}
	void tx4_toolbar::scrollRight() {
		if (queueScrollarea->rect().contains(queueScrollarea->mapFromGlobal(QCursor::pos()))) {
			if (scrollValue < queueScrollarea->horizontalScrollBar()->maximum()) {
				scrollValue = scrollValue+SCROLL_DIFF;
				queueScrollarea->horizontalScrollBar()->setValue(scrollValue);
			}
		}
	}
// }

void tx4_toolbar::updateEventQueue(QList<tx4_event_preview*> eventQueue) {
	eventQueueCount = eventQueue.count();
	QString formQueue;

	if (eventQueueCount <= 0) {
		b_openButton->setButtonState(false);
		//l_selectedEventsTitle->setLabelText(tx4_toolbar::tr("EVENT QUEUE: "));
		l_queueTitle->setLabelText("--");
		l_selectedEventsTitle->setStyleSheet(titleLabelStyleZeroDisabled);
		l_queueTitle->setStyleSheet(queueLabelStyleDisabled);
	} else {
		b_openButton->setButtonState(true);

		formQueue = "";
		int count = 0;
		eventQueueClipsCount = 0;
		tx4_event_preview *ep;
		foreach (ep, eventQueue) {
			count += 1;
			eventQueueClipsCount += ep->clipCount;
			QString newE = QString::number(ep->selectIndex) + QString(":") + QString("\"") + QString(ep->s_dateString) + QString("\"");
			formQueue += newE;
			if (count != eventQueueCount) { formQueue += QString(", "); }
		}
		l_queueTitle->setLabelText(formQueue);

		//formCount = tx4_toolbar::tr("EVENT QUEUE: ");
		l_selectedEventsTitle->setStyleSheet(titleLabelStyle);
		l_queueTitle->setStyleSheet(queueLabelStyle);
	}
	
	//l_selectedEventsTitle->setLabelText(formCount);
}

void tx4_toolbar::toggleEventsLoaded(bool loaded) {
	eventsLoaded = loaded;
	l_eventsLoadedTitle->l_valueLabel->setText(eventsLoaded ? tx4_toolbar::tr("true") : tx4_toolbar::tr("false"));
	l_eventsLoadedTitle->l_valueLabel->setStyleSheet(eventsLoaded ? loadedTrueLabelStyle : loadedFalseLabelStyle);
	b_loadEventsButton->setButtonState(!eventsLoaded);
}