
#include "tx4_view.h"

AspectRatioWidget::AspectRatioWidget(QWidget *widget, float width, float height, QWidget *parent) :
    QWidget(parent), arWidth(width), arHeight(height)
{

    this->setMinimumSize(VIEW_MIN_W, VIEW_MIN_H);

    layout = new QBoxLayout(QBoxLayout::LeftToRight, this);
    layout->setContentsMargins(0, 0, 0, 0);
    layout->setSpacing(10);
    // add spacer, then your widget, then spacer
    //layout->addItem(new QSpacerItem(20, 0, QSizePolicy::Fixed, QSizePolicy::Expanding));
    //layout->addStretch();
    layout->addItem(new QSpacerItem(0, 0));
    layout->addWidget(widget);
    //layout->addWidget(widget2);
    layout->addItem(new QSpacerItem(0, 0));
    //layout->addStretch();
    //layout->addItem(new QSpacerItem(20, 0, QSizePolicy::Fixed, QSizePolicy::Expanding));
}

void AspectRatioWidget::resizeEvent(QResizeEvent *event)
{
    float thisAspectRatio = (float)event->size().width() / event->size().height();
    int widgetStretch, outerStretch;

    if (thisAspectRatio > (arWidth/arHeight)) // too wide
    {
        layout->setDirection(QBoxLayout::LeftToRight);
        widgetStretch = height() * (arWidth/arHeight); // i.e., my width
        outerStretch = (width() - widgetStretch) / 2 + 0.5;
    }
    else // too tall
    {
        layout->setDirection(QBoxLayout::TopToBottom);
        widgetStretch = width() * (arHeight/arWidth); // i.e., my height
        outerStretch = (height() - widgetStretch) / 2 + 0.5;
    }

    layout->setStretch(0, outerStretch);
    layout->setStretch(1, widgetStretch);
    //layout->setStretch(2, widgetStretch);
    layout->setStretch(2, outerStretch);
}

//tx4_view::tx4_view(QWidget *parent)
//	: QWidget(parent) {
//
//	this->setAttribute(Qt::WA_StyledBackground); // <--- this attribute solves issue of background color not being drawn on custom widget, no need for reimplementing paintEvent, yet.
//	this->setMinimumSize(VIEW_MIN_W, VIEW_MIN_H);
//	QSizePolicy qsp(QSizePolicy::Preferred, QSizePolicy::Preferred);
//	qsp.setHeightForWidth(true);
//	this->setSizePolicy(qsp);
//	this->setStyleSheet(blueStyle);
//}
//
//tx4_view::~tx4_view() {}
//
//void tx4_view::resizeEvent(QResizeEvent *event) {
//    event->accept();
//
//	QWidget::resize(event->size().width()*9/16, event->size().width()*9/16);
//    //if(event->size().width() > event->size().height()){
//    //    QWidget::resize(event->size().height(),event->size().height());
//    //}else{
//    //    QWidget::resize(event->size().width(),event->size().width());
//    //}
//}