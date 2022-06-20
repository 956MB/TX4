#pragma once

#include <stdio.h> 
#include <sstream>
#include <stdlib.h> // atoll
#include <stdint.h> // uint64_t
#include <inttypes.h> // PRIu64
#include <QtWidgets/qboxlayout.h>
#include <iomanip>
#include <QTime>
#include <qdebug.h>

//const QStringList months = {"January", "February", "March", "April", "May", "June", "July", "August", "September", "October", "November", "December"};

struct QPairMonthsCompare
{
    template<typename T1, typename T2>
    bool operator()(const QPair<T1,T2> & a, const QPair<T1,T2> & b) const
    {
		QStringList months = {"January", "February", "March", "April", "May", "June", "July", "August", "September", "October", "November", "December"};
        return months.indexOf(a.first) < months.indexOf(b.first);
    }
};

class Util {
	public:
		static inline void cycleList(int &idx, int listCount) {
			idx += 1;
			if (idx == listCount)	{ idx = 0; }
		}

		static inline void cycleListBoth(int &idx, int incr, int listCount) {
			idx += incr;
			if (idx == listCount)	{ idx = 0; }
			if (idx == -1)			{ idx = listCount-1; }
		}

		//static const QStringList months = {"January", "February", "March", "April", "May", "June", "July", "August", "September", "October", "November", "December"};
		static inline QString limitString(const QString& aString, int maxLength) {
			const QString ELLIPSIS("...");
			if (aString.length() <= maxLength)
				return aString + "   ";

			//float spacePerPart = (maxLength - ELLIPSIS.length()) / 2.0;
			auto beforeEllipsis = aString.left(std::ceil(maxLength));
			//auto afterEllipsis = aString.right(std::floor(spacePerPart));

			return beforeEllipsis + ELLIPSIS;
		}

		static inline QString reasonMap(QString key, bool returnKey = false) {
			QMap<QString, QString> reasons{{"user_interaction_dashcam_icon_tapped", "Dashcam"}, {"user_interaction_honk", "Honk"}, {"sentry_aware_object_detection", "Object detection"}};
			if (returnKey) {
				return reasons.key(key);
			} else {
				return reasons.value(key);
			}
		}

		static inline QString humanSize(uint64_t bytes) {
			const char *suffix[] = {"B", "KB", "MB", "GB", "TB"};
			char length = sizeof(suffix) / sizeof(suffix[0]);

			int i = 0;
			double dblBytes = bytes;

			if (bytes > 1024) {
				for (i = 0; (bytes / 1024) > 0 && i<length-1; i++, bytes /= 1024)
					dblBytes = bytes / 1024.0;
			}

			static char output[200];
			sprintf(output, "%.02lf %s", dblBytes, suffix[i]);
			QString qoutput = QString::fromLocal8Bit(output);
			return qoutput;
		}

		static inline QString format_duration(qint64 len) {
			int milliseconds = len;
			int seconds      = milliseconds / 1000;
			milliseconds     = milliseconds % 1000;
			int minutes      = seconds / 60; 
			seconds          = seconds % 60;
			int hours        = minutes / 60;
			minutes          = minutes % 60;

			QTime time;
			time.setHMS(hours, minutes, seconds, milliseconds);

			return time.toString("hh:mm:ss");
		}

		static inline QString formatTimeline(int sec) {
			int seconds      = sec;
			int milliseconds = sec * 1000;
			int minutes      = seconds / 60; 
			seconds          = seconds % 60;
			int hours        = minutes / 60;
			minutes          = minutes % 60;

			QTime time;
			time.setHMS(hours, minutes, seconds, milliseconds);

			//return time.toString("hh:mm:ss");
			return time.toString("hh:mm:ss");
		}

		static inline void clearLayout(QLayout *layout, int takeIndex = 0) {
			if (layout == NULL)
				return;
			QLayoutItem *item;
			while((item = layout->takeAt(takeIndex))) {
				if (item->layout()) {
					clearLayout(item->layout());
					delete item->layout();
				}
				if (item->widget()) {
				   delete item->widget();
				}
				delete item;
			}
		}

		template<typename T>
		static inline void deleteAndCleanup(T*& ptr)
		{
			delete ptr;
			ptr = NULL;
		}

		static inline void setLayoutZero(QLayout *layout) {
			layout->setMargin(0);
			layout->setContentsMargins(0, 0, 0, 0);
			layout->setSpacing(0);
		}
		static inline void setLayoutZeroMargins(std::initializer_list<QLayout *> layouts, int left, int top, int right, int bottom) {
			for(auto &&layout : layouts) {
				layout->setMargin(0);
				layout->setContentsMargins(left, top, right, bottom);
				layout->setSpacing(0);
			}
		}

		static inline void resetWidgetExpanding(QWidget *widget) {
			widget->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
			widget->setMaximumSize(QWIDGETSIZE_MAX,QWIDGETSIZE_MAX);
			widget->setMinimumSize(0,0);
		}
		static inline void setWidgetFixedHeight(QWidget *widget, int height) {
			widget->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Fixed);
			widget->setFixedHeight(height);
		}
		static inline void setWidgetsSizePolicy(QSizePolicy::Policy hor, QSizePolicy::Policy ver, std::initializer_list<QWidget *> widgets) {
			for(auto &&w : widgets) {
				w->setSizePolicy(hor, ver);
			}
		}
		static inline void setWidgetsStyleSheet(QString stylesheet, std::initializer_list<QWidget *> widgets) {
			for(auto &&w : widgets) {
				w->setStyleSheet(stylesheet);
			}
		}
};