
#include "tx4_label.h"

tx4_label::tx4_label(const QString &text, const int &size, const QString &style, const QFont::Weight &weight, const Qt::AlignmentFlag &alignH, const Qt::AlignmentFlag &alignV, const QString &font, const int &spacing, const QString &tooltip, QWidget *parent) : QLabel(text, parent) {
	//QFont lFont("Gotham Medium", size, weight); // <- not using the tesla font yet, doesnt look as good
	//QFont lFont("iNoto Sans CJK KR Medium", size, weight);
	//QFont lFont("iNioto Sagns CJK KR Medium", size, weight);
	//QFont lFont("Anonymous Pro", size, weight);
	//QFont lFont("Anonffymous Pro", size, weight);
	//QFont lFont("Segoe UI", size, weight);
	//QFont lFont("Anonymous Pro", size, weight);
	//QFont lFont("IBM Plex Sans KR", size, weight);
	QFont lFont(font, size, weight);
	lFont.setHintingPreference(QFont::PreferNoHinting);
	lFont.setStyleStrategy(QFont::PreferAntialias);
	lFont.setPixelSize(size);
	lFont.setLetterSpacing(QFont::AbsoluteSpacing, spacing);
	lFont.setWeight(weight);
	lFont.setFamily(font);
	labelText = text;
	//QString _template = "<p style=\"line-height:%1\">%2<p>";
	//QString targetText = _template.arg(1).arg(labelText);
	//QLabel *l = new QLabel(targetText, this);
	//this->setText(labelText);
	this->setFont(lFont);
	this->setStyleSheet(style);
	this->setAlignment(alignH | alignV);
	this->setAutoFillBackground(true);
	this->setWordWrap(false);
	this->setMouseTracking(true);
	this->setToolTip(tooltip);

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
void tx4_label::setLabelSize(int newSize) {
	QFont font = this->font();
	font.setPixelSize(newSize);
	this->setFont(font);
}
void tx4_label::setLabelStyle(QString newStyle) {
	this->setStyleSheet(newStyle);
}
void tx4_label::setLabelWeight(QFont::Weight weight) {
	QFont font = this->font();
	font.setWeight(weight);
	this->setFont(font);
}
void tx4_label::setLabelAlignment(Qt::AlignmentFlag alignH, Qt::AlignmentFlag alignV) {
	this->setAlignment(alignH | alignV);
}


// SELECTABLE:
tx4_selectable_label::tx4_selectable_label(const QString &text, const int &size, const QString &style, const QFont::Weight &weight, const Qt::AlignmentFlag &alignH, const Qt::AlignmentFlag &alignV, const QString &font, const int &spacing, const QString &tooltip, QWidget *parent)
	: tx4_label(text, size, style, weight, alignH, alignV, font, spacing, tooltip, parent)
	, b_labelActive(true)
	, b_labelHovered(false)
	, b_labelSelected(false)
{
}

tx4_selectable_label::~tx4_selectable_label() {}

void tx4_selectable_label::setLabelActive(bool active) {
	b_labelActive = active;
}

// MOUSE EVENTS:
void tx4_selectable_label::enterEvent(QEvent *e) {
    if (b_labelActive) {
		b_labelHovered = true;
		if (!b_labelSelected) {
			this->setLabelStyle(S_SELECTABLE_LABEL_HOVERED);
		}
        QWidget::enterEvent(e);
    }
}
void tx4_selectable_label::leaveEvent(QEvent *e) {
    if (b_labelActive) {
		b_labelHovered = false;
		if (!b_labelSelected) {
			this->setLabelStyle(S_SELECTABLE_LABEL_NORMAL);
		}
        QWidget::leaveEvent(e);
    }
}
void tx4_selectable_label::mouseReleaseEvent(QMouseEvent *e) {
    if (b_labelActive) {
		b_labelSelected = !b_labelSelected;
		this->setLabelStyle(b_labelSelected ? S_SELECTABLE_LABEL_SELECTED : S_SELECTABLE_LABEL_HOVERED);
		QWidget::mouseReleaseEvent(e);
	}
}


// KEY/VALUE:
tx4_key_value_label::tx4_key_value_label(const QString &key, const QString &value, const int &size, const QFont::Weight &weight, const Qt::AlignmentFlag &align, const bool &mouseEvents, const QString &font, QWidget *parent) : QWidget(parent) {
	keyText = key;
	valueText = value;
	m_pressed = false;
	m_acceptMouseEvents = mouseEvents;
	keyStyle = S_KEY_LABEL;
	valueStyle = S_VALUE_LABEL_NORMAL;
	l_keyLabel = new tx4_label(key, size, keyStyle, weight, align, Qt::AlignVCenter, font);
	l_valueLabel = new tx4_label(value, size, valueStyle, weight, align, Qt::AlignVCenter, font);

	initLayout();
}

tx4_key_value_label::~tx4_key_value_label() {}

void tx4_key_value_label::initLayout() {
	QHBoxLayout *h_keyValueLayout = new QHBoxLayout(this);
	Util::setLayoutZero(h_keyValueLayout);

	h_keyValueLayout->addWidget(l_keyLabel);
	h_keyValueLayout->addWidget(new tx4_label(":", 14, keyStyle, QFont::Bold, Qt::AlignHCenter, Qt::AlignVCenter));
	h_keyValueLayout->addSpacerItem(new QSpacerItem(5, 0, QSizePolicy::Fixed, QSizePolicy::Expanding));
	//h_keyValueLayout->addWidget(new tx4_label("[", 10, S_PREVIEW_BAR_BRACE, QFont::Medium, Qt::AlignHCenter, Qt::AlignVCenter));
	h_keyValueLayout->addWidget(l_valueLabel);
	//h_keyValueLayout->addWidget(new tx4_label("]", 10, S_PREVIEW_BAR_BRACE, QFont::Medium, Qt::AlignHCenter, Qt::AlignVCenter));
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

// MOUSE EVENTS:
void tx4_key_value_label::enterEvent(QEvent *e) {
	if (m_acceptMouseEvents) {
		setValueLabelColor(S_VALUE_LABEL_HOVERED);
		QWidget::enterEvent(e);
	}
}
void tx4_key_value_label::leaveEvent(QEvent *e) {
	if (m_acceptMouseEvents) {
		setValueLabelColor(S_VALUE_LABEL_NORMAL);
		QWidget::leaveEvent(e);
	}
}
void tx4_key_value_label::mousePressEvent(QMouseEvent *e) {
	if (e->button() == Qt::LeftButton) {
		if (m_acceptMouseEvents) {
			if (this->rect().contains(this->mapFromGlobal(QCursor::pos()))) {
				if (!m_pressed) {
					m_pressed = true;
					setValueLabelColor(S_VALUE_LABEL_PRESSED);
				}
				QWidget::mousePressEvent(e);
			}
		}
	}
}
void tx4_key_value_label::mouseReleaseEvent(QMouseEvent *e) {
	if (e->button() == Qt::LeftButton) {
		if (m_acceptMouseEvents) {
			if (this->rect().contains(this->mapFromGlobal(QCursor::pos()))) {
				//emit clicked();

				m_pressed = false;
				setValueLabelColor(S_VALUE_LABEL_NORMAL);
			} else {
				m_pressed = false;
				setValueLabelColor(S_VALUE_LABEL_NORMAL);
			}
			QWidget::mouseReleaseEvent(e);
		}
	}
}