#ifndef TX4_INFO_BAR_H
#define TX4_INFO_BAR_H

#include <QWidget>
#include "../tx4_label.h"
#include "../util/tx4_util.h"
#include "../toolbar/tx4_toolbar_button.h"
#include "../tx4_event.h"
#include "../tx4_defines.h"

class tx4_info_bar : public QWidget {
	Q_OBJECT

	public:
		explicit tx4_info_bar(const QString &type, const QString &reason, const QString &city, const QString &date, const QString &time, std::initializer_list<QString> tooltips, QWidget* parent = nullptr);
		virtual ~tx4_info_bar();
		
		void updateInfo(QString type, QString reason, QString city, QString date, QString time, std::initializer_list<QString> tooltips);

	private:
		QStringList l_infoKeys;
		QStringList l_infoValues;
		QStringList l_infoTooltips;
		QWidget *w_timelineContainer;
		QString s_typeInfo;
		QString s_reasonInfo;
		QString s_cityInfo;
		QString s_dateInfo;
		QString s_timeInfo;
		QList<tx4_label*> l_infoList;

		void initContents();
};

#endif // TX4_INFO_BAR_H