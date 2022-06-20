
#include "tx4_toolbar_button_icon.h"

tx4_toolbar_button_icon::tx4_toolbar_button_icon(const QString &icon, const ButtonState &state, const QString &tooltip, const int &index, const bool &useText, QWidget *parent)
    : QWidget(parent) {

    s_state = state;
    b_pressed = false;
    b_iconPixmapSet = false;
    b_buttonDisabled = (state == ButtonState::Disabled ? true : false);
    b_useText = useText;
    s_buttonIcon = icon;
    s_buttonInnerText = "3";
    i_buttonIndex = index;

	this->setAttribute(Qt::WA_StyledBackground); // <--- this attribute solves issue of background color not being drawn on custom widget, no need for reimplementing paintEvent, yet.
    this->setFixedSize(53, 55);
	this->setSizePolicy(QSizePolicy::Fixed , QSizePolicy::Fixed);
	this->setStyleSheet(S_TOOLBAR_BUTTON_ICON_NORMAL);
    this->setToolTip(tooltip);

    initContents();
    setButtonState(s_state);
    repaintIconPixmap(b_buttonDisabled);
}

tx4_toolbar_button_icon::~tx4_toolbar_button_icon() {}

void tx4_toolbar_button_icon::initContents() {
    QHBoxLayout *h_buttonLayoutOuter = new QHBoxLayout(this);
	Util::setLayoutZero(h_buttonLayoutOuter);

    // icon
    QWidget *w_innerIcon = new QWidget;
    QHBoxLayout *h_innerIconLayout = new QHBoxLayout(w_innerIcon);
	Util::setLayoutZero(h_innerIconLayout);
    w_buttonIcon = new QLabel;
    w_buttonIcon->setStyleSheet(S_TOOLBAR_BUTTON_ICON_NORMAL);
    QPixmap p_newPixmap(s_buttonIcon);
    p_iconPixmap = p_newPixmap;
    w_buttonIcon->setPixmap(p_iconPixmap);
    h_innerIconLayout->addStretch();
    h_innerIconLayout->addWidget(w_buttonIcon);
    h_innerIconLayout->addStretch();
    b_iconPixmapSet = true;

    // label
    w_innerLabel = new QWidget;
    QHBoxLayout *h_innerLabelLayout = new QHBoxLayout(w_innerLabel);
	Util::setLayoutZero(h_innerLabelLayout);
    h_innerLabelLayout->setAlignment(Qt::AlignTop);
	h_innerLabelLayout->setContentsMargins(0,5,11,0);
    l_buttonInnerLabel = new tx4_label(s_buttonInnerText, 13, S_TOOLBAR_BUTTON_INNER_LABEL_NORMAL, QFont::Medium, Qt::AlignCenter);
    h_innerLabelLayout->addStretch();
    h_innerLabelLayout->addWidget(l_buttonInnerLabel);

    QWidget *w_innerLabelStack = new QWidget;
	//emptyStateStack->setFixedHeight(PREVIEW_H);
	w_innerLabelStack->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
	w_innerLabelStack->setStyleSheet(S_INNER_STACK);
	QStackedLayout *s_innerLabelStackLayout = new QStackedLayout(w_innerLabelStack);
	s_innerLabelStackLayout->setStackingMode(QStackedLayout::StackAll);
	Util::setLayoutZero(s_innerLabelStackLayout);
	s_innerLabelStackLayout->setContentsMargins(20, 0, 20, 0);

    s_innerLabelStackLayout->addWidget(w_innerLabel);
    s_innerLabelStackLayout->addWidget(w_innerIcon);
    h_buttonLayoutOuter->addWidget(w_innerLabelStack);
    w_innerLabel->setVisible(b_useText);

    this->setLayout(h_buttonLayoutOuter);
}

void tx4_toolbar_button_icon::setButtonState(ButtonState state) {
    s_state = state;
    b_buttonDisabled = (state == ButtonState::Disabled ? true : false);

    this->setStyleSheet(S_TOOLBAR_BUTTON_ICON_NORMAL);

    if (s_state == ButtonState::Selected) {
        this->setStyleSheet(S_TOOLBAR_BUTTON_ICON_SELECTED);
    }
    if (s_state == ButtonState::Disabled) {
        this->setStyleSheet(S_TOOLBAR_BUTTON_ICON_DISABLED);
    }
}

void tx4_toolbar_button_icon::updateInnerText(int text) {
    s_buttonInnerText = QString::number(text);
    l_buttonInnerLabel->setLabelText(s_buttonInnerText);
    w_innerLabel->setVisible((text >= 1 ? true : false));
    repaintIconPixmap((text >= 1 ? false : true));
}

void tx4_toolbar_button_icon::repaintIconPixmap(bool disabled) {
	if (b_iconPixmapSet) {
        b_buttonDisabled = disabled;
		QPixmap target = QPixmap(p_iconPixmap.size());
		target.fill(Qt::transparent);
		QPainter painter(&target);
		QPainterPath path = QPainterPath();

		painter.setRenderHints(QPainter::Antialiasing | QPainter::SmoothPixmapTransform);
		painter.setOpacity(disabled == true ? 0.4 : 1.0 );
		painter.drawPixmap(p_iconPixmap.rect(), p_iconPixmap);
		//painter.drawImage(w_contentLabel->rect(), p_thumbnailPixmap.toImage().convertToFormat((grayscale == true ? QImage::Format_Grayscale8 : QImage::Format_RGB32 )));

		w_buttonIcon->setPixmap(target);
	}
}


// MOUSE EVENTS:

void tx4_toolbar_button_icon::enterEvent(QEvent *e) {
    if (!b_buttonDisabled) {
        this->setStyleSheet(S_TOOLBAR_BUTTON_ICON_HOVERED);
        //buttonLabel->setLabelStyle(S_TOOLBAR_BUTTON_LABEL_SELECTED);
        QWidget::enterEvent(e);
    }
}
void tx4_toolbar_button_icon::leaveEvent(QEvent *e) {
    if (!b_buttonDisabled) {
        this->setStyleSheet(S_TOOLBAR_BUTTON_ICON_NORMAL);
        //if (s_state != ButtonState::Selected) { buttonLabel->setLabelStyle(S_TOOLBAR_BUTTON_LABEL_NORMAL); }
        QWidget::leaveEvent(e);
    }
}
void tx4_toolbar_button_icon::mousePressEvent(QMouseEvent *e) {
    if (e->button() == Qt::LeftButton) {
        if (!b_buttonDisabled) {
            if (!b_pressed) {
                b_pressed = true;
                //this->setStyleSheet(toolbarButtonStylePress);
                //buttonLabel->setLabelStyle(S_TOOLBAR_BUTTON_LABEL_PRESSED);
            }
            QWidget::mousePressEvent(e);
        }
    }
}
void tx4_toolbar_button_icon::mouseReleaseEvent(QMouseEvent *e) {
    if (e->button() == Qt::LeftButton) {
        if (!b_buttonDisabled) {
		    if (this->rect().contains(this->mapFromGlobal(QCursor::pos()))) {
                emit clicked(i_buttonIndex);
                b_pressed = false;
            }
            QWidget::mouseReleaseEvent(e);
        }
    }
}