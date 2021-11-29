
#include "tx4_control_bar.h"

tx4_control_bar::tx4_control_bar(QWidget *parent)
	: QWidget(parent) {

	s_playText = tx4_control_bar::tr("PLAY");
	s_pauseText = tx4_control_bar::tr("PAUSE");

	this->setAttribute(Qt::WA_StyledBackground); // <--- this attribute solves issue of background color not being drawn on custom widget, no need for reimplementing paintEvent, yet.
	//this->setFixedHeight(CONTROL_BAR_H);
	this->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Fixed);
	this->setStyleSheet(controlBarBodyStyle);

	initContents();
}

tx4_control_bar::~tx4_control_bar() {}

void tx4_control_bar::initContents() {
	QVBoxLayout *v_mainLayout = new QVBoxLayout(this);
	Util::setLayoutZero(v_mainLayout);
	v_mainLayout->setSpacing(16);

	initTimeline();
	//initButtons();
	
	//v_mainLayout->addSpacerItem(new QSpacerItem(0, 16, QSizePolicy::Expanding, QSizePolicy::Fixed));
	v_mainLayout->addWidget(w_timelineContainer);
	//v_mainLayout->addWidget(w_buttonContainer);
	//v_mainLayout->addSpacerItem(new QSpacerItem(0, 16, QSizePolicy::Expanding, QSizePolicy::Fixed));

	this->setLayout(v_mainLayout);
}

void tx4_control_bar::initTimeline() {
	initButtons();

	// timeline container top
	w_timelineContainer = new QWidget;
	w_timelineContainer->setFixedHeight(50);
	w_timelineContainer->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Fixed);
	w_timelineContainer->setStyleSheet(buttonContainerBodyStyle);
	QHBoxLayout *v_timelineContainerLayout = new QHBoxLayout(w_timelineContainer);
	Util::setLayoutZero(v_timelineContainerLayout);
	v_timelineContainerLayout->setContentsMargins(20,0,0,0);

	QWidget *w_rightContainer = new QWidget;
	w_rightContainer->setFixedHeight(21);
	w_rightContainer->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Fixed);
	w_rightContainer->setStyleSheet(timelineContainerStyle);
	QHBoxLayout *v_rightContainerLayout = new QHBoxLayout(w_rightContainer);
	Util::setLayoutZero(v_rightContainerLayout);

	QWidget *w_timelineBody = new QWidget;
	w_timelineBody->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
	w_timelineBody->setStyleSheet(timelineBodyStyle);
	QHBoxLayout *v_timelineBodyLayout = new QHBoxLayout(w_timelineBody);
	Util::setLayoutZero(v_timelineBodyLayout);
	//v_timelineBodyLayout->setContentsMargins(3,0,3,0);
	w_timelineSlider = new QSlider(Qt::Horizontal, w_timelineBody);
	w_timelineSlider->setTickPosition(QSlider::NoTicks);
	w_timelineSlider->setTickInterval(QSlider::NoTicks);
	w_timelineSlider->setMinimum(TIMELINE_MIN);
    w_timelineSlider->setMaximum(TIMELINE_MAX * STEPS);
	w_timelineSlider->setStyleSheet(timelineSliderStyle);
	w_timelineSlider->setSliderPosition(0);
	v_timelineBodyLayout->addWidget(w_timelineSlider);

	connect(w_timelineSlider, &QSlider::valueChanged, this, &tx4_control_bar::on_timelineValueUpdate);

	QWidget *w_timeContainer = new QWidget;
	w_timeContainer->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Expanding);
	w_timeContainer->setStyleSheet(timeContainerStyle);
	QHBoxLayout *v_timeContainerLayout = new QHBoxLayout(w_timeContainer);
	Util::setLayoutZero(v_timeContainerLayout);
	v_timeContainerLayout->setSpacing(4);
	v_timeContainerLayout->setContentsMargins(20,0,20,0);
	l_timeCurrentLabel = new tx4_label("00:00:00", 10, timeLabelStyle, QFont::Medium, Qt::AlignCenter);
	l_timeDividerLabel = new tx4_label("/", 10, dividerLabelStyle, QFont::Medium, Qt::AlignCenter);
	l_timeTotalLabel = new tx4_label("00:00:59", 10, timeLabelStyle, QFont::Medium, Qt::AlignCenter);
	v_timeContainerLayout->addWidget(l_timeCurrentLabel);
	v_timeContainerLayout->addWidget(l_timeDividerLabel);
	v_timeContainerLayout->addWidget(l_timeTotalLabel);

	v_rightContainerLayout->addWidget(w_timelineBody);
	//v_rightContainerLayout->addSpacerItem(new QSpacerItem(20, 0, QSizePolicy::Fixed, QSizePolicy::Expanding));
	v_rightContainerLayout->addWidget(w_timeContainer);

	//v_timelineContainerLayout->addSpacerItem(new QSpacerItem(20, 0, QSizePolicy::Fixed, QSizePolicy::Expanding));
	v_timelineContainerLayout->addWidget(w_buttonContainer);
	v_timelineContainerLayout->addSpacerItem(new QSpacerItem(20, 0, QSizePolicy::Fixed, QSizePolicy::Expanding));
	v_timelineContainerLayout->addWidget(w_rightContainer);
	//v_timelineContainerLayout->addSpacerItem(new QSpacerItem(20, 0, QSizePolicy::Fixed, QSizePolicy::Expanding));
	//v_timelineContainerLayout->addWidget(w_timeContainer);
}

void tx4_control_bar::initButtons() {
	// button container bottom
	w_buttonContainer = new QWidget;
	w_buttonContainer->setFixedHeight(CONTROL_BAR_H);
	w_buttonContainer->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Expanding);
	w_buttonContainer->setStyleSheet(buttonContainerBodyStyle);
	QHBoxLayout *h_buttonContainerLayout = new QHBoxLayout(w_buttonContainer);
	Util::setLayoutZero(h_buttonContainerLayout);
	h_buttonContainerLayout->setSpacing(2);

	//QWidget *w_leftContainer = new QWidget;
	//w_leftContainer->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Expanding);
	//QHBoxLayout *h_leftContainerLayout = new QHBoxLayout(w_leftContainer);
	//Util::setLayoutZero(h_leftContainerLayout);
	b_syncViewsButton = new tx4_toolbar_button(tx4_control_bar::tr("SYNC CLIPS"), false, "");
	//h_leftContainerLayout->setSpacing(2);
	//h_leftContainerLayout->addWidget(b_syncViewsButton);

	QWidget *w_buttonsContainer = new QWidget;
	w_buttonsContainer->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Expanding);
	QHBoxLayout *h_buttonsContainerLayout = new QHBoxLayout(w_buttonsContainer);
	Util::setLayoutZero(h_buttonsContainerLayout);
	b_playPauseButton = new tx4_toolbar_button(s_playText, true, "");
	b_backButton = new tx4_toolbar_button("10", true, "", "<", "<", 12);
	b_forwardButton = new tx4_toolbar_button("10", true, "", ">", ">", 12);
	h_buttonsContainerLayout->setSpacing(2);
	h_buttonsContainerLayout->addWidget(b_syncViewsButton);
	h_buttonsContainerLayout->addSpacerItem(new QSpacerItem(20, 0, QSizePolicy::Fixed, QSizePolicy::Expanding));
	h_buttonsContainerLayout->addWidget(b_backButton);
	h_buttonsContainerLayout->addWidget(b_playPauseButton);
	h_buttonsContainerLayout->addWidget(b_forwardButton);

	//h_buttonContainerLayout->addSpacerItem(new QSpacerItem(20, 0, QSizePolicy::Fixed, QSizePolicy::Expanding));
	//h_buttonContainerLayout->addWidget(w_leftContainer, 0, Qt::AlignLeft);
	h_buttonContainerLayout->addStretch();
	h_buttonContainerLayout->addWidget(w_buttonsContainer, Qt::AlignCenter);
	h_buttonContainerLayout->addStretch();
	//v_buttonContainerLayout->addSpacerItem(new QSpacerItem(20, 0, QSizePolicy::Fixed, QSizePolicy::Expanding));
}
// SCROLLWHEEL EVENTS: {
	
// }


// SLOTS: {
	void tx4_control_bar::on_timelineValueUpdate(int value) {
		QString timeValue = QString("00:00:") + QString::number(value/2);
		l_timeCurrentLabel->setLabelText(timeValue);
		//l_timeCurrentLabel->setLabelText(Util::formatTimeline(value/2));
	}
// }