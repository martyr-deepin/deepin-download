#ifndef ARIA2CRPCMSG_H
#define ARIA2CRPCMSG_H

#include <QMap>
#include <QNetworkAccessManager>

#include "optionstruct.h"


/** ============================================================ */

class MainWindow;
#include "mainwindow.h"

class GCJsonRPC;
#include "gcjsonrpc.h"

/** ============================================================ */

class Aria2cRPCMsg : QObject{

   Q_OBJECT

private:

   GCJsonRPC *gcjsonrpc;

   QMap<QString,QString> gidList;

   /** 发送消息 */
  void SendRPC2Aria2c( QString dz , QString id );
  void SendRPC2Aria2c( QString dz ,QJsonArray params,QString id );

  QString GetFileName( QString path );

  int  Errot_U = 0;
  MainWindow* mainUI;

public:

    Aria2cRPCMsg( QString actionResult , MainWindow* mainUI );

/** 返回消息分发*/
    void UpdateUIMsg( QJsonObject nObj , QString  method );
/** 返回错误 */
    void ReturnError( QString error_t );

    /**
     * 临时处置下载路径设置
     */
    void SendMsgAria2c_SetSavePath( QString SavePath  );

/** 任务处理 */
    //"addUri"
    void SendMsgAria2c_addUri(  QString uri ,QString id   );

    //"addTorrent"
    void SendMsgAria2c_addTorrent(  QString filename,QString id  );

    //"getPeers"
    void SendMsgAria2c_getPeers(  QString id  );

    //"addMetalink"
    void SendMsgAria2c_addMetalink(  QString filename,QString id   );

    //"remove"
    void SendMsgAria2c_remove( QString gid );

    //"pause"
    void SendMsgAria2c_pause( QString gid );

    //"forcePause"
    void SendMsgAria2c_forcePause( QString id );

    //"pauseAll"
    void SendMsgAria2c_pauseAll();

    //"forcePauseAll"
    void SendMsgAria2c_forcePauseAll();

    //"unpause"
    void SendMsgAria2c_unpause(  QString gid  );

    //"unpauseAll"
    void SendMsgAria2c_unpauseAll();

    //"forceRemove"
    void SendMsgAria2c_forceRemove();

    //"changePosition"
    void SendMsgAria2c_changePosition( QString id , int pos ,QString how  );

    //"tellStatus"
    void SendMsgAria2c_tellStatus( QString gid );

    //"getUris"
    void SendMsgAria2c_getUris( QString id  );

    //"getFiles"
    void SendMsgAria2c_getFiles( QString id );

    //"getServers"
    void SendMsgAria2c_getServers( QString id );

    //"tellActive"
    void SendMsgAria2c_tellActive();

    //"tellWaiting"
    void SendMsgAria2c_tellWaiting( int offset,int num  );

    //"tellStopped"
    void SendMsgAria2c_tellStopped( int offset,int num  );

    //"getOption"
    void SendMsgAria2c_getOption( QString id );

    //"changeUri"
    void SendMsgAria2c_changeUri( QString id ,int fileIndex, QString delUris, QString addUris );

    //"changeOption"
    void SendMsgAria2c_changeOption( changeOption setCOption ,QString id  );

    //"getGlobalOption"
    void SendMsgAria2c_getGlobalOption(  );

    //"changeGlobalOption"
    void SendMsgAria2c_changeGlobalOption( changeGlobalOption setCGoption );

    //"purgeDownloadResult"
    void SendMsgAria2c_purgeDownloadResult();

    //"removeDownloadResult"
    void SendMsgAria2c_removeDownloadResult( QString id  );

    //"getVersion"
    void SendMsgAria2c_getVersion();

    //"getSessionInfo"
    void SendMsgAria2c_getSessionInfo();

    //"shutdown"
    void SendMsgAria2c_shutdown();

    //"forceShutdown"
    void SendMsgAria2c_forceShutdown();

    //"getGlobalStat"
    void SendMsgAria2c_getGlobalStat();

    //"saveSession"
    void SendMsgAria2c_saveSession();

    //"system.multicall"
    void SendMsgAria2c_system_multicall();

    //"system.listMethods"
    void SendMsgAria2c_system_listMethods();

    //"system.listNotifications"
    void SendMsgAria2c_system_listNotifications();

private:    

    /** 返回消息 */
    //"addUri"
    void Aria2cRMsg_addUri( QJsonObject nObj );

    //"addTorrent"
    void Aria2cRMsg_addTorrent( QJsonObject nObj );

    //"getPeers"
    void Aria2cRMsg_getPeers( QJsonObject nObj );

    //"addMetalink"
    void Aria2cRMsg_addMetalink( QJsonObject nObj );

    //"remove"
    void Aria2cRMsg_remove( QJsonObject nObj );

    //"pause"
    void Aria2cRMsg_pause( QJsonObject nObj );

    //"forcePause"
    void Aria2cRMsg_forcePause( QJsonObject nObj );

    //"pauseAll"
    void Aria2cRMsg_pauseAll( QJsonObject nObj );

    //"forcePauseAll"
    void Aria2cRMsg_forcePauseAll( QJsonObject nObj );

    //"unpause"
    void Aria2cRMsg_unpause( QJsonObject nObj );

    //"unpauseAll"
    void Aria2cRMsg_unpauseAll( QJsonObject nObj );

    //"forceRemove"
    void Aria2cRMsg_forceRemove( QJsonObject nObj );

    //"changePosition"
    void Aria2cRMsg_changePosition( QJsonObject nObj );

    //"tellStatus"
    void Aria2cRMsg_tellStatus( QJsonObject nObj );

    //"getUris"
    void Aria2cRMsg_getUris( QJsonObject nObj );

    //"getFiles"
    void Aria2cRMsg_getFiles( QJsonObject nObj );

    //"getServers"
    void Aria2cRMsg_getServers( QJsonObject nObj );

    //"tellActive"
    void Aria2cRMsg_tellActive( QJsonObject nObj );

    //"tellWaiting"
    void Aria2cRMsg_tellWaiting( QJsonObject nObj );

    //"tellStopped"
    void Aria2cRMsg_tellStopped( QJsonObject nObj );

    //"getOption"
    void Aria2cRMsg_getOption( QJsonObject nObj );

    //"changeUri"
    void Aria2cRMsg_changeUri( QJsonObject nObj );

    //"changeOption"
    void Aria2cRMsg_changeOption( QJsonObject  nObj );

    //"getGlobalOption"
    void Aria2cRMsg_getGlobalOption( QJsonObject nObj );

    //"changeGlobalOption"
    void Aria2cRMsg_changeGlobalOption( QJsonObject nObj );

    //"purgeDownloadResult"
    void Aria2cRMsg_purgeDownloadResult( QJsonObject nObj );

    //"removeDownloadResult"
    void Aria2cRMsg_removeDownloadResult( QJsonObject nObj );

    //"getVersion"
    void Aria2cRMsg_getVersion( QJsonObject nObj );

    //"getSessionInfo"
    void Aria2cRMsg_getSessionInfo( QJsonObject nObj );

    //"shutdown"
    void Aria2cRMsg_shutdown( QJsonObject nObj );

    //"forceShutdown"
    void Aria2cRMsg_forceShutdown( QJsonObject nObj );

    //"getGlobalStat"
    void Aria2cRMsg_getGlobalStat( QJsonObject nObj );

    //"saveSession"
    void Aria2cRMsg_saveSession( QJsonObject nObj );

    //"system.multicall"
    void Aria2cRMsg_system_multicall( QJsonObject nObj );

    //"system.listMethods"
    void Aria2cRMsg_system_listMethods( QJsonObject nObj );

    //"system.listNotifications"
    void Aria2cRMsg_system_listNotifications( QJsonObject nObj );


    /**
     "aria2.tellActive",
     "aria2.tellWaiting",
     "aria2.tellStopped",
      三个返回消息结构相同，集中统一处理向UI 返回 *
     */
    void Aria2cRMsg_tellMessage( QJsonObject nObj );


};

#endif // ARIA2CRDPMSG_H
