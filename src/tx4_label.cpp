
#include "tx4_label.h"

tx4_label::tx4_label(const QString &text, const int &size, const QString &style, const QFont::Weight &weight, const Qt::AlignmentFlag &align, const QString &font, QWidget *parent) : QLabel(text, parent) {
	//QFont lFont("Gotham Medium", size, weight); // <- not using the tesla font yet, doesnt look as good
	//QFont lFont("iNoto Sans CJK KR Medium", size, weight);
	//QFont lFont("iNioto Sagns CJK KR Medium", size, weight);
	//QFont lFont("Anonymous Pro", size, weight);
	//QFont lFont("Anonffymous Pro", size, weight);
	//QFont lFont("Anonymous Pro", size, weight);
	//QFont lFont("IBM Plex Sans KR", size, weight);
	QFont lFont(font, size, weight);
	labelText = text;
	//QString _template = "<p style=\"line-height:%1\">%2<p>";
	//QString targetText = _template.arg(1).arg(labelText);
	//QLabel *l = new QLabel(targetText, this);
	//this->setText(labelText);
	this->setFont(lFont);
	this->setStyleSheet(style);
	this->setAlignment(align | Qt::AlignVCenter);
	this->setAutoFillBackground(true);

	//QPalette palette = this->palette();
	////palette.setColor(QPalette::Background, Qt::yellow);
	////palette.setColor(QPalette::Foreground, foreground);
	//palette.setColor(this->backgroundRole(), Qt::yellow);
	//palette.setColor(this->foregroundRole(), foreground);
	//this->setPalette(palette);
	//this->update();
}

tx4_label::~tx4_label() {}

void tx4_label::setLabelText(QString newText) {
	labelText = newText;
	this->setText(newText);
}
