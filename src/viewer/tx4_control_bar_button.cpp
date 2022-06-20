
#include "tx4_control_bar_button.h"

tx4_control_bar_button::tx4_control_bar_button(const QString &icon, const ButtonState &state, const QString &tooltip, const int &index, const bool &shrink, QWidget *parent)
    : QWidget(parent) {

    s_state = state;
    b_iconShrink = shrink;
    b_pressed = false;
    b_iconPixmapSet = false;
    b_buttonDisabled = (state == ButtonState::Disabled ? true : false);
    s_buttonIcon = icon;
    i_buttonIndex = index;

	this->setAttribute(Qt::WA_StyledBackground); // <--- this attribute solves issue of background color not being drawn on custom widget, no need for reimplementing paintEvent, yet.
    //this->setFixedWidth(20);
	this->setSizePolicy(QSizePolicy::Fixed , QSizePolicy::Fixed);
	this->setStyleSheet(S_CONTROL_BAR_BUTTON_NORMAL);
    this->setToolTip(tooltip);

    initContents();
    setButtonState(s_state);
}

tx4_control_bar_button::~tx4_control_bar_button() {}

void tx4_control_bar_button::initContents() {
    QHBoxLayout *h_buttonLayoutOuter = new QHBoxLayout(this);
	Util::setLayoutZero(h_buttonLayoutOuter);
    h_buttonLayoutOuter->setAlignment(Qt::AlignCenter);

    // icon
    QWidget *w_innerIcon = new QWidget;
    QHBoxLayout *h_innerIconLayout = new QHBoxLayout(w_innerIcon);
    h_innerIconLayout->setAlignment(Qt::AlignCenter);
	//Util::setLayoutZero(h_innerIconLayout);
    w_buttonIcon = new QLabel;
    w_buttonIcon->setStyleSheet(S_CONTROL_BAR_BUTTON_NORMAL);
    QPixmap p_newPixmap(s_buttonIcon);
    p_iconPixmap = p_newPixmap;
    w_buttonIcon->setPixmap(p_iconPixmap);
    h_innerIconLayout->addStretch();
    h_innerIconLayout->addWidget(w_buttonIcon);
    h_innerIconLayout->addStretch();
    b_iconPixmapSet = true;

    h_buttonLayoutOuter->addWidget(w_innerIcon);

    this->setLayout(h_buttonLayoutOuter);
}

void tx4_control_bar_button::setButtonState(ButtonState state) {
    s_state = state;
    b_buttonDisabled = ((state == ButtonState::Disabled || state == ButtonState::Hidden) ? true : false);
    repaintIconPixmap();
}

void tx4_control_bar_button::updateButtonIcon(QString newIcon) {
    s_buttonIcon = newIcon;
    QPixmap p_newPixmap(s_buttonIcon);
    p_iconPixmap = p_newPixmap;
    w_buttonIcon->setPixmap(p_iconPixmap);
    repaintIconPixmap();
}

void tx4_control_bar_button::repaintIconPixmap() {
	if (b_iconPixmapSet) {
		QPixmap target = QPixmap(p_iconPixmap.size());
		target.fill(Qt::transparent);
		QPainter painter(&target);
		QPainterPath path = QPainterPath();

		painter.setRenderHints(QPainter::Antialiasing | QPainter::SmoothPixmapTransform);
		painter.setOpacity(s_state == ButtonState::Hidden ? 0.0 : (b_pressed ? 0.5 : 1.0 ) );
		if (b_iconShrink && b_pressed) {
            painter.drawPixmap(1, 1, p_iconPixmap.rect().width()-2, p_iconPixmap.rect().height()-2, p_iconPixmap);
        } else {
            painter.drawPixmap(p_iconPixmap.rect(), p_iconPixmap);
        }

		w_buttonIcon->setPixmap(target);
	}
}


// MOUSE EVENTS:
void tx4_control_bar_button::mousePressEvent(QMouseEvent *e) {
    if (!b_buttonDisabled) {
        if (e->button() == Qt::LeftButton) {
            if (this->rect().contains(this->mapFromGlobal(QCursor::pos()))) {
                b_pressed = true;
            } else {
                b_pressed = false;
            }
            repaintIconPixmap();
            QWidget::mousePressEvent(e);
        }
    }
}
void tx4_control_bar_button::mouseReleaseEvent(QMouseEvent *e) {
    if (!b_buttonDisabled) {
        if (e->button() == Qt::LeftButton) {
		    if (this->rect().contains(this->mapFromGlobal(QCursor::pos()))) {
                emit clicked(i_buttonIndex);
            }
            b_pressed = false;
            repaintIconPixmap();

            QWidget::mouseReleaseEvent(e);
        }
    }
}


// TOGGLE
tx4_control_bar_button_toggle::tx4_control_bar_button_toggle(const QString &icon1, const QString &icon2, const ButtonState &state, const QString &tooltip, const int &index, const bool &shrink)
    : tx4_control_bar_button(icon1, state, tooltip, index, shrink)
    , s_icon1(icon1)
    , s_icon2(icon2)
    , b_buttonToggled(false)
    , s_useIcon(icon1)
{
}
tx4_control_bar_button_toggle::~tx4_control_bar_button_toggle() {}

void tx4_control_bar_button_toggle::toggleButton() {
    b_buttonToggled = !b_buttonToggled;
    s_useIcon = (b_buttonToggled ? s_icon2 : s_icon1);
    QPixmap p_newPixmap(s_useIcon);
    p_iconPixmap = p_newPixmap;
    w_buttonIcon->setPixmap(p_iconPixmap);
}

// MOUSE EVENTS:
void tx4_control_bar_button_toggle::mouseReleaseEvent(QMouseEvent *e) {
    if (e->button() == Qt::LeftButton) {
        if (!b_buttonDisabled) {
		    if (this->rect().contains(this->mapFromGlobal(QCursor::pos()))) {
                emit clicked(i_buttonIndex);
                b_pressed = false;
                toggleButton();
            }
            QWidget::mouseReleaseEvent(e);
        }
    }
}