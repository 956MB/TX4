
#include "tx4_toolbar.h"

tx4_toolbar::tx4_toolbar(QWidget *parent)
	: QWidget(parent)
	, l_buttons(QList<tx4_toolbar_button*> ())
	, i_selectedSavedEvents(0)
	, i_selectedSentryEvents(0)
{

	this->setAttribute(Qt::WA_StyledBackground); // <--- this attribute solves issue of background color not being drawn on custom widget, no need for reimplementing paintEvent, yet.
	this->setFixedHeight(TOOLBAR_H);
	this->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Fixed);
	this->setStyleSheet(S_TOOLBAR_BODY);

	initContents();
}

tx4_toolbar::~tx4_toolbar() {}

void tx4_toolbar::initContents() {
	QHBoxLayout *h_mainLayout = new QHBoxLayout(this);
	Util::setLayoutZero(h_mainLayout);
	h_mainLayout->setContentsMargins(0,0,0,0);

	// SECTION BUTTONS
	b_recentButton = new tx4_toolbar_button("RECENT", ButtonState::Enabled, "", 0);
	b_savedButton = new tx4_toolbar_button("SAVED", ButtonState::Selected, "", 1);
	b_sentryButton = new tx4_toolbar_button("SENTRY", ButtonState::Enabled, "", 2);
	b_favoritesButton = new tx4_toolbar_button("FAVORITES", ButtonState::Enabled, "", 3);
	//QObject::connect(b_recentButton, &tx4_toolbar_button::clicked, this, [=]{ &tx4_toolbar_new::on_handleButtonClick; });
	QObject::connect(b_recentButton, &tx4_toolbar_button::clicked, this, &tx4_toolbar::on_handleButtonClick);
	QObject::connect(b_savedButton, &tx4_toolbar_button::clicked, this, &tx4_toolbar::on_handleButtonClick);
	QObject::connect(b_sentryButton, &tx4_toolbar_button::clicked, this, &tx4_toolbar::on_handleButtonClick);
	QObject::connect(b_favoritesButton, &tx4_toolbar_button::clicked, this, &tx4_toolbar::on_handleButtonClick);
	l_buttons.append(b_recentButton);
	l_buttons.append(b_savedButton);
	l_buttons.append(b_sentryButton);
	l_buttons.append(b_favoritesButton);

	b_openButton = new tx4_toolbar_button_icon(ICONS_TOOLBAR_PLAY, ButtonState::Disabled, "", 4);
	b_importButton = new tx4_toolbar_button_icon(ICONS_IMPORT, ButtonState::Enabled, "", 5);
	b_settingsButton = new tx4_toolbar_button_icon(ICONS_DOTS, ButtonState::Enabled, "", 6);
	QObject::connect(b_openButton, &tx4_toolbar_button_icon::clicked, this, [=]{ emit openButtonClick(); });
	QObject::connect(b_importButton, &tx4_toolbar_button_icon::clicked, this, [=]{ emit importButtonClick(); });
	QObject::connect(b_settingsButton, &tx4_toolbar_button_icon::clicked, this, [=]{ emit settingsButtonClick(); });

	//h_mainLayout->addStretch();
	h_mainLayout->addWidget(b_recentButton);
	h_mainLayout->addWidget(b_savedButton);
	h_mainLayout->addWidget(b_sentryButton);
	h_mainLayout->addWidget(b_favoritesButton);
	h_mainLayout->addStretch();
	h_mainLayout->addWidget(b_openButton);
	h_mainLayout->addWidget(b_importButton);
	h_mainLayout->addWidget(b_settingsButton);

	this->setLayout(h_mainLayout);
}

void tx4_toolbar::resetButtonStates() {
	b_recentButton->setButtonState(ButtonState::Enabled);
	b_savedButton->setButtonState(ButtonState::Enabled);
	b_sentryButton->setButtonState(ButtonState::Enabled);
	b_favoritesButton->setButtonState(ButtonState::Enabled);
}
void tx4_toolbar::setButtonSelected(int idx) {
	resetButtonStates();
	l_buttons.at(idx)->setButtonState(ButtonState::Selected);
}
void tx4_toolbar::updateOpenEventsButtonState(int count) {
	b_openButton->updateInnerText(count);
}
void tx4_toolbar::updateImportButtonState(bool disabled) {
	b_importButton->repaintIconPixmap(disabled);
}
void tx4_toolbar::updatePageButtonState(int page, int incr) {
	if (page == 1) {
		i_selectedSavedEvents += incr;
		b_savedButton->updateInnerText(i_selectedSavedEvents);
	}
	if (page == 2) {
		i_selectedSentryEvents += incr;
		b_sentryButton->updateInnerText(i_selectedSentryEvents);
	}
}

//void tx4_toolbar::toggleEventsLoaded(bool loaded) {
//}

// SLOTS:

void tx4_toolbar::on_handleButtonClick(int buttonIndex) {
	setButtonSelected(buttonIndex);
	emit sectionButtonClick(buttonIndex);
}