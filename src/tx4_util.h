#pragma once

#include <stdio.h> 
#include <sstream>
#include <stdlib.h> // atoll
#include <stdint.h> // uint64_t
#include <inttypes.h> // PRIu64
#include <QtWidgets/qboxlayout.h>
#include <iomanip>
#include <QTime>

class Util {
	public:
		static inline void setLayoutZero(QLayout *layout) {
			layout->setMargin(0);
			layout->setContentsMargins(0, 0, 0, 0);
			layout->setSpacing(0);
		}
		static inline void setLayoutZeroMargins(QLayout *layout, int left, int top, int right, int bottom) {
			layout->setMargin(0);
			layout->setContentsMargins(left, top, right, bottom);
			layout->setSpacing(0);
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
			sprintf(output, "%.02lf%s", dblBytes, suffix[i]);
			QString qoutput = QString::fromLocal8Bit(output);
			return qoutput;
		}

		static inline QString format_duration(qint64 len) {
			//long milli = len;
			////3600000 milliseconds in an hour
			//long hr = milli / 3600000;
			//milli = milli - 3600000 * hr;
			////60000 milliseconds in a minute
			//long min = milli / 60000;
			//milli = milli - 60000 * min;
			////1000 milliseconds in a second
			//long sec = milli / 1000;
			//milli = milli - 1000 * sec;

			//QString out;
			//std::ostringstream sshr;
			//sshr << std::setw(1) << std::setfill('0') << hr;
			//std::ostringstream ssmin;
			//ssmin << std::setw(1) << std::setfill('0') << min;
			//std::ostringstream sssec;
			//sssec << std::setw(1) << std::setfill('0') << sec;

			//if (hr > 0) {
			//	out = QString::fromStdString(sshr.str()) + QString(":") + QString::fromStdString(ssmin.str()) + QString(":") + QString::fromStdString(sssec.str());
			//} else {
			//	out = QString::fromStdString(ssmin.str()) + QString(":") + QString::fromStdString(sssec.str());
			//}

			//return out;

			int milliseconds = len;
			int seconds      = milliseconds / 1000;
			milliseconds     = milliseconds % 1000;
			int minutes      = seconds / 60; 
			seconds          = seconds % 60;
			int hours        = minutes / 60;
			minutes          = minutes % 60;

			QTime time;
			time.setHMS(hours, minutes, seconds, milliseconds);

			//return time.toString("hh:mm:ss");
			if (hours > 0) {
				return time.toString("hh:mm:ss");
			} else {
				return time.toString("mm:ss");
			}
		}

};