
#include "tx4_meta_info.h"

tx4_meta_info::tx4_meta_info(const QString &timestamp, const QString &city, const QString &lat, const QString &lon, const QString &reason, const QString &camera, QWidget *parent) : QWidget(parent) {
	s_timestampB = QString("\"") + timestamp + QString("\"");
	s_cityB = QString("\"") + city + QString("\"");
	s_est_latB = QString("\"") + lat + QString("\"");
	s_est_lonB = QString("\"") + lon + QString("\"");
	s_reasonB = QString("\"") + reason + QString("\"");
	s_cameraB = QString("\"") + camera + QString("\"");

	this->setAttribute(Qt::WA_StyledBackground); // <--- this attribute solves issue of background color not being drawn on custom widget, no need for reimplementing paintEvent, yet.
	//this->setMinimumHeight(PREVIEW_H);
	this->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
	this->setStyleSheet(blankStyle);

	init();
}

tx4_meta_info::~tx4_meta_info() {}

void tx4_meta_info::init() {
	QVBoxLayout *v_bothLayout = new QVBoxLayout(this);
	Util::setLayoutZero(v_bothLayout);
	metaInfoBar = new tx4_preview_bar("", "", "", "", "", "/event.json", true);

	QStringList pre{"\"timestamp\"", "\"city\"", "\"est_lat\"", "\"est_lon\"", "\"reason\"", "\"camera\""};
	QStringList pos{s_timestampB, s_cityB, s_est_latB, s_est_lonB, s_reasonB, s_cameraB};

	QWidget *bracket1 = new QWidget;
	QHBoxLayout *h_bracket1Layout = new QHBoxLayout(bracket1);
	Util::setLayoutZeroMargins(h_bracket1Layout, 7,0,7,0);
	bracket1->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Fixed);
	h_bracket1Layout->addWidget(new tx4_label("{", 8, whiteStyle, QFont::Medium, Qt::AlignLeft, "Anonymous Pro"));
	h_bracket1Layout->addStretch();

	QWidget *bracket2 = new QWidget;
	QHBoxLayout *h_bracket2Layout = new QHBoxLayout(bracket2);
	Util::setLayoutZeroMargins(h_bracket2Layout, 7,0,7,0);
	bracket2->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Fixed);
	h_bracket2Layout->addWidget(new tx4_label("}", 8, whiteStyle, QFont::Medium, Qt::AlignLeft, "Anonymous Pro"));
	h_bracket2Layout->addStretch();

	v_bothLayout->addWidget(metaInfoBar);
	v_bothLayout->addStretch();
	v_bothLayout->addWidget(bracket1);
	//v_bothLayout->addSpacerItem(new QSpacerItem(0, 3, QSizePolicy::Expanding, QSizePolicy::Fixed));

	for (int i = 0; i < pos.count(); i++) {
		QWidget *_line = new QWidget;
		QHBoxLayout *h_lineLayout = new QHBoxLayout(_line);
		Util::setLayoutZeroMargins(h_lineLayout, 7,0,7,0);
		_line->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Fixed);
		h_lineLayout->addSpacerItem(new QSpacerItem(12, 0, QSizePolicy::Fixed, QSizePolicy::Expanding));
		addWidgetSep(h_lineLayout, new tx4_label(pre[i], 8, blueStyle, QFont::Medium, Qt::AlignLeft, "Anonymous Pro"), ":");
		addWidgetSep(h_lineLayout, new tx4_label(pos[i], 8, orangeStyle, QFont::Medium, Qt::AlignLeft, "Anonymous Pro"), ",");
		h_lineLayout->addStretch();
		v_bothLayout->addWidget(_line);
	}

	//v_bothLayout->addSpacerItem(new QSpacerItem(0, 3, QSizePolicy::Expanding, QSizePolicy::Fixed));
	v_bothLayout->addWidget(bracket2);
	v_bothLayout->addStretch();
}

void tx4_meta_info::addWidgetSep(QHBoxLayout *layout, tx4_label *label, QString sep) {
	label->setTextInteractionFlags(Qt::TextSelectableByMouse);
	layout->addWidget(label);
	layout->addWidget(new tx4_label(sep, 8, whiteStyle, QFont::Medium, Qt::AlignLeft, "Anonymous Pro"));
}