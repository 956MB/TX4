#ifndef TX4_VIEWER_H
#define TX4_VIEWER_H

#include <QWidget>
#include "../tx4_label.h"
#include "../util/tx4_util.h"
#include "../toolbar/tx4_toolbar_button.h"
#include "../tx4_event_preview.h"
#include "../tx4_event.h"
#include "tx4_view.h"
#include "tx4_control_bar.h"
#include "tx4_info_bar.h"
#include "tx4_views_layout.h"
#include "../tx4_defines.h"
#include "../util/tx4_shortcuts.h"

class tx4_viewer : public QWidget {
	Q_OBJECT

	public:
		explicit tx4_viewer(QList<tx4_event*> events, QWidget* parent = nullptr);
		virtual ~tx4_viewer();

		void resizeInnerViews();

		int n_currentEventIndex;
		QList<tx4_event*> l_loadedEvents;
		tx4_event *o_currentEvent;
		ViewsLayout e_selectedLayout;
		int n_currentLayoutIndex;
		int n_currentSelectedView;

	signals:
		void manualResize();

	private:
		tx4_shortcuts *o_shortcutManager;
		tx4_info_bar *w_infoBar;
		QWidget *w_innerViewsContainer;
		tx4_views_layout *w_viewsLayout;
		tx4_control_bar *w_controlBar;
		tx4_control_bar_button *b_prevButton;
		tx4_control_bar_button *b_nextButton;

		const QList<QPair<ViewsLayout, QString>> layouts = {{ViewsLayout::L3, ICONS_LAYOUT_L3}, {ViewsLayout::L4, ICONS_LAYOUT_L4}, {ViewsLayout::L13V, ICONS_LAYOUT_L13V}};

		void initContents();
		void initShortcuts();
		void initInfoBar();
		void initViews();
		void initViewsLayout();
		void initControlBar();

		void goNextEvent(int incr);
		void setButtonStates(ButtonState prevState, ButtonState nextState);

	private slots:
		void on_cycleLoadoutSignal();
		void on_selectedViewChangeSignal(int selectedIndex);
};

#endif // TX4_VIEWER_H