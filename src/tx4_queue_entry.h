#ifndef TX4_QUEUE_ENTRY_H
#define TX4_QUEUE_ENTRY_H

#include <QWidget>
#include "tx4_util.h"
#include "tx4_label.h"
#include "tx4_event_preview.h"

class tx4_queue_entry : public QWidget {
	Q_OBJECT

	public:
		explicit tx4_queue_entry(const QString &text, tx4_event_preview &preview, QWidget* parent = nullptr);
		~tx4_queue_entry();

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

		QString blankStyle = "background-color: none; border: none; outline: none;";
		QString queueLabelStyleNormal = "background-color: black; color: rgba(255,255,255,140);";
		QString queueLabelStyleHover = "background-color: black; color: rgba(255,246,0,255);";
		QString queueLabelStyleDisabled = "background-color: rgba(0,0,0,150); color: rgba(255,255,255,0);";
		
		void initContents();

	private slots:
		void on_selectedEnter();
		void on_selectedLeave();

};

#endif // TX4_QUEUE_ENTRY_H