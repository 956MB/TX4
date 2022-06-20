#ifndef TX4_EVENTS_SECTION_H
#define TX4_EVENTS_SECTION_H

#include <QWidget>
#include <qdebug.h>
#include "tx4_label.h"
#include "./util/tx4_util.h"
#include "tx4_event.h"
#include "tx4_event_preview.h"
#include "tx4_list_item.h"
#include "tx4_nav_button.h"
#include "./toolbar/tx4_toolbar_button.h"
#include "./tx4_defines.h"

class tx4_events_section : public QWidget {
	Q_OBJECT

	public:
		explicit tx4_events_section(const GroupLayout &layout, QWidget* parent = nullptr);
		virtual ~tx4_events_section();

		bool b_eventsLoaded;
		GroupLayout gl_sectionLayout;
		QList<tx4_event*> l_events;
		QList<tx4_event*> l_selectedEvents;
		QList<tx4_list_item*> l_listItems;
		QList<tx4_event_preview*> l_previews;
		QList<tx4_event_preview*> l_selectedPreviews;
		int i_selectedCount;
		int i_totalEvents;
		qint64 i_selectedSize;
		qint64 i_selectedLength;
		qint64 i_totaslSizeNum;
		qint64 i_totaslLengthNum;
		QString s_totalSizeDisplay;
		QString s_totalLengthDisplay;
		//void toggleSelectMode(bool active);
		void toggleEventsLoaded(bool active);
		void initEmptyState(bool active);
		void populateEvents(QList<tx4_event*> events, int indexOffset);
		void populateGrid(qint64 &sizeCount, qint64 &timeCount, QLayout *addLayout, QList<tx4_event*> events, int indexOffset);
		void populateList(qint64 &sizeCount, qint64 &timeCount, QLayout *addLayout, QList<tx4_event*> events, int indexOffset);
		void resizeEventPreviews(int window_w);
		void manualInfoUpdate();

		// TODO: public select/deselect for all
		//void selectAll();
		//void deselectAll();

	//protected:
	//	virtual void wheelEvent(QWheelEvent* event);

	signals:
		void eventSelect(tx4_event *);
		void eventDeselect(tx4_event *);
		void infoUpdate(int, int, QString, QString);

	//protected:
	//	virtual void resizeEvent(QResizeEvent *event);

	private:
		tx4_label *l_emptyState;
		//QWidget *w_scrollContainer;
		//QWidget *w_sectionScroll;
		QWidget *w_sectionContents;
		QWidget *w_emptyState;
		//QScrollArea *scrollarea;

		int i_scrollValue;
		bool selectAllClicked;

		void initContents();
		void initPalette();
		//void scrollLeft();
		//void scrollRight();
		void setPreviewGrayscales(bool set);

	private slots:
		void on_updateSelect(int idx);
		void on_updateDeselect(int idx);

};

#endif // TX4_EVENTS_SECTION_H