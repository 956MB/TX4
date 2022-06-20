
#include "tx4_control_bar.h"

tx4_control_bar::tx4_control_bar(QWidget *parent)
	: QWidget(parent) {

	i_barSteps = 59;

	this->setAttribute(Qt::WA_StyledBackground); // <--- this attribute solves issue of background color not being drawn on custom widget, no need for reimplementing paintEvent, yet.
	this->setFixedHeight(CONTROL_BAR_H);
	this->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Fixed);
	this->setStyleSheet(S_CONTROL_BAR_BODY);

	initContents();
}

tx4_control_bar::~tx4_control_bar() {}

void tx4_control_bar::initContents() {
	QHBoxLayout *h_mainLayout = new QHBoxLayout(this);
	Util::setLayoutZero(h_mainLayout);

	initTimeline();
	
	h_mainLayout->addWidget(w_timelineContainer);

	this->setLayout(h_mainLayout);
}

void tx4_control_bar::initTimeline() {
	QWidget *w_buttonsLeftContainer = new QWidget;
	QWidget *w_buttonsRightContainer = new QWidget;
	QWidget *w_currentTimeContainer = new QWidget;
	QWidget *w_totalTimeContainer = new QWidget;
	w_timelineContainer = new QWidget;
	QWidget *w_timelineBody = new QWidget;
	Util::setWidgetsSizePolicy(QSizePolicy::Fixed, QSizePolicy::Expanding, {w_buttonsLeftContainer, w_buttonsRightContainer, w_currentTimeContainer, w_totalTimeContainer});
	Util::setWidgetsSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding, {w_timelineContainer, w_timelineBody});

	// timeline container top
	w_timelineContainer->setStyleSheet(S_BUTTON_CONTAINER_BODY);
	QHBoxLayout *h_timelineContainerLayout = new QHBoxLayout(w_timelineContainer);
	Util::setLayoutZero(h_timelineContainerLayout);
	h_timelineContainerLayout->setContentsMargins(OUTER_MARGIN*2,0,OUTER_MARGIN*2,0);

	w_timelineBody->setStyleSheet(S_TIMELINE_BODY);
	QHBoxLayout *h_timelineBodyLayout = new QHBoxLayout(w_timelineBody);
	Util::setLayoutZero(h_timelineBodyLayout);
	//v_timelineBodyLayout->setContentsMargins(3,0,3,0);
	w_timelineSlider = new QSlider(Qt::Horizontal, w_timelineBody);
	w_timelineSlider->setTickPosition(QSlider::NoTicks);
	w_timelineSlider->setTickInterval(QSlider::NoTicks);
	w_timelineSlider->setMinimum(TIMELINE_MIN);
    w_timelineSlider->setMaximum(TIMELINE_MAX * i_barSteps);
	w_timelineSlider->setStyleSheet(S_TIMELINE_SLIDER);
	w_timelineSlider->setSliderPosition(0);

	QObject::connect(w_timelineSlider, &QSlider::valueChanged, this, &tx4_control_bar::on_timelineValueUpdate);

	// buttons left
	w_buttonsLeftContainer->setStyleSheet(S_TIMELINE_CONTAINER);
	QHBoxLayout *h_buttonsLeftContainerLayout = new QHBoxLayout(w_buttonsLeftContainer);
	Util::setLayoutZero(h_buttonsLeftContainerLayout);
	h_buttonsLeftContainerLayout->setSpacing(7);
	h_buttonsLeftContainerLayout->setContentsMargins(0,0,7,0);
	b_backButton = new tx4_control_bar_button(ICONS_CONTROL_BAR_SKIP_BACK_CURVED, ButtonState::Enabled, "", 0);
	b_playPauseButton = new tx4_control_bar_button_toggle(ICONS_CONTROL_BAR_PLAY_CURVED, ICONS_CONTROL_BAR_PAUSE, ButtonState::Enabled, "", 1);
	b_playPauseButton->setFixedWidth(30);
	b_forwardButton = new tx4_control_bar_button(ICONS_CONTROL_BAR_SKIP_FORWARD_CURVED, ButtonState::Enabled, "", 2);
	h_buttonsLeftContainerLayout->addWidget(b_backButton);
	h_buttonsLeftContainerLayout->addWidget(b_playPauseButton);
	h_buttonsLeftContainerLayout->addWidget(b_forwardButton);

	// buttons right
	w_buttonsRightContainer->setStyleSheet(S_TIMELINE_CONTAINER);
	QHBoxLayout *h_buttonsRightContainerLayout = new QHBoxLayout(w_buttonsRightContainer);
	Util::setLayoutZero(h_buttonsRightContainerLayout);
	h_buttonsRightContainerLayout->setSpacing(7);
	h_buttonsRightContainerLayout->setContentsMargins(7,0,0,0);
	b_fullscreenButton = new tx4_control_bar_button(ICONS_CONTROL_BAR_FULLSCREEN_CURVED, ButtonState::Enabled, "", 3);
	b_layoutButton = new tx4_control_bar_button(ICONS_LAYOUT_L3, ButtonState::Enabled, "", 4, true);
	b_layoutButton->setFixedWidth(40); // TODO: cant set 18/19 wide icon fixed width, for some reason cuts off icon. COULD be padding, if i set default level of padding around button icon, i can calculate the fixed width by iconW + padding*2
	h_buttonsRightContainerLayout->addWidget(b_fullscreenButton);
	h_buttonsRightContainerLayout->addWidget(b_layoutButton);

	//QObject::connect(w_timelineSlider, &QSlider::valueChanged, this, &tx4_control_bar::on_timelineValueUpdate);
	QObject::connect(b_layoutButton, &tx4_control_bar_button::clicked, this, &tx4_control_bar::on_cycleLoadoutClicked);

	// time current
	w_currentTimeContainer->setFixedWidth(60);
	w_currentTimeContainer->setStyleSheet(S_TIMELINE_CONTAINER);
	QHBoxLayout *h_currentTimeContainerLayout = new QHBoxLayout(w_currentTimeContainer);
	Util::setLayoutZero(h_currentTimeContainerLayout);
	l_timeCurrentLabel = new tx4_label("0:00", 13, S_TIME_LABEL, QFont::DemiBold, Qt::AlignHCenter, Qt::AlignVCenter);
	h_currentTimeContainerLayout->addWidget(l_timeCurrentLabel);

	// time total
	w_totalTimeContainer->setFixedWidth(60);
	w_totalTimeContainer->setStyleSheet(S_TIMELINE_CONTAINER);
	QHBoxLayout *h_totalTimeContainerLayout = new QHBoxLayout(w_totalTimeContainer);
	Util::setLayoutZero(h_totalTimeContainerLayout);
	l_timeTotalLabel = new tx4_label("0:59", 13, S_TIME_LABEL, QFont::DemiBold, Qt::AlignHCenter, Qt::AlignVCenter);
	h_totalTimeContainerLayout->addWidget(l_timeTotalLabel);

	h_timelineBodyLayout->addWidget(w_buttonsLeftContainer);
	h_timelineBodyLayout->addWidget(w_currentTimeContainer);
	h_timelineBodyLayout->addWidget(w_timelineSlider);
	h_timelineBodyLayout->addWidget(w_totalTimeContainer);
	h_timelineBodyLayout->addWidget(w_buttonsRightContainer);
	h_timelineContainerLayout->addWidget(w_timelineBody);
}

void tx4_control_bar::resetControlBar() {

}

void tx4_control_bar::updateLayoutIcon(QString newIcon) {
	b_layoutButton->updateButtonIcon(newIcon);
}


// SLOTS:
void tx4_control_bar::on_timelineValueUpdate(int value) {
	QString timeValue = QString("0:") + QString::number(value/TIMELINE_MAX).rightJustified(2, '0');;
	l_timeCurrentLabel->setLabelText(timeValue);
	//l_timeCurrentLabel->setLabelText(Util::formatTimeline(value/2));
}
void tx4_control_bar::on_cycleLoadoutClicked() {
	// change layout button icon
	emit cycleLayout();
}