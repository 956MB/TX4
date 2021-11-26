
#include "tx4_shortcuts.h"

tx4_shortcuts::tx4_shortcuts(QWidget *parent)
	: QWidget(parent) {

	QShortcut *shortcut_esc = new QShortcut(QKeySequence(Qt::Key_Escape), this);
	QShortcut *shortcut_selectMode = new QShortcut(QKeySequence(Qt::Key_S), this);

	connect(shortcut_esc, &QShortcut::activated, this, [=]{ emit signal_esc(); });
	connect(shortcut_selectMode, &QShortcut::activated, this, [=]{ emit signal_selectMode(); });
}

tx4_shortcuts::~tx4_shortcuts() {}
