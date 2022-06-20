#ifndef TX4_TOOLBAR_NEW_H
#define TX4_TOOLBAR_NEW_H

#include <QWidget>
#include "../tx4_label.h"
#include "../util/tx4_util.h"
#include "tx4_toolbar_button.h"
#include "tx4_toolbar_button_icon.h"
#include "../tx4_event_preview.h"
#include "../tx4_queue_entry.h"
#include "../tx4_defines.h"

class tx4_toolbar : public QWidget {
	Q_OBJECT

	public:
		explicit tx4_toolbar(QWidget* parent = nullptr);
		virtual ~tx4_toolbar();

		void resetButtonStates();
		void setButtonSelected(int idx);
		void updateOpenEventsButtonState(int count);
		void updateImportButtonState(bool disabled);
		void updatePageButtonState(int page, int incr);

	private:
		int i_selectedSavedEvents;
		int i_selectedSentryEvents;

		QList<tx4_toolbar_button*> l_buttons;
		tx4_toolbar_button *b_recentButton;
		tx4_toolbar_button *b_savedButton;
		tx4_toolbar_button *b_sentryButton;
		tx4_toolbar_button *b_favoritesButton;
		tx4_toolbar_button_icon *b_openButton;
		tx4_toolbar_button_icon *b_importButton;
		tx4_toolbar_button_icon *b_settingsButton;

		void initContents();

	public slots:
		void on_handleButtonClick(int buttonIndex);

	signals:
		void sectionButtonClick(int idx);
		void openButtonClick();
		void importButtonClick();
		void settingsButtonClick();
};

#endif // TX4_TOOLBAR_NEW_H