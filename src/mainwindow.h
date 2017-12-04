#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QDragEnterEvent>
#include <QDropEvent>
#include <QCloseEvent>
//#include <QAction>
//#include <QMap>

#include "gcsystemtrayicon.h"
//#include "gcslidebar.h"
//#include "gcmenubar.h"
//#include "gctoolbar.h"
#include "gcstatusbar.h"
#include "sqlitefunt.h"


//#include <dimagebutton.h>
#include <QHBoxLayout>

/**
* 预声明： rpc 接口 / 子窗口类
* ================================================ */
class Aria2cRPCMsg;
#include "aria2crpcmsg.h"

class NewDown;
#include "newdown.h"

class ConfigDlg;
#include "configdlg.h"

class AboutDlg;
#include "aboutdlg.h"

class MWM;
#include "mwm.h"

class DownListView;
#include "downlistview.h"

//class GCThread;
//#include "gcthread.h"


/** =============================================== */
#include <DMainWindow>

#include "slidebar.h"
#include "toolbar.h"

DWIDGET_USE_NAMESPACE


class MainWindow : public DMainWindow
{
    Q_OBJECT

public:
    MainWindow(DMainWindow *parent = 0);
    ~MainWindow();
    //QSize sizeHint() const;
    //void keyPressEvent(QKeyEvent *keyEvent);
    //void resizeEvent(QResizeEvent* event);

public:
    SQLiteFunt *downDB;

protected:

    //GCThread   *wThread;
    //void initMainWindow();
    int  initAria2cWork();
    void dragEnterEvent( QDragEnterEvent *e );
    void dropEvent( QDropEvent *e );
    void closeEvent( QCloseEvent *event );

    bool closeApp = false;
    QWidget *centerWidget;

private:

    QString         actionResult;
    QTimer          *m_Active;
    QTimer          *m_Stop;
    QTimer          *m_Down;
    QTimer          *m_Wait;
    QTimer          *m_All;
    QClipboard      *board;         //剪贴板
    Aria2cRPCMsg    *aria2c;
    QList<TBItem>   dlist;

    /** 控件、窗口、对话框 */
    NewDown          *newDownDlg;
    ConfigDlg        *configDlg;
    AboutDlg         *aboutDlg;
    MWM              *mwm;
    DownListView     *downListView;
    GCSystemTrayIcon *systemTrayIcon;
    GCStatusBar      *statusBar;

    void LoadTableView( QWidget *centerWidget );
    void LoadSlideBar( QWidget *leftWidget );
    void LoadStatusbar( QWidget *bottomWidget );
    void LoadMaiMenubar( QWidget *topWidget );
    void LoadTrayIcon();

    void LoadDownList();
    void CloseAllWindow();

    QList<QString> FindDownloadUrl( const QString &strText );

    //////////////////////////////////////////////////////////////////

    int SlideSelItem  = -1;

    ////////////////////////////////////////////////////////////////////


    //QString GetFileName( QString path );

    ///////////////////////////////////////////////////////////////////

    void Pause();
    void UnPause();
    void Property();
    void AgainDown();
    void Remove();
    void OpenDownFile();
    void DeleteDownFileDB();
    void AddBtFile();
    void AddMetalinkFile();
    void CopyUrlToBoard();
    void ShowWindow();
    void ShowTrayMenu();

    //////////////////////////////////////////////////////////////////

    void UpdateMWM( QString text );
    void SeeBoard();
    void OpenDownFilePath( QString filepath );

    ///////////////////////////////////////////////////////////////////

    QWidget *layoutWidget;
    QHBoxLayout *layout;

    SlideBar *slidebar;
    ToolBar  *toolbar;


public:
    void ShowMessageTip( QString text );
    void AppendDownBT( QString btfilepath );
    void AppendDownUrl( QString urlStr  );
    void AppendDownMetalink( QString Metalinkfilepath );
    void OpenLinkFile( QString filenmae );
    QMenu* ShareRMenu();
    int GetSlideSelRow();

    void StartRun( QString DownFileUrl );
    void OPenDownUrlDlg( QString DownFileUrl );

/** RPC 消息返回处理 */
public:
    void UpdateGUI_StatusMsg( TBItem tbitem );
    void UpdateGUI_StatusMsg(  QList<TBItem>  tbList );
    void UpdateGUI_CommandMsg( QJsonObject nObj );

/**  定时轮循 信号触发*/
private slots:
    void GetWaitList();
    void GetDDList();
    void GetStopList();
    void GetActiveList();

    void UpdateDownStatus();

    void SelSlideItem( int row );
    void SelToolItem( int btn );

private:


};

#endif // MAINWINDOW_H
