#ifndef TX4_TOOLBAR_H
#define TX4_TOOLBAR_H

#include <QWidget>
#include "tx4_label.h"
#include "tx4_util.h"
#include "tx4_toolbar_button.h"
#include "tx4_event_preview.h"

#define TOOLBAR_H 50
#define SCROLL_DIFF 35

class tx4_toolbar : public QWidget {
	Q_OBJECT

	public:
		explicit tx4_toolbar(const bool &loaded, const bool &auto_load, QWidget* parent = nullptr);
		~tx4_toolbar();

		void updateEventQueue(QList<tx4_event_preview*> eventQueue);
		void toggleEventsLoaded(bool loaded);

	signals:
		void eventsOpen();
		void eventsLoad();

	protected:
		virtual void wheelEvent(QWheelEvent* event);

	private:
		tx4_toolbar_button *b_openButton;
		tx4_toolbar_button *b_loadEventsButton;
		tx4_label *l_selectedEventsTitle;
		tx4_label *l_queueTitle;
		tx4_key_value_label *l_eventsLoadedTitle;
		//tx4_label *l_eventsLoadedValue;
		tx4_key_value_label *l_autoLoadTitle;
		//tx4_label *l_autoLoadValue;
		QScrollArea *queueScrollarea;
		int scrollValue;
		int eventQueueCount;
		int eventQueueClipsCount;
		bool eventsLoaded;
		bool autoLoad;

		QString toolbarBodyStyle = "background-color: rgba(255,255,255,15); border: none; outline: none;";
		QString loadedTrueLabelStyle = "background-color: none; color: rgba(0,255,0,255);";
		QString loadedFalseLabelStyle = "background-color: none; color: rgba(255,0,0,255);";
		QString titleLabelStyle = "background-color: none; color: rgba(255,255,255,255);";
		QString queueLabelStyle = "background-color: black; color: rgba(255,255,255,140);";
		QString queueLabelStyleDisabled = "background-color: rgba(0,0,0,150); color: rgba(255,255,255,0);";
		QString titleLabelStyleZero = "background-color: none; color: rgba(255,255,255,140);";
		QString titleLabelStyleZeroDisabled = "background-color: none; color: rgba(255,255,255,60);";
		QString blankStyle = "background-color: none; border: none; outline: none;";
		QString braceStyle = "background-color: none; color: rgba(255,255,255,78);";
		QString scrollAreaStyle = "background-color: black; border: none; outline: none;";

		void initContents();
		void scrollLeft();
		void scrollRight();

};

#endif // TX4_TOOLBAR_H