#ifndef TX4_DEFINES_H
#define TX4_DEFINES_H

// TX4
#define START_W				1000
#define START_H				650
#define MIN_W				800
#define MIN_H				700
#define TITLEBAR_BUTTON_W	40 // windows: 46
constexpr auto S_STACKED_WIDGET = "background-color: none; border: none; outline: none;";

// DIR
constexpr auto TESLA_DRIVE	 = "C:/Users/infga/Downloads/TeslaCam";
constexpr auto ROOT			 = "./";
constexpr auto CAM_FOLDER	 = "TeslaCam";
constexpr auto CAPTION		 = "Select root of \"TeslaCam\" folder...";
constexpr auto SAVED_FOLDER	 = "SavedClips";
constexpr auto SENTRY_FOLDER = "SentryClips";
constexpr auto THUMB_PNG	 = "thumb.png";

constexpr auto ICONS_TOOLBAR_PLAY						= ":/icons/play_icon.png";
constexpr auto ICONS_IMPORT								= ":/icons/import_icon.png";
constexpr auto ICONS_DOTS								= ":/icons/dots_icon.png";
constexpr auto ICONS_PLUS								= ":/icons/plus_icon.png";
constexpr auto ICONS_MINUS								= ":/icons/minus_icon.png";
constexpr auto ICONS_ARROW_LEFT							= ":/icons/icons8-expand-arrow-left.png";
constexpr auto ICONS_ARROW_LEFT_HOVER					= ":/icons/icons8-expand-arrow-left-hover.png";
constexpr auto ICONS_ARROW_RIGHT						= ":/icons/icons8-expand-arrow-right.png";
constexpr auto ICONS_ARROW_RIGHT_HOVER					= ":/icons/icons8-expand-arrow-right-hover.png";
constexpr auto ICONS_CONTROL_BAR_PLAY					= ":/icons/play.png";
constexpr auto ICONS_CONTROL_BAR_PAUSE					= ":/icons/pause.png";
constexpr auto ICONS_CONTROL_BAR_SKIP_BACK				= ":/icons/skip_back.png";
constexpr auto ICONS_CONTROL_BAR_SKIP_FORWARD			= ":/icons/skip_forward.png";
constexpr auto ICONS_CONTROL_BAR_FULLSCREEN				= ":/icons/fullscreen.png";
constexpr auto ICONS_CONTROL_BAR_PLAY_CURVED			= ":/icons/play_curved.png";
constexpr auto ICONS_CONTROL_BAR_SKIP_BACK_CURVED		= ":/icons/skip_back_curved.png";
constexpr auto ICONS_CONTROL_BAR_SKIP_FORWARD_CURVED	= ":/icons/skip_forward_curved.png";
constexpr auto ICONS_CONTROL_BAR_FULLSCREEN_CURVED		= ":/icons/fullscreen_curved.png";
constexpr auto ICONS_BAR								= ":/icons/bar.png";
constexpr auto ICONS_BACK_ARROW							= ":/icons/back_arrow_2.png";
constexpr auto ICONS_LAYOUT_L3							= ":/icons/L3.png";
constexpr auto ICONS_LAYOUT_L4							= ":/icons/L4.png";
constexpr auto ICONS_LAYOUT_L13V						= ":/icons/L13V.png";
constexpr auto ICONS_LAYOUT_L13H						= ":/icons/L13H.png";
constexpr auto ICONS_LAYOUT_L121V						= ":/icons/L121V.png";
constexpr auto ICONS_LAYOUT_L121H						= ":/icons/L121H.png";

constexpr auto S_BLANK						= "background-color: none; border: none; outline: none;";
constexpr auto S_KEY_LABEL					= "background-color: none; border: none; color: #ffffff;";
constexpr auto S_VALUE_LABEL_NORMAL			= "background-color: none; border: none; color: #7b7b7b;";
constexpr auto S_VALUE_LABEL_HOVERED		= "background-color: none; border: none; color: #5a5a5a;"; // TODO: use color for layout icon
constexpr auto S_VALUE_LABEL_PRESSED		= "background-color: none; border: none; color: #3a3a3a;";
constexpr auto S_SELECTABLE_LABEL_NORMAL	= "background-color: none; border: none; color: #5e5e5e;";
constexpr auto S_SELECTABLE_LABEL_HOVERED	= "background-color: none; border: none; color: #f2f2f2;";
constexpr auto S_SELECTABLE_LABEL_SELECTED	= "background-color: none; border: none; color: #f2f2f2;";

#define CLIP_LEN		59000 // TODO: temp duration value for all clips, because of qmediaplkayer metadata problem, 59000ms = 59s
#define PREVIEW_W		208
#define PREVIEW_H		117
#define LIST_ITEM_H		45
#define PAGE_ACTIONS_H	35
#define CORNER_ANGLE	18
#define BORDER_W		3
#define OUTER_MARGIN	30

// EVENT
constexpr auto EVENT_JSON = "/event.json";

// CONTROL_BAR //
#define CONTROL_BAR_H	55
#define TIMELINE_MIN	0
#define TIMELINE_MAX	3
#define STEPS			59
constexpr auto S_CONTROL_BAR_BUTTON_NORMAL	= "background-color: none; border: none; outline: none;";
constexpr auto S_CONTROL_BAR_BODY			= "background-color: black; border: none; outline: none;";
constexpr auto S_BUTTON_CONTAINER_BODY		= "background-color: black; border: none; outline: none;";
constexpr auto S_TIMELINE_BODY				= "background-color: black; border: none; outline: none;";
constexpr auto S_TIMELINE_CONTAINER			= "background-color: black; border: none; outline: none;";
constexpr auto S_TIME_LABEL					= "background-color: none; border: none; outline: none; color: white;";
constexpr auto S_TIMELINE_SLIDER			= "QSlider::groove:horizontal { background: black; } QSlider::handle:horizontal { width: 8px; border-radius: 4px; margin-top: 7px; margin-bottom: 6px; background: #f6f6f6; } QSlider::add-page:horizontal { background: rgba(255,255,255,50); height: 3px; margin-top: 10px; margin-bottom: 9px; position: absolute; } QSlider::sub-page:horizontal { background: #f6f6f6; height: 3px; margin-top: 10px; margin-bottom: 9px; position: absolute; }";
//constexpr auto S_TIMELINE_SLIDER			= "QSlider::groove:horizontal { background: black; } QSlider::handle:horizontal { width: 3px; background: #f6f6f6; border-right: 3px solid black; } QSlider::add-page:horizontal { background: rgba(255,255,255,60); height: 5px; margin: 9px 0; position: absolute; right: 3px; } QSlider::sub-page:horizontal { background: #f6f6f6; height: 5px; margin: 9px 0; position: absolute; left: 3px }";
//constexpr auto enabled_slider				= "QSlider::groove:horizontal { height: 7px; background: rgba(255,255,255,50); margin: 2px 0; border-radius: 1px; } QSlider::handle:horizontal { width: 40px; margin: -3px 0 } QSlider::add-page:horizontal { margin: 1px 0; background: rgba(255,255,255,255); border-radius: 2px; }";

// INFO BAR
#define INFO_BAR_H 55
constexpr auto S_INFO_BAR_BODY				= "background-color: black; border: none; outline: none;";
constexpr auto S_INFO_BAR_BODY_TRANSPARENT	= "background-color: none; border: none; outline: none;";
constexpr auto S_INFO_BAR_TEXT_VALUE		= "background-color: black; border: none; outline: none; color: #ffffff";

// VIEW
#define VIEW_MIN_W		304
#define VIEW_MIN_H		171
#define VIEW_START_H	50
#define VIEW_W			160
#define VIEW_H			112
#define VIEW_L3_DIVIDE	5
#define VIEW_RATIO		3/4
constexpr auto S_VIEW_NORMAL		= "background-color: black; border: none; border-radius: 6px; outline: none;";
constexpr auto S_VIEW_SELECTED		= "background-color: rgba(0,0,0,75); border: none; border-radius: 6px; outline: none;";
constexpr auto S_VIEW_TEXT_LABEL	= "background-color: none; border: none; outline: none; color: white;";

// VIEWER
constexpr auto S_VIEWER_SCREEN	= "background-color: none; border: none; outline: none;";

// VIEWS LAYOUT
constexpr auto S_LAYOUT_BODY	= "background-color: rgba(17, 17, 17, 255); border: none; border-radius: 8px; outline: none;";
constexpr auto S_STACK_BODY		= "background-color: none; border: none; border-radius: 8px; outline: none;";

// PREVIEW BAR
#define BAR_H	25
constexpr auto S_PREVIEW_BAR_NORMAL = "background-color: none; border: none; outline: none;"; // rgba(70,70,70,245)
//constexpr auto barStyleHover					= "background-color: rgba(70,70,70,245); border-left: 3px solid #8f8f8f; border-top: 0px solid #8f8f8f; border-right: 3px solid #8f8f8f; border-bottom: 3px solid #8f8f8f; outline: none;";
//constexpr auto barStyleHoverTop				= "background-color: rgba(70,70,70,245); border-left: 3px solid #8f8f8f; border-top: 3px solid #8f8f8f; border-right: 3px solid #8f8f8f; border-bottom: 0px solid #8f8f8f; outline: none;";
//constexpr auto queue_barStyleHoverTop			= "background-color: rgba(70,70,70,245); border-left: 3px solid #f6ed19; border-top: 3px solid #f6ed19; border-right: 3px solid #f6ed19; border-bottom: 0px solid #f6ed19; outline: none;";
constexpr auto S_PREVIEW_BAR_HOVER_SMODE		= "background-color: rgba(70,70,70,255); border-left: 3px solid #f6f6f6; border-top: 0px solid #f6f6f6; border-right: 3px solid #f6f6f6; border-bottom: 3px solid #f6f6f6; outline: none;";
constexpr auto S_PREVIEW_BAR_HOVER_SMODE_TOP	= "background-color: rgba(70,70,70,255); border-left: 3px solid #f6f6f6; border-top: 3px solid #f6f6f6; border-right: 3px solid #f6f6f6; border-bottom: 0px solid #f6f6f6; outline: none;";
constexpr auto S_PREVIEW_BAR_TEXT				= "background-color: none; border: none; outline: none; color: rgba(255,255,255,220)";
constexpr auto S_PREVIEW_BAR_BRACE				= "background-color: none; border: none; outline: none; color: rgba(255,255,255,120)";

// PAGE ACTIONS
#define ACTIONS_H	65
constexpr auto S_ACTIONS_BODY		= "background-color: none; border: none; outline: none;";
constexpr auto S_ACTIONS_BODY_INNER = "background-color: none; border-bottom: 1px solid #4c4a48; outline: none;";
constexpr auto S_ACTIONS_TEXT		= "background-color: none; border: none; outline: none;";
//constexpr auto actionsKeyStyle	= "background-color: none; border: none; color: #ffffff; outline: none;";
//constexpr auto actionsValueStyle	= "background-color: none; border: none; color: #909090; outline: none;";

// EVENTS GROUP /TITLE
constexpr auto S_GROUP_BODY_NORMAL			= "background-color: none; border: none; outline: none;";
constexpr auto S_GROUP_TITLE_NORMAL			= "background-color: none; border: none; color: #909090; outline: none;";
constexpr auto S_GROUP_TITLE_INFO_NORMAL	= "background-color: none; border: none; color: #5b5b5b; outline: none;";
constexpr auto S_GROUP_TITLE_INFO_SELECTED	= "background-color: none; border: none; color: #ffffff; outline: none;";

// EVENTS PAGE
constexpr auto S_EVENTS_PAGE_BODY			= "background-color: none; border: none; outline: none;";
constexpr auto S_EVENTS_PAGE_EMPTY_STATE	= "background-color: none; border: none; outline: none;";
constexpr auto S_EVENTS_PAGE_STACK			= "background-color: none; border: none; outline: none;";

// EVENTS SECTION
#define SECTION_H			135
#define CLICK_SCROLL_DIFF	250
constexpr auto S_TITLE_LABEL				= "background-color: none; color: white;";
constexpr auto S_SUB_LABEL_OFF				= "background-color: none; color: rgba(255,255,255,60);";
constexpr auto S_EVENTS_SECTION_BODY		= "background-color: none; border: none; outline: none;";
constexpr auto S_EVENTS_SECTION_EMPTY_STATE = "background-color: none; border: none; outline: none;";
constexpr auto S_EVENTS_SECTION_SCROLL_BODY = "background-color: none; border: none; outline: none;";

// QUEUE ENTRY
constexpr auto blankStyle				= "background-color: none; border: none; outline: none;";
constexpr auto S_QUEUE_LABEL_NORMAL		= "background-color: black; color: rgba(255,255,255,140);";
constexpr auto S_QUEUE_LABEL_HOVER		= "background-color: black; color: rgba(255,246,0,255);";
constexpr auto S_QUEUE_LABEL_DISABLED	= "background-color: rgba(0,0,0,150); color: rgba(255,255,255,0);";

// EVENT PREVIEW
// yellows
constexpr auto S_QUEUE_HOVER_SMODE		= "background-color: rgba(255,255,255,20); border: 2px solid #f6ed19; outline: none;";
constexpr auto S_QUEUE_BAR_HOVER		= "background-color: rgba(70,70,70,245); border-left: 2px solid #f6ed19; border-top: 0px solid #f6ed19; border-right: 2px solid #f6ed19; border-bottom: 2px solid #f6ed19; outline: none;";
constexpr auto S_QUEUE_SELECT_IDX_LABEL = "background-color: none; border: none; outline: none; color: #f6ed19;";
// whites
//constexpr auto S_QUEUE_HOVER_SMODE			= "background-color: rgba(255,255,255,20); border: 2px solid rgba(255,255,255,255); outline: none;";
//constexpr auto S_QUEUE_BAR_HOVER				= "background-color: rgba(70,70,70,245); border-left: 2px solid rgba(255,255,255,100); border-top: 0px solid rgba(255,255,255,100); border-right: 2px solid rgba(255,255,255,100); border-bottom: 2px solid rgba(255,255,255,100); outline: none;";
//constexpr auto S_QUEUE_SELECT_IDX_LABEL		= "background-color: none; border: none; outline: none; color: rgba(255,255,255,255);";
constexpr auto S_THUMB_UNAVAILABLE_LABEL		= "background-color: none; border: none; outline: none; color: rgba(255,255,255,50);";
constexpr auto S_SELECT_IDX_LABEL				= "background-color: none; border: none; outline: none; color: white;";
constexpr auto S_SELECT_IDX_SCREEN				= "background-color: none; border: none; outline: none;";
constexpr auto S_META_DATA_SCREEN				= "background-color: none; border: none; outline: none;"; // rgba(255,255,255,15)
constexpr auto S_EVENT_PREVIEW_NORMAL			= "background-color: none; border: none; border-radius: 0px; outline: none;";
constexpr auto S_EVENT_PREVIEW_HOVER			= "background-color: black; border: 1px solid #424242; border-radius: 0px; outline: none;";
constexpr auto S_EVENT_PREVIEW_SELECTED			= "background-color: black; border: 2px solid #ffffff; border-radius: 0px; outline: none;";
constexpr auto S_EVENT_PREVIEW_CONTENT_NORMAL	= "background-color: none; border: none; border-radius: 0px; outline: none;";
constexpr auto S_EVENT_PREVIEW_CONTENT_HOVER	= "background-color: none; border-left: 2px solid white; border-top: 2px solid white; border-right: 2px solid white; border-bottom: 0px solid white; outline: none;";

// LIST ITEM
constexpr auto S_LIST_ITEM_TEXT_EMPTY		= "background-color: none; border: none; outline: none; color: #a1a1a1";
constexpr auto S_LIST_ITEM_TEXT_NORMAL		= "background-color: none; border: none; outline: none; color: #a1a1a1";
constexpr auto S_LIST_ITEM_TEXT_HOVER		= "background-color: rgba(22, 22, 22, 255); border: none; outline: none; color: #ffffff";
constexpr auto S_LIST_ITEM_TEXT_SELECTED	= "background-color: rgba(40, 40, 40, 255); border: none; outline: none; color: #ffffff";
constexpr auto S_LIST_ITEM_EMPTY			= "background-color: none; border: none; border-radius: 4px; outline: none;";
constexpr auto S_LIST_ITEM_NORMAL			= "background-color: none; border: none; border-radius: 4px; outline: none;";
constexpr auto S_LIST_ITEM_HOVER			= "background-color: rgba(22, 22, 22, 255); border: none; border-radius: 4px; outline: none;"; // 111111
constexpr auto S_LIST_ITEM_SELECTED			= "background-color: rgba(40, 40, 40, 255); border: none; border-radius: 4px; outline: none;"; // 1e1e1e
constexpr auto S_LIST_ITEM_CONTENT_NORMAL	= "background-color: none; border: none; outline: none;";
constexpr auto S_LIST_ITEM_CONTENT_HOVER	= "background-color: none; border-left: 2px solid white; border-top: 2px solid white; border-right: 2px solid white; border-bottom: 0px solid white; outline: none;";

// LIST BUTTON
constexpr auto S_LIST_BUTTON_INNER_STACK_NORMAL		= "background-color: none; border: none; outline: none;";
constexpr auto S_LIST_BUTTON_INNER_STACK_HOVERED	= "background-color: none; border: none; outline: none;"; // rgba(255,255,255,15)
constexpr auto S_LIST_BUTTON_INNER_LABEL_NORMAL		= "background-color: none; border: none; outline: none; color: #a1a1a1;";
constexpr auto S_LIST_BUTTON_INNER_LABEL_HOVERED	= "background-color: none; border: none; outline: none; color: #ffffff;";
constexpr auto S_LIST_BUTTON_INNER_LABEL_DISABLED	= "background-color: none; border: none; outline: none; color: #2c2c2c;";
constexpr auto S_LIST_BUTTON_ICON_NORMAL			= "background-color: none; border: none; outline: none;";
//constexpr auto S_TOOLBAR_BUTTON_ICON_HOVERED		= "background-color: rgba(255,255,255,15); border: none; outline: none;";
//constexpr auto S_TOOLBAR_BUTTON_ICON_SELECTED		= "background-color: none; border-bottom: 4px solid #4c4a48; outline: none;";
//constexpr auto S_TOOLBAR_BUTTON_ICON_DISABLED		= "background-color: none; border: none; outline: none;";

// TOOLBAR
#define TOOLBAR_H 55
constexpr auto S_TOOLBAR_BODY	= "background-color: none; border-bottom: 1px solid #4c4a48; outline: none;"; //1c1c1c
//constexpr auto S_TOOLBAR_BODY = "background-color: #212121; border: none; outline: none;";

// TOOLBAR BUTTON
constexpr auto S_TOOLBAR_BUTTON_LABEL_NORMAL	= "background-color: none; border: none; outline: none; color: #2c2c2c;";
constexpr auto S_TOOLBAR_BUTTON_LABEL_SELECTED	= "background-color: none; border: none; outline: none; color: #ffffff;"; // #dbdddc
constexpr auto S_TOOLBAR_BUTTON_LABEL_PRESSED	= "background-color: none; border: none; outline: none; color: #909090;";
constexpr auto S_TOOLBAR_BUTTON_LABEL_DISABLED	= "background-color: none; border: none; outline: none; color: rgba(255,255,255,100);";
constexpr auto S_TOOLBAR_BUTTON_NORMAL			= "background-color: none; border: none; outline: none;";
constexpr auto S_TOOLBAR_BUTTON_SELECTED		= "background-color: none; border-bottom: 4px solid #4c4a48; outline: none;";
constexpr auto S_TOOLBAR_BUTTON_DISABLED		= "background-color: none; border: none; outline: none;";

// TOOLBAR BUTTON ICON
constexpr auto S_INNER_STACK						= "background-color: none; border: none; outline: none;";
constexpr auto S_TOOLBAR_BUTTON_INNER_LABEL_NORMAL	= "background-color: none; border: none; outline: none; color: #a1a1a1;";
constexpr auto S_TOOLBAR_BUTTON_ICON_NORMAL			= "background-color: none; border: none; outline: none;";
constexpr auto S_TOOLBAR_BUTTON_ICON_HOVERED		= "background-color: rgba(255,255,255,15); border: none; outline: none;";
constexpr auto S_TOOLBAR_BUTTON_ICON_SELECTED		= "background-color: none; border-bottom: 4px solid #4c4a48; outline: none;";
constexpr auto S_TOOLBAR_BUTTON_ICON_DISABLED		= "background-color: none; border: none; outline: none;";

// NAV BUTTON
//constexpr auto extraLabelStyle		= "background-color: none; border: none; outline: none; color: rgba(255,255,255,70);";
//constexpr auto buttonLabelStyle		= "background-color: none; border: none; outline: none; color: white;";
//constexpr auto buttonLabelStyleDisabled = "background-color: none; border: none; outline: none; color: rgba(255,255,255,100);";
//constexpr auto barStyleNormal			= "background-color: rgba(255,255,255,50); border: none; outline: none;";
constexpr auto S_NAV_BUTTON_NORMAL		= "background-color: black; border: none; outline: none;";
constexpr auto S_NAV_BUTTON_HOVER		= "background-color: #222222; border: none; outline: none;";
constexpr auto S_NAV_BUTTON_DISABLED	= "background-color: #222222; border: none; outline: none;";
//constexpr auto S_NAV_BUTTON_NORMAL	= "background-color: #222222; border: none; outline: none;";
//constexpr auto S_NAV_BUTTON_HOVER		= "background-color: #4e4e4e; border: none; outline: none;";
//constexpr auto S_NAV_BUTTON_DISABLED	= "background-color: #222222; border: none; outline: none;";

// META INFO
constexpr auto S_META_WHITE		= "background-color: none; border: none; outline: none; color: white;";
constexpr auto S_META_BLUE		= "background-color: none; border: none; outline: none; color: rgba(90, 157, 230, 255);";
constexpr auto S_META_ORANGE	= "background-color: none; border: none; outline: none; color: rgba(232, 160, 104, 255);";

enum class GroupLayout
{
	Grid=0,
	List=1
};

enum class GroupSort
{
	None=0,
	Date=1,
	City=2,
	Reason=3,
	Size=4,
	Length=5
};

enum class ButtonState
{
	Disabled=0,
	Enabled=1,
	Hovered=2,
	Selected=3,
	Hidden=4
};

enum class PreviewState
{
	Disabled=0,
	Normal=1,
	Hovered=2,
	Selected=3
};

// L3:
//		|----------------------|
//		| ..0..          ##1## |
//		| .....          ##### |
//		|                      |
//		|                      |
//		|                      |
//		| ##2##          ##3## |
//		| #####          ##### |
//		|----------------------|
// L4:
//		|----------------------|
//		| #########  ######### |
//		| ####0####  ####1#### |
//		| #########  ######### |
//		|                      |
//		| #########  ######### |
//		| ####2####  ####3#### |
//		| #########  ######### |
//		|----------------------|
// L13V:
//		|----------------------|
//		| #################### |
//		| #########0########## |
//		| #################### |
//		|                      |
//		| ###### ###### ###### |
//		| ##1### ##2### ##3### |
//		| ###### ###### ###### |
//		|----------------------|
// L13H:
//		|----------------------|
//		| ########### ######## |
//		| ########### ###1#### |
//		| ########### ######## |
//		| ###########          |
//		| ########### ######## |
//		| #####0##### ###2#### |
//		| ########### ######## |
//		| ###########          |
//		| ########### ######## |
//		| ########### ###3#### |
//		| ########### ######## |
//		|----------------------|
// L121V:
//		|----------------------|
//		| #################### |
//		| #########0########## |
//		| #################### |
//		|                      |
//		| #########  ######### |
//		| ####1####  ####2#### |
//		| #########  ######### |
//
//		| #################### |
//		| #########3########## |
//		| #################### |
//		|----------------------|
// L121H:
//		|--------------------------------|
//		| #########  ########  ######### |
//		| #########  ###1####  ######### |
//		| #########  ########  ######### |
//		| #########  ########  ######### |
//		| #########  ########  ######### |
//		| #####0###            ######### |
//		| #########  ########  ######### |
//		| #########  ########  ######### |
//		| #########  ########  ######### |
//		| #########  ###3####  ######### |
//		| #########  ########  ######### |
//		|--------------------------------|

enum class ViewsLayout
{
	L3=0,
	L4=1,
	L13V=2,
	L13H=3,
	L121V=4,
	L121H=5
};

#endif // TX4_DEFINES_H