
#include "tx4_toolbar_button.h"

tx4_toolbar_button::tx4_toolbar_button(const QString &text, const bool &enabled, const QString &tooltip, QWidget *parent)
    : QWidget(parent) {

    s_enabled = enabled;
    buttonText = text;

	this->setAttribute(Qt::WA_StyledBackground); // <--- this attribute solves issue of background color not being drawn on custom widget, no need for reimplementing paintEvent, yet.
    //this->setFixedSize(w, h);
	this->setSizePolicy(QSizePolicy::Preferred , QSizePolicy::Expanding);
	this->setStyleSheet(toolbarButtonStyleNormal);
    this->setToolTip(tooltip);

    initContents();
    setButtonState(s_enabled);
}

tx4_toolbar_button::~tx4_toolbar_button() {}

void tx4_toolbar_button::initContents() {
    QHBoxLayout *h_buttonLayout = new QHBoxLayout(this);
	Util::setLayoutZero(h_buttonLayout);
    h_buttonLayout->setContentsMargins(20, 0, 20, 0);

    buttonLabel = new tx4_label(buttonText, 10, buttonLabelStyle, QFont::Medium, Qt::AlignCenter, "Anonymous Pro");

    //h_buttonLayout->addStretch();
    h_buttonLayout->addWidget(new tx4_label("*", 10, extraLabelStyle, QFont::Medium, Qt::AlignCenter, "Anonymous Pro"));
    h_buttonLayout->addWidget(buttonLabel);
    h_buttonLayout->addWidget(new tx4_label("*", 10, extraLabelStyle, QFont::Medium, Qt::AlignCenter, "Anonymous Pro"));
    //h_buttonLayout->addStretch();
    this->setLayout(h_buttonLayout);
}

void tx4_toolbar_button::setButtonState(bool state) {
    s_enabled = state;

    if (s_enabled) {
        this->setStyleSheet(toolbarButtonStyleNormal);
        buttonLabel->setStyleSheet(buttonLabelStyle);
    } else {
        this->setStyleSheet(toolbarButtonStyleDisabled);
        buttonLabel->setStyleSheet(buttonLabelStyleDisabled);
    }
}


void tx4_toolbar_button::enterEvent(QEvent *e) {
    if (s_enabled) {
        this->setStyleSheet(toolbarButtonStyleHover);

        QWidget::enterEvent(e);
    }
}

void tx4_toolbar_button::leaveEvent(QEvent *e) {
    if (s_enabled) {
        this->setStyleSheet(toolbarButtonStyleNormal);

        QWidget::leaveEvent(e);
    }
}
void tx4_toolbar_button::mouseReleaseEvent(QMouseEvent *e) {
    if (s_enabled) {
        emit clicked();
        QWidget::mouseReleaseEvent(e);
    }
}