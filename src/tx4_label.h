#ifndef TX4_LABEL_H
#define TX4_LABEL_H

#include <QtWidgets>
#include <QLabel>

class tx4_label : public QLabel {
	Q_OBJECT

	public:
		explicit tx4_label(const QString &text, const int &size, const QString &style, const QFont::Weight &weight, const Qt::AlignmentFlag &align, const QString &font, QWidget *parent = nullptr);
		~tx4_label();

	public:
		QString labelText;
		void setLabelText(QString newText);

};

#endif // TX4_LABEL_H