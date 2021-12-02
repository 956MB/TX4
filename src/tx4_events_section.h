#ifndef TX4_RECENTS_H
#define TX4_RECENTS_H

#include <QWidget>
#include "tx4_label.h"
#include "tx4_util.h"
#include "tx4_event.h"
#include "tx4_event_preview.h"
#include "tx4_nav_button.h"
#include "tx4_toolbar_button.h"

#define SECTION_H 250
#define SCROLL_DIFF 250
#define CLICK_SCROLL_DIFF 250
//#define TITLE_BUTTONS_DIST 40

class tx4_events_section : public QWidget {
	Q_OBJECT

	public:
		explicit tx4_events_section(const QString &title, QWidget* parent = nullptr);
		~tx4_events_section();

		bool eventsLoaded;
		QList<tx4_event_preview*> previews;
		QList<tx4_event*> events;
		QList<tx4_event_preview*> selectedPreviews;
		QList<tx4_event*> selectedEvents;
		void toggleSelectMode(bool active);
		void toggleEventsLoaded(bool active);
		void initEmptyState(bool active);
		void populateEvents(QList<tx4_event*> events);
		void setNavButtonStates(bool style_left, bool style_right, bool enable_left, bool enable_right);
		void setSelectDeselectButtonState(bool state = false, bool visible = true);
		void setReturnButtonState(bool state = false, bool visible = true);

		// TODO: public select/deselect for all
		void selectAll();
		void deselectAll();

	protected:
		virtual void wheelEvent(QWheelEvent* event);

	signals:
		void eventSelect(tx4_event *, tx4_event_preview *);
		void eventDeselect(tx4_event *, tx4_event_preview *);

	private:
		tx4_label *l_sectionTitle;
		tx4_label *l_countSubitle;
		tx4_label *l_sizeSubitle;
		tx4_label *l_lengthSubitle;
		tx4_label *l_emptyState;
		QWidget *w_scrollContainer;
		QWidget *w_rightContainer;
		QWidget *w_sectionScroll;
		QWidget *w_emptyState;
		QScrollArea *scrollarea;
		tx4_nav_button *b_navButtonLeft;
		tx4_nav_button *b_navButtonRight;
		tx4_toolbar_button *b_returnButton;
		tx4_toolbar_button *b_selectDeselectAllButton;

		int i_scrollValue;
		bool selectModeActive;
		bool selectAllClicked;
		int i_selectedCount;
		int i_totalEvents;
		qint64 i_selectedSize;
		qint64 i_selectedLength;
		QString s_totalSize;
		QString s_totalLength;
		QString sectionTitle;

		QString titleBarStyle = "background-color: rgba(38, 38, 38, 255); border: none; outline: none;";
		QString titleLabelStyle = "background-color: none; color: white;";
		QString subLabelStyle = "background-color: none; color: rgba(255,255,255,150);";
		QString subLabelBraceStyle = "background-color: none; color: rgba(255,255,255,60);";
		QString subLabelStyleOff = "background-color: none; color: rgba(255,255,255,60);";
		QString locRed = "background-color: none; border: none; color: rgba(255,0,0,255);";
		QString locOrange = "background-color: none; border: none; color: rgba(255,132,0,255);";
		QString locYellow = "background-color: none; border: none; color: rgba(255,222,0,255);";
		QString locGreen = "background-color: none; border: none; color: rgba(0,255,0,255);";
		//QString sectionStyle = "background-color: none; border: none; outline: none;";
		QString sectionStyle = "background-color: rgba(255, 255, 255, 20); border: none; outline: none;";
		QString emptyStateStyle = "background-color: rgba(0, 0, 0, 150); border: none; outline: none;";
		QString buttonHolderStyle = "background-color: #141414; border: none; outline: none;";
		QString scrollAreaStyle = "background-color: black; border: none; outline: none;";
		QString navButtonStyle = "background-color: #222222; border: none; outline: none;";
		QString restyle = "background-color: rgba(255, 0, 0, 20); border: none; outline: none;";
		QString gestyle = "background-color: rgba(0, 255, 0, 20); border: none; outline: none;";

		void initContents();
		void initPalette();
		void scrollLeft();
		void scrollRight();
		void resetSubtitle();

		void goLeft(const int &amount);
		void goRight(const int &amount);

	private slots:
		void on_updateSelect(int idx);
		void on_updateDeselect(int idx);
		void on_navLeftClick();
		void on_navRightClick();
		void on_returnClick();
		void on_selectDeselectAll();
		void on_selectAll();
		void on_deselectAll();

};

#endif // TX4_RECENTS_H