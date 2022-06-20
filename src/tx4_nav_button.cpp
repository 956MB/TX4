
#include "tx4_nav_button.h"

tx4_nav_button::tx4_nav_button(const QString &text, const bool &enabled, const QString &tooltip, const bool &left, QWidget *parent)
    : QPushButton(parent) {

    s_enabled = enabled;
    buttonText = text;

    QPixmap leftPixNormal(ICONS_ARROW_LEFT);
    QPixmap leftPixHover(ICONS_ARROW_LEFT_HOVER);
    QPixmap rightPixNormal(ICONS_ARROW_RIGHT);
    QPixmap rightPixHover(ICONS_ARROW_RIGHT_HOVER);
    if (left) {
        normalIcon = new QIcon(leftPixNormal);
        hoverIcon = new QIcon(leftPixHover);
    } else {
        normalIcon = new QIcon(rightPixNormal);
        hoverIcon = new QIcon(rightPixHover);
    }

	this->setAttribute(Qt::WA_StyledBackground); // <--- this attribute solves issue of background color not being drawn on custom widget, no need for reimplementing paintEvent, yet.
    this->setFixedWidth(24);
	this->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Expanding);
	this->setStyleSheet(S_NAV_BUTTON_NORMAL);
    this->setToolTip(tooltip);
	this->setIconSize(QSize(20, 40));
    if (enabled) {
        this->setIcon(*normalIcon);
    } else {
        this->setIcon(QIcon());
    }

    initContents();
    setButtonState(s_enabled);
}

tx4_nav_button::~tx4_nav_button() {}

void tx4_nav_button::initContents() {
    QHBoxLayout *h_buttonLayout = new QHBoxLayout(this);
	Util::setLayoutZero(h_buttonLayout);
    //h_buttonLayout->setContentsMargins(20, 0, 20, 0);

    //buttonBar = new QWidget;
    //buttonBar->setFixedSize(1, 30);
    //buttonBar->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
    //buttonBar->setStyleSheet(S_PREVIEW_BAR_NORMAL);
    //buttonLabel = new tx4_label(buttonText, 10, buttonLabelStyle, QFont::Medium, Qt::AlignCenter, "Anonymous Pro");
    //h_buttonLayout->addStretch();
    //h_buttonLayout->addWidget(buttonBar);
    //h_buttonLayout->addStretch();
    
    this->setLayout(h_buttonLayout);
}

void tx4_nav_button::setButtonState(bool state) {
    s_enabled = state;

    if (s_enabled) {
        //buttonBar->setVisible(true);
        this->setIcon(*normalIcon);
        this->setStyleSheet(S_NAV_BUTTON_NORMAL);
    } else {
        //buttonBar->setVisible(false);
        this->setIcon(QIcon());
        this->setStyleSheet(S_NAV_BUTTON_DISABLED);
    }
}


void tx4_nav_button::enterEvent(QEvent *e) {
    if (s_enabled) {
        this->setIcon(*hoverIcon);
        this->setStyleSheet(S_NAV_BUTTON_HOVER);
        QWidget::enterEvent(e);
    }
}

void tx4_nav_button::leaveEvent(QEvent *e) {
    if (s_enabled) {
        this->setIcon(*normalIcon);
        this->setStyleSheet(S_NAV_BUTTON_NORMAL);
        QWidget::leaveEvent(e);
    }
}
void tx4_nav_button::mouseReleaseEvent(QMouseEvent *e) {
    if (s_enabled) {
        emit buttonClicked();
        QWidget::mouseReleaseEvent(e);
    }
}