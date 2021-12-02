
#include "tx4_label.h"

tx4_label::tx4_label(const QString &text, const int &size, const QString &style, const QFont::Weight &weight, const Qt::AlignmentFlag &alignH, const Qt::AlignmentFlag &alignV, const QString &font, QWidget *parent) : QLabel(text, parent) {
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
	this->setAlignment(alignH | alignV);
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
void tx4_label::setLabelColor(QString newStyle) {
	this->setStyleSheet(newStyle);
}
void tx4_label::setLabelAlignment(Qt::AlignmentFlag alignH, Qt::AlignmentFlag alignV) {
	this->setAlignment(alignH | alignV);
}


tx4_key_value_label::tx4_key_value_label(const QString &key, const QString &value, const int &size, const QString &key_style, const QString &value_style, const QFont::Weight &weight, const Qt::AlignmentFlag &align, const QString &font, QWidget *parent) : QWidget(parent) {
	keyText = key;
	valueText = value;
	keyStyle = key_style;
	valueStyle = value_style;
	l_keyLabel = new tx4_label(key, size, key_style, weight, align, Qt::AlignVCenter, font);
	l_valueLabel = new tx4_label(value, size, value_style, weight, align, Qt::AlignVCenter, font);

	initLayout();
}

tx4_key_value_label::~tx4_key_value_label() {}

void tx4_key_value_label::initLayout() {
	QHBoxLayout *h_keyValueLayout = new QHBoxLayout(this);
	Util::setLayoutZero(h_keyValueLayout);

	h_keyValueLayout->addWidget(l_keyLabel);
	h_keyValueLayout->addWidget(new tx4_label(":", 10, labelStyle, QFont::Medium, Qt::AlignHCenter, Qt::AlignVCenter, "Anonymous Pro"));
	h_keyValueLayout->addSpacerItem(new QSpacerItem(5, 0, QSizePolicy::Fixed, QSizePolicy::Expanding));
	h_keyValueLayout->addWidget(new tx4_label("[", 10, braceStyle, QFont::Medium, Qt::AlignHCenter, Qt::AlignVCenter, "Anonymous Pro"));
	h_keyValueLayout->addWidget(l_valueLabel);
	h_keyValueLayout->addWidget(new tx4_label("]", 10, braceStyle, QFont::Medium, Qt::AlignHCenter, Qt::AlignVCenter, "Anonymous Pro"));
}
void tx4_key_value_label::setKeyLabelText(QString newText) {
	keyText = newText;
	l_keyLabel->setLabelText(keyText);
}
void tx4_key_value_label::setValueLabelText(QString newText) {
	valueText = newText;
	l_valueLabel->setLabelText(valueText);
}
void tx4_key_value_label::setKeyLabelColor(QString newStyle) {
	keyStyle = newStyle;
	l_keyLabel->setStyleSheet(keyStyle);
}
void tx4_key_value_label::setValueLabelColor(QString newStyle) {
	valueStyle = newStyle;
	l_valueLabel->setStyleSheet(valueStyle);
}