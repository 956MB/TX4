#ifndef TX4_CONTROL_BAR_H
#define TX4_CONTROL_BAR_H

#include <QWidget>
#include "../tx4_label.h"
#include "../tx4_event.h"
#include "../util/tx4_util.h"
#include "./tx4_control_bar_button.h"
#include "../tx4_defines.h"

class tx4_control_bar : public QWidget {
	Q_OBJECT

	public:
		explicit tx4_control_bar(QWidget* parent = nullptr);
		virtual ~tx4_control_bar();

		void resetControlBar();
		void updateLayoutIcon(QString newIcon);

	signals:
		void cycleLayout();

	private:
		QWidget *w_timelineContainer;
		tx4_control_bar_button *b_backButton;
		tx4_control_bar_button_toggle *b_playPauseButton;
		tx4_control_bar_button *b_forwardButton;
		tx4_control_bar_button *b_layoutButton;
		tx4_control_bar_button *b_fullscreenButton;
		tx4_label *l_timeCurrentLabel;
		tx4_label *l_timeTotalLabel;
		QSlider *w_timelineSlider;

		//QString s_playText;
		//QString s_pauseText;
		//bool m_masterBar;
		int i_barSteps;

		void initContents();
		void initTimeline();
		//void initButtons();

	private slots:
		void on_timelineValueUpdate(int value);
		void on_cycleLoadoutClicked();
};

#endif // TX4_CONTROL_BAR_H