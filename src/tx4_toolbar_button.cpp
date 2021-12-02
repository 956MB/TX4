
#include "tx4_toolbar_button.h"

tx4_toolbar_button::tx4_toolbar_button(const QString &text, const bool &enabled, const QString &tooltip, const QString &extraLeft, const QString &extraRight, const int &lrpadding, QWidget *parent)
    : QWidget(parent) {

    s_enabled = enabled;
    m_pressed = false;
    buttonText = text;
    extraTextLeft = extraLeft;
    extraTextRight = extraRight;
    padding = lrpadding;

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
    h_buttonLayout->setContentsMargins(padding, 0, padding, 0);

    buttonLabel = new tx4_label(buttonText, 10, buttonLabelStyle, QFont::Medium, Qt::AlignCenter);

    //h_buttonLayout->addStretch();
    //h_buttonLayout->addWidget(new tx4_label(extraTextLeft, 10, extraLabelStyle, QFont::Medium, Qt::AlignCenter));
    h_buttonLayout->addWidget(buttonLabel);
    //h_buttonLayout->addWidget(new tx4_label(extraTextRight, 10, extraLabelStyle, QFont::Medium, Qt::AlignCenter));
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

void tx4_toolbar_button::setButtonText(QString text) {
    if (s_enabled) {
        buttonLabel->setLabelText(text);
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
void tx4_toolbar_button::mousePressEvent(QMouseEvent *e) {
    if (s_enabled) {
        if (!m_pressed) {
            m_pressed = true;
            this->setStyleSheet(toolbarButtonStylePress);
        }
        QWidget::mouseReleaseEvent(e);
    }
}
void tx4_toolbar_button::mouseReleaseEvent(QMouseEvent *e) {
    if (s_enabled) {
		if (this->rect().contains(this->mapFromGlobal(QCursor::pos()))) {
            m_pressed = false;
            this->setStyleSheet(toolbarButtonStyleHover);
            emit clicked();
        } else {
            m_pressed = false;
            this->setStyleSheet(toolbarButtonStyleNormal);
        }
        QWidget::mouseReleaseEvent(e);
    }
}