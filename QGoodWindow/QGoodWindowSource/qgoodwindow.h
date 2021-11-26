/*
The MIT License (MIT)

Copyright © 2018-2021 Antonio Dias

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
SOFTWARE.
*/

#ifndef QGOODWINDOW_H
#define QGOODWINDOW_H

#include <QtCore>
#include <QtGui>
#include <QtWidgets>

#ifdef QGOODWINDOW

#ifdef Q_OS_WIN
class WinWidget;
class NativeEventFilter;
#endif

#if defined Q_OS_WIN || defined Q_OS_LINUX
class Shadow;
#endif

#endif

/** **QGoodWindow** class contains the public API's to control the behavior of the customized window.
 *
 * On Windows, **QGoodWindow** class inherits from `QMainWindow` which is used as a widget,
 * then a native window is created, a `WinWidget` fill this native window and finally the
 * *QGoodWindow* widget covers the `WinWidget` using layouts.
 *
 * On Linux and macOS the **QGoodWindow** behaves like a frameless `QMainWindow`.
 */
class QGoodWindow : public QMainWindow
{
    Q_OBJECT
public:

    enum DdeCommand {
        DDEOpen = 0x0001,  // < open a file via explorer
        DDENew = 0x0002,   // < create a new file via explorer
        DDEPrint = 0x0004, // < print a file via explorer
    };
    Q_DECLARE_FLAGS(DdeCommands, DdeCommand)

    /** Constructor of *QGoodWindow*.
    *
    * On Windows creates the native window, the `WinWidget`, turns the `QMainWindow` as
    * a widget, creates the shadow, initialize default values and calls the `QMainWindow`
    * parent constructor.
    *
    * On Linux creates the frameless `QMainWindow`, use the shadow only to create resize borders,
    * and the real shadow is draw by current Linux window manager.
    *
    * On macOS creates a `QMainWindow` with full access to the title bar,
    * and hide native minimize, zoom and close buttons.
    */
    explicit QGoodWindow(QWidget *parent = nullptr, const QColor &clear_color = QColor(Qt::white));

    /** Destructor of *QGoodWindow*. */
    ~QGoodWindow();

    //Functions
    /** Returns the window id of the *QGoodWindow*. */
    WId winId() const;

public slots:
    /*** QGoodWindow functions begin ***/

    /** On Windows, Linux and macOS, returns the actual title bar height, on other OSes returns 0. */
    int titleBarHeight() const;

    /** On Windows, Linux and macOS, return the actual icon width, on other OSes returns 0. */
    int iconWidth() const;

    /** On Windows, Linux and macOS, returns the left margin of the customized title bar, on other OSes returns 0. */
    int leftMargin() const;

    /** On Windows, Linux and macOS, returns the right margin of the customized title bar, on other OSes returns 0. */
    int rightMargin() const;

    /** Set the tile bar height, icon width, left and right margins of the customized title bar. */
    void setMargins(int title_bar_height, int icon_width, int left, int right);

    /** Set the mask for the left margin of the customized title bar. */
    void setLeftMask(const QRegion &mask);

    /** Set the mask for the right margin of the customized title bar. */
    void setRightMask(const QRegion &mask);

    /** Get the size that should be the size of the mask on the left margin of the customized title bar. */
    QSize leftMaskSize() const;

    /** Get the size that should be the size of the mask on the right margin of the customized title bar. */
    QSize rightMaskSize() const;

    /*** QGoodWindow functions end ***/

    /** Set fixed size for *QGoodWindow* to width \e w and height \e h. */
    void setFixedSize(int w, int h);

    /** Set fixed size for *QGoodWindow* to \e size. */
    void setFixedSize(const QSize &size);

    /** Returns the geometry for *QGoodWindow* including extended frame and excluding shadow. */
    QRect frameGeometry() const;

    /** Same as *frameGeometry()*. */
    QRect geometry() const;

    /** Geometry excluding position, position is always `QPoint(0, 0)`. */
    QRect rect() const;

    /** Position of the window on screen. */
    QPoint pos() const;

    /** Size of the window on screen. */
    QSize size() const;

    /** X position of the window on screen. */
    int x() const;

    /** Y position of the window on screen. */
    int y() const;

    /** Width of the window. */
    int width() const;

    /** Height of the window. */
    int height() const;

    /** Move the window to \e x - \e y coordinates. */
    void move(int x, int y);

    /** Move the window to \e pos. */
    void move(const QPoint &pos);

    /** Resize the window to \e width - \e height size. */
    void resize(int width, int height);

    /** Resize the window to \e size. */
    void resize(const QSize &size);

    /** Set geometry to pos \e x - \e y, width \e w and height \e h. */
    void setGeometry(int x, int y, int w, int h);

    /** Set geometry to \e rect. */
    void setGeometry(const QRect &rect);

    /** Activates the *QGoodWindow*. */
    void activateWindow();

    /** Shows the *QGoodWindow*. */
    void show();

    /** Shows or restore the *QGoodWindow*. */
    void showNormal();

    /** Shows or maximize the *QGoodWindow*. */
    void showMaximized();

    /** Minimize the *QGoodWindow*. */
    void showMinimized();

    /** Turns the *QGoodWindow* into full screen mode. Including the title bar. */
    void showFullScreen();

    /** Hide the *QGoodWindow*. */
    void hide();

    /** Close the *QGoodWindow*. */
    void close();

    /** Returns if the *QGoodWindow* is visible or not. */
    bool isVisible() const;

    /** Returns if the *QGoodWindow* is enabled or not. */
    bool isEnabled() const;

    /** Returns if the *QGoodWindow* is the foreground window or not. */
    bool isActiveWindow() const;

    /** Returns if the *QGoodWindow* is maximized or not. */
    bool isMaximized() const;

    /** Returns if the *QGoodWindow* is minimized or not. */
    bool isMinimized() const;

    /** Returns if the *QGoodWindow* is in full screen mode or not. */
    bool isFullScreen() const;

    /** Returns the *QGoodWindow* state. */
    Qt::WindowStates windowState() const;

    /** Sets the state of the *QGoodWindow* to \e state. */
    void setWindowState(Qt::WindowStates state);

    /** Returns the window handle of the *QGoodWindow*. */
    QWindow *windowHandle() const;

    /** Returns the opacity of the *QGoodWindow*. */
    qreal windowOpacity() const;

    /** Sets the opacity of the *QGoodWindow* to \e level. Where 0.0 is fully transparent and 1.0 fully opaque. */
    void setWindowOpacity(qreal level);

    /** Returns the title of the *QGoodWindow*. */
    QString windowTitle() const;

    /** Sets the title of the *QGoodWindow* to \e title. */
    void setWindowTitle(const QString &title);

    /** Returns the icon of the *QGoodWindow*. */
    QIcon windowIcon() const;

    /** Sets the icon of the *QGoodWindow* to \e icon. */
    void setWindowIcon(const QIcon &icon);

protected:
    //Functions
    bool event(QEvent *event);
    bool eventFilter(QObject *watched, QEvent *event);
    bool nativeEvent(const QByteArray &eventType, void *message, long *result);

    // —— events ———————————————————————————
    /**
    * reimpl as DDE events come as windows events and are not translated by Qt.
    */
    //virtual bool winEvent(MSG *message, long *result);
   
    // —— helpers for the file registration ——————————————————
    /**
    * virtual function that must be implemented by the derived class to react to the open command
    * from Windows.
    *
    * @param filePath file that was selected in the explorer
    */
    virtual void ddeOpenFile(const QString& filePath);
   
    /**
    * virtual function that must be implemented by the derived class to react to the new command
    * from Windows.
    *
    * @param filePath file that was selected in the explorer
    */
    virtual void ddeNewFile(const QString& filePath);
   
    /**
    * virtual function that must be implemented by the derived class to react to the print command
    * from Windows.
    *
    * @param filePath file that was selected in the explorer
    */
    virtual void ddePrintFile(const QString& filePath);
   
    /**
    * virtual function that must be implemented by get custom DDE commands from the explorer. If, e.g.
    * a print or copy command should be available in explorer and they are registered via registerCommand,
    * this function is called.
    *
    * @param command name of the command
    * @param params parameter string, containing the hole stuff, also " and commas.
    *
    * @note a command like this [compare("%1")] will result in the parameters:
    command = "compare";
    params = "\"<filepath>\"";
    */
    virtual void executeUnknownDdeCommand(const QString& command, const QString& params);
   
    /**
    * Call this method to register the file type in Windows. It creates the default command
    * which means the app is started with the file to open as parameter. If @arg registerForDDE
    * is true, the DDE events are also created so the opening of a file is done in typical MDI
    * behavior (all files open in the same app).
    *
    * @param documentId id of the document, typically <Application>.Document —> see in registry, e.g. "GiMdi.Document"
    * @param fileTypeName free name of the file type, e.g. "MDI Text Editor Document"
    * @param fileExtension File extension, including the dot (e.g. ".gidoc")
    * @param appIconIndex index of the app icon to use for the file in the windows explorer, typically the application icon
    * @param registerForDDE true if DDE should be used (typical for MDI apps), typically false for SDI apps.
    * @param commands a combination of the commands to install.
    *
    * @note If more then the default commands are needed, then subsequent calls of registerCommand are needed.
    *
    * @note DDEOpen leads to the DDE command: [open("%1")]
    DDENew leads to the DDE command: [new("%1")]
    DDEPrint leads to the DDE command: [print("%1")]
    */
    void registerFileType(const QString& documentId,
            const QString& fileTypeName,
            const QString& fileExtension,
            qint32 appIconIndex = 0,
            bool registerForDDE = false,
            DdeCommands commands = DDEOpen);
   
    /**
    * registers one command for a given file type. It is called for the predefined DDE command
    * types from registerFileType. if more then the normal commands are needed, it can be called
    * in addition to registerFileType.
    *
    * @code
    MainWindow::MainWindow(QWidget *parent, Qt::WindowFlags flags) :
    DocumentWindow(parent, flags)
    {
        …
        registerFileType("GiMdi.Document", "MDI Text Editor Document", ".gidoc", 0, true);
        registerCommand("fancyCommand", "GiMdi.Document", "-fancy %1", "[fancy(\"%1\")]");
        enableShellOpen();
        …
    }
    @endcode
    */
    void registerCommand(const QString& command,
            const QString& documentId,
            const QString cmdLineArg = QString::null,
            const QString ddeCommand = QString::null);
   
    /**
    * Call this method to enable the user to open data files associated with your application
    * by double-clicking the files in the windows file manager.
    *
    * Use it together with registerFileType to register the fspezified file types or provida a
    * registry file (*.reg) which does this.
    */
    void enableShellOpen();

private:

    // —— private helpers ————————————————————————
    /**
    * implementation of the WM_DDE_INITIATE windows message
    */
    bool ddeInitiate(MSG* message, long* result);
   
    /**
    * implementation of the WM_DDE_EXECUTE windows message
    */
    bool ddeExecute(MSG* message, long* result);
   
    /**
    * implementation of the WM_DDE_TERMINATE windows message
    */
    bool ddeTerminate(MSG* message, long* result);
   
    /**
    * Sets specified value in the registry under HKCU\Software\Classes, which is mapped to HKCR then.
    */
    bool SetHkcrUserRegKey(QString key, const QString& value, const QString& valueName = QString::null);
   
    /**
    * this method is called to do the DDE command handling. It does argument splitting and then calls
    * ddeOpenFile, ddeNewFile, ddePrintFile or executeUnknownDdeCommand.
    */
    void executeDdeCommand(const QString& command, const QString& params);
   
    // —— members ——————————————————————————-
    bool m_registerForDDE; //< used to identfy, if the dde commands should be written to the registry*/
    QString m_appAtomName; /**< the name of the application, without file extension*/
    QString m_systemTopicAtomName; /**< the name of the system topic atom, typically "System"*/
    ATOM m_appAtom; /**< The windows atom needed for DDE communication*/
    ATOM m_systemTopicAtom; /**< The windows system topic atom needed for DDE communication*/
    // —— not allowed members ——————————————————————-

#ifdef QGOODWINDOW
#ifdef Q_OS_WIN
    //Functions
    static LRESULT WndProc(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam);
    void handleActivation();
    void handleDeactivation();
    void enableCaption();
    void disableCaption();
    void frameChanged();
    void sizeMoveWindow();
    LRESULT ncHitTest(int x, int y);
    void showContextMenu(int x, int y);
    void showContextMenu();
    void moveCenterDialog(QDialog *dialog);

    //Variables
    HWND m_hwnd;
    QPointer<WinWidget> m_win_widget;
    QPointer<Shadow> m_shadow;
    QPointer<QWidget> m_helper_widget;
    QMainWindow *m_main_window;
    NativeEventFilter *m_native_event;
    QWindow *m_window_handle;

    QPointer<QWidget> m_focus_widget;

    bool m_is_full_screen;
    QRect m_rect_origin;

    bool m_active_state;

    Qt::WindowState m_state;

    QColor m_clear_color;

    friend class WinWidget;
    friend class NativeEventFilter;
#endif
#ifdef Q_OS_LINUX
    //Functions
    void setCursorForCurrentPos();
    void startSystemMoveResize();
    void sizeMove();
    void sizeMoveBorders();

    //Variables
    QList<QPointer<Shadow>> m_shadow_list;

    int m_margin;
    QPoint m_cursor_pos;
    bool m_resize_move;
    bool m_resize_move_started;
    qreal m_pixel_ratio;

    friend class Shadow;
#endif
#ifdef Q_OS_MAC
    void notificationReceiver(const QByteArray &notification);
    QPoint m_pos;

    friend class Notification;
#endif
#if defined Q_OS_LINUX || defined Q_OS_MAC
    //Functions
    int ncHitTest(int x, int y);

    //Variables
    bool m_mouse_button_pressed;
#endif
#if defined Q_OS_WIN || defined Q_OS_LINUX
    bool m_fixed_size;
#endif

    QRegion m_left_mask;
    QRegion m_right_mask;

    int m_title_bar_height;
    int m_icon_width;
    int m_left_margin;
    int m_right_margin;
#endif
};

Q_DECLARE_OPERATORS_FOR_FLAGS(QGoodWindow::DdeCommands)

#endif // QGOODWINDOW_H
