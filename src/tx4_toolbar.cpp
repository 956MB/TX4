
#include "tx4_toolbar.h"

tx4_toolbar::tx4_toolbar(const bool &loaded, const bool &auto_load, QWidget *parent)
	: QWidget(parent) {

	scrollValue = 0;
	eventQueueCount = 0;
	//eventQueueClipsCount = 0;
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
	QObject::connect(b_openButton, &tx4_toolbar_button::clicked, this, [=]{ emit eventsOpen(); });
	QObject::connect(b_loadEventsButton, &tx4_toolbar_button::clicked, this, [=]{ emit eventsLoad(); });
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
	l_selectedEventsTitle = new tx4_label(tx4_toolbar::tr("EVENT QUEUE: "), 9, titleLabelStyleZeroDisabled, QFont::DemiBold, Qt::AlignLeft);
	l_selectedEventsTitle->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Expanding);

	w_queueContainer = new QWidget;
	w_queueContainer->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
	QHBoxLayout *h_queueContainerLayout = new QHBoxLayout(w_queueContainer);
	Util::setLayoutZero(h_queueContainerLayout);
	h_queueContainerLayout->setContentsMargins(10,0,10,0);
	//l_queueTitle = new tx4_label("--", 10, queueLabelStyleDisabled, QFont::Medium, Qt::AlignLeft);
	//l_queueTitle->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Expanding);
	//l_queueTitle->setContentsMargins(10,0,10,0);
	//h_queueContainerLayout->addWidget(l_queueTitle);
	//h_queueContainerLayout->addStretch();

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
	queueScrollarea->setWidget(w_queueContainer);
	h_scrollContainerLayout->addWidget(queueScrollarea);

	QWidget *loadedContainer = new QWidget;
	loadedContainer->setStyleSheet(blankStyle);
	loadedContainer->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Expanding);
	QHBoxLayout *h_loadedContainerLayout = new QHBoxLayout(loadedContainer);
	Util::setLayoutZero(h_loadedContainerLayout);

	l_eventsLoadedTitle = new tx4_key_value_label(tx4_toolbar::tr("DIR LOADED"), eventsLoaded ? tx4_toolbar::tr("true") : tx4_toolbar::tr("false"), 9, titleLabelStyle, eventsLoaded ? loadedTrueLabelStyle : loadedFalseLabelStyle, QFont::Medium, Qt::AlignLeft);
	l_eventsLoadedTitle->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Expanding);
	l_autoLoadTitle = new tx4_key_value_label(tx4_toolbar::tr("AUTO LOAD"), autoLoad ? tx4_toolbar::tr("true") : tx4_toolbar::tr("false"), 9, titleLabelStyle, autoLoad ? loadedTrueLabelStyle : loadedFalseLabelStyle, QFont::Medium, Qt::AlignLeft);
	l_autoLoadTitle->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Expanding);

	h_loadedContainerLayout->addWidget(l_eventsLoadedTitle);
	h_loadedContainerLayout->addSpacerItem(new QSpacerItem(10, 0, QSizePolicy::Fixed, QSizePolicy::Expanding));
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

void tx4_toolbar::updateEventQueue(QList<tx4_event*> &eventQueue, QList<tx4_event_preview*> &previewQueue) {
	auto *queue_hbox = qobject_cast<QHBoxLayout*>(w_queueContainer->layout());
	eventQueueCount = eventQueue.count();
	//QString formQueue;

	if (eventQueueCount <= 0) {
		b_openButton->setButtonText(tx4_toolbar::tr("VIEW EVENTS"));
		b_openButton->setButtonState(false);
		//l_selectedEventsTitle->setLabelText(tx4_toolbar::tr("EVENT QUEUE: "));
		Util::clearLayout(queue_hbox);
		//l_queueTitle->setLabelText("--");
		l_selectedEventsTitle->setStyleSheet(titleLabelStyleZeroDisabled);
		//l_queueTitle->setStyleSheet(queueLabelStyleDisabled);
	} else {
		b_openButton->setButtonState(true);
		b_openButton->setButtonText(tx4_toolbar::tr("VIEW EVENTS") + QString(" (O)"));
		Util::clearLayout(queue_hbox);

		//formQueue = "";
		int count = 0;
		//eventQueueClipsCount = 0;
		tx4_event *e;
		foreach (e, eventQueue) {
			//eventQueueClipsCount += e->clipCount;
			QString formQueue = "";
			QString newE = QString::number(e->selectIndex) + QString(":") + QString("\"") + QString(e->s_dateDisplay) + QString("\"");
			formQueue += newE;
			//if (count != eventQueueCount) { formQueue += QString(", "); }

			tx4_queue_entry *w_newEntry = new tx4_queue_entry(formQueue, *previewQueue[count]);
			queue_hbox->addWidget(w_newEntry);
			if (count != eventQueueCount-1) {
				queue_hbox->addWidget(new tx4_label(", ", 10, queueLabelStyle, QFont::Medium, Qt::AlignCenter));
			}
			count += 1;
		}
		queue_hbox->addStretch();
		w_queueContainer->setLayout(queue_hbox);
		//l_queueTitle->setLabelText(formQueue);

		//formCount = tx4_toolbar::tr("EVENT QUEUE: ");
		l_selectedEventsTitle->setStyleSheet(titleLabelStyle);
		//l_queueTitle->setStyleSheet(queueLabelStyle);
	}
	
	//l_selectedEventsTitle->setLabelText(formCount);
}

void tx4_toolbar::toggleEventsLoaded(bool loaded) {
	eventsLoaded = loaded;
	l_eventsLoadedTitle->l_valueLabel->setText(eventsLoaded ? tx4_toolbar::tr("true") : tx4_toolbar::tr("false"));
	l_eventsLoadedTitle->l_valueLabel->setStyleSheet(eventsLoaded ? loadedTrueLabelStyle : loadedFalseLabelStyle);
	b_loadEventsButton->setButtonState(!eventsLoaded);
	b_loadEventsButton->setButtonText(eventsLoaded ? tx4_toolbar::tr("LOAD DIR") + QString(" (L)") : tx4_toolbar::tr("LOAD DIR"));
}