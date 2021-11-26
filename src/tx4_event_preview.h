#ifndef TX4_CLIP_PREVIEW_H
#define TX4_CLIP_PREVIEW_H

#include <QWidget>
#include "tx4_label.h"
#include "tx4_util.h"
#include "tx4_checkbox.h"
#include "tx4_preview_bar.h"
#include "tx4_meta_info.h"
#include "tx4_event.h"

#define PREVIEW_W 240
#define PREVIEW_H 135

class tx4_event_preview : public QWidget {
	Q_OBJECT

	public:
		explicit tx4_event_preview(const QString &date, const QString &loc, const QString &size, const QString &length, const QString &timestamp, const QString &city, const QString &lat, const QString &lon, const QString &reason, const QString &camera, const QString &loc_style, const int &index, QWidget* parent = nullptr);
		~tx4_event_preview();

	public:
		int previewIndex;
		int selectIndex;
		QString s_dateString;
		QString s_locString;
		QString s_sizeString;
		QString s_lengthString;
		QString s_locStyle;
		QString s_timestampString;
		QString s_cityString;
		QString s_latString;
		QString s_lonString;
		QString s_reasonString;
		QString s_cameraString;
		int clipCount;

		void setSelectModeState(bool active);
		void setSelectIdx(int idx);

	signals:
		void select(int idx);
		void deselect(int idx);

	protected:
		//bool event(QEvent *e) override;
		void paintEvent(QPaintEvent *);
		virtual void enterEvent(QEvent *e);
		virtual void leaveEvent(QEvent *e);
		//virtual void mousePressEvent(QMouseEvent *e);
		virtual void mouseReleaseEvent(QMouseEvent *e);

	private:
		QWidget *w_contentContainer;
		QWidget *w_contentScreen;
		QWidget *w_metaDataScreen;
		QWidget *w_selectIdxScreen;
		tx4_label *l_selectIdxLabel;
		QImage *contentImage;
		QPixmap contentPixmap;
		QLabel *contentLabel;
		tx4_preview_bar *previewInfoBar;
		tx4_meta_info* metaInfo;

		bool selectModeActive;
		bool metaDataActive;
		bool previewActive;
		bool previewSelected;
		bool previewHovered;

		QString thumbUnavailableLabelStyle = "background-color: none; border: none; outline: none; color: rgba(255,255,255,50);";
		QString selectIdxLabelStyle = "background-color: none; border: none; outline: none; color: white;";
		QString selectIdxScreenStyle = "background-color: none; border: none; outline: none;";
		QString metaDataScreenStyle = "background-color: rgba(255,255,255,15); border: none; outline: none;";
		QString normalStyle = "background-color: rgba(255,255,255,15); border: none; outline: none;";
		QString hoverStyle = "background-color: rgba(255,255,255,20); border: 3px solid rgba(255,255,255,40); outline: none;";
		QString hoverStyle_SelectMode = "background-color: rgba(255,255,255,20); border: 3px solid rgba(255,255,255,160); outline: none;";
		QString contentStyleNormal = "background-color: none; border: none; outline: none;";
		QString contentStyleHover = "background-color: none; border-left: 3px solid white; border-top: 3px solid white; border-right: 3px solid white; border-bottom: 0px solid white; outline: none;";
		QString blankStyle = "background-color: none; border: none; outline: none;";

		void initContents();
		void leftClick();
		void rightClick();
		void addCreateMetaInfo();
		void removeMetaInfo();

};

#endif // TX4_CLIP_PREVIEW_H