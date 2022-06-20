
#include "tx4_info_bar.h"

tx4_info_bar::tx4_info_bar(const QString &type, const QString &reason, const QString &city, const QString &date, const QString &time, std::initializer_list<QString> tooltips, QWidget *parent)
	: QWidget(parent)
	, s_typeInfo(type)
	, s_reasonInfo(reason)
	, s_cityInfo(city)
	, s_dateInfo(date)
	, s_timeInfo(time)
	, l_infoList(QList<tx4_label*> ())
{
	l_infoKeys << "Type:"
			   << "Reason:"
			   << "City:"
			   << "Date:"
			   << "Time:";

	l_infoValues << s_typeInfo
			     << Util::reasonMap(s_reasonInfo)
			     << s_cityInfo
			     << s_dateInfo
			     << s_timeInfo;

	for (auto &t: tooltips) {
		l_infoTooltips.append(t);
	}
			  
	this->setAttribute(Qt::WA_StyledBackground); // <--- this attribute solves issue of background color not being drawn on custom widget, no need for reimplementing paintEvent, yet.
	this->setFixedHeight(INFO_BAR_H);
	this->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Fixed);
	this->setStyleSheet(S_INFO_BAR_BODY);

	initContents();
}

tx4_info_bar::~tx4_info_bar() {}

void tx4_info_bar::initContents() {
	QHBoxLayout *h_mainLayout = new QHBoxLayout(this);
	Util::setLayoutZero(h_mainLayout);
	h_mainLayout->setContentsMargins(OUTER_MARGIN*2,0,OUTER_MARGIN*2,0);

	QWidget *w_container = new QWidget;
	QHBoxLayout *h_containerLayout = new QHBoxLayout(w_container);
	Util::setLayoutZero(h_containerLayout);
	h_containerLayout->setSpacing(22);

	for (int i = 0; i < l_infoKeys.count(); i++) {
		QWidget *w_textContainer = new QWidget;
		w_textContainer->setStyleSheet(S_INFO_BAR_BODY);
		QHBoxLayout *h_textLayout = new QHBoxLayout(w_textContainer);
		Util::setLayoutZero(h_textLayout);
		h_textLayout->setSpacing(4);
		h_textLayout->setAlignment(Qt::AlignLeading);
		w_textContainer->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Expanding);

		tx4_label *w_infoKey = new tx4_label(l_infoKeys[i], 13, S_VALUE_LABEL_HOVERED, QFont::DemiBold, Qt::AlignLeading, Qt::AlignVCenter);
		tx4_label *w_infoValue = new tx4_label(l_infoValues[i], 13, S_INFO_BAR_TEXT_VALUE, QFont::DemiBold, Qt::AlignLeading, Qt::AlignVCenter, "Gotham", 0, l_infoTooltips[i]);

		l_infoList.append(w_infoValue);
		h_textLayout->addWidget(w_infoKey);
		h_textLayout->addWidget(w_infoValue);
		h_containerLayout->addWidget(w_textContainer);
	}

	h_mainLayout->addStretch();
	h_mainLayout->addWidget(w_container);
	h_mainLayout->addStretch();

	this->setLayout(h_mainLayout);
}

void tx4_info_bar::updateInfo(QString type, QString reason, QString city, QString date, QString time, std::initializer_list<QString> tooltips) {
	s_typeInfo = type;
	s_reasonInfo = Util::reasonMap(reason);
	s_cityInfo = city;
	s_dateInfo = date;
	s_timeInfo = time;
	l_infoList.at(0)->setLabelText(s_typeInfo);
	l_infoList.at(1)->setLabelText(s_reasonInfo);
	l_infoList.at(2)->setLabelText(s_cityInfo);
	l_infoList.at(3)->setLabelText(s_dateInfo);
	l_infoList.at(4)->setLabelText(s_timeInfo);
	l_infoTooltips.clear();
	for (auto &t: tooltips) {
		l_infoTooltips.append(t);
	}
}