
#include "tx4_shortcuts.h"

tx4_shortcuts::tx4_shortcuts(QWidget *parent)
	: QWidget(parent) {

	QShortcut *shortcut_esc = new QShortcut(QKeySequence(Qt::Key_Escape), this);
	//QShortcut *shortcut_selectMode = new QShortcut(QKeySequence(Qt::Key_S), this);
	QShortcut *shortcut_open = new QShortcut(QKeySequence(Qt::Key_O), this);
	QShortcut *shortcut_load = new QShortcut(QKeySequence(Qt::Key_L), this);

	connect(shortcut_esc, &QShortcut::activated, this, [=]{ emit signal_esc(); });
	connect(shortcut_open, &QShortcut::activated, this, [=]{ emit signal_open(); });
	connect(shortcut_load, &QShortcut::activated, this, [=]{ emit signal_load(); });
	//connect(shortcut_selectMode, &QShortcut::activated, this, [=]{ emit signal_selectMode(); });
}

tx4_shortcuts::~tx4_shortcuts() {}
