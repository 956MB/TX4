
#include "tx4_checkbox.h"
#include <qboxlayout.h>
#include <QStackedLayout>

tx4_checkbox::tx4_checkbox(QWidget *parent) : QWidget(parent) {
	checkActive = false;

	this->setAttribute(Qt::WA_StyledBackground); // <--- this attribute solves issue of background color not being drawn on custom widget, no need for reimplementing paintEvent, yet.
	this->setMinimumSize(BOX_S, BOX_S);
	this->setFixedSize(BOX_S, BOX_S);
	this->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
	this->setStyleSheet(blankStyle);

	initContents();
	//initPalette();
}

tx4_checkbox::~tx4_checkbox() {}

void tx4_checkbox::setCheckboxState(bool state) {
	checkActive = state;
	inner->setVisible(checkActive);
}

void tx4_checkbox::initContents() {
	QStackedLayout *s_contentLayout = new QStackedLayout(this);
	s_contentLayout->setStackingMode(QStackedLayout::StackAll);
	s_contentLayout->setAlignment(Qt::AlignCenter | Qt::AlignHCenter | Qt::AlignVCenter);
	Util::setLayoutZero(s_contentLayout);

	outer = new QWidget;
	outer->setFixedSize(BOX_S, BOX_S);
	outer->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
	outer->setStyleSheet(outerStyle);

	QWidget *h_innerContainer = new QWidget;
	QHBoxLayout *h_innerContainerLayout = new QHBoxLayout(h_innerContainer);
	Util::setLayoutZero(h_innerContainerLayout);
	QWidget *lw = new QWidget;
	QWidget *rw = new QWidget;
	lw->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
	rw->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
	inner = new QWidget;
	inner->setFixedSize(BOX_S-12, BOX_S-12);
	inner->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
	inner->setStyleSheet(innerStyle);
	h_innerContainerLayout->addWidget(lw);
	h_innerContainerLayout->addWidget(inner);
	h_innerContainerLayout->addWidget(rw);

	s_contentLayout->addWidget(h_innerContainer);
	s_contentLayout->addWidget(outer);

	this->setLayout(s_contentLayout);
}