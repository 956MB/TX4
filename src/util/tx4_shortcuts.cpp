
#include "tx4_shortcuts.h"

tx4_shortcuts::tx4_shortcuts(QWidget *parent)
	: QObject(parent)
{
	w_parentWidget = parent;
	b_shortCutsSet = false;
}

tx4_shortcuts::~tx4_shortcuts() {}


tx4_shortcuts_main::tx4_shortcuts_main(QWidget *parent)
	: tx4_shortcuts(parent)
{

	QShortcut *shortcut_Num1 = new QShortcut(QKeySequence(Qt::Key_1), w_parentWidget);
	QShortcut *shortcut_Num2 = new QShortcut(QKeySequence(Qt::Key_2), w_parentWidget);
	QShortcut *shortcut_Num3 = new QShortcut(QKeySequence(Qt::Key_3), w_parentWidget);
	QShortcut *shortcut_Num4 = new QShortcut(QKeySequence(Qt::Key_4), w_parentWidget);
	QShortcut *shortcut_esc = new QShortcut(QKeySequence(Qt::Key_Escape), w_parentWidget);
	QShortcut *shortcut_open = new QShortcut(QKeySequence(Qt::Key_O), w_parentWidget);
	QShortcut *shortcut_load = new QShortcut(QKeySequence(Qt::Key_L), w_parentWidget);

	QObject::connect(shortcut_Num1, &QShortcut::activated, this, [=]{ emit shortcutNum1(); });
	QObject::connect(shortcut_Num2, &QShortcut::activated, this, [=]{ emit shortcutNum2(); });
	QObject::connect(shortcut_Num3, &QShortcut::activated, this, [=]{ emit shortcutNum3(); });
	QObject::connect(shortcut_Num4, &QShortcut::activated, this, [=]{ emit shortcutNum4(); });
	QObject::connect(shortcut_esc, &QShortcut::activated, this, [=]{ emit shortcutEsc(); });
	QObject::connect(shortcut_open, &QShortcut::activated, this, [=]{ emit shortcutOpen(); });
	QObject::connect(shortcut_load, &QShortcut::activated, this, [=]{ emit shortcutLoad(); });

	b_shortCutsSet = true;
}

tx4_shortcuts_main::~tx4_shortcuts_main() {}


tx4_shortcuts_viewer::tx4_shortcuts_viewer(QWidget *parent)
	: tx4_shortcuts(parent)
{
	// NOTE: Qt::SHIFT/Qt::CTRL works, not Qt::Key_Shift for some reason
	// Also: (Qt::SHIFT, Qt::Key_Left) doesnt work, (Qt::SHIFT + Qt::Key_Left) works
	QShortcut *shortcut_playPause = new QShortcut(QKeySequence(Qt::Key_Space), w_parentWidget);
	QShortcut *shortcut_skipBack = new QShortcut(QKeySequence(Qt::SHIFT + Qt::Key_Left), w_parentWidget);
	QShortcut *shortcut_skipForward = new QShortcut(QKeySequence(Qt::SHIFT + Qt::Key_Right), w_parentWidget);
	QShortcut *shortcut_skipBackInterval = new QShortcut(QKeySequence(Qt::Key_Left), w_parentWidget);
	QShortcut *shortcut_skipForwardInterval = new QShortcut(QKeySequence(Qt::Key_Right), w_parentWidget);
	QShortcut *shortcut_fullscreenViewer = new QShortcut(QKeySequence(Qt::Key_F), w_parentWidget);
	QShortcut *shortcut_navigateNextEvent = new QShortcut(QKeySequence(Qt::Key_Enter), w_parentWidget);
	QShortcut *shortcut_navigatePreviousEvent = new QShortcut(QKeySequence(Qt::Key_Backspace), w_parentWidget);

	QObject::connect(shortcut_playPause, &QShortcut::activated, this, [=]{ emit shortcutPlayPause(); });
	QObject::connect(shortcut_skipBack, &QShortcut::activated, this, [=]{ emit shortcutSkipBack(); });
	QObject::connect(shortcut_skipForward, &QShortcut::activated, this, [=]{ emit shortcutSkipForward(); });
	QObject::connect(shortcut_skipBackInterval, &QShortcut::activated, this, [=]{ emit shortcutSkipBackInterval(); });
	QObject::connect(shortcut_skipForwardInterval, &QShortcut::activated, this, [=]{ emit shortcutSkipForwardInterval(); });
	QObject::connect(shortcut_fullscreenViewer, &QShortcut::activated, this, [=]{ emit shortcutFullscreenViewer(); });
	QObject::connect(shortcut_navigateNextEvent, &QShortcut::activated, this, [=]{ emit shortcutNavigateNextEvent(); });
	QObject::connect(shortcut_navigatePreviousEvent, &QShortcut::activated, this, [=]{ emit shortcutNavigatePreviousEvent(); });

	b_shortCutsSet = true;
}

tx4_shortcuts_viewer::~tx4_shortcuts_viewer() {}
