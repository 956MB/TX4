
#include "tx4_preview_bar.h"

tx4_preview_bar::tx4_preview_bar(const QString &date, const QString &loc, const QString &size, const QString &length, const QString &loc_style, const QString &meta, const bool &top, QWidget *parent) : QWidget(parent) {
	this->setAttribute(Qt::WA_StyledBackground); // <--- this attribute solves issue of background color not being drawn on custom widget, no need for reimplementing paintEvent, yet.

	QHBoxLayout *h_barLayout = new QHBoxLayout(this);
	Util::setLayoutZero(h_barLayout);
	h_barLayout->setContentsMargins(6,0,6,0);
	//h_barLayout->setSpacing(6);
	this->setFixedHeight(BAR_H);
	this->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Fixed);
	this->setStyleSheet(barStyleNormal);

	dateText = new tx4_label(date, 10, barTextStyle, QFont::Medium, Qt::AlignCenter, "Anonymous Pro");
	locText = new tx4_label(loc, 10, barTextStyle, QFont::Medium, Qt::AlignCenter, "Anonymous Pro");
	sizeText = new tx4_label(size, 10, barTextStyle, QFont::Medium, Qt::AlignCenter, "Anonymous Pro");
	lengthText = new tx4_label(length, 10, barTextStyle, QFont::Medium, Qt::AlignCenter, "Anonymous Pro");
	topText = new tx4_label(meta, 10, barTextStyle, QFont::Medium, Qt::AlignCenter, "Anonymous Pro");

	if (top) {
		h_barLayout->addStretch();
		h_barLayout->addWidget(new tx4_label("[", 10, braceStyle, QFont::Medium, Qt::AlignCenter, "Anonymous Pro"));
		h_barLayout->addWidget(topText);
		h_barLayout->addWidget(new tx4_label("]", 10, braceStyle, QFont::Medium, Qt::AlignCenter, "Anonymous Pro"));
		h_barLayout->addStretch();
	} else {
		h_barLayout->addStretch();
		//h_barLayout->addWidget(new tx4_label("[", 10, braceStyle, QFont::Medium, Qt::AlignCenter, "Anonymous Pro"));
		h_barLayout->addWidget(locText);
		h_barLayout->addStretch();
		h_barLayout->addWidget(new tx4_label("|", 10, braceStyle, QFont::Medium, Qt::AlignCenter, "Anonymous Pro"));
		//h_barLayout->addWidget(new tx4_label("]", 10, braceStyle, QFont::Medium, Qt::AlignCenter, "Anonymous Pro"));
		h_barLayout->addStretch();
		//h_barLayout->addWidget(new tx4_label("[", 10, braceStyle, QFont::Medium, Qt::AlignCenter, "Anonymous Pro"));
		h_barLayout->addWidget(dateText);
		h_barLayout->addStretch();
		h_barLayout->addWidget(new tx4_label("|", 10, braceStyle, QFont::Medium, Qt::AlignCenter, "Anonymous Pro"));
		//h_barLayout->addWidget(new tx4_label("]", 10, braceStyle, QFont::Medium, Qt::AlignCenter, "Anonymous Pro"));
		h_barLayout->addStretch();
		//h_barLayout->addWidget(new tx4_label("[", 10, braceStyle, QFont::Medium, Qt::AlignCenter, "Anonymous Pro"));
		h_barLayout->addWidget(sizeText);
		h_barLayout->addStretch();
		h_barLayout->addWidget(new tx4_label("|", 10, braceStyle, QFont::Medium, Qt::AlignCenter, "Anonymous Pro"));
		//h_barLayout->addWidget(new tx4_label("]", 10, braceStyle, QFont::Medium, Qt::AlignCenter, "Anonymous Pro"));
		h_barLayout->addStretch();
		//h_barLayout->addWidget(new tx4_label("[", 10, braceStyle, QFont::Medium, Qt::AlignCenter, "Anonymous Pro"));
		h_barLayout->addWidget(lengthText);
		//h_barLayout->addWidget(new tx4_label("]", 10, braceStyle, QFont::Medium, Qt::AlignCenter, "Anonymous Pro"));
		h_barLayout->addStretch();
	}

	this->setLayout(h_barLayout);
}

tx4_preview_bar::~tx4_preview_bar() {}

void tx4_preview_bar::setHoverStyle(bool top) {
	if (top) {
		this->setStyleSheet(barStyleHoverTop);
	} else {
		this->setStyleSheet(barStyleNormal);
	}
}
void tx4_preview_bar::setSelectedStyle(bool top) {
	if (top) {
		this->setStyleSheet(barStyleHover_SelectModeTop);
	} else {
		this->setStyleSheet(barStyleHover_SelectMode);
	}
}