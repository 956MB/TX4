
#include "tx4_list_button.h"

tx4_list_button::tx4_list_button(const ButtonState &state, const QString &iconSelect, const QString &iconDeselect, const QString &tooltip, const int &index, QWidget *parent)
    : QWidget(parent) {

    s_state = state;
    b_pressed = false;
    b_parentHovered = false;
    b_iconPixmapsSet = false;
    b_buttonDisabled = (state == ButtonState::Disabled ? true : false);
    s_buttonIconSelect = iconSelect;
    s_buttonIconDeselect = iconDeselect;
    s_buttonInnerText = QString::number(index+1);
    i_buttonIndex = index;

	this->setAttribute(Qt::WA_StyledBackground); // <--- this attribute solves issue of background color not being drawn on custom widget, no need for reimplementing paintEvent, yet.
    this->setFixedSize(LIST_ITEM_H, LIST_ITEM_H);
	this->setSizePolicy(QSizePolicy::Fixed , QSizePolicy::Fixed);
	this->setStyleSheet(S_LIST_BUTTON_INNER_STACK_NORMAL);
    this->setToolTip(tooltip);

    initContents();
    setButtonState(s_state);
    //repaintIconPixmap(b_buttonDisabled);
}

tx4_list_button::~tx4_list_button() {}

void tx4_list_button::initContents() {
    QVBoxLayout *v_mainLayout = new QVBoxLayout(this);
	Util::setLayoutZero(v_mainLayout);
	v_mainLayout->setContentsMargins(7,7,7,7);

	w_iconsStackWidget = new QStackedWidget;

    // index text
    QWidget *w_textWidget = new QWidget;
    QHBoxLayout *h_textLayout = new QHBoxLayout(w_textWidget);
	Util::setLayoutZero(h_textLayout);
    h_textLayout->setAlignment(Qt::AlignCenter);
    w_buttonInnerText = new tx4_label(s_buttonInnerText, 13, S_LIST_BUTTON_INNER_LABEL_NORMAL, QFont::Medium);
    h_textLayout->addWidget(w_buttonInnerText);

    // select icon
    QWidget *w_iconSelectWidget = new QWidget;
    QHBoxLayout *h_iconSelectLayout = new QHBoxLayout(w_iconSelectWidget);
	Util::setLayoutZero(h_iconSelectLayout);
    h_iconSelectLayout->setAlignment(Qt::AlignCenter);
    w_buttonIconSelect = new QLabel;
    w_buttonIconSelect->setStyleSheet(S_LIST_BUTTON_ICON_NORMAL);
    QPixmap p_selectIconPixmap(s_buttonIconSelect);
    w_buttonIconSelect->setPixmap(p_selectIconPixmap);
    h_iconSelectLayout->addWidget(w_buttonIconSelect);

    // deselect icon
    QWidget *w_iconDeselectWidget = new QWidget;
    QHBoxLayout *h_iconDeselectLayout = new QHBoxLayout(w_iconDeselectWidget);
	Util::setLayoutZero(h_iconDeselectLayout);
    h_iconDeselectLayout->setAlignment(Qt::AlignCenter);
    w_buttonIconDeselect = new QLabel;
    w_buttonIconDeselect->setStyleSheet(S_LIST_BUTTON_ICON_NORMAL);
    QPixmap p_deselectIconPixmap(s_buttonIconDeselect);
    w_buttonIconDeselect->setPixmap(p_deselectIconPixmap);
    h_iconDeselectLayout->addWidget(w_buttonIconDeselect);

    w_iconsStackWidget->addWidget(w_textWidget);
	w_iconsStackWidget->addWidget(w_iconSelectWidget);
	w_iconsStackWidget->addWidget(w_iconDeselectWidget);
	w_iconsStackWidget->setCurrentIndex(0);
	v_mainLayout->addWidget(w_iconsStackWidget);

    b_iconPixmapsSet = true;
    this->setLayout(v_mainLayout);
}

void tx4_list_button::setButtonState(ButtonState state) {
    s_state = state;
    b_buttonDisabled = (state == ButtonState::Disabled ? true : false);

    if (s_state == ButtonState::Disabled) { w_iconsStackWidget->setCurrentIndex(0); }
    if (s_state == ButtonState::Enabled) {
        if (!b_parentHovered) { w_iconsStackWidget->setCurrentIndex(0); }
    }
    if (s_state == ButtonState::Hovered) { w_iconsStackWidget->setCurrentIndex(1); }
    if (s_state == ButtonState::Selected) { w_iconsStackWidget->setCurrentIndex(2); }
}

//void tx4_list_button::updateInnerText(int text) {
//    //l_buttonInnerLabel->setLabelText(QString::number(text));
//    //w_innerLabel->setVisible((text >= 1 ? true : false));
//    //repaintIconPixmap((text >= 1 ? false : true));
//}
//
//void tx4_list_button::repaintIconPixmap(bool disabled) {
//	//if (b_iconPixmapSet) {
// //       b_buttonDisabled = disabled;
//	//	QPixmap target = QPixmap(p_iconPixmap.size());
//	//	target.fill(Qt::transparent);
//	//	QPainter painter(&target);
//	//	QPainterPath path = QPainterPath();
//
//	//	painter.setRenderHints(QPainter::Antialiasing | QPainter::SmoothPixmapTransform);
//	//	painter.setOpacity(disabled == true ? 0.4 : 1.0 );
//	//	painter.drawPixmap(p_iconPixmap.rect(), p_iconPixmap);
//	//	//painter.drawImage(w_contentLabel->rect(), p_thumbnailPixmap.toImage().convertToFormat((grayscale == true ? QImage::Format_Grayscale8 : QImage::Format_RGB32 )));
//
//	//	w_buttonIcon->setPixmap(target);
//	//}
//}


// MOUSE EVENTS:

void tx4_list_button::enterEvent(QEvent *e) {
    if (!b_buttonDisabled) {
        this->setStyleSheet(S_LIST_BUTTON_INNER_STACK_HOVERED);
        setButtonState((s_state == ButtonState::Selected ? ButtonState::Selected : ButtonState::Hovered));
        QWidget::enterEvent(e);
    }
}
void tx4_list_button::leaveEvent(QEvent *e) {
    if (!b_buttonDisabled) {
        this->setStyleSheet(S_LIST_BUTTON_INNER_STACK_NORMAL);
        setButtonState((s_state == ButtonState::Selected ? ButtonState::Selected : ButtonState::Enabled));
        QWidget::leaveEvent(e);
    }
}
void tx4_list_button::mousePressEvent(QMouseEvent *e) {
    if (e->button() == Qt::LeftButton) {
        if (!b_buttonDisabled) {
            if (!b_pressed) {
                b_pressed = true;
            }
            QWidget::mousePressEvent(e);
        }
    }
}
void tx4_list_button::mouseReleaseEvent(QMouseEvent *e) {
    if (e->button() == Qt::LeftButton) {
        if (!b_buttonDisabled) {
		    if (this->rect().contains(this->mapFromGlobal(QCursor::pos()))) {
                emit clicked(i_buttonIndex);

                b_pressed = false;
            } else {
                b_pressed = false;
            }
            QWidget::mouseReleaseEvent(e);
        }
    }
}