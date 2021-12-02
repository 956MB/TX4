
#include "tx4.h"

tx4::tx4(QWidget *parent)
	: QGoodWindow(parent)
	, selectedEvents(QList<tx4_event*> ())
	, selectedPreviews(QList<tx4_event_preview*> ()) {

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
	m_eventViewerOpen = false;
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

	w_screensContainer = new QStackedWidget;
	w_screensContainer->setStyleSheet(stackedWidgetStyle);
	//QStackedLayout *screensLayout = new QStackedLayout(w_screensContainer);
	//Util::setLayoutZero(screensLayout);
	//screensLayout->setStackingMode(QStackedLayout::StackAll);

	initMainScreen();
	//initViewerScreen();
	w_screensContainer->addWidget(w_mainScreen);
	//w_screensContainer->addWidget(w_viewerScreen);
	w_screensContainer->setCurrentIndex(0);
	innerLayout->addWidget(w_screensContainer);

	QStackedLayout *outerlayout = new QStackedLayout(outerFrame);
	outerlayout->setStackingMode(QStackedLayout::StackAll);
	Util::setLayoutZero(outerlayout);
	// TODO: QStackedLayout in reverse order for some reason (first item added is on top)
	outerlayout->addWidget(innerFrame);

	setCentralWidget(outerFrame);

	QObject::connect(title_bar, &TitleBar::showMinimized, this, &tx4::showMinimized);
	QObject::connect(title_bar, &TitleBar::showNormal, this, &tx4::showNormal);
	QObject::connect(title_bar, &TitleBar::showMaximized, this, &tx4::showMaximized);
	QObject::connect(title_bar, &TitleBar::closeWindow, this, &tx4::close);
	QObject::connect(this, &tx4::windowTitleChanged, this, [=](const QString &title) {
		title_bar->setTitle(title);
	});
	//QObject::connect(this, &tx4::windowIconChanged, this, [=](const QIcon &icon) {
	//	if (!icon.isNull()) {
	//		const int pix_size = qCeil(16 * pixelRatio());
	//		title_bar->setIcon(icon.pixmap(pix_size , pix_size));
	//	}
	//});

	//QObject::connect(w_deleteDialog, &PHOT_Dialog::dialog_confirm, this, &PHOT::on_dialogConfirm);
	//QObject::connect(w_deleteDialog, &PHOT_Dialog::dialog_cancel, this, &PHOT::on_dialogCancel);

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
	QObject::connect(title_bar, &TitleBar::goBack, this, &tx4::on_handleCloseEvents);

	this->setWindowTitle(m_title);
	this->resize(qRound(START_W * pixelRatio()) , qRound(START_H * pixelRatio()));
	//this->setFixedSize(qRound(START_W * pixelRatio()) , qRound(START_H * pixelRatio()));
	this->setMinimumSize(MIN_W , MIN_H);
	this->setMargins(qRound(32*pixelRatio()) , qRound(30*pixelRatio()) , -20 , qRound(36*3*pixelRatio()));
	this->move(QGuiApplication::primaryScreen()->availableGeometry().center() - rect().center());
}

void tx4::initMainScreen() {
	w_mainScreen = new QWidget;
	QVBoxLayout *v_mainLayout = new QVBoxLayout(w_mainScreen);
	Util::setLayoutZero(v_mainLayout);
	v_mainLayout->setContentsMargins(0,0,0,20);
	v_mainLayout->setSpacing(20);

	initToolbar();
	// sections
	w_recentSection = new tx4_events_section(tx4_events_section::tr("RECENT"));
	w_savedSection = new tx4_events_section(tx4_events_section::tr("SAVED"));
	w_sentrySection = new tx4_events_section(tx4_events_section::tr("SENTRY"));
	w_recentSection->setNavButtonStates(false, false, false, false);
	w_savedSection->setNavButtonStates(false, false, false, false);
	w_sentrySection->setNavButtonStates(false, false, false, false);
	w_recentSection->setSelectDeselectButtonState(false, false);
	w_savedSection->setSelectDeselectButtonState(false, true);
	w_sentrySection->setSelectDeselectButtonState(false, true);
	QObject::connect(w_recentSection, &tx4_events_section::eventSelect, this, &tx4::on_eventSelectChange);
	QObject::connect(w_recentSection, &tx4_events_section::eventDeselect, this, &tx4::on_eventDeselectChange);
	QObject::connect(w_savedSection, &tx4_events_section::eventSelect, this, &tx4::on_eventSelectChange);
	QObject::connect(w_savedSection, &tx4_events_section::eventDeselect, this, &tx4::on_eventDeselectChange);
	QObject::connect(w_sentrySection, &tx4_events_section::eventSelect, this, &tx4::on_eventSelectChange);
	QObject::connect(w_sentrySection, &tx4_events_section::eventDeselect, this, &tx4::on_eventDeselectChange);

	v_mainLayout->addWidget(w_toolbar);
	//v_mainLayout->addStretch();
	v_mainLayout->addWidget(w_recentSection);
	v_mainLayout->addWidget(w_savedSection);
	v_mainLayout->addWidget(w_sentrySection);
	//v_mainLayout->addWidget(w_recentsSection);
	//v_mainLayout->addWidget(w_eventsSection);
}

void tx4::initViewerScreen() {
	w_viewerScreen = new tx4_viewer;
}

void tx4::initToolbar() {
	w_toolbar = new tx4_toolbar(false, false);
	o_tx4Dir = new tx4_dir(false, true, "C:/Users/infga/Downloads/TeslaCam");

	QObject::connect(w_toolbar, &tx4_toolbar::eventsOpen, this, &tx4::on_eventsOpenSignal);
	QObject::connect(w_toolbar, &tx4_toolbar::eventsLoad, this, &tx4::on_eventsLoadSignal);
	QObject::connect(o_tx4Dir, &tx4_dir::err_teslaCamFolder, this, &tx4::on_teslaCamFolderError);
	QObject::connect(o_tx4Dir, &tx4_dir::err_savedClipsFolder, this, &tx4::on_savedClipsFolderError);
	QObject::connect(o_tx4Dir, &tx4_dir::err_sentryClipsFolder, this, &tx4::on_sentryClipsFolderError);
	QObject::connect(o_tx4Dir, &tx4_dir::err_savedClipsFolderEmpty, this, &tx4::on_savedClipsFolderEmptyError);
	QObject::connect(o_tx4Dir, &tx4_dir::err_sentryClipsFolderEmpty, this, &tx4::on_sentryClipsFolderEmptyError);
}

void tx4::initShortcuts() {
	o_shortcutManager = new tx4_shortcuts(this);

	QObject::connect(o_shortcutManager, &tx4_shortcuts::signal_esc, this, &tx4::on_handleCloseEvents);
	QObject::connect(o_shortcutManager, &tx4_shortcuts::signal_open, this, &tx4::on_eventsOpenSignal);
	QObject::connect(o_shortcutManager, &tx4_shortcuts::signal_load, this, &tx4::on_eventsLoadSignal);
	//workerstarted = false;
	//tx4_worker *worker = new tx4_worker(800);
	//WorkerThread = new QThread;
	//myWorker->moveToThread(WorkerThread);
	//QObject::connect( this, SIGNAL(startWork()), myWorker, SLOT(StartWork()) );
	//QObject::connect( this, SIGNAL(stopWork()), myWorker, SLOT(StopWork()) );
	//QObject::connect( this, SIGNAL(startWork()), myWorker, SLOT(StartWork()) );
	//QObject::connect( this, SIGNAL(stopWork()), myWorker, SLOT(StopWork()) );
	//QObject::connect(worker, &tx4_worker::oneLoop, this, [=]{ qDebug() << "print::here"; });
	//QObject::connect(o_shortcutManager, &tx4_shortcuts::signal_selectMode, this, [=]{
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
	void tx4::on_eventSelectChange(tx4_event *eselect, tx4_event_preview *epselect) {
		selectedEvents.append(eselect);
		selectedPreviews.append(epselect);

		int selectIdx = 1;
		tx4_event *e;
		foreach (e, selectedEvents) {
			e->setSelectIdx(selectIdx);
			selectIdx += 1;
		}

		selectIdx = 1;
		tx4_event_preview *ep;
		foreach (ep, selectedPreviews) {
			ep->setSelectIdx(selectIdx);
			selectIdx += 1;
		}

		w_toolbar->updateEventQueue(selectedEvents, selectedPreviews);
	}
	void tx4::on_eventDeselectChange(tx4_event *edeselect, tx4_event_preview *epdeselect) {
		if (selectedEvents.removeOne(edeselect)) {
			int selectIdx = 1;
			tx4_event *e;
			foreach (e, selectedEvents) {
				e->setSelectIdx(selectIdx);
				selectIdx += 1;
			}
		}
		if (selectedPreviews.removeOne(epdeselect)) {
			int selectIdx = 1;
			tx4_event_preview *ep;
			foreach (ep, selectedPreviews) {
				ep->setSelectIdx(selectIdx);
				selectIdx += 1;
			}
		}

		w_toolbar->updateEventQueue(selectedEvents, selectedPreviews);
	}
	void tx4::on_eventsOpenSignal() {
		if (!m_eventViewerOpen && selectedEvents.count() >= 1) {
			initViewerScreen();
			w_screensContainer->addWidget(w_viewerScreen);
			w_screensContainer->setCurrentIndex(1);
			w_mainScreen->setVisible(false);
			w_screensContainer->removeWidget(w_mainScreen);
			m_eventViewerOpen = true;
			title_bar->setBackBtn(m_eventViewerOpen);
		}
	}
	void tx4::on_eventsLoadSignal() {
		if (!m_eventsLoaded) {
			m_eventsLoaded = true;

			bool load_success = o_tx4Dir->loadTeslaDrive();

			if (load_success) {
				w_savedSection->populateEvents(o_tx4Dir->savedEvents);
				w_sentrySection->populateEvents(o_tx4Dir->sentryEvents);
				
				w_toolbar->toggleEventsLoaded(true);
				w_recentSection->setNavButtonStates(false, false, false, false);
				w_recentSection->setSelectDeselectButtonState(false, false);
				w_recentSection->setReturnButtonState(false, false);

				w_savedSection->toggleEventsLoaded(true);
				w_savedSection->setNavButtonStates(true, true, true, true);
				w_savedSection->setSelectDeselectButtonState(true, true);
				w_savedSection->setReturnButtonState(false, false);

				w_sentrySection->toggleEventsLoaded(true);
				w_sentrySection->setNavButtonStates(true, true, true, true);
				w_sentrySection->setSelectDeselectButtonState(true, true);
				w_sentrySection->setReturnButtonState(false, false);
			} else {
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
	void tx4::on_savedClipsFolderEmptyError() {
	}
	void tx4::on_sentryClipsFolderEmptyError() {
	}

	void tx4::on_handleCloseEvents() {
		// close viewer
		if (w_viewerScreen != NULL && m_eventViewerOpen) {
			w_screensContainer->addWidget(w_mainScreen);
			w_mainScreen->setVisible(true);
			w_screensContainer->setCurrentIndex(0);
			w_screensContainer->removeWidget(w_viewerScreen);
			Util::deleteAndCleanup(w_viewerScreen); // TODO: works somehow
			m_eventViewerOpen = false;
			title_bar->setBackBtn(m_eventViewerOpen);
			return;
		}
	}
// }