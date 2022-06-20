#ifndef TX4_EVENTS_PAGE_H
#define TX4_EVENTS_PAGE_H

#include <QWidget>
#include <QMap>
#include "tx4_label.h"
#include "./util/tx4_util.h"
#include "tx4_events_group.h"
#include "tx4_page_actions.h"
#include "./tx4_defines.h"

struct Group {
   QString title;
   QList<tx4_event*> events;
};

struct QListLengthCompare {
    template<typename T>
    bool operator()(const T &a, const T & b) const {
        return a->i_TotalClipLength < b->i_TotalClipLength;
    }
};
struct QListSizeCompare {
    template<typename T>
    bool operator()(const T &a, const T & b) const {
        return a->i_Size < b->i_Size;
    }
};

class tx4_events_page : public QWidget {
	Q_OBJECT

	public:
		explicit tx4_events_page(const int &pageIdx, const GroupLayout &useLayout = GroupLayout::List, QWidget* parent = nullptr);
		virtual ~tx4_events_page();

		int i_pageIndex;
		bool b_groupsLoaded;
		GroupLayout gl_pageLayout;
		//void appendSection(tx4_events_section* section);
		void populateEvents(QList<tx4_event*> events, GroupSort sortBy);
		void toggleEventsLoaded(bool active);
		void resizeSectionContents(int window_w);

	private:
		QVBoxLayout *v_pageLayout;
		QStackedWidget *w_emptyStateStackWidget;
		//QMap<QString, QList<tx4_event*>> m_groupMap;
		QList<QPair<QString, QList<tx4_event*>>> l_groupList;
		QList<tx4_events_group*> l_eventGroups;
		QList<tx4_events_section*> l_loadedSections;
		QWidget *w_emptyState;
		tx4_page_actions *w_pageActions;
		GroupSort e_pageSort;
		bool b_sortAscending;
		const QStringList months = {"January", "February", "March", "April", "May", "June", "July", "August", "September", "October", "November", "December"};

		void initContents();
		void updateSectionsInfo();
		void populateContents(GroupSort sortBy);
		void resortContents(GroupSort sortBy, bool ascending);
		void formGroups(QList<tx4_event*> events);
		void sortGroup(QList<tx4_event*> &events, GroupSort sortBy);
		void createGroupLayoutGrid(tx4_events_group *addGroup, QList<tx4_event*> eventList, short indexOffset);
		void createGroupLayoutList(tx4_events_group *addGroup, QList<tx4_event*> eventList, short indexOffset);

	signals:
		void eventSelect(tx4_event *);
		void eventDeselect(tx4_event *);

	private slots:
		void on_groupEventSelected(tx4_event *eselect);
		void on_groupEventDeselected(tx4_event *eselect);
	//	void on_updateGroupInfo(bool selectMode, int selectedClips, int totalClips, QString size, QString length);
};

#endif // TX4_EVENTS_PAGE_H