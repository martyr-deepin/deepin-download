#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QDragEnterEvent>
#include <QDropEvent>
#include <QCloseEvent>


#include <QtNetwork/QNetworkAccessManager>
#include <QtNetwork/QNetworkRequest>
#include <QtNetwork/QNetworkReply>


//#include <QAction>
//#include <QMap>

#include "gcsystemtrayicon.h"
//#include "gcslidebar.h"
//#include "gcmenubar.h"
//#include "gctoolbar.h"
#include "gcstatusbar.h"
#include "sqlitefunt.h"
#include "slidebar.h"
#include "toolbar.h"

///////////////////////////////////////////////////

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

class GCThread;
#include "gcthread.h"


/** =============================================== */

#include <DMainWindow>


/** */
#include "dwaterprogress.h"
#include "dtkwidget_global.h"
#include "dwidget.h"
#include "dstandardpaths.h"



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
    void ShowMW();
public:
    SQLiteFunt      *downDB;
    Aria2cRPCMsg    *aria2c;    

protected:

    QString CacheDir;    
    void initMainWindow();
    void setupMenu();
    int  initAria2cWork();
    void dragEnterEvent( QDragEnterEvent *e );
    void dropEvent( QDropEvent *e );
    void closeEvent( QCloseEvent *event );
    void resizeEvent(QResizeEvent* event);


    void slotActionInvoked(uint id, QString action );
    void notifyActivator( QString title ,QString text  );

    bool closeApp = false;
    QWidget *centerWidget;

private:

    QString         actionResult;

    QThread         *thread;
    GCThread        *workThread;
    QTimer          *threadTimer;
/**
    QTimer          *m_Active;
    QTimer          *m_Stop;
    QTimer          *m_Down;
    QTimer          *m_Wait;
    QTimer          *m_All;
**/
    QClipboard      *board;         //剪贴板

    QList<TBItem>   dlist;

    /** 控件、窗口、对话框 */
    NewDown          *newDownDlg;
    ConfigDlg        *configDlg;
    AboutDlg         *aboutDlg;
    MWM              *mwm;               //悬浮窗　暂弃用
    DownListView     *downListView;
    GCSystemTrayIcon *systemTrayIcon;   //状态栏（托盘 ）
    GCStatusBar      *statusBar;
    //QMenu            *m_ContextMenu;
    Dtk::Widget::DWaterProgress *waterProgress;

    void LoadTableView( QWidget *centerWidget );
    void LoadSlideBar( QWidget *leftWidget );
    void LoadStatusbar( QWidget *bottomWidget );
    void LoadMaiMenubar( QWidget *topWidget );
    void LoadTrayIcon();

    void LoadDownList();
    void CloseAllWindow();
    void closeSaveSetup();

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
    void DeleteAllRecord();
    void AddBtFile();
    void AddMetalinkFile();
    void CopyUrlToBoard();
    void ShowWindow();
    void ShowTrayMenu();
    void RemoveAria2Cache();

    void RightTMenu( int itemID );
    //////////////////////////////////////////////////////////////////

    void UpdateMWM( QString text );
    void SeeBoard();
    void OpenDownFilePath( QString filepath );

    ///////////////////////////////////////////////////////////////////

    QWidget *layoutWidget;
    QHBoxLayout *layout;

    SlideBar *slidebar;
    ToolBar  *toolbar;
    QLabel   *bottomlabel;


public:
    void SetBottomStatusText( QString text );
    void ShowMessageTip( QString text );

    void AppendDownBT( QString btfilepath ,QString SavePath = "*"  );
    void AppendDownUrl( QString urlStr ,QString SavePath = "*" );
    void AppendDownMetalink( QString Metalinkfilepath ,QString SavePath = "*");

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

signals:
     //void start();
     void HandSort( int col );

/**  定时轮循 信号触发*/
private slots:

    void GetWaitList();
    void GetDDList();
    void RecycleList();
    void GetStopList();
    void GetActiveList();
    void UpdateDownStatus();

    void SelSlideItem( int row );
    void SelToolItem( int btn );
    void SearchChang( QString  text );
    void SearchfocusOut();
    void ShowContextMenu( const QPoint &point );

    void OnNetworkReply( QList<TBItem*> *tbList );
    void OnNetworkReplyNode( TBItem* tbitem );

private:


};

#endif // MAINWINDOW_H
