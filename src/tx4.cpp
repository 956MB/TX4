
#include "tx4.h"

tx4::tx4(QWidget *parent)
	: QGoodWindow(parent)
	, m_groupsInitialized(false)
	, l_selectedEvents(QList<tx4_event*> ())
	, l_selectedPreviews(QList<tx4_event_preview*> ()) {

	//registerFileType("GiMdi.Document", "MDI Text Editor Document", ".gidoc", 0, true);
	//registerCommand("fancyCommand", "GiMdi.Document", "-fancy %1", "[fancy(\"%1\")]");
	//enableShellOpen();

	initWindowConfig();
	initShortcuts();
	on_eventsLoadSignal();
	//m_groupsInitialized = true;
}

tx4::~tx4() {}


void tx4::initWindowConfig() {
	window_w = START_W;
	m_title = "";
	m_dark = true;
	m_selectMode = true;
	m_eventsLoaded = false;
	m_eventViewerOpen = false;
	m_frame_style = QString("QFrame {background-color: %0;}");
	//m_frame_style = QString("QFrame {background-color: %0; border: %1;}");
	m_color_str = "#000000";
	//QString border_str = "1px solid #4c4a48";
	QString border_str = "none";

#ifdef QGOODWINDOW
	f_outerFrame = new QFrame(this);
	f_innerFrame = new QFrame(this);

	QWidget *w_titlebarContent = new QWidget;
	QHBoxLayout *h_titlebarContentsLayout = new QHBoxLayout(w_titlebarContent);
	Util::setLayoutZero(h_titlebarContentsLayout);
	title_bar = new TitleBar(pixelRatio(), this);
	backbtn = new CaptionButton(CaptionButton::IconType::Back, pixelRatio(), this);
	backbtn->setFixedSize(qRound(46 * pixelRatio()), qRound(32 * pixelRatio()));
	QObject::connect(backbtn, &CaptionButton::clicked, this, &tx4::on_handleCloseEvents);

	h_titlebarContentsLayout->addWidget(backbtn);
	h_titlebarContentsLayout->addWidget(title_bar);
	backbtn->setVisible(false);

	QVBoxLayout *innerLayout = new QVBoxLayout(f_innerFrame);
	Util::setLayoutZero(innerLayout);
	innerLayout->addWidget(w_titlebarContent);
	//innerLayout->addWidget(title_bar);

	w_screensContainer = new QStackedWidget;
	w_screensContainer->setStyleSheet(S_STACKED_WIDGET);

	initMainScreen();
	//initViewerScreen();
	w_screensContainer->addWidget(w_mainScreen);
	//w_screensContainer->addWidget(w_viewerScreen);
	w_screensContainer->setCurrentIndex(0);
	innerLayout->addWidget(w_screensContainer);

	QStackedLayout *outerlayout = new QStackedLayout(f_outerFrame);
	outerlayout->setStackingMode(QStackedLayout::StackAll);
	Util::setLayoutZero(outerlayout);
	// TODO: QStackedLayout in reverse order for some reason (first item added is on top)
	outerlayout->addWidget(f_innerFrame);

	setCentralWidget(f_outerFrame);

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

	f_innerFrame->setStyleSheet(m_frame_style.arg(m_color_str));
	//f_innerFrame->setStyleSheet(m_frame_style.arg(m_color_str).arg(border_str));
	//mat_thumbFrame->setStyleSheet(m_frame_style.arg(border_str));
    title_bar->setDarkMode(m_dark);
 //   title_bar->setBackBtn(false);
	//QObject::connect(title_bar, &TitleBar::goBack, this, &tx4::on_handleCloseEvents);

	this->setWindowTitle(m_title);
	this->resize(qRound(START_W * pixelRatio()) , qRound(START_H * pixelRatio()));
	//this->setFixedSize(qRound(START_W * pixelRatio()) , qRound(START_H * pixelRatio()));
	//this->setMinimumSize((PREVIEW_W * 4) + 80 + 36 , MIN_H);
	this->setMinimumSize(MIN_W, MIN_H);
	this->setMargins(qRound(32*pixelRatio()) , qRound(30*pixelRatio()) , -20 , qRound(36*3*pixelRatio()));
	this->move(QGuiApplication::primaryScreen()->availableGeometry().center() - rect().center());
}

void tx4::initMainScreen() {
	w_mainScreen = new QWidget;
	QVBoxLayout *v_mainLayout = new QVBoxLayout(w_mainScreen);
	Util::setLayoutZero(v_mainLayout);
	v_mainLayout->setContentsMargins(0,0,0,OUTER_MARGIN);
	//v_mainLayout->setSpacing(6);

	o_tx4Dir = new tx4_dir(false, true, TESLA_DRIVE);
	QObject::connect(o_tx4Dir, &tx4_dir::err_teslaCamFolder, this, &tx4::on_teslaCamFolderError);
	QObject::connect(o_tx4Dir, &tx4_dir::err_savedClipsFolder, this, &tx4::on_savedClipsFolderError);
	QObject::connect(o_tx4Dir, &tx4_dir::err_sentryClipsFolder, this, &tx4::on_sentryClipsFolderError);
	QObject::connect(o_tx4Dir, &tx4_dir::err_savedClipsFolderEmpty, this, &tx4::on_savedClipsFolderEmptyError);
	QObject::connect(o_tx4Dir, &tx4_dir::err_sentryClipsFolderEmpty, this, &tx4::on_sentryClipsFolderEmptyError);

	QWidget *w_toolbarContainer = new QWidget;
	QHBoxLayout *h_toolbarContainerLayout = new QHBoxLayout(w_toolbarContainer);
	Util::setLayoutZero(h_toolbarContainerLayout);
	h_toolbarContainerLayout->setContentsMargins(OUTER_MARGIN,0,OUTER_MARGIN,0);
	w_toolbar = new tx4_toolbar();
	h_toolbarContainerLayout->addWidget(w_toolbar);
	QObject::connect(w_toolbar, &tx4_toolbar::sectionButtonClick, this, &tx4::on_pageSelectSignal);
	QObject::connect(w_toolbar, &tx4_toolbar::openButtonClick, this, &tx4::on_eventsOpenSignal);
	QObject::connect(w_toolbar, &tx4_toolbar::importButtonClick, this, &tx4::on_eventsLoadSignal);
	QObject::connect(w_toolbar, &tx4_toolbar::settingsButtonClick, this, [=]{ qDebug() << "settings::here"; });

	// PAGES:
	w_recentPage = new tx4_events_page(0);
	w_savedPage = new tx4_events_page(1);
	w_sentryPage = new tx4_events_page(2);
	w_favoritesPage = new tx4_events_page(3);
	QObject::connect(w_recentPage, &tx4_events_page::eventSelect, this, &tx4::on_eventSelectChange);
	QObject::connect(w_recentPage, &tx4_events_page::eventDeselect, this, &tx4::on_eventDeselectChange);
	QObject::connect(w_savedPage, &tx4_events_page::eventSelect, this, &tx4::on_eventSelectChange);
	QObject::connect(w_savedPage, &tx4_events_page::eventDeselect, this, &tx4::on_eventDeselectChange);
	QObject::connect(w_sentryPage, &tx4_events_page::eventSelect, this, &tx4::on_eventSelectChange);
	QObject::connect(w_sentryPage, &tx4_events_page::eventDeselect, this, &tx4::on_eventDeselectChange);
	QObject::connect(w_favoritesPage, &tx4_events_page::eventSelect, this, &tx4::on_eventSelectChange);
	QObject::connect(w_favoritesPage, &tx4_events_page::eventDeselect, this, &tx4::on_eventDeselectChange);

	w_pagesStackWidget = new QStackedWidget;
	w_pagesStackWidget->addWidget(w_recentPage);
	w_pagesStackWidget->addWidget(w_savedPage);
	w_pagesStackWidget->addWidget(w_sentryPage);
	w_pagesStackWidget->addWidget(w_favoritesPage);
	w_pagesStackWidget->setCurrentIndex(1);

	v_mainLayout->addWidget(w_toolbarContainer);
	v_mainLayout->addWidget(w_pagesStackWidget);
}

void tx4::initViewerScreen() {
	w_viewerScreen = new tx4_viewer(l_selectedEvents);
	QObject::connect(w_viewerScreen, &tx4_viewer::manualResize, this, &tx4::on_manualResizeSignal);
}

void tx4::initShortcuts() {
	o_shortcutManager = new tx4_shortcuts_main(this);

	QObject::connect(o_shortcutManager, &tx4_shortcuts::shortcutNum1, this, [=]{ on_pageSelectSignal(0); });
	QObject::connect(o_shortcutManager, &tx4_shortcuts::shortcutNum2, this, [=]{ on_pageSelectSignal(1); });
	QObject::connect(o_shortcutManager, &tx4_shortcuts::shortcutNum3, this, [=]{ on_pageSelectSignal(2); });
	QObject::connect(o_shortcutManager, &tx4_shortcuts::shortcutNum4, this, [=]{ on_pageSelectSignal(3); });
	QObject::connect(o_shortcutManager, &tx4_shortcuts::shortcutEsc, this, [=]{ qDebug() << "shortcutEsc::here"; });
	QObject::connect(o_shortcutManager, &tx4_shortcuts::shortcutOpen, this, [=]{ qDebug() << "shortcutOpen::here"; });
	QObject::connect(o_shortcutManager, &tx4_shortcuts::shortcutLoad, this, [=]{ qDebug() << "shortcutLoad::here"; });

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

// OVERRIDES:
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
			f_innerFrame->setStyleSheet(m_frame_style.arg(m_color_str));
			//f_innerFrame->setStyleSheet(m_frame_style.arg(m_color_str).arg(border_str));
			//mat_thumbFrame->setStyleSheet(m_frame_style.arg(border_str));
			title_bar->setMaximized(isMaximized());
			title_bar->setVisible(!isFullScreen());

			if (!isFullScreen())
				setMargins(qRound(32 * pixelRatio()) , qRound(5 * pixelRatio()) , qRound(46 * pixelRatio()) , qRound(46 * 3 * pixelRatio()));
				//setMargins(qRound(32 * pixelRatio()) , qRound(5 * pixelRatio()) , 0 , qRound(window_w * pixelRatio()));
			else
				setMargins(0 , 0 , 0 , 0);

			break;
		}
		case QEvent::WindowActivate: {
		#ifndef Q_OS_MAC
			QString border_str = (windowState().testFlag(Qt::WindowNoState) ? "1px solid #5c5a58" : "none");
			f_innerFrame->setStyleSheet(m_frame_style.arg(m_color_str));
			//f_innerFrame->setStyleSheet(m_frame_style.arg(m_color_str).arg(border_str));
			//mat_thumbFrame->setStyleSheet(m_frame_style.arg(border_str));
		#endif
			title_bar->setActive(true);

			break;
		}
		case QEvent::WindowDeactivate: {
		#ifndef Q_OS_MAC
			QString border_str = (windowState().testFlag(Qt::WindowNoState) ? "1px solid #393939" : "none");
			f_innerFrame->setStyleSheet(m_frame_style.arg(m_color_str));
			//f_innerFrame->setStyleSheet(m_frame_style.arg(m_color_str).arg(border_str));
			//mat_thumbFrame->setStyleSheet(m_frame_style.arg(border_str));
		#endif
			title_bar->setActive(false);

			break;
		}
	#endif
		case QEvent::Resize: {
			int new_size = size().width();
			//if (new_size != window_w) {
			//}
			window_w = new_size;
			resizeSectionContents(window_w);
			//qDebug() << *window_w;
			break;
		}
		//case QEvent::MouseButtonPress:
		//	qDebug() << "MOUSE HOLDING PRESS HERE"; break;
		default:
			break;
	}

	return QGoodWindow::event(event);
}

void tx4::resizeSectionContents(int window_w) {
	if (m_eventViewerOpen) {
		w_viewerScreen->resizeInnerViews();
	}
	if (m_groupsInitialized && !m_eventViewerOpen) {
		//w_recentPage->resizeSectionPreviews(window_w);
		w_savedPage->resizeSectionContents(window_w);
		w_sentryPage->resizeSectionContents(window_w);
	}
}


// SLOTS:

void tx4::on_manualResizeSignal() {
	this->resize(qRound(START_W * pixelRatio()) , qRound(START_H * pixelRatio() + 3));
}
void tx4::on_pageSelectSignal(int idx) {
	if (!m_eventViewerOpen) {
		w_pagesStackWidget->setCurrentIndex(idx);
		w_toolbar->setButtonSelected(idx);
		resizeSectionContents(window_w);
	}
}
void tx4::on_eventSelectChange(tx4_event *eselect) {
	l_selectedEvents.append(eselect);
	//l_selectedPreviews.append(epselect);

	int selectIdx = 1;
	for (auto &e : l_selectedEvents) {
		e->setSelectIdx(selectIdx);
		selectIdx += 1;
	}

	w_toolbar->updatePageButtonState(eselect->i_inPage, 1);
	w_toolbar->updateOpenEventsButtonState(l_selectedEvents.count());
}
void tx4::on_eventDeselectChange(tx4_event *edeselect) {
	if (l_selectedEvents.removeOne(edeselect)) {
		int selectIdx = 1;
		for (auto &e : l_selectedEvents) {
			e->setSelectIdx(selectIdx);
			selectIdx += 1;
		}
	}

	w_toolbar->updatePageButtonState(edeselect->i_inPage, -1);
	w_toolbar->updateOpenEventsButtonState(l_selectedEvents.count());
}
void tx4::on_eventsOpenSignal() {
	if (!m_eventViewerOpen && l_selectedEvents.count() >= 1) {
		initViewerScreen();
		w_screensContainer->addWidget(w_viewerScreen);
		w_mainScreen->setVisible(false);
		w_screensContainer->setCurrentIndex(1);
		w_screensContainer->removeWidget(w_mainScreen);
		m_eventViewerOpen = true;
		backbtn->setVisible(m_eventViewerOpen);
	}
}
void tx4::on_eventsLoadSignal() {
	if (!m_eventViewerOpen && !m_eventsLoaded) {
		bool load_success = o_tx4Dir->loadTeslaDrive(true);

		if (load_success) {
			w_savedPage->populateEvents(o_tx4Dir->savedEvents, GroupSort::None);
			w_sentryPage->populateEvents(o_tx4Dir->sentryEvents, GroupSort::None);
			w_savedPage->toggleEventsLoaded(true);
			w_sentryPage->toggleEventsLoaded(true);

			m_eventsLoaded = true;
			m_groupsInitialized = true;
			// TODO: workaround to make event previews properly resize after loading because window size doesnt change if i call "resizeSectionContents(window_w)"
			//this->resize(qRound(START_W * pixelRatio() + 1) , qRound(START_H * pixelRatio()));
			//on_manualResizeSignal();
			w_toolbar->updateImportButtonState(m_eventsLoaded);
		}
	}
}
void tx4::on_handleCloseEvents() {
	if (w_viewerScreen != NULL && m_eventViewerOpen) {
		w_screensContainer->addWidget(w_mainScreen);
		w_mainScreen->setVisible(true);
		w_screensContainer->setCurrentIndex(0);
		w_screensContainer->removeWidget(w_viewerScreen);
		Util::deleteAndCleanup(w_viewerScreen); // TODO: works somehow
		m_eventViewerOpen = false;
		backbtn->setVisible(m_eventViewerOpen);
		return;
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