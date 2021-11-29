
#include "tx4_viewer.h"

tx4_viewer::tx4_viewer(QWidget *parent)
	: QWidget(parent) {

	this->setAttribute(Qt::WA_StyledBackground); // <--- this attribute solves issue of background color not being drawn on custom widget, no need for reimplementing paintEvent, yet.
	//this->setFixedHeight(TOOLBAR_H);
	this->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
	this->setStyleSheet(viewerScreenStyle);

	initContents();
}

tx4_viewer::~tx4_viewer() {}

void tx4_viewer::initContents() {
	QVBoxLayout *v_contentsLayout = new QVBoxLayout(this);
	Util::setLayoutZero(v_contentsLayout);

	initViews();
	initControlBar();

	v_contentsLayout->addSpacerItem(new QSpacerItem(0, 30, QSizePolicy::Expanding, QSizePolicy::Fixed));
	v_contentsLayout->addWidget(w_viewsContainer);
	v_contentsLayout->addSpacerItem(new QSpacerItem(0, 20, QSizePolicy::Expanding, QSizePolicy::Fixed));
	v_contentsLayout->addWidget(w_controlBar);
	v_contentsLayout->addSpacerItem(new QSpacerItem(0, 30, QSizePolicy::Expanding, QSizePolicy::Fixed));

	this->setLayout(v_contentsLayout);
}

void tx4_viewer::initViews() {
	w_viewsContainer = new QWidget;
	w_viewsContainer->setStyleSheet(outerContainerStyle);
	//w_viewsContainer->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
	QVBoxLayout *v_viewsParentLayout = new QVBoxLayout(w_viewsContainer);
	Util::setLayoutZero(v_viewsParentLayout);
	v_viewsParentLayout->setSpacing(10);
	v_viewsParentLayout->setContentsMargins(0,20,0,20);

	QWidget *w_viewOne = new QWidget;
	QWidget *w_viewTwo = new QWidget;
	w_viewOne->setStyleSheet(viewStyle);
	w_viewTwo->setStyleSheet(viewStyle);
	AspectRatioWidget *w_viewOneContainer = new AspectRatioWidget(w_viewOne, 16, 9);
	AspectRatioWidget *w_viewTwoContainer = new AspectRatioWidget(w_viewTwo, 16, 9);
	w_viewOneContainer->setStyleSheet(greenStyle);
	w_viewTwoContainer->setStyleSheet(greenStyle);

	QWidget *w_viewThree = new QWidget;
	QWidget *w_viewFour = new QWidget;
	w_viewThree->setStyleSheet(viewStyle);
	w_viewFour->setStyleSheet(viewStyle);
	AspectRatioWidget *w_viewThreeContainer = new AspectRatioWidget(w_viewThree, 16, 9);
	AspectRatioWidget *w_viewFourContainer = new AspectRatioWidget(w_viewFour, 16, 9);
	w_viewThreeContainer->setStyleSheet(greenStyle);
	w_viewFourContainer->setStyleSheet(greenStyle);

	QWidget *w_topContainer = new QWidget;
	QWidget *w_bottomContainer = new QWidget;
	w_topContainer->setSizePolicy(QSizePolicy::Minimum, QSizePolicy::Minimum);
	w_bottomContainer->setSizePolicy(QSizePolicy::Minimum, QSizePolicy::Minimum);
	w_topContainer->setStyleSheet(horContainerStyle);
	w_bottomContainer->setStyleSheet(horContainerStyle);
	QHBoxLayout *h_topLayout = new QHBoxLayout(w_topContainer);
	QHBoxLayout *h_bottomLayout = new QHBoxLayout(w_bottomContainer);
	Util::setLayoutZero(h_topLayout);
	Util::setLayoutZero(h_bottomLayout);
	h_topLayout->setSpacing(10);
	h_bottomLayout->setSpacing(10);
	h_topLayout->setContentsMargins(50,0,50,0);
	h_bottomLayout->setContentsMargins(50,0,50,0);

	//h_topLayout->addStretch();
	h_topLayout->addWidget(w_viewOneContainer);
	h_topLayout->addWidget(w_viewTwoContainer);
	//h_topLayout->addStretch();
	//h_bottomLayout->addStretch();
	h_bottomLayout->addWidget(w_viewThreeContainer);
	h_bottomLayout->addWidget(w_viewFourContainer);
	//h_bottomLayout->addStretch();
	v_viewsParentLayout->addWidget(w_topContainer);
	v_viewsParentLayout->addWidget(w_bottomContainer);
}

void tx4_viewer::initControlBar() {
	w_controlBar = new tx4_control_bar;

}