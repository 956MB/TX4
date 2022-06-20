#ifndef TX4_EVENTS_GROUP_TITLE_H
#define TX4_EVENTS_GROUP_TITLE_H

#include <QWidget>
#include "tx4_label.h"
#include "./util/tx4_util.h"
#include "tx4_events_section.h"
#include "./tx4_defines.h"

class tx4_events_group_title : public QWidget {
	Q_OBJECT

	public:
		explicit tx4_events_group_title(const QString &title, const QString &style, const bool &mouseActions = true, QWidget* parent = nullptr);
		virtual ~tx4_events_group_title();

		void updateTitleString(bool selected, QString newTitle);

	signals:
		void clicked();

	protected:
		virtual void enterEvent(QEvent *e);
		virtual void leaveEvent(QEvent *e);
		virtual void mousePressEvent(QMouseEvent *e);
		virtual void mouseReleaseEvent(QMouseEvent *e);

	private:
		tx4_label *l_titleLabel;
		bool m_pressed;
		bool m_mouseActions;
		QString s_groupTitle;
		QString s_titleStyle;

		void initContents();
};

#endif // TX4_EVENTS_GROUP_TITLE_H