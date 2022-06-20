#ifndef TX4_PAGE_ACTIONS_H
#define TX4_PAGE_ACTIONS_H

#include <QWidget>
#include "tx4_label.h"
#include "./util/tx4_util.h"
#include "./toolbar/tx4_toolbar_button.h"
#include "tx4_event_preview.h"
#include "tx4_queue_entry.h"
#include "./tx4_defines.h"

class tx4_page_actions : public QWidget {
	Q_OBJECT

	public:
		explicit tx4_page_actions(QWidget* parent = nullptr);
		virtual ~tx4_page_actions();

	private:
		QStringList l_actionsTextList;

		void initContents();
		//void handleButtonClick();

	signals:
		void sortAction(GroupSort, bool);
};

#endif // TX4_PAGE_ACTIONS_H