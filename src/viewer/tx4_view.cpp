
#include "tx4_view.h"

tx4_view::tx4_view(QList<QFileInfo> clips, const QString &text, const int &index, const bool &selected, const bool &selectable, const bool &clickable, QWidget *parent)
	: QWidget(parent)
    , i_viewIndex(index)
    , l_clipsList(clips)
    , b_controlsShown(true)
    , b_viewSelectable(selectable)
    , b_viewSelected(selected)
    , b_viewClickable(clickable)
    , s_viewText(text)
{

	this->setAttribute(Qt::WA_StyledBackground); // <--- this attribute solves issue of background color not being drawn on custom widget, no need for reimplementing paintEvent, yet.
	//this->setMinimumSize(VIEW_MIN_W, VIEW_MIN_H);
	//QSizePolicy qsp(QSizePolicy::Preferred, QSizePolicy::Preferred);
	//qsp.setHeightForWidth(true);
	//this->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
	this->setStyleSheet(b_viewSelected ? S_VIEW_SELECTED : S_VIEW_NORMAL);

    initContents();
}

tx4_view::~tx4_view() {}

void tx4_view::initContents() {
    QStackedLayout *outerlayout = new QStackedLayout(this);
	outerlayout->setStackingMode(QStackedLayout::StackAll);
	Util::setLayoutZero(outerlayout);

    //initPlayer();

    w_controlsWidget = new QWidget;
    w_controlsWidget->setStyleSheet(S_BLANK);
	w_controlsWidget->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    QVBoxLayout *v_controlsLayout = new QVBoxLayout(w_controlsWidget);
	Util::setLayoutZero(v_controlsLayout);

	QWidget *w_textContainer = new QWidget;
    QHBoxLayout *h_textLayout = new QHBoxLayout(w_textContainer);
	Util::setLayoutZero(h_textLayout);
    h_textLayout->setContentsMargins(10,0,0,10);
	l_viewLabel = new tx4_label(s_viewText, 13, S_VIEW_TEXT_LABEL, QFont::DemiBold, Qt::AlignHCenter, Qt::AlignVCenter);
    h_textLayout->addWidget(l_viewLabel);
    h_textLayout->addStretch();

    v_controlsLayout->addStretch();
    v_controlsLayout->addWidget(w_textContainer);

    outerlayout->addWidget(w_controlsWidget);
    //outerlayout->addWidget(w_playerVideoWidget);

    w_controlsWidget->setVisible(b_controlsShown);
    l_viewLabel->setVisible(!b_viewSelected);
    //w_player->play();
}

void tx4_view::initPlayer() {
    clipPlaylist = new QMediaPlaylist;
    for (int i = 0; i < l_clipsList.length(); i++) {
        //qDebug() << l_clipsList[i].absoluteFilePath() + QString(".mp4");
        clipPlaylist->addMedia(QUrl::fromLocalFile(l_clipsList[i].absoluteFilePath()));
    }
    clipPlaylist->setCurrentIndex(1);

    w_player = new QMediaPlayer;
    w_player->setPlaylist(clipPlaylist);
    //connect(player, SIGNAL(positionChanged(qint64)), this, SLOT(positionChanged(qint64)));
    w_player->setVolume(0);

    w_playerVideoWidget = new QVideoWidget;
    w_playerVideoWidget->setAspectRatioMode(Qt::KeepAspectRatio);
    w_player->setVideoOutput(w_playerVideoWidget);
    //w_playerVideoWidget->show();
}
//void tx4_view::enterEvent(QEvent *e) {
//    //controlsShown = true;
//    //w_controlsWidget->setVisible(controlsShown);
//}
//void tx4_view::leaveEvent(QEvent *e) {
//    //controlsShown = false;
//    //w_controlsWidget->setVisible(controlsShown);
//}
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

void tx4_view::setViewState(bool selected) {
    b_viewSelected = selected;
	this->setStyleSheet(b_viewSelected ? S_VIEW_SELECTED : S_VIEW_NORMAL);
    l_viewLabel->setVisible(!b_viewSelected);
}


// MOUSE EVENTS
void tx4_view::mouseReleaseEvent(QMouseEvent *e) {
    if (!b_viewSelected && (b_viewClickable || b_viewSelectable)) {
        if (e->button() == Qt::LeftButton) {
		    if (this->rect().contains(this->mapFromGlobal(QCursor::pos()))) {
                if (b_viewClickable) {
                    emit clicked();
                } else if (b_viewSelectable) {
                    emit selected();
                }
            }

            QWidget::mouseReleaseEvent(e);
        }
    }
}


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