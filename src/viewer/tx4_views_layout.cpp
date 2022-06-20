
#include "tx4_views_layout.h"

tx4_views_layout::tx4_views_layout(tx4_event *l_event, int selectedView, const ViewsLayout &layout, QWidget *parent)
	: QWidget(parent)
	, loadedEvent(l_event)
	, e_layout(layout)
	, n_selectedView(selectedView)
	, l_allViews(QList<tx4_view*> ())
{

	this->setAttribute(Qt::WA_StyledBackground); // <--- this attribute solves issue of background color not being drawn on custom widget, no need for reimplementing paintEvent, yet.
	this->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
	this->setStyleSheet(S_LAYOUT_BODY);

	initContents();
}
tx4_views_layout::~tx4_views_layout() {}

void tx4_views_layout::initContents() {
	QHBoxLayout *h_mainLayout = new QHBoxLayout(this);
	Util::setLayoutZero(h_mainLayout);
	h_mainLayout->setSpacing(0);

	w_viewsContainer = new QStackedWidget;
	w_viewsContainer->setStyleSheet(S_STACK_BODY);

	h_mainLayout->addWidget(w_viewsContainer);
	this->setLayout(h_mainLayout);
}


// LAYOUT L3
tx4_views_layout_L3::tx4_views_layout_L3(tx4_event *l_event, int selectedView, const ViewsLayout &layout)
    : tx4_views_layout(l_event, selectedView, layout)
{
	initLayout();
}
tx4_views_layout_L3::~tx4_views_layout_L3() {}

void tx4_views_layout_L3::initLayout() {
	QWidget *w_masterViewContainer = new QWidget;
	w_masterViewContainer->setStyleSheet(S_VIEW_SELECTED);
	QBoxLayout *v_masterContainerLayout = new QBoxLayout(QBoxLayout::TopToBottom, w_masterViewContainer);
	Util::setLayoutZero(v_masterContainerLayout);
	v_masterContainerLayout->setContentsMargins(OUTER_MARGIN,OUTER_MARGIN,OUTER_MARGIN,OUTER_MARGIN);
	w_viewsContainer->setContentsMargins(OUTER_MARGIN/2,OUTER_MARGIN/2,OUTER_MARGIN/2,OUTER_MARGIN/2);

	// top
	QWidget *w_topContainer = new QWidget;
	QBoxLayout *h_topLayout = new QBoxLayout(QBoxLayout::LeftToRight, w_topContainer);
	Util::setLayoutZero(h_topLayout);
	w_viewFront = new tx4_view(loadedEvent->l_frontClips, "Front", 0, (0 == n_selectedView), true, false);
	w_viewBack = new tx4_view(loadedEvent->l_backClips, "Rear", 1, (1 == n_selectedView), true, false);
	Util::setWidgetsSizePolicy(QSizePolicy::Expanding, QSizePolicy::Fixed, {w_topContainer, w_viewFront, w_viewBack});
	w_viewFront->setFixedSize(VIEW_W, VIEW_H);
	w_viewBack->setFixedSize(VIEW_W, VIEW_H);
	h_topLayout->insertWidget(0, w_viewFront);
	h_topLayout->insertStretch(1);
	h_topLayout->insertWidget(2, w_viewBack);

	// bottom
	QWidget *w_bottomContainer = new QWidget;
	QBoxLayout *h_bottomLayout = new QBoxLayout(QBoxLayout::LeftToRight, w_bottomContainer);
	Util::setLayoutZero(h_bottomLayout);
	w_viewLeft = new tx4_view(loadedEvent->l_leftClips, "Left", 2, (2 == n_selectedView), true, false);
	w_viewRight = new tx4_view(loadedEvent->l_rightClips, "Right", 3, (3 == n_selectedView), true, false);
	Util::setWidgetsSizePolicy(QSizePolicy::Expanding, QSizePolicy::Fixed, {w_bottomContainer, w_viewLeft, w_viewRight});
	w_viewLeft->setFixedSize(VIEW_W, VIEW_H);
	w_viewRight->setFixedSize(VIEW_W, VIEW_H);
	h_bottomLayout->insertWidget(0, w_viewLeft);
	h_bottomLayout->insertStretch(1);
	h_bottomLayout->insertWidget(2, w_viewRight);

	Util::setWidgetsStyleSheet(S_BLANK, {w_topContainer, w_bottomContainer});

	QObject::connect(w_viewFront, &tx4_view::selected, this, [=]{ swapSelectedView(w_viewFront); });
	QObject::connect(w_viewBack, &tx4_view::selected, this, [=]{ swapSelectedView(w_viewBack); });
	QObject::connect(w_viewLeft, &tx4_view::selected, this, [=]{ swapSelectedView(w_viewLeft); });
	QObject::connect(w_viewRight, &tx4_view::selected, this, [=]{ swapSelectedView(w_viewRight); });

	v_masterContainerLayout->insertWidget(0, w_topContainer);
	v_masterContainerLayout->insertStretch(1);
	v_masterContainerLayout->insertWidget(2, w_bottomContainer);

	w_viewsContainer->addWidget(w_masterViewContainer);
	w_viewsContainer->setCurrentIndex(0);
	
	l_allViews.append(w_viewFront);
	l_allViews.append(w_viewBack);
	l_allViews.append(w_viewLeft);
	l_allViews.append(w_viewRight);
}

// TODO: not resizing views for L3 layout currently

//void tx4_views_layout_L3::resizeLayoutViews() {
//	
//	//int containerWidth = w_viewsContainer->width();
//	//int width = containerWidth/VIEW_L3_DIVIDE;
//	//int height = width * VIEW_RATIO;
//	//qDebug() << width << " " << height;
//	//for (auto &view : l_allViews) {
//	//	view->setFixedSize(width, height);
//	//}
//}

void tx4_views_layout_L3::swapSelectedView(tx4_view *viewClicked) {
	for (auto &view : l_allViews) {
		view->setViewState(view == viewClicked ? true : false);
		if (view == viewClicked) {
			emit selectedViewChange(viewClicked->i_viewIndex);
		}
	}
}


// LAYOUT L4
tx4_views_layout_L4::tx4_views_layout_L4(tx4_event *l_event, int selectedView, const ViewsLayout &layout)
    : tx4_views_layout(l_event, selectedView, layout)
{
	initLayout();
}
tx4_views_layout_L4::~tx4_views_layout_L4() {}

void tx4_views_layout_L4::initLayout() {
	QWidget *w_layoutContainer = new QWidget;
	QBoxLayout *v_containerLayout = new QBoxLayout(QBoxLayout::TopToBottom, w_layoutContainer);
	Util::setLayoutZero(v_containerLayout);
	v_containerLayout->setContentsMargins(OUTER_MARGIN/2,OUTER_MARGIN/2,OUTER_MARGIN/2,OUTER_MARGIN/2);
	v_containerLayout->setSpacing(OUTER_MARGIN/2);

	// top
	QWidget *w_topContainer = new QWidget;
	QBoxLayout *h_topLayout = new QBoxLayout(QBoxLayout::LeftToRight, w_topContainer);
	Util::setLayoutZero(h_topLayout);
	h_topLayout->setSpacing(OUTER_MARGIN/2);
	w_viewFront = new tx4_view(loadedEvent->l_frontClips, "Front", 0, false, false, false);
	w_viewBack = new tx4_view(loadedEvent->l_backClips, "Rear", 1, false, false, false);
	Util::setWidgetsSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding, {w_topContainer, w_viewFront, w_viewBack});
	h_topLayout->insertWidget(0, w_viewFront);
	h_topLayout->insertWidget(1, w_viewBack);

	// bottom
	QWidget *w_bottomContainer = new QWidget;
	QBoxLayout *h_bottomLayout = new QBoxLayout(QBoxLayout::LeftToRight, w_bottomContainer);
	Util::setLayoutZero(h_bottomLayout);
	w_viewLeft = new tx4_view(loadedEvent->l_leftClips, "Left", 2, false, false, false);
	w_viewRight = new tx4_view(loadedEvent->l_rightClips, "Right", 3, false, false, false);
	Util::setWidgetsSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding, {w_bottomContainer, w_viewLeft, w_viewRight});
	h_bottomLayout->insertWidget(0, w_viewLeft);
	h_bottomLayout->insertWidget(1, w_viewRight);
	h_bottomLayout->setSpacing(OUTER_MARGIN/2);

	v_containerLayout->insertWidget(0, w_topContainer);
	v_containerLayout->insertWidget(1, w_bottomContainer);

	w_viewsContainer->addWidget(w_layoutContainer);
	w_viewsContainer->setCurrentIndex(0);

	l_allViews.append(w_viewFront);
	l_allViews.append(w_viewBack);
	l_allViews.append(w_viewLeft);
	l_allViews.append(w_viewRight);
}


// LAYOUT L13V
tx4_views_layout_L13V::tx4_views_layout_L13V(tx4_event *l_event, int selectedView, const ViewsLayout &layout)
    : tx4_views_layout(l_event, selectedView, layout)
	, l_lowerViews(QList<tx4_view*> ())
{
	initLayout();
}
tx4_views_layout_L13V::~tx4_views_layout_L13V() {}

void tx4_views_layout_L13V::initLayout() {
	QWidget *w_layoutContainer = new QWidget;
	QBoxLayout *v_containerLayout = new QBoxLayout(QBoxLayout::TopToBottom, w_layoutContainer);
	Util::setLayoutZero(v_containerLayout);
	v_containerLayout->setContentsMargins(OUTER_MARGIN/2,OUTER_MARGIN/2,OUTER_MARGIN/2,OUTER_MARGIN/2);
	v_containerLayout->setSpacing(OUTER_MARGIN/2);

	// top
	w_topContainer = new QWidget;
	QBoxLayout *h_topLayout = new QBoxLayout(QBoxLayout::LeftToRight, w_topContainer);
	Util::setLayoutZero(h_topLayout);
	w_viewBack = new tx4_view(loadedEvent->l_backClips, "Rear", 2, false, false, true);
	Util::setWidgetsSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding, {w_topContainer, w_viewBack});
	h_topLayout->insertWidget(0, w_viewBack);

	// bottom
	w_bottomContainer = new QWidget;
	QBoxLayout *h_bottomLayout = new QBoxLayout(QBoxLayout::LeftToRight, w_bottomContainer);
	Util::setLayoutZero(h_bottomLayout);
	w_viewLeft = new tx4_view(loadedEvent->l_leftClips, "Left", 1, false, false, true);
	w_viewFront = new tx4_view(loadedEvent->l_frontClips, "Front", 0, false, false, true);
	w_viewRight = new tx4_view(loadedEvent->l_rightClips, "Right", 3, false, false, true);
	Util::setWidgetsSizePolicy(QSizePolicy::Expanding, QSizePolicy::Fixed, {w_bottomContainer, w_viewLeft, w_viewFront, w_viewRight});
	h_bottomLayout->insertWidget(0, w_viewLeft);
	h_bottomLayout->insertWidget(1, w_viewFront);
	h_bottomLayout->insertWidget(2, w_viewRight);
	h_bottomLayout->setSpacing(OUTER_MARGIN/2);

	// TODO: For now not using the click to swap for layout L13V
	QObject::connect(w_viewFront, &tx4_view::clicked, this, [=]{ swapUpperView(w_viewFront); });
	QObject::connect(w_viewBack, &tx4_view::clicked, this, [=]{ swapUpperView(w_viewBack); });
	QObject::connect(w_viewLeft, &tx4_view::clicked, this, [=]{ swapUpperView(w_viewLeft); });
	QObject::connect(w_viewRight, &tx4_view::clicked, this, [=]{ swapUpperView(w_viewRight); });

	v_containerLayout->insertWidget(0, w_topContainer);
	v_containerLayout->insertWidget(1, w_bottomContainer);
	w_viewsContainer->addWidget(w_layoutContainer);
	w_viewsContainer->setCurrentIndex(0);

	l_allViews.append(w_viewFront);
	l_allViews.append(w_viewBack);
	l_allViews.append(w_viewLeft);
	l_allViews.append(w_viewRight);
	l_upperView = w_viewBack;
	l_lowerViews.append(w_viewLeft);
	l_lowerViews.append(w_viewFront);
	l_lowerViews.append(w_viewRight);
}

void tx4_views_layout_L13V::resizeLayoutViews() {
	int upperViewHeight = l_upperView->height();
	for (auto &view: l_lowerViews) {
		Util::setWidgetFixedHeight(view, upperViewHeight/2);
	}
}

void tx4_views_layout_L13V::swapUpperView(tx4_view *viewClicked) {
	if (l_lowerViews.contains(viewClicked)) {
		auto *h_topContainerLayout = qobject_cast<QBoxLayout*>(w_topContainer->layout());
		auto *h_bottomContainerLayout = qobject_cast<QBoxLayout*>(w_bottomContainer->layout());

		tx4_view *upperView = qobject_cast<tx4_view*>(h_topContainerLayout->takeAt(0)->widget());
		int lowerViewIdx = w_bottomContainer->layout()->indexOf(viewClicked);

		h_bottomContainerLayout->removeWidget(viewClicked);
		h_bottomContainerLayout->insertWidget(lowerViewIdx, upperView);
		h_topContainerLayout->insertWidget(0, viewClicked);

		l_lowerViews.removeOne(viewClicked);
		l_lowerViews.append(upperView);

		resizeLayoutViews();
		l_upperView = viewClicked;
		Util::resetWidgetExpanding(l_upperView);
	}
}