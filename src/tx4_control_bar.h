#ifndef TX4_CONTROL_BAR_H
#define TX4_CONTROL_BAR_H

#include <QWidget>
#include "tx4_label.h"
#include "tx4_util.h"
#include "tx4_toolbar_button.h"

#define CONTROL_BAR_H 50
#define SCROLL_DIFF 35
#define TIMELINE_MIN 0
#define TIMELINE_MAX 2
#define STEPS 59

class tx4_control_bar : public QWidget {
	Q_OBJECT

	public:
		explicit tx4_control_bar(QWidget* parent = nullptr);
		~tx4_control_bar();

	private:
		QWidget *w_timelineContainer;
		QWidget *w_buttonContainer;
		tx4_toolbar_button *b_syncViewsButton;
		tx4_toolbar_button *b_playPauseButton;
		tx4_toolbar_button *b_backButton;
		tx4_toolbar_button *b_forwardButton;
		tx4_label *l_timeCurrentLabel;
		tx4_label *l_timeDividerLabel;
		tx4_label *l_timeTotalLabel;
		QSlider *w_timelineSlider;

		QString s_playText;
		QString s_pauseText;

		QString controlBarBodyStyle = "background-color: #0f0f0f; border: none; outline: none;";
		QString buttonContainerBodyStyle = "background-color: #181818; border: none; outline: none;";
		QString timelineContainerStyle = "background-color: #181818; border: none; outline: none;";
		QString timelineBodyStyle = "background-color: black; border: none; outline: none;";
		QString timeContainerStyle = "background-color: #262626; border: none; outline: none;";
		QString timeLabelStyle = "background-color: none; border: none; outline: none; color: white;";
		QString dividerLabelStyle = "background-color: none; border: none; outline: none; color: rgba(255,255,255,190);";

		QString timelineSliderStyle = "QSlider::groove:horizontal { background: black; } QSlider::handle:horizontal { width: 3px; background: #f6f6f6; border-right: 3px solid black; } QSlider::add-page:horizontal { background: rgba(255,255,255,60); height: 5px; margin: 9px 0; position: absolute; right: 3px; } QSlider::sub-page:horizontal { background: #f6f6f6; height: 5px; margin: 9px 0; position: absolute; left: 3px }";

		QString enabled_slider = "QSlider::groove:horizontal { height: 7px; background: rgba(255,255,255,50); margin: 2px 0; border-radius: 1px; } QSlider::handle:horizontal { width: 40px; margin: -3px 0 } QSlider::add-page:horizontal { margin: 1px 0; background: rgba(255,255,255,255); border-radius: 2px; }";

		void initContents();
		void initTimeline();
		void initButtons();

	private slots:
		void on_timelineValueUpdate(int value);

};

#endif // TX4_CONTROL_BAR_H