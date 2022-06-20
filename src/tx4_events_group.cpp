
#include "tx4_events_group.h"

tx4_events_group::tx4_events_group(const QString &title, QWidget *parent)
	: QWidget(parent)
	, l_eventSections(QList<tx4_events_section*> ())
	, s_groupTitle(title)
{

	b_groupActive = true;

	this->setAttribute(Qt::WA_StyledBackground); // <--- this attribute solves issue of background color not being drawn on custom widget, no need for reimplementing paintEvent, yet.
	//this->setFixedHeight(ACTIONS_H);
	this->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Fixed);
	this->setStyleSheet(S_GROUP_BODY_NORMAL);

	initContents();
}

tx4_events_group::~tx4_events_group() {}

void tx4_events_group::initContents() {
	QVBoxLayout *v_groupLayout = new QVBoxLayout(this);
	Util::setLayoutZero(v_groupLayout);
	//v_groupLayout->setContentsMargins(0,0,0,OUTER_MARGIN);

	QWidget *w_titleContainer = new QWidget;
	QVBoxLayout *v_titleLayout = new QVBoxLayout(w_titleContainer);
	Util::setLayoutZero(v_titleLayout);
	v_titleLayout->setContentsMargins(OUTER_MARGIN, 0, OUTER_MARGIN, 0);

	w_groupTitle = new tx4_events_group_title(s_groupTitle, S_VALUE_LABEL_PRESSED);
	//w_groupInfo = new tx4_events_group_title("0/0  0.00GB  00:00:00", S_GROUP_TITLE_INFO_NORMAL, false);
	//w_groupInfo->layout()->setContentsMargins(0,1,0,1);
	QObject::connect(w_groupTitle, &tx4_events_group_title::clicked, this, &tx4_events_group::on_toggleGroupActive);

	v_titleLayout->addWidget(w_groupTitle);
	//v_titleLayout->addWidget(w_groupInfo);

	w_sectionContainer = new QWidget;
	v_containerLayout = new QVBoxLayout(w_sectionContainer);
	Util::setLayoutZero(v_containerLayout);
	//v_containerLayout->setContentsMargins(0,0,0,10);

	v_groupLayout->addWidget(w_titleContainer);
	v_groupLayout->addWidget(w_sectionContainer);

	this->setLayout(v_groupLayout);
}

void tx4_events_group::appendSection(tx4_events_section *section) {
	//QObject::connect(section, &tx4_events_section::infoUpdate, this, &tx4_events_group::on_updateGroupInfo);
	QObject::connect(section, &tx4_events_section::eventSelect, this, &tx4_events_group::on_eventSelect);
	QObject::connect(section, &tx4_events_section::eventDeselect, this, &tx4_events_group::on_eventDeselect);
	v_containerLayout->addWidget(section);
	l_eventSections.append(section);
}

// SLOTS:

void tx4_events_group::on_toggleGroupActive() {
	b_groupActive = !b_groupActive;
	//w_groupInfo->setVisible(b_groupActive);
	w_sectionContainer->setVisible(b_groupActive);
}
//void tx4_events_group::on_updateGroupInfo(int selectedClips, int totalClips, QString size, QString length) {
//	//QString formInfo = QString::number(selectedClips) + QString("/") + QString::number(totalClips) + QString("  ") + size + QString("  ") + length;
//
//	//w_groupInfo->updateTitleString(false, formInfo);
//}
void tx4_events_group::on_eventSelect(tx4_event *eselect) {
	emit eventSelect(eselect);
}
void tx4_events_group::on_eventDeselect(tx4_event *eselect) {
	emit eventDeselect(eselect);
}