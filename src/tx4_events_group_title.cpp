
#include "tx4_events_group_title.h"

tx4_events_group_title::tx4_events_group_title(const QString &title, const QString &style, const bool &mouseActions, QWidget *parent)
	: QWidget(parent)
	, s_groupTitle(title)
	, m_mouseActions(mouseActions)
	, s_titleStyle(style)
{

	m_pressed = false;

	this->setAttribute(Qt::WA_StyledBackground); // <--- this attribute solves issue of background color not being drawn on custom widget, no need for reimplementing paintEvent, yet.
	//this->setFixedHeight(TOOLBAR_H);
	this->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Preferred);
	this->setStyleSheet(S_GROUP_BODY_NORMAL);

	initContents();
}

tx4_events_group_title::~tx4_events_group_title() {}

void tx4_events_group_title::initContents() {
	QHBoxLayout *h_titleLayout = new QHBoxLayout(this);
	Util::setLayoutZero(h_titleLayout);
	h_titleLayout->setContentsMargins(0, 13, 0, 13);
	l_titleLabel = new tx4_label(s_groupTitle, 13, s_titleStyle, QFont::Medium);
	l_titleLabel->setWordWrap(false);
	h_titleLayout->addWidget(l_titleLabel);
	h_titleLayout->addStretch();

	this->setLayout(h_titleLayout);
}

void tx4_events_group_title::updateTitleString(bool selected, QString newTitle) {
	l_titleLabel->setLabelText(newTitle);
	l_titleLabel->setStyleSheet(selected == true ? S_GROUP_TITLE_INFO_SELECTED : S_GROUP_TITLE_INFO_NORMAL);
}

void tx4_events_group_title::enterEvent(QEvent *e) {
	if (m_mouseActions) {
		l_titleLabel->setLabelStyle(S_VALUE_LABEL_NORMAL);
		QWidget::enterEvent(e);
	}
}
void tx4_events_group_title::leaveEvent(QEvent *e) {
	if (m_mouseActions) {
		l_titleLabel->setLabelStyle(S_VALUE_LABEL_PRESSED);
		QWidget::leaveEvent(e);
	}
}
void tx4_events_group_title::mousePressEvent(QMouseEvent *e) {
	if (e->button() == Qt::LeftButton) {
		if (m_mouseActions) {
			if (this->rect().contains(this->mapFromGlobal(QCursor::pos()))) {
				if (!m_pressed) {
					m_pressed = true;
					l_titleLabel->setLabelStyle(S_VALUE_LABEL_HOVERED);
				}
				QWidget::mousePressEvent(e);
			}
		}
	}
}
void tx4_events_group_title::mouseReleaseEvent(QMouseEvent *e) {
	if (e->button() == Qt::LeftButton) {
		if (m_mouseActions) {
			if (this->rect().contains(this->mapFromGlobal(QCursor::pos()))) {
				emit clicked();
				m_pressed = false;
				l_titleLabel->setLabelStyle(S_VALUE_LABEL_PRESSED);
			} else {
				m_pressed = false;
				l_titleLabel->setLabelStyle(S_VALUE_LABEL_PRESSED);
			}
			QWidget::mouseReleaseEvent(e);
		}
	}
}