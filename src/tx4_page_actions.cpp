
#include "tx4_page_actions.h"

tx4_page_actions::tx4_page_actions(QWidget *parent)
	: QWidget(parent) {

	l_actionsTextList << "DATE"
					  << "CITY"
				      << "REASON"
				      << "SIZE"
				      << "LENGTH";

	this->setAttribute(Qt::WA_StyledBackground); // <--- this attribute solves issue of background color not being drawn on custom widget, no need for reimplementing paintEvent, yet.
	this->setFixedHeight(PAGE_ACTIONS_H);
	this->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Fixed);
	this->setStyleSheet(S_ACTIONS_BODY);

	initContents();
}

tx4_page_actions::~tx4_page_actions() {}

void tx4_page_actions::initContents() {
	QHBoxLayout *h_actionsOuterLayout = new QHBoxLayout(this);
	Util::setLayoutZero(h_actionsOuterLayout);
	h_actionsOuterLayout->setContentsMargins(OUTER_MARGIN,0,OUTER_MARGIN,0);

	QWidget *w_actionsInner = new QWidget;
	w_actionsInner->setStyleSheet(S_ACTIONS_BODY_INNER);
	QHBoxLayout *h_actionsInnerLayout = new QHBoxLayout(w_actionsInner);
	Util::setLayoutZero(h_actionsInnerLayout);
	h_actionsInnerLayout->setSpacing(1);
	h_actionsInnerLayout->setContentsMargins(173,0,45,0);
	//h_actionsOuterLayout->addSpacerItem(new QSpacerItem(128, 0, QSizePolicy::Fixed, QSizePolicy::Expanding));

	for (int i = 0; i < l_actionsTextList.count(); i++) {
		QWidget *w_textContainer = new QWidget;
		w_textContainer->setStyleSheet(S_ACTIONS_TEXT);
		QHBoxLayout *h_textLayout = new QHBoxLayout(w_textContainer);
		Util::setLayoutZero(h_textLayout);
		h_textLayout->setAlignment(Qt::AlignLeading);
		w_textContainer->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);

		tx4_selectable_label *w_infoText = new tx4_selectable_label(l_actionsTextList[i], 13, S_SELECTABLE_LABEL_NORMAL, QFont::Medium, Qt::AlignLeading, Qt::AlignVCenter);
		w_infoText->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Expanding);
		w_infoText->setLabelActive(false);
		h_textLayout->addWidget(w_infoText);

		//if (i == 2) {
		//	h_textLayout->addSpacerItem(new QSpacerItem(139, 0, QSizePolicy::Expanding, QSizePolicy::Expanding));
		//}
		h_actionsInnerLayout->addWidget(w_textContainer);
	}

	h_actionsOuterLayout->addWidget(w_actionsInner);

	this->setLayout(h_actionsOuterLayout);
}