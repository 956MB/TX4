#ifndef TX4_META_INFO_H
#define TX4_META_INFO_H

#include <QtWidgets>
#include <QLabel>
#include "tx4_label.h"
#include "tx4_util.h"
#include "tx4_preview_bar.h"

class tx4_meta_info : public QWidget {
	Q_OBJECT

	public:
		explicit tx4_meta_info(const QString &timestamp, const QString &city, const QString &lat, const QString &lon, const QString &reason, const QString &camera, QWidget *parent = nullptr);
		~tx4_meta_info();

	public:
		tx4_preview_bar *metaInfoBar;

	private:
		QString s_timestampB;
		QString s_cityB;
		QString s_est_latB;
		QString s_est_lonB;
		QString s_reasonB;
		QString s_cameraB;

		// meta info styles:
		QString whiteStyle = "background-color: none; border: none; outline: none; color: white;";
		QString blueStyle = "background-color: none; border: none; outline: none; color: rgba(90, 157, 230, 255);";
		QString orangeStyle = "background-color: none; border: none; outline: none; color: rgba(232, 160, 104, 255);";
		QString blankStyle = "background-color: none; border: none; outline: none;";

		void init();
		void addWidgetSep(QHBoxLayout *layout, tx4_label *label, QString sep);

};

#endif // TX4_META_INFO_H