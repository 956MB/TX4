#ifndef TX4_CLIP_PREVIEW_H
#define TX4_CLIP_PREVIEW_H

#include <QWidget>
#include "tx4_label.h"
#include "./util/tx4_util.h"
#include "tx4_preview_bar.h"
#include "tx4_meta_info.h"
#include "tx4_event.h"
#include "./tx4_defines.h"
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc.hpp>

class tx4_event_preview : public QWidget {
	Q_OBJECT

	public:
		explicit tx4_event_preview(const QString &date, const QString &loc, const QString &size, const QString &length, const QString &timestamp, const QString &city, const QString &lat, const QString &lon, const QString &reason, const QString &camera, const QString &loc_style, const QString &thumbnail, const int &index, QWidget* parent = nullptr);
		virtual ~tx4_event_preview();

	public:
		int i_sectionIndex;
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
		//tx4_label *l_selectIdxLabel;
		tx4_meta_info* metaInfo;
		bool b_metaDataActive;
		bool b_previewHovered;
		bool b_previewSelected;
		bool b_previewGrayscaled;

		//void setSelectModeState(bool active);
		void setSelectIdx(int idx);
		void setOwnStylesheet(QString parentSS, QString barSS = "", QString selectIdxSS = "", QString metaSS = "");

		// TODO: public select/deselect for all
		void selectPreview();
		void deselectPreview();
		void resizePreview(int window_w);
		void repaintPreview(bool grayscale, PreviewState state);

	signals:
		void select(int idx);
		void deselect(int idx);
		void selectedEnter();
		void selectedLeave();

	protected:
		//bool event(QEvent *e) override;
		//void paintEvent(QPaintEvent *);
		virtual void enterEvent(QEvent *e);
		virtual void leaveEvent(QEvent *e);
		//virtual void mousePressEvent(QMouseEvent *e);
		//virtual void resizeEvent(QResizeEvent *event);
		virtual void mouseReleaseEvent(QMouseEvent *e);

	private:
		QWidget *w_contentContainer;
		QWidget *w_contentStack;
		QWidget *w_metaDataScreen;
		//QWidget *w_borderOverlayOuter;
		//QWidget *w_borderOverlayInner;
		QPixmap p_thumbnailPixmap;
		QLabel *w_contentLabel;

		bool b_selectModeActive;
		bool b_previewActive;
		bool b_thumbnailPixmapSet;
		//double m_ratio;
		int i_saveWindowW;
		//QGraphicsDropShadowEffect *effect;

		void initContents();
		void leftClick();
		void rightClick();
		void createMetaInfo();
		void removeMetaInfo();
		void createThumbnailPixmap(cv::Mat thumbMat);
};

#endif // TX4_CLIP_PREVIEW_H