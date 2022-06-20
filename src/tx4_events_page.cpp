
#include "tx4_events_page.h"

tx4_events_page::tx4_events_page(const int &pageIdx, const GroupLayout &useLayout, QWidget *parent)
	: QWidget(parent)
	, i_pageIndex(pageIdx)
	, l_eventGroups(QList<tx4_events_group*> ())
	, l_loadedSections(QList<tx4_events_section*> ())
	, l_groupList(QList<QPair<QString, QList<tx4_event*>>> ())
	, b_groupsLoaded(false)
	, e_pageSort(GroupSort::None)
	, b_sortAscending(true)
	, gl_pageLayout(useLayout)
{

	this->setAttribute(Qt::WA_StyledBackground); // <--- this attribute solves issue of background color not being drawn on custom widget, no need for reimplementing paintEvent, yet.
	//this->setFixedHeight(ACTIONS_H);
	this->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
	this->setStyleSheet(S_EVENTS_PAGE_BODY);

	initContents();
}

tx4_events_page::~tx4_events_page() {}

void tx4_events_page::initContents() {
	v_pageLayout = new QVBoxLayout(this);
	Util::setLayoutZero(v_pageLayout);
	v_pageLayout->setAlignment(Qt::AlignCenter);
	//v_pageLayout->setContentsMargins(0,0,0,OUTER_MARGIN);

	w_emptyState = new QWidget;
	QWidget *w_emptyStateInner = new QWidget;
	Util::setWidgetsSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding, {w_emptyState, w_emptyStateInner});

	w_emptyState->setStyleSheet(S_EVENTS_PAGE_EMPTY_STATE);
	QVBoxLayout *v_emptyStateLayout = new QVBoxLayout(w_emptyState);
	Util::setLayoutZero(v_emptyStateLayout);
	v_emptyStateLayout->setAlignment(Qt::AlignCenter);

	QHBoxLayout *h_emptyStateLayout = new QHBoxLayout(w_emptyStateInner);
	Util::setLayoutZero(h_emptyStateLayout);
	h_emptyStateLayout->setAlignment(Qt::AlignCenter);
	h_emptyStateLayout->setContentsMargins(20, 0, 20, 0);
	tx4_label *l_emptyState = new tx4_label("NO EVENTS LOADED", 13, S_VALUE_LABEL_HOVERED, QFont::Medium, Qt::AlignCenter);
	h_emptyStateLayout->addSpacerItem(new QSpacerItem(20, 0, QSizePolicy::Fixed, QSizePolicy::Expanding));
	h_emptyStateLayout->addStretch();
	h_emptyStateLayout->addWidget(l_emptyState);
	h_emptyStateLayout->addStretch();
	h_emptyStateLayout->addSpacerItem(new QSpacerItem(20, 0, QSizePolicy::Fixed, QSizePolicy::Expanding));
	v_emptyStateLayout->addStretch();
	v_emptyStateLayout->addWidget(w_emptyStateInner);
	v_emptyStateLayout->addStretch();

	w_emptyStateStackWidget = new QStackedWidget;
	w_emptyStateStackWidget->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Fixed);
	w_emptyStateStackWidget->setStyleSheet(S_EVENTS_PAGE_STACK);
	w_emptyStateStackWidget->addWidget(w_emptyState);
	w_emptyStateStackWidget->setCurrentIndex(0);

	w_pageActions = new tx4_page_actions();

	v_pageLayout->addWidget(w_pageActions);
	v_pageLayout->addWidget(w_emptyStateStackWidget);
	w_pageActions->setVisible(false);

	this->setLayout(v_pageLayout);
}

void tx4_events_page::populateEvents(QList<tx4_event*> events, GroupSort sortBy) {
	e_pageSort = sortBy;
	formGroups(events);
	populateContents(sortBy);
}

void tx4_events_page::populateContents(GroupSort sortBy) {
	auto *stackLayout = qobject_cast<QLayout*>(w_emptyStateStackWidget->layout());
	Util::clearLayout(stackLayout, 1);

	if (!l_groupList.isEmpty()) {
		QWidget *w_groupsVStack = new QWidget;
		QVBoxLayout *v_groupsLayout = new QVBoxLayout(w_groupsVStack);
		Util::setLayoutZero(v_groupsLayout);
		short indexOffset = 0;

		for (auto &g : l_groupList) {
			QString groupTitle = g.first;
			QString groupTitleEx = g.second[0]->s_yearS;
			tx4_events_group *w_newGroup = new tx4_events_group(groupTitle + groupTitleEx);
			QList<tx4_event*> groupList = g.second;

			if (sortBy != GroupSort::None) {
				sortGroup(groupList, sortBy);
			}

			if (gl_pageLayout == GroupLayout::Grid) {
				createGroupLayoutGrid(w_newGroup, groupList, indexOffset);
			} else if (gl_pageLayout == GroupLayout::List) {
				createGroupLayoutList(w_newGroup, groupList, indexOffset);
			}

			indexOffset += groupList.count();
			v_groupsLayout->addWidget(w_newGroup);
		}

		w_emptyStateStackWidget->addWidget(w_groupsVStack);
	}
}

void tx4_events_page::resortContents(GroupSort sortBy, bool ascending) {
	e_pageSort = sortBy;
	b_sortAscending = ascending;
	populateContents(e_pageSort);
}

void tx4_events_page::toggleEventsLoaded(bool active) {
	b_groupsLoaded = active;
	w_pageActions->setVisible(b_groupsLoaded);
	w_emptyState->setVisible(!b_groupsLoaded);
	w_emptyStateStackWidget->setCurrentIndex(1);
	v_pageLayout->setAlignment(Qt::AlignTop);
	updateSectionsInfo();
}

void tx4_events_page::updateSectionsInfo() {
	if (gl_pageLayout == GroupLayout::Grid) {
		if (l_loadedSections.count() >= 1) {
			for (int i = 0; i < l_loadedSections.count(); i++) {
				l_loadedSections.at(i)->manualInfoUpdate();
			}
		}
	}
}

void tx4_events_page::resizeSectionContents(int window_w) {
	if (b_groupsLoaded && l_loadedSections.count() >= 1) {
		for (int sec = 0; sec < l_loadedSections.count(); sec++) {
			if (gl_pageLayout == GroupLayout::Grid) {
				for (int prev = 0; prev < l_loadedSections.at(sec)->l_previews.count(); prev++) {
					l_loadedSections.at(sec)->l_previews.at(prev)->resizePreview(window_w);
				}
			} else if (gl_pageLayout == GroupLayout::List) {
				for (int item = 0; item < l_loadedSections.at(sec)->l_listItems.count(); item++) {
					l_loadedSections.at(sec)->l_listItems.at(item)->repaintItem();
				}
			}
		}
	}
}

void tx4_events_page::formGroups(QList<tx4_event*> events) {
	int currentYear = QDate::currentDate().year();
	QString currYearS = QString::number(currentYear);
	QMap<QString, QList<tx4_event*>> m_groupMap;

	for (int i = 0; i < events.count(); i++) {
		QString useTimestamp = events.at(i)->s_metaDataTimestampString;
		QString yearS(QStringRef(&useTimestamp, 0, 4).toString());
		QString dateS(QStringRef(&useTimestamp, 5, 2).toString());
		dateS.remove(QRegExp("^[0]*"));

		QString titlePre = months[dateS.toInt()-1];
		QString yearEx = (yearS == currYearS ? "" : (QString(" ") + yearS));
	
		if (m_groupMap.contains(titlePre)) {
			QList<tx4_event*> existList = m_groupMap.value(titlePre);
			existList.append(events.at(i));
			m_groupMap.insert(titlePre, existList);
		} else {
			events.at(i)->s_yearS = yearEx;
			QList<tx4_event*> newList({events.at(i)});
			m_groupMap.insert(titlePre, newList);
		}
	}

	// Move groups from map to list and sort by group title
	for (auto k : m_groupMap.keys()) {
		l_groupList.append(QPair<QString, QList<tx4_event*>>(k, m_groupMap[k]));
	}
	qSort(l_groupList.begin(), l_groupList.end(), QPairMonthsCompare());
}

void tx4_events_page::sortGroup(QList<tx4_event*> &events, GroupSort sortBy) {
	//if (sortBy == GroupSort::Date) qSort(events.begin(), events.end(), QListSizeCompare());
	//if (sortBy == GroupSort::City) qSort(events.begin(), events.end(), QListSizeCompare());
	if (sortBy == GroupSort::Size) qSort(events.begin(), events.end(), QListSizeCompare());
	if (sortBy == GroupSort::Length) qSort(events.begin(), events.end(), QListLengthCompare());
}

void tx4_events_page::createGroupLayoutGrid(tx4_events_group *addGroup, QList<tx4_event*> eventList, short indexOffset) {
	int sectionCount = 0;
	while (1) {
		tx4_events_section *w_sectionGrid = new tx4_events_section(gl_pageLayout);
		QList<tx4_event*> sectionEvents;
		for (int r = 0; r < 4; r++) {
			int selectIndex = sectionCount + r;
			if (selectIndex >= eventList.count()) { break; }
			sectionEvents.append(eventList.at(selectIndex));
		}
		w_sectionGrid->populateEvents(sectionEvents, indexOffset);
		w_sectionGrid->toggleEventsLoaded(true);
		addGroup->appendSection(w_sectionGrid);
		QObject::connect(addGroup, &tx4_events_group::eventSelect, this, &tx4_events_page::on_groupEventSelected);
		QObject::connect(addGroup, &tx4_events_group::eventDeselect, this, &tx4_events_page::on_groupEventDeselected);
		l_loadedSections.append(w_sectionGrid);
		sectionCount += 4;
		if (sectionCount >= eventList.count()) { break; }
	}
}

void tx4_events_page::createGroupLayoutList(tx4_events_group *addGroup, QList<tx4_event*> eventList, short indexOffset) {
	tx4_events_section *w_sectionList = new tx4_events_section(gl_pageLayout);
	w_sectionList->populateEvents(eventList, indexOffset);
	w_sectionList->toggleEventsLoaded(true);
	addGroup->appendSection(w_sectionList);
	QObject::connect(addGroup, &tx4_events_group::eventSelect, this, &tx4_events_page::on_groupEventSelected);
	QObject::connect(addGroup, &tx4_events_group::eventDeselect, this, &tx4_events_page::on_groupEventDeselected);
	l_loadedSections.append(w_sectionList);
}

void tx4_events_page::on_groupEventSelected(tx4_event *eselect) {
	emit eventSelect(eselect);
}
void tx4_events_page::on_groupEventDeselected(tx4_event *eselect) {
	emit eventDeselect(eselect);
}