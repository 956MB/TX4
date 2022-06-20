#ifndef TX4_LIST_ITEM_H
#define TX4_LIST_ITEM_H

#include <QWidget>
#include "tx4_label.h"
#include "./util/tx4_util.h"
#include "tx4_list_button.h"
#include "tx4_event.h"
#include "./tx4_defines.h"
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc.hpp>

class tx4_list_item : public QWidget {
	Q_OBJECT

	public:
		explicit tx4_list_item(const tx4_event* event, const QString &thumbnail, const int &index, const int &displayIndex, QWidget* parent = nullptr);
		virtual ~tx4_list_item();

	public:
		int i_eventIndex;
		int i_displayIndex;
		int selectIndex;
		QString s_dateString;
		//QString s_locString;
		QString s_sizeString;
		QString s_lengthString;
		QString s_timestampString;
		QString s_cityString;
		QString s_latString;
		QString s_lonString;
		QString s_reasonString;
		//QString s_cameraString;
		bool b_listItemHovered;
		bool b_listItemSelected;
		bool b_selectModeActive;
		bool b_listItemActive;

		// TODO: public select/deselect for all
		void selectItem();
		void deselectItem();
		//void resizePreview(int window_w);
		void repaintItem();

	signals:
		void select(int idx);
		void deselect(int idx);
		void selectedEnter();
		void selectedLeave();

	protected:
		virtual void enterEvent(QEvent *e);
		virtual void leaveEvent(QEvent *e);

	private:
		QWidget *w_contentContainer;
		QWidget *w_itemBackground;
		//QPixmap p_smallPreviewPixmap;
		tx4_list_button *w_listButton;
		QLabel *w_smallPreviewLabel;
		bool b_previewPixmapSet;
		QList<tx4_label*> l_itemLabels;
		QStringList l_infoTextList;

		void initContents(QString thumbMat);
		void setHoverStyles(bool hovered, QString backgroundStyle, bool parentHoverd, ButtonState buttonState);
		void setSelectStyles(bool selected, QString backgroundStyle, ButtonState buttonState);
		void setLabelStyles(QString style);
		//void createThumbnailPixmap(cv::Mat thumbMat);

	private slots:
		void on_buttonClicked();
};

#endif // TX4_LIST_ITEM_H