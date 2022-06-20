
#include "tx4_toolbar_button.h"

tx4_toolbar_button::tx4_toolbar_button(const QString &text, const ButtonState &state, const QString &tooltip, const int &index, const int &lrpadding, QWidget *parent)
    : QWidget(parent) {

    s_state = state;
    m_pressed = false;
    buttonText = text;
    padding = lrpadding;
    i_buttonIndex = index;
    s_buttonInnerText = "";

	this->setAttribute(Qt::WA_StyledBackground); // <--- this attribute solves issue of background color not being drawn on custom widget, no need for reimplementing paintEvent, yet.
    //this->setFixedSize(w, h);
	this->setSizePolicy(QSizePolicy::Preferred , QSizePolicy::Expanding);
	this->setStyleSheet(S_TOOLBAR_BUTTON_NORMAL);
    this->setToolTip(tooltip);

    initContents();
    setButtonState(s_state);
}

tx4_toolbar_button::~tx4_toolbar_button() {}

void tx4_toolbar_button::initContents() {
    QHBoxLayout *h_buttonLayoutOuter = new QHBoxLayout(this);
	Util::setLayoutZero(h_buttonLayoutOuter);
    h_buttonLayoutOuter->setContentsMargins(0, 3, padding, 0);

    innerButton = new QWidget;
	innerButton->setSizePolicy(QSizePolicy::Preferred, QSizePolicy::Preferred);
    QHBoxLayout *h_buttonLayoutInner = new QHBoxLayout(innerButton);
	Util::setLayoutZero(h_buttonLayoutInner);
    h_buttonLayoutInner->setContentsMargins(0,0,0,11);

    buttonLabel = new tx4_label(buttonText, 20, S_TOOLBAR_BUTTON_LABEL_NORMAL, QFont::Medium, Qt::AlignCenter);
    buttonLabel->setLabelAlignment(Qt::AlignCenter, Qt::AlignBottom);

    w_innerLabel = new QWidget;
    QHBoxLayout *h_innerLabelLayout = new QHBoxLayout(w_innerLabel);
	Util::setLayoutZero(h_innerLabelLayout);
    h_innerLabelLayout->setAlignment(Qt::AlignTop);
	h_innerLabelLayout->setContentsMargins(0,5,0,0);
    l_buttonInnerLabel = new tx4_label(s_buttonInnerText, 13, S_TOOLBAR_BUTTON_INNER_LABEL_NORMAL, QFont::Medium, Qt::AlignCenter);
    h_innerLabelLayout->addStretch();
    h_innerLabelLayout->addWidget(l_buttonInnerLabel);

    QWidget *w_innerLabelStack = new QWidget;
	w_innerLabelStack->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Preferred);
	w_innerLabelStack->setStyleSheet(S_INNER_STACK);
	QStackedLayout *s_innerLabelStackLayout = new QStackedLayout(w_innerLabelStack);
	s_innerLabelStackLayout->setStackingMode(QStackedLayout::StackAll);
	Util::setLayoutZero(s_innerLabelStackLayout);
	s_innerLabelStackLayout->setContentsMargins(20, 0, 20, 0);

    h_buttonLayoutInner->addWidget(buttonLabel);
    s_innerLabelStackLayout->addWidget(w_innerLabel);
    s_innerLabelStackLayout->addWidget(innerButton);
    h_buttonLayoutOuter->addWidget(w_innerLabelStack);
    w_innerLabel->setVisible(false);

    this->setLayout(h_buttonLayoutOuter);
}

void tx4_toolbar_button::setButtonState(ButtonState state) {
    s_state = state;

    this->setStyleSheet(S_TOOLBAR_BUTTON_DISABLED);
    buttonLabel->setLabelStyle(S_TOOLBAR_BUTTON_LABEL_DISABLED);

    if (s_state == ButtonState::Enabled) {
        innerButton->setStyleSheet(S_TOOLBAR_BUTTON_NORMAL);
        buttonLabel->setLabelStyle(S_TOOLBAR_BUTTON_LABEL_NORMAL);
        //buttonLabel->setLabelSize(20);
    }
    if (s_state == ButtonState::Selected) {
        innerButton->setStyleSheet(S_TOOLBAR_BUTTON_SELECTED);
        buttonLabel->setLabelStyle(S_TOOLBAR_BUTTON_LABEL_SELECTED);
        //buttonLabel->setLabelSize(22);
    }
}

void tx4_toolbar_button::setButtonText(QString text) {
    if (s_state != ButtonState::Disabled) {
        buttonLabel->setLabelText(text);
    }
}

void tx4_toolbar_button::updateInnerText(int text) {
    s_buttonInnerText = QString::number(text);
    l_buttonInnerLabel->setLabelText(s_buttonInnerText);
    w_innerLabel->setVisible((text >= 1 ? true : false));
}


// MOUSE EVENTS:

void tx4_toolbar_button::enterEvent(QEvent *e) {
    if (s_state != ButtonState::Disabled) {
        //this->setStyleSheet(S_TOOLBAR_BUTTON_ICON_NORMAL);
        buttonLabel->setLabelStyle(S_TOOLBAR_BUTTON_LABEL_SELECTED);
        QWidget::enterEvent(e);
    }
}
void tx4_toolbar_button::leaveEvent(QEvent *e) {
    if (s_state != ButtonState::Disabled) {
        //this->setStyleSheet(S_TOOLBAR_BUTTON_ICON_NORMAL);
        if (s_state != ButtonState::Selected) { buttonLabel->setLabelStyle(S_TOOLBAR_BUTTON_LABEL_NORMAL); }
        QWidget::leaveEvent(e);
    }
}
void tx4_toolbar_button::mousePressEvent(QMouseEvent *e) {
    if (e->button() == Qt::LeftButton) {
        if (s_state != ButtonState::Disabled) {
            if (!m_pressed) {
                m_pressed = true;
                //this->setStyleSheet(toolbarButtonStylePress);
                buttonLabel->setLabelStyle(S_TOOLBAR_BUTTON_LABEL_PRESSED);
            }
            QWidget::mousePressEvent(e);
        }
    }
}
void tx4_toolbar_button::mouseReleaseEvent(QMouseEvent *e) {
    if (e->button() == Qt::LeftButton) {
        if (s_state != ButtonState::Disabled) {
		    if (this->rect().contains(this->mapFromGlobal(QCursor::pos()))) {
                emit clicked(i_buttonIndex);

                m_pressed = false;
            } else {
                m_pressed = false;
            }
            QWidget::mouseReleaseEvent(e);
        }
    }
}