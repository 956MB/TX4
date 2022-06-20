#ifndef TX4_QUEUE_ENTRY_H
#define TX4_QUEUE_ENTRY_H

#include <QWidget>
#include "./util/tx4_util.h"
#include "tx4_label.h"
#include "tx4_event_preview.h"
#include "./tx4_defines.h"

class tx4_queue_entry : public QWidget {
	Q_OBJECT

	public:
		explicit tx4_queue_entry(const QString &text, tx4_event_preview &preview, QWidget* parent = nullptr);
		virtual ~tx4_queue_entry();

	protected:
		virtual void enterEvent(QEvent *e);
		virtual void leaveEvent(QEvent *e);

	private:
		QString textContent;
		QString previewCurrentStylesheet;
		QString previewHoverStylesheet;
		QString barCurrentStylesheet;
		QString barHoverStylesheet;
		QString selectIdxCurrentStylesheet;
		QString selectIdxHoverStylesheet;
		tx4_event_preview *eventPreview;
		tx4_label *entryLabel;
		
		void initContents();

	private slots:
		void on_selectedEnter();
		void on_selectedLeave();

};

#endif // TX4_QUEUE_ENTRY_H