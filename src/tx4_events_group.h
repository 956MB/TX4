#ifndef TX4_EVENTS_GROUP_H
#define TX4_EVENTS_GROUP_H

#include <QWidget>
#include "tx4_label.h"
#include "./util/tx4_util.h"
#include "tx4_events_section.h"
#include "tx4_events_group_title.h"
#include "./tx4_defines.h"

class tx4_events_group : public QWidget {
	Q_OBJECT

	public:
		explicit tx4_events_group(const QString &title, QWidget* parent = nullptr);
		virtual ~tx4_events_group();

		void appendSection(tx4_events_section* section);

	private:
		QWidget *w_sectionContainer;
		QVBoxLayout *v_containerLayout;
		tx4_events_group_title *w_groupTitle;
		//tx4_events_group_title *w_groupInfo;
		QList<tx4_events_section*> l_eventSections;
		
		bool b_groupActive;
		QString s_groupTitle;

		void initContents();

	signals:
		void eventSelect(tx4_event *);
		void eventDeselect(tx4_event *);
		//void eventSelectList(tx4_event *, tx4_event_preview *);
		//void eventDeselectList(tx4_event *, tx4_event_preview *);

	private slots:
		void on_toggleGroupActive();
		//void on_updateGroupInfo(int selectedClips, int totalClips, QString size, QString length);
		void on_eventSelect(tx4_event *eselect);
		void on_eventDeselect(tx4_event *eselect);
		//void on_eventSelectList(tx4_event *eselect, tx4_event_preview *epselect);
		//void on_eventDeselectList(tx4_event *eselect, tx4_event_preview *epselect);
};

#endif // TX4_EVENTS_GROUP_H