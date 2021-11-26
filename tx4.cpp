
#include "tx4.h"

tx4::tx4(QWidget *parent)
	: QGoodWindow(parent)
	, selectedEvents(QList<tx4_event_preview*> ()) {

	//registerFileType("GiMdi.Document", "MDI Text Editor Document", ".gidoc", 0, true);
	//registerCommand("fancyCommand", "GiMdi.Document", "-fancy %1", "[fancy(\"%1\")]");
	//enableShellOpen();

	initWindowConfig();
	initShortcuts();

	on_eventsLoadSignal();
}

tx4::~tx4() {}


void tx4::initWindowConfig() {
	window_w = START_W;
	m_title = "";
	m_dark = true;
	m_selectMode = true;
	m_eventsLoaded = false;
	m_frame_style = QString("QFrame {background-color: %0; border: %1;}");
	m_color_str = "#000000";
	QString border_str = "none";

#ifdef QGOODWINDOW
	title_bar = new TitleBar(pixelRatio(), false, this);
	outerFrame = new QFrame(this);
	innerFrame = new QFrame(this);

	QVBoxLayout *innerLayout = new QVBoxLayout(innerFrame);
	Util::setLayoutZero(innerLayout);
	innerLayout->addWidget(title_bar);

	w_screensContainer = new QWidget;
	QStackedLayout *screensLayout = new QStackedLayout(w_screensContainer);
	screensLayout->setStackingMode(QStackedLayout::StackAll);
	Util::setLayoutZero(screensLayout);
	initMainContainer();
	screensLayout->addWidget(w_mainContainer);
	innerLayout->addWidget(w_screensContainer);

	QStackedLayout *outerlayout = new QStackedLayout(outerFrame);
	outerlayout->setStackingMode(QStackedLayout::StackAll);
	Util::setLayoutZero(outerlayout);
	// TODO: QStackedLayout in reverse order for some reason (first item added is on top)
	outerlayout->addWidget(innerFrame);

	setCentralWidget(outerFrame);

	connect(title_bar, &TitleBar::showMinimized, this, &tx4::showMinimized);
	connect(title_bar, &TitleBar::showNormal, this, &tx4::showNormal);
	connect(title_bar, &TitleBar::showMaximized, this, &tx4::showMaximized);
	connect(title_bar, &TitleBar::closeWindow, this, &tx4::close);
	connect(this, &tx4::windowTitleChanged, this, [=](const QString &title) {
		title_bar->setTitle(title);
	});
	//connect(this, &tx4::windowIconChanged, this, [=](const QIcon &icon) {
	//	if (!icon.isNull()) {
	//		const int pix_size = qCeil(16 * pixelRatio());
	//		title_bar->setIcon(icon.pixmap(pix_size , pix_size));
	//	}
	//});

	//connect(w_deleteDialog, &PHOT_Dialog::dialog_confirm, this, &PHOT::on_dialogConfirm);
	//connect(w_deleteDialog, &PHOT_Dialog::dialog_cancel, this, &PHOT::on_dialogCancel);

#ifndef Q_OS_MAC
	if (windowState().testFlag(Qt::WindowNoState))
		border_str = "1px solid #5c5a58";
#endif

#else
	frame = new QFrame(this);
	setCentralWidget(frame);
#endif

	innerFrame->setStyleSheet(m_frame_style.arg(m_color_str).arg(border_str));
	//frame->setStyleSheet(m_frame_style.arg(border_str));
    title_bar->setDarkMode(m_dark);
    title_bar->setBackBtn(false);
	//connect(title_bar, &TitleBar::goBack, this, &QtTemplate::on_cropButtonPressed);

	this->setWindowTitle(m_title);
	this->resize(qRound(START_W * pixelRatio()) , qRound(START_H * pixelRatio()));
	//this->setFixedSize(qRound(START_W * pixelRatio()) , qRound(START_H * pixelRatio()));
	this->setMinimumSize(MIN_W , MIN_H);
	this->setMargins(qRound(32*pixelRatio()) , qRound(30*pixelRatio()) , -20 , qRound(36*3*pixelRatio()));
	this->move(QGuiApplication::primaryScreen()->availableGeometry().center() - rect().center());
}

void tx4::initMainContainer() {
	w_mainContainer = new QWidget;
	QVBoxLayout *v_mainLayout = new QVBoxLayout(w_mainContainer);
	Util::setLayoutZero(v_mainLayout);
	v_mainLayout->setContentsMargins(0,0,0,20);
	v_mainLayout->setSpacing(20);

	initToolbar();
	// sections
	w_recentSection = new tx4_events_section(tx4_events_section::tr("RECENT"));
	w_savedSection = new tx4_events_section(tx4_events_section::tr("SAVED"));
	w_sentrySection = new tx4_events_section(tx4_events_section::tr("SENTRY"));
	connect(w_recentSection, &tx4_events_section::eventSelect, this, &tx4::on_eventSelectChange);
	connect(w_recentSection, &tx4_events_section::eventDeselect, this, &tx4::on_eventDeselectChange);
	connect(w_savedSection, &tx4_events_section::eventSelect, this, &tx4::on_eventSelectChange);
	connect(w_savedSection, &tx4_events_section::eventDeselect, this, &tx4::on_eventDeselectChange);
	connect(w_sentrySection, &tx4_events_section::eventSelect, this, &tx4::on_eventSelectChange);
	connect(w_sentrySection, &tx4_events_section::eventDeselect, this, &tx4::on_eventDeselectChange);
	//w_recentsSection = new tx4_recents;
	//w_eventsSection = new tx4_events;
	//connect(w_recentsSection, &tx4_recents::eventSelect, this, &tx4::on_eventSelectChange);
	//connect(w_eventsSection, &tx4_events::eventSelect, this, &tx4::on_eventSelectChange);
	//connect(w_recentsSection, &tx4_recents::eventDeselect, this, &tx4::on_eventSelectChange);
	//connect(w_eventsSection, &tx4_events::eventDeselect, this, &tx4::on_eventSelectChange);

	v_mainLayout->addWidget(w_toolbar);
	//v_mainLayout->addStretch();
	v_mainLayout->addWidget(w_recentSection);
	v_mainLayout->addWidget(w_savedSection);
	v_mainLayout->addWidget(w_sentrySection);
	//v_mainLayout->addWidget(w_recentsSection);
	//v_mainLayout->addWidget(w_eventsSection);
}

void tx4::initToolbar() {
	w_toolbar = new tx4_toolbar(false, false);
	o_tx4Dir = new tx4_dir(false, true, "C:/Users/infga/Downloads/TeslaCam");

	connect(w_toolbar, &tx4_toolbar::eventsLoad, this, &tx4::on_eventsLoadSignal);
	connect(o_tx4Dir, &tx4_dir::no_teslaCamFolder, this, &tx4::on_teslaCamFolderError);
	connect(o_tx4Dir, &tx4_dir::no_savedClipsFolder, this, &tx4::on_savedClipsFolderError);
	connect(o_tx4Dir, &tx4_dir::no_sentryClipsFolder, this, &tx4::on_sentryClipsFolderError);
}

void tx4::initShortcuts() {
	//o_shortcutManager = new tx4_shortcuts(this);
	//workerstarted = false;
	//tx4_worker *worker = new tx4_worker(800);
	//WorkerThread = new QThread;
	//myWorker->moveToThread(WorkerThread);
	//connect( this, SIGNAL(startWork()), myWorker, SLOT(StartWork()) );
	//connect( this, SIGNAL(stopWork()), myWorker, SLOT(StopWork()) );
	//connect( this, SIGNAL(startWork()), myWorker, SLOT(StartWork()) );
	//connect( this, SIGNAL(stopWork()), myWorker, SLOT(StopWork()) );
	//connect(worker, &tx4_worker::oneLoop, this, [=]{ qDebug() << "print::here"; });
	//connect(o_shortcutManager, &tx4_shortcuts::signal_selectMode, this, [=]{
	//	qDebug() << "signal_selectMode::here";
	//	if (workerstarted) {
	//		workerstarted = false;
	//		worker->stopWorker();
	//	} else {
	//		workerstarted = true;
	//		worker->startWorker();
	//	}
	//});
	//worker->start();
}

// OVERRIDES //
//
//void PHOT::closeEvent(QCloseEvent *event) {
	//int result = QMessageBox::question(this , "Close window" , "Are you sure to close?");
	//if (result != QMessageBox::Yes)
	//	event->ignore();
//}


bool tx4::nativeEvent(const QByteArray &eventType , void *message , long *result) {
	return QGoodWindow::nativeEvent(eventType , message , result);
}

bool tx4::event(QEvent *event) {
	switch (event->type()) {
	#ifdef QGOODWINDOW
		case QEvent::Show:
		case QEvent::WindowStateChange: {
			QString border_str = "none";
		#ifndef Q_OS_MAC
			if (windowState().testFlag(Qt::WindowNoState)) {
				if (isActiveWindow())
					border_str = "1px solid #5c5a58";
				else
					border_str = "1px solid #393939";
			}
		#endif
			innerFrame->setStyleSheet(m_frame_style.arg(m_color_str).arg(border_str));
			//frame->setStyleSheet(m_frame_style.arg(border_str));
			title_bar->setMaximized(isMaximized());
			title_bar->setVisible(!isFullScreen());

			if (!isFullScreen())
				setMargins(qRound(30 * pixelRatio()) , qRound(5 * pixelRatio()) , 0 , qRound(36 * 3 * pixelRatio()));
			else
				setMargins(0 , 0 , 0 , 0);

			break;
		}
		case QEvent::WindowActivate: {
		#ifndef Q_OS_MAC
			QString border_str = (windowState().testFlag(Qt::WindowNoState) ? "1px solid #5c5a58" : "none");
			innerFrame->setStyleSheet(m_frame_style.arg(m_color_str).arg(border_str));
			//frame->setStyleSheet(m_frame_style.arg(border_str));
		#endif
			title_bar->setActive(true);

			break;
		}
		case QEvent::WindowDeactivate: {
		#ifndef Q_OS_MAC
			QString border_str = (windowState().testFlag(Qt::WindowNoState) ? "1px solid #393939" : "none");
			innerFrame->setStyleSheet(m_frame_style.arg(m_color_str).arg(border_str));
			//frame->setStyleSheet(m_frame_style.arg(border_str));
		#endif
			title_bar->setActive(false);

			break;
		}
	#endif
		case QEvent::Resize: {
			int new_size = size().width();
			if (new_size != window_w) {
			}
			window_w = new_size;
			break;
		}
		//case QEvent::MouseButtonPress:
		//	qDebug() << "MOUSE HOLDING PRESS HERE"; break;
		default:
			break;
	}

	return QGoodWindow::event(event);
}


// SLOTS: {
	void tx4::on_selectModeSignal() {
		//qDebug() << "S HIT";
		//m_selectMode = !m_selectMode;
		//w_recentsSection->toggleSelectMode(m_selectMode);
		//w_eventsSection->toggleSelectMode(m_selectMode);
		//w_recentSection->toggleSelectMode(m_selectMode);
		//w_savedSection->toggleSelectMode(m_selectMode);
		//w_sentrySection->toggleSelectMode(m_selectMode);
	}
	void tx4::on_eventSelectChange(tx4_event_preview *pselect) {
		////qDebug() << "Before: " << selectedEvents.count();
		//selectedEvents.clear();
		//int selectIdx = 1;

		//tx4_event_preview *ep;
		//foreach (ep, w_1Section->selectedPreviews) {
		//	ep->setSelectIdx(selectIdx);
		//	selectedEvents.append(ep);
		//	selectIdx += 1;
		//}
		//foreach (ep, w_2Section->selectedPreviews) {
		//	ep->setSelectIdx(selectIdx);
		//	selectedEvents.append(ep);
		//	selectIdx += 1;
		//}
		//foreach (ep, w_3Section->selectedPreviews) {
		//	ep->setSelectIdx(selectIdx);
		//	selectedEvents.append(ep);
		//	selectIdx += 1;
		//}
		////foreach (ep, w_recentsSection->selectedPreviews) {
		////	selectedEvents.append(ep);
		////}
		////foreach (ep, w_eventsSection->selectedPreviews) {
		////	selectedEvents.append(ep);
		////}

		////qDebug() << "After: " << selectedEvents.count();
		//w_toolbar->updateEventQueue(selectedEvents);

		selectedEvents.append(pselect);

		int selectIdx = 1;
		tx4_event_preview *ep;
		foreach (ep, selectedEvents) {
			ep->setSelectIdx(selectIdx);
			//selectedEvents.append(ep);
			selectIdx += 1;
		}

		w_toolbar->updateEventQueue(selectedEvents);
	}
	void tx4::on_eventDeselectChange(tx4_event_preview *pdeselect) {
		if (selectedEvents.removeOne(pdeselect)) {
			int selectIdx = 1;
			tx4_event_preview *ep;
			foreach (ep, selectedEvents) {
				ep->setSelectIdx(selectIdx);
				//selectedEvents.append(ep);
				selectIdx += 1;
			}

			w_toolbar->updateEventQueue(selectedEvents);
		}
	}
	void tx4::on_eventsLoadSignal() {
		if (!m_eventsLoaded) {
			m_eventsLoaded = true;

			bool load_success = o_tx4Dir->loadTeslaDrive();

			if (load_success) {
				qDebug() << "exit:: " << true;

				w_savedSection->populateEvents(o_tx4Dir->savedEvents);
				w_sentrySection->populateEvents(o_tx4Dir->sentryEvents);
				w_toolbar->toggleEventsLoaded(true);
				//w_recentSection->toggleEventsLoaded(true);
				w_savedSection->toggleEventsLoaded(true);
				w_sentrySection->toggleEventsLoaded(true);
			} else {
				qDebug() << "exit:: " << false;
			}
		}
	}

	// tx4_dir errors
	void tx4::on_teslaCamFolderError() {
	}
	void tx4::on_savedClipsFolderError() {
	}
	void tx4::on_sentryClipsFolderError() {
	}
// }