#ifndef TX4_VIEWS_LAYOUT
#define TX4_VIEWS_LAYOUT

#include <QWidget>
#include "../tx4_label.h"
#include "../util/tx4_util.h"
#include "../toolbar/tx4_toolbar_button.h"
#include "tx4_view.h"
#include "../tx4_defines.h"

class tx4_views_layout_L3;
class tx4_views_layout_L4;
class tx4_views_layout_L13V;

class tx4_views_layout : public QWidget {
	Q_OBJECT

	friend class tx4_views_layout_L3;
	friend class tx4_views_layout_L4;
	friend class tx4_views_layout_L13V;

	public:
		explicit tx4_views_layout(tx4_event *l_event, int selectedView, const ViewsLayout &layout, QWidget* parent = nullptr);
		virtual ~tx4_views_layout();

		virtual void resizeLayoutViews() {};

		ViewsLayout e_layout;
		tx4_event *loadedEvent;

	signals:
		void selectedViewChange(int);

	private:
		QStackedWidget *w_viewsContainer;
		QList<tx4_view*> l_allViews;
		tx4_view *w_viewFront;
		tx4_view *w_viewBack;
		tx4_view *w_viewRight;
		tx4_view *w_viewLeft;
		int n_selectedView;

		void initContents();
};

class tx4_views_layout_L3 : public tx4_views_layout {
	Q_OBJECT

	public:
		tx4_views_layout_L3(tx4_event *l_event, int selectedView, const ViewsLayout &layout = ViewsLayout::L3);
		virtual ~tx4_views_layout_L3();

	private:
		QWidget *w_masterViewContainer;

		void initLayout();
		void swapSelectedView(tx4_view *viewClicked);
};

class tx4_views_layout_L4 : public tx4_views_layout {
	Q_OBJECT

	public:
		tx4_views_layout_L4(tx4_event *l_event, int selectedView, const ViewsLayout &layout = ViewsLayout::L4);
		virtual ~tx4_views_layout_L4();

	private:
		void initLayout();
};

class tx4_views_layout_L13V : public tx4_views_layout {
	Q_OBJECT

	public:
		tx4_views_layout_L13V(tx4_event *l_event, int selectedView, const ViewsLayout &layout = ViewsLayout::L13V);
		virtual ~tx4_views_layout_L13V();

		void resizeLayoutViews() override;

	private:
		tx4_view *l_upperView;
		QList<tx4_view*> l_lowerViews;
		QWidget *w_topContainer;
		QWidget *w_bottomContainer;

		void initLayout();
		void swapUpperView(tx4_view *viewClicked);
};

#endif // TX4_VIEWS_LAYOUT