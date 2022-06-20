
#include "tx4_preview_bar.h"

tx4_preview_bar::tx4_preview_bar(const QString &date, const QString &loc, const QString &size, const QString &length, const QString &meta, const bool &top, QWidget *parent) : QWidget(parent) {
	this->setAttribute(Qt::WA_StyledBackground); // <--- this attribute solves issue of background color not being drawn on custom widget, no need for reimplementing paintEvent, yet.

	QHBoxLayout *h_barLayout = new QHBoxLayout(this);
	Util::setLayoutZero(h_barLayout);
	h_barLayout->setContentsMargins(6,9,6,0);
	//h_barLayout->setSpacing(6);
	//this->setFixedHeight(BAR_H);
	this->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Fixed);
	this->setStyleSheet(S_PREVIEW_BAR_NORMAL);

	dateText = new tx4_label(date, 10, S_PREVIEW_BAR_TEXT, QFont::Medium, Qt::AlignCenter);
	locText = new tx4_label(loc, 10, S_PREVIEW_BAR_TEXT, QFont::Medium, Qt::AlignCenter);
	sizeText = new tx4_label(size, 10, S_PREVIEW_BAR_TEXT, QFont::Medium, Qt::AlignCenter);
	lengthText = new tx4_label(length, 10, S_PREVIEW_BAR_TEXT, QFont::Medium, Qt::AlignCenter);
	topText = new tx4_label(meta, 10, S_PREVIEW_BAR_TEXT, QFont::Medium, Qt::AlignCenter);

	if (top) {
		h_barLayout->addStretch();
		//h_barLayout->addWidget(new tx4_label("[", 10, S_PREVIEW_BAR_BRACE, QFont::Medium, Qt::AlignCenter, Qt::AlignVCenter, "Anonymous Pro", 0));
		h_barLayout->addWidget(topText);
		//h_barLayout->addWidget(new tx4_label("]", 10, S_PREVIEW_BAR_BRACE, QFont::Medium, Qt::AlignCenter, Qt::AlignVCenter, "Anonymous Pro", 0));
		h_barLayout->addStretch();
	} else {
		h_barLayout->addStretch();
		//h_barLayout->addWidget(new tx4_label("[", 10, S_PREVIEW_BAR_BRACE, QFont::Medium, Qt::AlignCenter));
		h_barLayout->addWidget(dateText);
		h_barLayout->addStretch();
		h_barLayout->addWidget(new tx4_label("|", 10, S_PREVIEW_BAR_BRACE, QFont::Medium, Qt::AlignCenter));
		//h_barLayout->addWidget(new tx4_label("]", 10, S_PREVIEW_BAR_BRACE, QFont::Medium, Qt::AlignCenter));
		h_barLayout->addStretch();
		//h_barLayout->addWidget(new tx4_label("[", 10, S_PREVIEW_BAR_BRACE, QFont::Medium, Qt::AlignCenter));
		h_barLayout->addWidget(locText);
		h_barLayout->addStretch();
		h_barLayout->addWidget(new tx4_label("|", 10, S_PREVIEW_BAR_BRACE, QFont::Medium, Qt::AlignCenter));
		//h_barLayout->addWidget(new tx4_label("]", 10, S_PREVIEW_BAR_BRACE, QFont::Medium, Qt::AlignCenter));
		h_barLayout->addStretch();
		//h_barLayout->addWidget(new tx4_label("[", 10, S_PREVIEW_BAR_BRACE, QFont::Medium, Qt::AlignCenter));
		h_barLayout->addWidget(sizeText);
		h_barLayout->addStretch();
		h_barLayout->addWidget(new tx4_label("|", 10, S_PREVIEW_BAR_BRACE, QFont::Medium, Qt::AlignCenter));
		//h_barLayout->addWidget(new tx4_label("]", 10, S_PREVIEW_BAR_BRACE, QFont::Medium, Qt::AlignCenter));
		h_barLayout->addStretch();
		//h_barLayout->addWidget(new tx4_label("[", 10, S_PREVIEW_BAR_BRACE, QFont::Medium, Qt::AlignCenter));
		h_barLayout->addWidget(lengthText);
		//h_barLayout->addWidget(new tx4_label("]", 10, S_PREVIEW_BAR_BRACE, QFont::Medium, Qt::AlignCenter));
		h_barLayout->addStretch();
	}

	this->setLayout(h_barLayout);
}

tx4_preview_bar::~tx4_preview_bar() {}

void tx4_preview_bar::setHoverStyle(bool top, QString topStyle) {
	if (top) {
		this->setStyleSheet(topStyle);
	} else {
		this->setStyleSheet(S_PREVIEW_BAR_NORMAL);
	}
}
void tx4_preview_bar::setSelectedStyle(bool top) {
	if (top) {
		this->setStyleSheet(S_PREVIEW_BAR_HOVER_SMODE_TOP);
	} else {
		this->setStyleSheet(S_PREVIEW_BAR_HOVER_SMODE);
	}
}
void tx4_preview_bar::setTextStylesheet(QString setStyle) {
	dateText->setStyleSheet(setStyle);
	locText->setStyleSheet(setStyle);
	sizeText->setStyleSheet(setStyle);
	lengthText->setStyleSheet(setStyle);
	topText->setStyleSheet(setStyle);
}