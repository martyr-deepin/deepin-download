#include "aria2crpcmsg.h"
#include <QFile>
#include <QProcess>
#include <QSettings>
#include <QtNetwork/QNetworkAccessManager>
#include <QtNetwork/QNetworkRequest>
#include <QtNetwork/QNetworkReply>
#include <QStringList>
#include <QJsonObject>
#include <QJsonDocument>
#include <QJsonArray>
#include <QByteArray>
#include "base64.h"


Aria2cRPCMsg::Aria2cRPCMsg( QString actionResult , MainWindow* mainUI )
{

    this->mainUI = mainUI;
    gcjsonrpc = new GCJsonRPC( actionResult , this );
}

/**
*
* 发送消息处理
*/
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void Aria2cRPCMsg::SendRPC2Aria2c( QString dz , QString id )
{

    ///
    ///** secret  **/
    /////////////////////////////////////////////////////////////////

    QString gid =  id; //this->gidList[ id ];

    QJsonArray params;

    if ( gid != "0" ){

       params.append( gid );
       SendRPC2Aria2c( dz , params ,id );

    }else{

       //qDebug() << "SendRPC2Aria2c getresultID" << gid;
       SendRPC2Aria2c( dz , params ,id );
    }

}

void Aria2cRPCMsg::SendRPC2Aria2c( QString dz ,QJsonArray params,QString id )
{

    gcjsonrpc->SendMessage( "2.0", id , dz , params );
}


/**
*  任务处理
*/
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/**
* aria2.addUri
* 添加新下载URL
*/
void Aria2cRPCMsg::SendMsgAria2c_addUri( QString uri ,QString id ){

    QJsonArray json_array;
    QJsonArray item;
    item.append( uri );
    json_array.append(item);

    SendRPC2Aria2c( "aria2.addUri", json_array ,id );

}

/**
 * "aria2.addTorrent"
 * 添加 BT 下载
*/
void Aria2cRPCMsg::SendMsgAria2c_addTorrent( QString filename ,QString id  ){


    QFile file( filename );
    file.open( QIODevice::ReadOnly  /*| QIODevice::Text */ );
    QString torrent = Base64::encode( file.readAll()  );

    file.close();

    //qDebug() << "torrent" << torrent;

    QJsonArray item;
    item.append( torrent );

    SendRPC2Aria2c( "aria2.addTorrent", item ,id);

}

/**
 * aria2.getPeers
 * returns a list peers of the download denoted
 * （ 仅适用于BitTorrent ）
*/
void Aria2cRPCMsg::SendMsgAria2c_getPeers( QString id   ){

    SendRPC2Aria2c( "aria2.getPeers" , id );

}

/**
* aria2.addMetalink
* 添加 Metalink 下载
*/
void Aria2cRPCMsg::SendMsgAria2c_addMetalink(  QString filename,QString id  ){


    QFile file( filename );
    file.open( QIODevice::ReadOnly /*| QIODevice::Text */);
    QString metalink = Base64::encode( file.readAll()  );
    file.close();

    //qDebug() << "metalink" << metalink;

    QJsonArray item;
    item.append( metalink );

    SendRPC2Aria2c( "aria2.addMetalink", item , id );

}

/**
* aria2.remove
* 移除
*/
void Aria2cRPCMsg::SendMsgAria2c_remove( QString gid ){


   SendRPC2Aria2c( "aria2.remove" , gid );
}

/**
* aria2.pause
* 暂停
*/
void Aria2cRPCMsg::SendMsgAria2c_pause( QString gid  ){

    SendRPC2Aria2c( "aria2.pause" , gid );
}

/**
 * "forcePause"
 * 强制暂停
*/
void Aria2cRPCMsg::SendMsgAria2c_forcePause( QString id  ){

    SendRPC2Aria2c( "aria2.forcePause" , id );

}

/**
 * "pauseAll"
 * 暂停所有
*/
void Aria2cRPCMsg::SendMsgAria2c_pauseAll(){

    SendRPC2Aria2c( "aria2.pauseAll" ,"0" );
}

/**
 * "forcePauseAll"
 * 强制暂停
*/
void Aria2cRPCMsg::SendMsgAria2c_forcePauseAll(){

    SendRPC2Aria2c( "aria2.forcePauseAll" ,"0" );
}


/**
* aria2.unpause
* 恢复暂停
*/
void Aria2cRPCMsg::SendMsgAria2c_unpause(  QString gid  ){

    SendRPC2Aria2c( "aria2.unpause" , gid );
}

/**
 * "unpauseAll"
 * 恢复所有
*/
void Aria2cRPCMsg::SendMsgAria2c_unpauseAll(){

    SendRPC2Aria2c( "aria2.unpauseAll" ,"0" );
}

/**
 * "forceRemove"
 * 强制停止任务（ 移除任务 ）
*/
void Aria2cRPCMsg::SendMsgAria2c_forceRemove(){

    SendRPC2Aria2c( "aria2.forceRemove" ,"0" );

}

/**
 * aria2.changePosition
*/
void Aria2cRPCMsg::SendMsgAria2c_changePosition( QString id , int pos ,QString how  ){

    /** 更改队列中由gid表示的下载位置。 **/
    //pos 整数
    //how 字符串: 如果是 POS_SET，它会将下载相对于队列的开始位置。
          // 如果是 POS_CUR，它会将下载到相对于当前位置的位置。
          // 如果是 POS_END，它会将下载相对于队列末尾的位置。

    QString gid = this->gidList[ id ];

    QJsonArray item;
    item.append( gid );   //gid
    item.append( pos );   //pos
    item.append( how );   //how

    //qDebug() << "changePosition params: " <<  item;
    SendRPC2Aria2c( "aria2.changePosition" , item ,"0" );

}

/**
* aria2.tellStatus
* 下载进度
*/
void Aria2cRPCMsg::SendMsgAria2c_tellStatus( QString gid ){

   SendRPC2Aria2c( "aria2.tellStatus" , gid );
}

/**
* aria2.getUris
* 获取下载中使用的URI
*/
void Aria2cRPCMsg::SendMsgAria2c_getUris( QString id ){

   SendRPC2Aria2c( "aria2.getUris" ,id );
}


/**
 * aria2.getFiles
 * 下载文件列表
*/
void Aria2cRPCMsg::SendMsgAria2c_getFiles(  QString id  ){

    SendRPC2Aria2c( "aria2.getFiles" , id );

}

/**
 * aria2.getServers
 * 当前连接的HTTP（S）/ FTP / SFTP服务器
*/
void Aria2cRPCMsg::SendMsgAria2c_getServers( QString id  ){

    SendRPC2Aria2c( "aria2.getServers" ,id );
}

/**
 * aria2.tellActive
 * 返回活动下载列表
*/
void Aria2cRPCMsg::SendMsgAria2c_tellActive(){

   SendRPC2Aria2c( "aria2.tellActive" ,"0" );
}

/**
 * aria2.tellWaiting
 * 返回等待下载的列表
*/
void Aria2cRPCMsg::SendMsgAria2c_tellWaiting( int offset,int num  ){

    //如果offset为正整数，则该方法返回[ offset，offset + num ] 范围内的下载。
    //offset可以是负整数。offset == -1 最后下载在等待队列; offset == -2下载前最后一次下载，响应中的下载​​顺序颠倒。
    QJsonArray item;
    item.append( offset );   //offset
    item.append( num );  //num

    SendRPC2Aria2c( "aria2.tellWaiting" , item ,"0"  );

}

/**
 * aria2.tellStopped
 * 返回停止下载的列表
*/
void Aria2cRPCMsg::SendMsgAria2c_tellStopped( int offset,int num ){

    QJsonArray item;
    item.append( offset );   //offset
    item.append( num );      //num
    SendRPC2Aria2c( "aria2.tellStopped" , item ,"0" );
}

/**
 * aria2.getOption
 * 返回下载选项
*/
void Aria2cRPCMsg::SendMsgAria2c_getOption( QString id ){

   SendRPC2Aria2c( "aria2.getOption" ,id );
}

/**
 * aria2.changeUri
 * 从delUris中删除URI 并附加addUris中的URI
*/
void Aria2cRPCMsg::SendMsgAria2c_changeUri( QString id ,int fileIndex, QString delUris, QString addUris ){

    // 方法从delUris中删除URI 并附加addUris中的URI， 以由gid表示。delUris 和 addUris 是字符串列表。下载可以包含多个文件，并且URI附加到每个文件。
    // fileIndex 用于选择要删除/附加给定URI的文件。
    // fileIndex is 1-based 用于指定 URI 在现有等待 URI 列表中的插入位置。
    // fileIndex is 0-based 当省略位置时，将URI附加到列表的后面。
    // 方法首先执行删除，然后执行添加
    /**
    'params':[ '2089b05ecca3d829',
               1,
               [],
               ['http://example.org/file']
             ]
    **/

    QJsonArray params;
    QJsonArray tmpK;
    QJsonArray urlAdder;

    QString gid = this->gidList[ id ];

    params.append( gid  );    //gid
    params.append( fileIndex ); //fileIndex
    tmpK.append( delUris );
    params.append( tmpK );  //delUris
    urlAdder.append( addUris  );
    params.append( urlAdder ); //addUris

    SendRPC2Aria2c( "aria2.changeUri" , params ,"0" );

}

/**
 * aria2.changeOption
 * 更改下载选项
*/
void Aria2cRPCMsg::SendMsgAria2c_changeOption( changeOption setCOption ,QString id  ){

    /**
        bt-max-peers
        bt-request-peer-speed-limit
        bt-remove-unselected-file
        force-save
        max-download-limit
        max-upload-limit
    **/
        QString gid = this->gidList[ id ];
        QJsonArray  item;
        QJsonObject options;
        //options.insert( "bt-max-peers", setCOption.bt_max_peers );
        //options.insert( "bt-request-peer-speed-limit", setCOption.bt_request_peer_speed_limit );
        //options.insert( "bt-remove-unselected-file", setCOption.bt_remove_unselected_file );
        //options.insert( "force-save", setCOption.force_save );
        options.insert( "max-download-limit", setCOption.max_download_limit );
        options.insert( "max-upload-limit", setCOption.max_upload_limit );
        item.append( gid  );
        item.append( options );
        SendRPC2Aria2c( "aria2.changeOption" , item ,id );

}

/**
 * aria2.getGlobalOption
 * 返回全局选项
*/
void Aria2cRPCMsg::SendMsgAria2c_getGlobalOption(){

    SendRPC2Aria2c( "aria2.getGlobalOption" ,"0" );

}

/**
 * aria2.changeGlobalOption
 * 更改全局选项
*/
void Aria2cRPCMsg::SendMsgAria2c_changeGlobalOption( changeGlobalOption setCGoption ){

    /**
        bt-max-open-files
        download-result
        keep-unfinished-download-result
        log
        log-level
        max-concurrent-downloads
        max-download-result
        max-overall-download-limit
        max-overall-upload-limit
        optimize-concurrent-downloads
        save-cookies
        save-session
        server-stat-of
    **/

        QJsonArray item;
        QJsonObject option;

        //option.insert( "bt-max-open-files", setCGoption.bt_max_open_files );
        //option.insert( "download-result",setCGoption.download_result );
        //option.insert( "keep-unfinished-download-result",setCGoption.keep_unfinished_download_result );
        //option.insert( "log",setCGoption.log );
        //option.insert( "log-level", setCGoption.log_level );
        //option.insert( "max-concurrent-downloads", setCGoption.max_concurrent_downloads  );
        //option.insert( "max-download-result", setCGoption.max_download_result  );
        option.insert( "max-overall-download-limit",setCGoption.max_overall_download_limit );
        option.insert( "max-overall-upload-limit", setCGoption.max_overall_upload_limit  );
        //option.insert( "optimize-concurrent-downloads", setCGoption.optimize_concurrent_downloads );
        //option.insert( "save-cookies", setCGoption.save_cookies );
        //option.insert( "save-session", setCGoption.save_session );
        //option.insert( "server-stat-of", setCGoption.server_stat_of );

        item.append( option );

        SendRPC2Aria2c( "aria2.changeGlobalOption" , item ,"0" );      

}

/**
 * aria2.purgeDownloadResult
 * 清除完成/错误/删除下载到可用内存
*/
void Aria2cRPCMsg::SendMsgAria2c_purgeDownloadResult(){

    SendRPC2Aria2c( "aria2.purgeDownloadResult" ,"0" );
}

/**
 * aria2.removeDownloadResult
 * 从内存中删除(gid)完成/错误/删除的下载
*/
void Aria2cRPCMsg::SendMsgAria2c_removeDownloadResult( QString id ){

    SendRPC2Aria2c( "aria2.removeDownloadResult" ,id );
}

/**
 * aria2.getVersion
 * 返回aria2的版本和已启用的功能列表
*/
void Aria2cRPCMsg::SendMsgAria2c_getVersion(){

    SendRPC2Aria2c( "aria2.getVersion" ,"0" );
}

/**
 * aria2.getSessionInfo
 * 返回会话信息
*/
void Aria2cRPCMsg::SendMsgAria2c_getSessionInfo(){

   SendRPC2Aria2c( "aria2.getSessionInfo" ,"0" );
}

/**
 * aria2.shutdown
 * 关闭aria2
*/
void Aria2cRPCMsg::SendMsgAria2c_shutdown(){

   SendRPC2Aria2c( "aria2.shutdown" ,"0" );
}

/**
 * aria2.forceShutdown
 * 强制关闭aria2
*/
void Aria2cRPCMsg::SendMsgAria2c_forceShutdown(){

    SendRPC2Aria2c( "aria2.forceShutdown" ,"0" );
}

/**
 * aria2.getGlobalStat
 * 全局统计信息
*/
void Aria2cRPCMsg::SendMsgAria2c_getGlobalStat(){


    SendRPC2Aria2c( "aria2.getGlobalStat" ,"0" );

}

/**
 * aria2.saveSession
 * *********** 调用失败，原因暂不明 ******************
*/
void Aria2cRPCMsg::SendMsgAria2c_saveSession(){

    SendRPC2Aria2c( "aria2.saveSession" ,"0" );

}


/**
 * system.multicall
 * 单个请求中封装了多个方法调用
*/
void Aria2cRPCMsg::SendMsgAria2c_system_multicall(){

    // 在单个请求中封装了多个方法调用
    // 一个结构体的数组,结构包含两个键： methodName 和 params
    /**
    'params':[ [ { 'methodName':'aria2.addUri','params':[ ['http://example.org'] ] },
                 { 'methodName':'aria2.addTorrent','params':[ base64.b64encode(open('file.torrent').read()) ] }
             ] ]
    **/

    QJsonObject mm;
    mm.insert( "methodName" ,"aria2.addUri" );
    QJsonArray mp;
    mp.append( "http://example.org/xx.zip"  );
    QJsonArray item;
    item.append( mp );
    mm.insert( "params" , item );

    QJsonArray kk;
    kk.append( mm );
    QJsonArray paramss;
    paramss.append( kk );

    SendRPC2Aria2c( "system.multicall", paramss ,"0" );

}

/**
 * system.listMethods
 * 返回所有可用RPC方法
*/
void Aria2cRPCMsg::SendMsgAria2c_system_listMethods(){

    //返回所有可用RPC方法
    SendRPC2Aria2c( "system.listMethods" ,"0" );
}

/**
 * system.listNotifications
 * 返回所有可用的RPC通知
*/
void Aria2cRPCMsg::SendMsgAria2c_system_listNotifications(){

    //返回所有可用的RPC通知
    SendRPC2Aria2c( "system.listNotifications" ,"0" );

}

/**
*  返回消息分发
*/
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void Aria2cRPCMsg::UpdateUIMsg( QJsonObject nObj , QString  method  ){

    /**
    * JSONRPC 消息 返回格式：

    * 字符串： GID *
    {"id":"qwer","jsonrpc":"2.0","result":"9c6fffa4873a562e"}
    * 数组  *
    {"id":"qwer","jsonrpc":"2.0","result":[]
    * 对象 *
    {"id":"qwer","jsonrpc":"2.0","result":{}
    * 错误 ERROR  *
    {"id":"qwer","jsonrpc":"2.0","error":{"code":1,"message":"Invalid GID "}}
    * ======================================================================================= */

  //qDebug() << "====================== Aria2cRPCMsg::UpdateUI "+ method +"==========================" ;

  QString id = nObj.value("id").toString();
  QString jsonrpc = nObj.value("jsonrpc").toString();
  //qDebug()  << "id "<< id;
  //qDebug()  << "jsonrpc "<< jsonrpc;
  QString resultID =  nObj.value("result").toString();
  //QJsonObject result_OBj = nObj.value("result").toObject();

  QJsonObject errorOBj = nObj.value("error").toObject();
  QString  error_id  = errorOBj.value("id").toString();
  QString  error_message  = errorOBj.value("message").toString();

  //qDebug()  << "error_id "<< error_id;
  //qDebug()  << "error_message "<< error_message;

  if ( error_id != "" || error_message != ""  ){

      //qDebug() << "error_message =====> " << error_message;
      return;
  }

  if ( resultID != "" && resultID.length() == 16 ){

      this->gidList.insert( id,resultID  );
  }

  const QStringList listMethods = {

       "aria2.addUri",             // 0
       "aria2.addTorrent",         // 1
       "aria2.getPeers",           // 2
       "aria2.addMetalink",        // 3
       "aria2.remove",             // 4
       "aria2.pause",              // 5
       "aria2.forcePause",         // 6
       "aria2.pauseAll",           // 7
       "aria2.forcePauseAll",      // 8
       "aria2.unpause",            // 9
       "aria2.unpauseAll",         // 10
       "aria2.forceRemove",        // 11
       "aria2.changePosition",     // 12
       "aria2.tellStatus",         // 13
       "aria2.getUris",            // 14
       "aria2.getFiles",           // 15
       "aria2.getServers",         // 16
       "aria2.tellActive",         // 17
       "aria2.tellWaiting",        // 18
       "aria2.tellStopped",        // 19
       "aria2.getOption",          // 20
       "aria2.changeUri",          // 21
       "aria2.changeOption",       // 22
       "aria2.getGlobalOption",    // 23
       "aria2.changeGlobalOption",   // 24
       "aria2.purgeDownloadResult",  // 25
       "aria2.removeDownloadResult", // 26
       "aria2.getVersion",           // 27
       "aria2.getSessionInfo",       // 28
       "aria2.shutdown",             // 29
       "aria2.forceShutdown",        // 30
       "aria2.getGlobalStat",        // 31
       "aria2.saveSession",          // 32
       "system.multicall",           // 33
       "system.listMethods",         // 34
       "system.listNotifications"    // 35
   };

  switch (  listMethods.indexOf( method ) ) {

      case 0 : //"aria2.addUri"
          this->Aria2cRMsg_addUri( nObj );
          break;
      case 1 : //"aria2.addTorrent"
          this->Aria2cRMsg_addTorrent( nObj );
          break;
      case 2 : //"aria2.getPeers"
          this->Aria2cRMsg_getPeers( nObj );
          break;
      case 3 : //"aria2.addMetalink"
          this->Aria2cRMsg_addMetalink( nObj );
          break;
      case 4 : //"aria2.remove"
          this->Aria2cRMsg_remove( nObj );
          break;
      case 5 : //"aria2.pause"
          this->Aria2cRMsg_pause( nObj );
          break;
      case 6 : //"aria2.forcePause"
          this->Aria2cRMsg_forcePause( nObj );
          break;
      case 7 : //"aria2.pauseAll"
          this->Aria2cRMsg_pauseAll( nObj );
          break;
      case 8 : //"aria2.forcePauseAll"
          this->Aria2cRMsg_forcePauseAll( nObj );
          break;
      case 9 : //"aria2.unpause"
          this->Aria2cRMsg_unpause( nObj );
          break;
      case 10 : //"aria2.unpauseAll"
          this->Aria2cRMsg_unpauseAll( nObj );
          break;
      case 11 : //"aria2.forceRemove"
          this->Aria2cRMsg_forceRemove( nObj );
          break;
      case 12 : //"aria2.changePosition"
          this->Aria2cRMsg_changePosition( nObj );
          break;
      case 13 : //"aria2.tellStatus"
          this->Aria2cRMsg_tellStatus( nObj );
          break;
      case 14 : //"aria2.getUris"
          this->Aria2cRMsg_getUris( nObj );
          break;
      case 15 : //"aria2.getFiles"
          this->Aria2cRMsg_getFiles( nObj );
          break;
      case 16 : //"aria2.getServers"
          this->Aria2cRMsg_getServers( nObj );
          break;
      case 17 : //"aria2.tellActive"
          this->Aria2cRMsg_tellActive( nObj );
          break;
      case 18 : //"aria2.tellWaiting"
          this->Aria2cRMsg_tellWaiting( nObj );
          break;
      case 19 : //"aria2.tellStopped"
          this->Aria2cRMsg_tellStopped( nObj );
          break;
      case 20 : //"aria2.getOption"
          this->Aria2cRMsg_getOption( nObj );
          break;
      case 21 : //"aria2.changeUri"
          this->Aria2cRMsg_changeUri( nObj );
          break;
      case 22 : //"aria2.changeOption"
          this->Aria2cRMsg_changeOption( nObj );
          break;
      case 23 : //"aria2.getGlobalOption"
          this->Aria2cRMsg_getGlobalOption( nObj );
          break;
      case 24 : //"aria2.changeGlobalOption"
          this->Aria2cRMsg_changeGlobalOption( nObj );
          break;
      case 25 : //"aria2.purgeDownloadResult"
          this->Aria2cRMsg_purgeDownloadResult( nObj );
          break;
      case 26 : //"aria2.removeDownloadResult"
          this->Aria2cRMsg_removeDownloadResult( nObj );
          break;
      case 27 : //"aria2.getVersion"
          this->Aria2cRMsg_getVersion( nObj );
          break;
      case 28 : //"aria2.getSessionInfo"
          this->Aria2cRMsg_getSessionInfo( nObj );
          break;
      case 29 : //"aria2.shutdown"
          this->Aria2cRMsg_shutdown( nObj );
          break;
      case 30 : //"aria2.forceShutdown"
          this->Aria2cRMsg_forceShutdown( nObj );
          break;
      case 31 : //"aria2.getGlobalStat"
          this->Aria2cRMsg_getGlobalStat( nObj );
          break;
      case 32 : //"aria2.saveSession"
          this->Aria2cRMsg_saveSession( nObj );
          break;
      case 33 : //"system.multicall"
          this->Aria2cRMsg_system_multicall( nObj );
          break;
      case 34 : //"system.listMethods"
          this->Aria2cRMsg_system_listMethods( nObj );
          break;
      case 35 : //"system.listNotifications"
          this->Aria2cRMsg_system_listNotifications( nObj );
          break;
      default:
          break;
  }

}

////////////////////////////////////////////////////////////////////////////////////////////////////

/**
* 返回消息处理
*/
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

//"aria2.addUri"
void Aria2cRPCMsg::Aria2cRMsg_addUri( QJsonObject nObj ){

    /** OK: "{"id":"100","jsonrpc":"2.0","result":"ab3e671a1812e81b"}" */

    QString result = nObj.value("result").toString();
    //qDebug() << result;

    DDRecord t;
    t.id =  nObj.value("id").toString();
    t.gid = nObj.value("result").toString();

    this->mainUI->downDB->SetDTaskGid( t );

}

//"aria2.addTorrent"
void Aria2cRPCMsg::Aria2cRMsg_addTorrent( QJsonObject nObj ){

    /** OK: "{"id":"200","jsonrpc"2.0","result":["678ba8d6ba1ec249"]}" */
    /** OK: "{\"id\":\"57\",\"jsonrpc\":\"2.0\",\"result\":\"c9c0a1a260a83f40\"}"*/
/*
    DDRecord t;
    t.id =  nObj.value("id").toString();
    QJsonArray results =  nObj.value("result").toArray();
    for( int i = 0 ; i < results.size(); i++ ){

        QString result = results.at(i).toString();
        //qDebug() << "result " << result;
        t.gid = result;
    }
    downDB->SetDBRecord( t );
*/

    QString result = nObj.value("result").toString();
    //qDebug() << result;

    DDRecord t;
    t.id =  nObj.value("id").toString();
    t.gid = nObj.value("result").toString();

    this->mainUI->downDB->SetDTaskGid( t );

}

//"aria2.getPeers"
void Aria2cRPCMsg::Aria2cRMsg_getPeers( QJsonObject nObj ){

  /** OK: "{"id":"100","jsonrpc":"2.0","result":[]}" */
  QJsonArray results =  nObj.value("result").toArray();
  for( int i = 0 ; i < results.size(); i++ ){

        QString result = results.at(i).toString();
        //qDebug() << "result " << result;
  }

}

//"aria2.addMetalink"
void Aria2cRPCMsg::Aria2cRMsg_addMetalink( QJsonObject nObj ){

  /** OK: "{"id":"200","jsonrpc":"2.0","result":["678ba8d6ba1ec249"]}" */

  //QString result = nObj.value("result").toString();
  ////qDebug() << result;

  DDRecord t;
  t.id =  nObj.value("id").toString();

  QJsonArray results =  nObj.value("result").toArray();
  for( int i = 0 ; i < results.size(); i++ ){

      QString result = results.at(i).toString();
      //qDebug() << "result " << result;

      t.gid = result;
  }

  this->mainUI->downDB->SetDTaskGid( t );

}

//"aria2.remove"
void Aria2cRPCMsg::Aria2cRMsg_remove( QJsonObject nObj ){

    /** OK: "{"id":"100","jsonrpc":"2.0","result":"ab3e671a1812e81b"}" */

    QString result = nObj.value("result").toString();
    //qDebug() << result;

    DDRecord t;
    t.id =  nObj.value("id").toString();
    t.gid = nObj.value("result").toString();

    this->mainUI->downDB->SetDTaskGid( t );


}

//"aria2.pause"
void Aria2cRPCMsg::Aria2cRMsg_pause( QJsonObject nObj ){

    /** OK: "{"id":"100","jsonrpc":"2.0","result":"231545b19d50fe15"}" */

    QString result = nObj.value("result").toString();
    //qDebug() << result;

    DDRecord t;
    t.id =  nObj.value("id").toString();
    t.gid = nObj.value("result").toString();

    this->mainUI->downDB->SetDTaskGid( t );

}

//"aria2.forcePause"
void Aria2cRPCMsg::Aria2cRMsg_forcePause( QJsonObject nObj ){

    /** OK: "{"id":"100","jsonrpc":"2.0","result":"85115ce9b08bfe50"}" */

    QString result = nObj.value("result").toString();
    //qDebug() << result;

    DDRecord t;
    t.id =  nObj.value("id").toString();
    t.gid = nObj.value("result").toString();

    this->mainUI->downDB->SetDTaskGid( t );
}

//"aria2.pauseAll"
void Aria2cRPCMsg::Aria2cRMsg_pauseAll( QJsonObject nObj ){

    /** OK: "{"id":"100","jsonrpc":"2.0","result":"OK"}" */

    QString result = nObj.value("result").toString();
    //qDebug() << result;
}

//"aria2.forcePauseAll"
void Aria2cRPCMsg::Aria2cRMsg_forcePauseAll( QJsonObject nObj ){

    /** OK: "{"id":"100","jsonrpc":"2.0","result":"OK"}" */

    QString result = nObj.value("result").toString();
    //qDebug() << result;
}

//"aria2.unpause"
void Aria2cRPCMsg::Aria2cRMsg_unpause( QJsonObject nObj ){

    /** OK: "{"id":"100","jsonrpc":"2.0","result":"85115ce9b08bfe50"}" */

    QString result = nObj.value("result").toString();
    //qDebug() << result;

    DDRecord t;
    t.id =  nObj.value("id").toString();
    t.gid = nObj.value("result").toString();

    this->mainUI->downDB->SetDTaskGid( t );


}

//"aria2.unpauseAll"
void Aria2cRPCMsg::Aria2cRMsg_unpauseAll( QJsonObject nObj ){

   /** OK: "{"id":"100","jsonrpc":"2.0","result":"OK"}" */

    QString result = nObj.value("result").toString();
    //qDebug() << result;
}

//"aria2.forceRemove"
void Aria2cRPCMsg::Aria2cRMsg_forceRemove( QJsonObject nObj ){

   /** OK: "{"id":"100","jsonrpc":"2.0","result":"85115ce9b08bfe50"}" */

    QString result = nObj.value("result").toString();
    //qDebug() << result;

    DDRecord t;
    t.id =  nObj.value("id").toString();
    t.gid = nObj.value("result").toString();

    this->mainUI->downDB->SetDTaskGid( t );
}

//"aria2.changePosition"
void Aria2cRPCMsg::Aria2cRMsg_changePosition( QJsonObject nObj ){

   //qDebug() << "aria2.changePosition";
}


//"aria2.getUris"
void Aria2cRPCMsg::Aria2cRMsg_getUris( QJsonObject nObj ){

    /**
        {
          "id": "100",
          "jsonrpc": "2.0",
          "result": [
            {
              "status": "used",
              "uri": "http://sw.bos.baidu.com/sw-search-sp/software/16d5a98d3e034/QQ_8.9.5.22062_setup.exe"
            }
          ]
        }
    */
    QJsonArray results = nObj.value("result").toArray();
    for( int i = 0 ; i < results.size() ; i++ ){

        QJsonObject result = results.at(i).toObject();
        //qDebug() << "status" << result.value( "status" ).toString();
        //qDebug() << "uri" << result.value( "uri" ).toString();
    }

}

//"aria2.getFiles"
void Aria2cRPCMsg::Aria2cRMsg_getFiles( QJsonObject nObj ){

     /**
        {
          "id": "100",
          "jsonrpc": "2.0",
          "result": [
            {
              "completedLength": "26214400",
              "index": "1",
              "length": "71154592",
              "path": "/home/gaochong/Desktop/QQ_8.9.5.22062_setup.1.exe",
              "selected": "true",
              "uris": [
                {
                  "status": "used",
                  "uri": "http://sw.bos.baidu.com/sw-search-sp/software/16d5a98d3e034/QQ_8.9.5.22062_setup.exe"
                }
              ]
            }
          ]
        }
      **/

    QJsonArray  results = nObj.value("result").toArray();

    for( int i = 0 ; i < results.size(); i++ ){

        QJsonObject result = results.at( i ).toObject();
        //qDebug() <<  "completedLength" << result.value("completedLength").toString();
        //qDebug() <<  "index" << result.value("index").toString();
        //qDebug() <<  "length" << result.value("length").toString();
        //qDebug() <<  "path" << result.value("path").toString();
        //qDebug() <<  "selected" << result.value("selected").toString();

        QJsonArray uris = result.value("uris").toArray();
        for( int j = 0 ; j < uris.size() ; j++ ){

            QJsonObject uri = uris.at(j).toObject();
            //qDebug() <<  "status" << uri.value("status");
            //qDebug() <<  "uri" << uri.value("uri");
        }
    }

}

//"aria2.getServers"
void Aria2cRPCMsg::Aria2cRMsg_getServers( QJsonObject nObj ){

      /**
        {
          "id": "100",
          "jsonrpc": "2.0",
          "result": [
            {
              "index": "1",
              "servers": [
                {
                  "currentUri": "http://sw.bos.baidu.com/sw-search-sp/software/16d5a98d3e034/QQ_8.9.5.22062_setup.exe",
                  "downloadSpeed": "187768",
                  "uri": "http://sw.bos.baidu.com/sw-search-sp/software/16d5a98d3e034/QQ_8.9.5.22062_setup.exe"
                }
              ]
            }
          ]
        }
        */

        QJsonArray  results = nObj.value("result").toArray();

        for( int i = 0 ; i < results.size() ; i++ ){

            QJsonObject result = results.at( i ).toObject();

            //qDebug() << "index " << result.value("index").toString();

            QJsonArray servers = result.value("servers").toArray();

            for( int j = 0 ;  j < servers.size() ; j++ ){

                QJsonObject server = servers.at( j ).toObject();

                //qDebug() << "currentUri " << server.value("currentUri").toString();
                //qDebug() << "downloadSpeed " << server.value("downloadSpeed").toString();
                //qDebug() << "uri " << server.value("uri").toString();
            }
        }

}

/**
*
=================================================================================================== **/

//"aria2.tellStatus"
void Aria2cRPCMsg::Aria2cRMsg_tellStatus( QJsonObject nObj ){

    /**
        {
          "id": "100",
          "jsonrpc": "2.0",
          "result": {
            "bitfield": "fffffffffffffffff0",
            "completedLength": "71154592",
            "connections": "0",
            "dir": "/home/gaochong/Desktop",
            "downloadSpeed": "0",
            "errorCode": "0",
            "errorMessage": ",
            "files": [
              {
                "completedLength": "71154592",
                "index": "1",
                "length": "71154592",
                "path": "/home/gaochong/Desktop/QQ_8.9.5.22062_setup.exe",
                "selected": "true",
                "uris": [
                  {
                    "status": "used",
                    "uri": "http://sw.bos.baidu.com/sw-search-sp/software/16d5a98d3e034/QQ_8.9.5.22062_setup.exe"
                  }
                ]
              }
            ],
            "gid": "4783c9b98d8faa97",
            "numPieces": "68",
            "pieceLength": "1048576",
            "status": "complete",
            "totalLength": "71154592",
            "uploadLength": "0",
            "uploadSpeed": "0"
          }
        }
    */


        TBItem tbitem;

        QJsonObject  result = nObj.value("result").toObject();
/*
        //qDebug() << "bitfield" << result.value("bitfield").toString();
        //qDebug() << "completedLength" << result.value("completedLength").toString();
        //qDebug() << "connections" << result.value("connections").toString();
        //qDebug() << "dir " << result.value("dir").toString();
        //qDebug() << "downloadSpeed " << result.value("downloadSpeed").toString();
        ////qDebug() << "errorCode " << result.value("errorCode").toString();
        ////qDebug() << "errorMessage " << result.value("errorMessage").toString();

*/
        QJsonArray files = result.value("files").toArray();

        for( int i = 0 ; i < files.size() ; i++ ){

            QJsonObject file = files.at(i).toObject();
/*
            //qDebug() <<  "completedLength" << file.value("completedLength").toString();
            //qDebug() <<  "index" << file.value("index").toString();
            //qDebug() <<  "length" << file.value("length").toString();
            //qDebug() <<  "path" << file.value("path").toString();
            //qDebug() <<  "selected" << file.value("selected").toString();
*/
            tbitem.savepath =  file.value("path").toString();


            QJsonArray uris = file.value("uris").toArray();
            for( int j = 0 ; j < uris.size() ; j++ ){

                QJsonObject uri = uris.at(j).toObject();

/*
                //qDebug() <<  "status" << uri.value("status");
                //qDebug() <<  "uri" << uri.value("uri");
*/

                tbitem.uri = uri.value("uri").toString();

            }

            if( uris.size() == 0 ){
                tbitem.uri = tbitem.savepath;
            }
        }


/*
        //qDebug() <<"gid"<< result.value("gid").toString();
        //qDebug() <<"numPieces"<< result.value("numPieces").toString();
        //qDebug() <<"pieceLength"<< result.value("pieceLength").toString();
        //qDebug() <<"status"<< result.value("status").toString();
        //qDebug() <<"totalLength"<< result.value("totalLength").toString();
        //qDebug() <<"uploadLength"<< result.value("uploadLength").toString();
        //qDebug() <<"uploadSpeed"<< result.value("uploadSpeed").toString();
*/

         tbitem.gid = result.value("gid").toString();

         QString totalLength = result.value("totalLength").toString();
         QString completedLength = result.value( "completedLength" ).toString();

         bool ok;
         long totalLength_long = totalLength.toLong( &ok,10 );
         long completedLength_long = completedLength.toLong( &ok,10 );

         ////qDebug() << "totalLengthr_long " << totalLength_long;
         ////qDebug() << "completedLength_long " << completedLength_long;

         int  bitfield = 0;
         if ( completedLength_long >0 ){

           bitfield = qRound( completedLength_long * 100.0 / totalLength_long );
         }

         tbitem.RestTime = totalLength + "|" + completedLength;
         tbitem.Progress = QString::number( bitfield ,10 );  //进度
         tbitem.Speed = result.value( "downloadSpeed" ).toString(); //下载速度
         tbitem.State = result.value( "status" ).toString();    //状态

         this->mainUI->UpdateGUI_StatusMsg( tbitem );

}

//"aria2.tellActive"
void Aria2cRPCMsg::Aria2cRMsg_tellActive( QJsonObject nObj ){

    Aria2cRMsg_tellMessage( nObj );

}

//"aria2.tellWaiting"
void Aria2cRPCMsg::Aria2cRMsg_tellWaiting( QJsonObject nObj ){

    Aria2cRMsg_tellMessage( nObj );

}

//"aria2.tellStopped"
void Aria2cRPCMsg::Aria2cRMsg_tellStopped( QJsonObject nObj ){

    Aria2cRMsg_tellMessage( nObj );

}

/** ================================================================================================ ***/

//"aria2.getOption"
void Aria2cRPCMsg::Aria2cRMsg_getOption( QJsonObject nObj ){

    /**
    {
      "id": "100",
      "jsonrpc": "2.0",
      "result": {
        "allow-overwrite": "false",
        "allow-piece-length-change": "false",
        "always-resume": "true",
        "async-dns": "true",
        "auto-file-renaming": "true",
        "bt-enable-hook-after-hash-check": "true",
        "bt-enable-lpd": "false",
        "bt-force-encryption": "false",
        "bt-hash-check-seed": "true",
        "bt-max-peers": "55",
        "bt-metadata-only": "false",
        "bt-min-crypto-level": "plain",
        "bt-remove-unselected-file": "false",
        "bt-request-peer-speed-limit": "51200",
        "bt-require-crypto": "false",
        "bt-save-metadata": "false",
        "bt-seed-unverified": "false",
        "bt-stop-timeout": "0",
        "bt-tracker-connect-timeout": "60",
        "bt-tracker-interval": "0",
        "bt-tracker-timeout": "60",
        "check-integrity": "false",
        "conditional-get": "false",
        "connect-timeout": "60",
        "content-disposition-default-utf8": "false",
        "continue": "true",
        "dir": "/home/gaochong/Desktop",
        "dry-run": "false",
        "enable-http-keep-alive": "true",
        "enable-http-pipelining": "false",
        "enable-mmap": "false",
        "enable-peer-exchange": "true",
        "file-allocation": "prealloc",
        "follow-metalink": "true",
        "follow-torrent": "true",
        "force-save": "false",
        "ftp-pasv": "true",
        "ftp-reuse-connection": "true",
        "ftp-type": "binary",
        "hash-check-only": "false",
        "http-accept-gzip": "false",
        "http-auth-challenge": "false",
        "http-no-cache": "false",
        "lowest-speed-limit": "0",
        "max-connection-per-server": "1",
        "max-download-limit": "0",
        "max-file-not-found": "0",
        "max-mmap-limit": "9223372036854775807",
        "max-resume-failure-tries": "0",
        "max-tries": "5",
        "max-upload-limit": "0",
        "metalink-enable-unique-protocol": "true",
        "metalink-preferred-protocol": "none",
        "min-split-size": "20971520",
        "no-file-allocation-limit": "5242880",
        "no-netrc": "false",
        "parameterized-uri": "false",
        "pause-metadata": "false",
        "piece-length": "1048576",
        "proxy-method": "get",
        "realtime-chunk-checksum": "true",
        "remote-time": "false",
        "remove-control-file": "false",
        "retry-wait": "0",
        "reuse-uri": "true",
        "rpc-save-upload-metadata": "true",
        "save-not-found": "true",
        "seed-ratio": "1.0",
        "split": "5",
        "stream-piece-selector": "default",
        "timeout": "60",
        "uri-selector": "feedback",
        "use-head": "false",
        "user-agent": "aria2/1.32.0"
      }
    }
 */

    Option itemOption;

    QJsonObject result = nObj.value("result").toObject();

    itemOption.allow_overwrite   = result.value("allow-overwrite").toString();
    itemOption.allow_piece_length_change   = result.value("allow-piece-length-change").toString();
    itemOption.always_resume   = result.value("always-resume").toString();
    itemOption.async_dns   = result.value("async-dns").toString();
    itemOption.auto_file_renaming   = result.value("auto-file-renaming").toString();
    itemOption.bt_enable_hook_after_hash_check   = result.value("bt-enable-hook-after-hash-check").toString();
    itemOption.bt_enable_lpd   = result.value("bt-enable-lpd").toString();
    itemOption.bt_force_encryption   = result.value("bt-force-encryption").toString();
    itemOption.bt_hash_check_seed   = result.value("bt-hash-check-seed").toString();
    itemOption.bt_max_peers   = result.value("bt-max-peers").toString();
    itemOption.bt_metadata_only   = result.value("bt-metadata-only").toString();
    itemOption.bt_min_crypto_level   = result.value("bt-min-crypto-level").toString();
    itemOption.bt_remove_unselected_file   = result.value("bt-remove-unselected-file").toString();
    itemOption.bt_request_peer_speed_limit   = result.value("bt-request-peer-speed-limit").toString();
    itemOption.bt_require_crypto   = result.value("bt-require-crypto").toString();
    itemOption.bt_save_metadata   = result.value("bt-save-metadata").toString();
    itemOption.bt_seed_unverified   = result.value("bt-seed-unverified").toString();
    itemOption.bt_stop_timeout   = result.value("bt-stop-timeout").toString();
    itemOption.bt_tracker_connect_timeout   = result.value("bt-tracker-connect-timeout").toString();
    itemOption.bt_tracker_interval   = result.value("bt-tracker-interval").toString();
    itemOption.bt_tracker_timeout   = result.value("bt-tracker-timeout").toString();
    itemOption.check_integrity   = result.value("check-integrity").toString();
    itemOption.conditional_get   = result.value("conditional-get").toString();
    itemOption.connect_timeout   = result.value("connect-timeout").toString();
    itemOption.content_disposition_default_utf8  = result.value("content-disposition-default-utf8").toString();
    itemOption._continue   = result.value("continue").toString();
    itemOption.dir   = result.value("dir").toString();
    itemOption.dry_run   = result.value("dry-run").toString();
    itemOption.enable_http_keep_alive   = result.value("enable-http-keep-alive").toString();
    itemOption.enable_http_pipelining   = result.value("enable-http-pipelining").toString();
    itemOption.enable_mmap   = result.value("enable-mmap").toString();
    itemOption.enable_peer_exchange   = result.value("enable-peer-exchange").toString();
    itemOption.file_allocation   = result.value("file-allocation").toString();
    itemOption.follow_metalink   = result.value("follow-metalink").toString();
    itemOption.follow_torrent   = result.value("follow-torrent").toString();
    itemOption.force_save   = result.value("force-save").toString();
    itemOption.ftp_pasv   = result.value("ftp-pasv").toString();
    itemOption.ftp_reuse_connection   = result.value("ftp-reuse-connection").toString();
    itemOption.ftp_type   = result.value("ftp-type").toString();
    itemOption.hash_check_only   = result.value("hash-check-only").toString();
    itemOption.http_accept_gzip   = result.value("http-accept-gzip").toString();
    itemOption.http_auth_challenge   = result.value("http-auth-challenge").toString();
    itemOption.http_no_cache   = result.value("http-no-cache").toString();
    itemOption.lowest_speed_limit   = result.value("lowest-speed-limit").toString();
    itemOption.max_connection_per_server   = result.value("max-connection-per-server").toString();
    itemOption.max_download_limit   = result.value("max-download-limit").toString();
    itemOption.max_file_not_found   = result.value("max-file-not-found").toString();
    itemOption.max_mmap_limit   = result.value("max-mmap-limit").toString();
    itemOption.max_resume_failure_tries   = result.value("max-resume-failure-tries").toString();
    itemOption.max_tries   = result.value("max-tries").toString();
    itemOption.max_upload_limit   = result.value("max-upload-limit").toString();
    itemOption.metalink_enable_unique_protocol   = result.value("metalink-enable-unique-protocol").toString();
    itemOption.metalink_preferred_protocol   = result.value("metalink-preferred-protocol").toString();
    itemOption.min_split_size   = result.value("min-split-size").toString();
    itemOption.no_file_allocation_limit   = result.value("no-file-allocation-limit").toString();
    itemOption.no_netrc   = result.value("no-netrc").toString();
    itemOption.parameterized_uri   = result.value("parameterized-uri").toString();
    itemOption.pause_metadata   = result.value("pause-metadata").toString();
    itemOption.piece_length   = result.value("piece-length").toString();
    itemOption.proxy_method   = result.value("proxy-method").toString();
    itemOption.realtime_chunk_checksum   = result.value("realtime-chunk-checksum").toString();
    itemOption.remote_time   = result.value("remote-time").toString();
    itemOption.remove_control_file   = result.value("remove-control-file").toString();
    itemOption.retry_wait   = result.value("retry-wait").toString();
    itemOption.reuse_uri   = result.value("reuse-uri").toString();
    itemOption.rpc_save_upload_metadata   = result.value("rpc-save-upload-metadata").toString();
    itemOption.save_not_found   = result.value("save-not-found").toString();
    itemOption.seed_ratio = result.value("seed-ratio").toString();
    itemOption.split   = result.value("split").toString();
    itemOption.stream_piece_selector   = result.value("stream-piece-selector").toString();
    itemOption.timeout   = result.value("timeout").toString();
    itemOption.uri_selector   = result.value("uri-selector").toString();
    itemOption.use_head   = result.value("use-head").toString();
    itemOption.user_agent = result.value("user-agent").toString();

    //qDebug() << itemOption.allow_overwrite;
    //qDebug() << itemOption.allow_piece_length_change;
    //qDebug() << itemOption.always_resume;
    //qDebug() << itemOption.async_dns;
    //qDebug() << itemOption.auto_file_renaming;
    //qDebug() << itemOption.bt_enable_hook_after_hash_check;
    //qDebug() << itemOption.bt_enable_lpd;
    //qDebug() << itemOption.bt_force_encryption;
    //qDebug() << itemOption.bt_hash_check_seed;
    //qDebug() << itemOption.bt_max_peers;
    //qDebug() << itemOption.bt_metadata_only;
    //qDebug() << itemOption.bt_min_crypto_level;
    //qDebug() << itemOption.bt_remove_unselected_file;
    //qDebug() << itemOption.bt_request_peer_speed_limit;
    //qDebug() << itemOption.bt_require_crypto;
    //qDebug() << itemOption.bt_save_metadata;
    //qDebug() << itemOption.bt_seed_unverified;
    //qDebug() << itemOption.bt_stop_timeout;
    //qDebug() << itemOption.bt_tracker_connect_timeout;
    //qDebug() << itemOption.bt_tracker_interval;
    //qDebug() << itemOption.bt_tracker_timeout;
    //qDebug() << itemOption.check_integrity;
    //qDebug() << itemOption.conditional_get;
    //qDebug() << itemOption.connect_timeout;
    //qDebug() << itemOption.content_disposition_default_utf8 ;
    //qDebug() << itemOption._continue;
    //qDebug() << itemOption.dir;
    //qDebug() << itemOption.dry_run;
    //qDebug() << itemOption.enable_http_keep_alive;
    //qDebug() << itemOption.enable_http_pipelining;
    //qDebug() << itemOption.enable_mmap ;
    //qDebug() << itemOption.enable_peer_exchange;
    //qDebug() << itemOption.file_allocation;
    //qDebug() << itemOption.follow_metalink;
    //qDebug() << itemOption.follow_torrent;
    //qDebug() << itemOption.force_save;
    //qDebug() << itemOption.ftp_pasv;
    //qDebug() << itemOption.ftp_reuse_connection;
    //qDebug() << itemOption.ftp_type;
    //qDebug() << itemOption.hash_check_only;
    //qDebug() << itemOption.http_accept_gzip ;
    //qDebug() << itemOption.http_auth_challenge ;
    //qDebug() << itemOption.http_no_cache;
    //qDebug() << itemOption.lowest_speed_limit;
    //qDebug() << itemOption.max_connection_per_server ;
    //qDebug() << itemOption.max_download_limit;
    //qDebug() << itemOption.max_file_not_found;
    //qDebug() << itemOption.max_mmap_limit;
    //qDebug() << itemOption.max_resume_failure_tries;
    //qDebug() << itemOption.max_tries;
    //qDebug() << itemOption.max_upload_limit;
    //qDebug() << itemOption.metalink_enable_unique_protocol ;
    //qDebug() << itemOption.metalink_preferred_protocol ;
    //qDebug() << itemOption.min_split_size;
    //qDebug() << itemOption.no_file_allocation_limit;
    //qDebug() << itemOption.no_netrc;
    //qDebug() << itemOption.parameterized_uri;
    //qDebug() << itemOption.pause_metadata;
    //qDebug() << itemOption.piece_length;
    //qDebug() << itemOption.proxy_method;
    //qDebug() << itemOption.realtime_chunk_checksum;
    //qDebug() << itemOption.remote_time;
    //qDebug() << itemOption.remove_control_file ;
    //qDebug() << itemOption.retry_wait;
    //qDebug() << itemOption.reuse_uri;
    //qDebug() << itemOption.rpc_save_upload_metadata;
    //qDebug() << itemOption.save_not_found ;
    //qDebug() << itemOption.seed_ratio;
    //qDebug() << itemOption.split;
    //qDebug() << itemOption.stream_piece_selector;
    //qDebug() << itemOption.timeout;
    //qDebug() << itemOption.uri_selector;
    //qDebug() << itemOption.use_head;
    //qDebug() << itemOption.user_agent;
}

//"aria2.changeUri"
void Aria2cRPCMsg::Aria2cRMsg_changeUri( QJsonObject nObj ){

   /** OK: "{\"id\":\"0\",\"jsonrpc\":\"2.0\",\"result\":[0,1]}" */

    QString result = nObj.value("result").toString();
    qDebug()<< "result" << result;

}

//"aria2.changeOption"
void Aria2cRPCMsg::Aria2cRMsg_changeOption( QJsonObject  nObj ){

   /** OK: "{\"id\":\"100\",\"jsonrpc\":\"2.0\",\"result\":\"OK\"}" */

    QString result = nObj.value("result").toString();
    qDebug()<< "result" << result;
}

//"aria2.getGlobalOption"
void Aria2cRPCMsg::Aria2cRMsg_getGlobalOption( QJsonObject nObj ){

    /**
    {
      "id": "100",
      "jsonrpc": "2.0",
      "result": {
        "allow-overwrite": "false",
        "allow-piece-length-change": "false",
        "always-resume": "true",
        "async-dns": "true",
        "auto-file-renaming": "true",
        "auto-save-interval": "60",
        "bt-detach-seed-only": "false",
        "bt-enable-hook-after-hash-check": "true",
        "bt-enable-lpd": "false",
        "bt-force-encryption": "false",
        "bt-hash-check-seed": "true",
        "bt-max-open-files": "100",
        "bt-max-peers": "55",
        "bt-metadata-only": "false",
        "bt-min-crypto-level": "plain",
        "bt-remove-unselected-file": "false",
        "bt-request-peer-speed-limit": "51200",
        "bt-require-crypto": "false",
        "bt-save-metadata": "false",
        "bt-seed-unverified": "false",
        "bt-stop-timeout": "0",
        "bt-tracker-connect-timeout": "60",
        "bt-tracker-interval": "0",
        "bt-tracker-timeout": "60",
        "ca-certificate": "/etc/ssl/certs/ca-certificates.crt",
        "check-certificate": "false",
        "check-integrity": "false",
        "conditional-get": "false",
        "conf-path": "/home/gaochong/.config/aria2/aria2.conf",
        "connect-timeout": "60",
        "console-log-level": "notice",
        "content-disposition-default-utf8": "false",
        "continue": "true",
        "daemon": "false",
        "deferred-input": "false",
        "dht-file-path": "/home/gaochong/.cache/aria2/dht.dat",
        "dht-file-path6": "/home/gaochong/.cache/aria2/dht6.dat",
        "dht-listen-port": "6881-6999",
        "dht-message-timeout": "10",
        "dir": "/home/gaochong/Desktop",
        "disable-ipv6": "true",
        "disk-cache": "16777216",
        "download-result": "default",
        "dry-run": "false",
        "dscp": "0",
        "enable-color": "true",
        "enable-dht": "true",
        "enable-dht6": "false",
        "enable-http-keep-alive": "true",
        "enable-http-pipelining": "false",
        "enable-mmap": "false",
        "enable-peer-exchange": "true",
        "enable-rpc": "true",
        "event-poll": "epoll",
        "file-allocation": "prealloc",
        "follow-metalink": "true",
        "follow-torrent": "true",
        "force-save": "false",
        "ftp-pasv": "true",
        "ftp-reuse-connection": "true",
        "ftp-type": "binary",
        "hash-check-only": "false",
        "help": "#basic",
        "http-accept-gzip": "false",
        "http-auth-challenge": "false",
        "http-no-cache": "false",
        "human-readable": "true",
        "keep-unfinished-download-result": "true",
        "listen-port": "6881-6999",
        "log-level": "debug",
        "lowest-speed-limit": "0",
        "max-concurrent-downloads": "5",
        "max-connection-per-server": "1",
        "max-download-limit": "0",
        "max-download-result": "1000",
        "max-file-not-found": "0",
        "max-mmap-limit": "9223372036854775807",
        "max-overall-download-limit": "524288",
        "max-overall-upload-limit": "0",
        "max-resume-failure-tries": "0",
        "max-tries": "5",
        "max-upload-limit": "0",
        "metalink-enable-unique-protocol": "true",
        "metalink-preferred-protocol": "none",
        "min-split-size": "20971520",
        "min-tls-version": "TLSv1",
        "netrc-path": "/home/gaochong/.netrc",
        "no-conf": "false",
        "no-file-allocation-limit": "5242880",
        "no-netrc": "false",
        "optimize-concurrent-downloads": "false",
        "parameterized-uri": "false",
        "pause-metadata": "false",
        "peer-id-prefix": "A2-1-32-0-",
        "piece-length": "1048576",
        "proxy-method": "get",
        "quiet": "false",
        "realtime-chunk-checksum": "true",
        "remote-time": "false",
        "remove-control-file": "false",
        "retry-wait": "0",
        "reuse-uri": "true",
        "rlimit-nofile": "1024",
        "rpc-allow-origin-all": "false",
        "rpc-listen-all": "false",
        "rpc-listen-port": "6800",
        "rpc-max-request-size": "2097152",
        "rpc-save-upload-metadata": "true",
        "rpc-secure": "false",
        "save-not-found": "true",
        "save-session": "/home/gaochong/aria2c.cache",
        "save-session-interval": "0",
        "seed-ratio": "1.0",
        "server-stat-timeout": "86400",
        "show-console-readout": "true",
        "show-files": "false",
        "socket-recv-buffer-size": "0",
        "split": "5",
        "stderr": "false",
        "stop": "0",
        "stream-piece-selector": "default",
        "summary-interval": "60",
        "timeout": "60",
        "truncate-console-readout": "true",
        "uri-selector": "feedback",
        "use-head": "false",
        "user-agent": "aria2/1.32.0"
      }
    }
    */

    GlobalOption globaloption;

    QJsonObject result = nObj.value("result").toObject();

    globaloption.allow_overwrite = result.value("allow-overwrite").toString();
    globaloption.allow_piece_length_change  = result.value("allow-piece-length-change").toString();
    globaloption.always_resume  = result.value("always-resume").toString();
    globaloption.async_dns  = result.value("async-dns").toString();
    globaloption.auto_file_renaming  = result.value("auto-file-renaming").toString();
    globaloption.auto_save_interval  = result.value("auto-save-interval").toString();
    globaloption.bt_detach_seed_only  = result.value("bt-detach-seed-only").toString();
    globaloption.bt_enable_hook_after_hash_check  = result.value("bt-enable-hook-after-hash-check").toString();
    globaloption.bt_enable_lpd  = result.value("bt-enable-lpd").toString();
    globaloption.bt_force_encryption  = result.value("bt-force-encryption").toString();
    globaloption.bt_hash_check_seed  = result.value("bt-hash-check-seed").toString();
    globaloption.bt_max_open_files  = result.value("bt-max-open-files").toString();
    globaloption.bt_max_peers  = result.value("bt-max-peers").toString();
    globaloption.bt_metadata_only  = result.value("bt-metadata-only").toString();
    globaloption.bt_min_crypto_level  = result.value("bt-min-crypto-level").toString();
    globaloption.bt_remove_unselected_file  = result.value("bt-remove-unselected-file").toString();
    globaloption.bt_request_peer_speed_limit  = result.value("bt-request-peer-speed-limit").toString();
    globaloption.bt_require_crypto  = result.value("bt-require-crypto").toString();
    globaloption.bt_save_metadata  = result.value("bt-save-metadata").toString();
    globaloption.bt_seed_unverified  = result.value("bt-seed-unverified").toString();
    globaloption.bt_stop_timeout  = result.value("bt-stop-timeout").toString();
    globaloption.bt_tracker_connect_timeout  = result.value("bt-tracker-connect-timeout").toString();
    globaloption.bt_tracker_interval  = result.value("bt-tracker-interval").toString();
    globaloption.bt_tracker_timeout  = result.value("bt-tracker-timeout").toString();
    globaloption.ca_certificate  = result.value("ca-certificate").toString();
    globaloption.check_certificate  = result.value("check-certificate").toString();
    globaloption.check_integrity  = result.value("check-integrity").toString();
    globaloption.conditional_get  = result.value("conditional-get").toString();
    globaloption.conf_path  = result.value("conf-path").toString();
    globaloption.connect_timeout  = result.value("connect-timeout").toString();
    globaloption.console_log_level  = result.value("console-log-level").toString();
    globaloption.content_disposition_default_utf8  = result.value("content-disposition-default-utf8").toString();
    globaloption._continue  = result.value("continue").toString();
    globaloption.daemon  = result.value("daemon").toString();
    globaloption.deferred_input  = result.value("deferred-input").toString();
    globaloption.dht_file_path  = result.value("dht-file-path").toString();
    globaloption.dht_file_path6  = result.value("dht-file-path6").toString();
    globaloption.dht_listen_port  = result.value("dht-listen-port").toString();
    globaloption.dht_message_timeout  = result.value("dht-message-timeout").toString();
    globaloption.dir  = result.value("dir").toString();
    globaloption.disable_ipv6  = result.value("disable-ipv6").toString();
    globaloption.disk_cache  = result.value("disk-cache").toString();
    globaloption.download_result  = result.value("download-result").toString();
    globaloption.dry_run  = result.value("dry-run").toString();
    globaloption.dscp  = result.value("dscp").toString();
    globaloption.enable_color  = result.value("enable-color").toString();
    globaloption.enable_dht  = result.value("enable-dht").toString();
    globaloption.enable_dht6  = result.value("enable-dht6").toString();
    globaloption.enable_http_keep_alive  = result.value("enable-http-keep-alive").toString();
    globaloption.enable_http_pipelining  = result.value("enable-http-pipelining").toString();
    globaloption.enable_mmap  = result.value("enable-mmap").toString();
    globaloption.enable_peer_exchange  = result.value("enable-peer-exchange").toString();
    globaloption.enable_rpc  = result.value("enable-rpc").toString();
    globaloption.event_poll  = result.value("event-poll").toString();
    globaloption.file_allocation  = result.value("file-allocation").toString();
    globaloption.follow_metalink  = result.value("follow-metalink").toString();
    globaloption.follow_torrent  = result.value("follow-torrent").toString();
    globaloption.force_save  = result.value("force-save").toString();
    globaloption.ftp_pasv  = result.value("ftp-pasv").toString();
    globaloption.ftp_reuse_connection  = result.value("ftp-reuse-connection").toString();
    globaloption.ftp_type  = result.value("ftp-type").toString();
    globaloption.hash_check_only  = result.value("hash-check-only").toString();
    globaloption.help  = result.value("help").toString();
    globaloption.http_accept_gzip  = result.value("http-accept-gzip").toString();
    globaloption.http_auth_challenge  = result.value("http-auth-challenge").toString();
    globaloption.http_no_cache  = result.value("http-no-cache").toString();
    globaloption.human_readable  = result.value("human-readable").toString();
    globaloption.keep_unfinished_download_result  = result.value("keep-unfinished-download-result").toString();
    globaloption.listen_port  = result.value("listen-port").toString();
    globaloption.log_level  = result.value("log-level").toString();
    globaloption.lowest_speed_limit  = result.value("lowest-speed-limit").toString();
    globaloption.max_concurrent_downloads  = result.value("max-concurrent-downloads").toString();
    globaloption.max_connection_per_server  = result.value("max-connection-per-server").toString();
    globaloption.max_download_limit  = result.value("max-download-limit").toString();
    globaloption.max_download_result  = result.value("max-download-result").toString();
    globaloption.max_file_not_found  = result.value("max-file-not-found").toString();
    globaloption.max_mmap_limit  = result.value("max-mmap-limit").toString();
    globaloption.max_overall_download_limit  = result.value("max-overall-download-limit").toString();
    globaloption.max_overall_upload_limit  = result.value("max-overall-upload-limit").toString();
    globaloption.max_resume_failure_tries  = result.value("max-resume-failure-tries").toString();
    globaloption.max_tries  = result.value("max-tries").toString();
    globaloption.max_upload_limit  = result.value("max-upload-limit").toString();
    globaloption.metalink_enable_unique_protocol  = result.value("metalink-enable-unique-protocol").toString();
    globaloption.metalink_preferred_protocol  = result.value("metalink-preferred-protocol").toString();
    globaloption.min_split_size  = result.value("min-split-size").toString();
    globaloption.min_tls_version  = result.value("min-tls-version").toString();
    globaloption.netrc_path  = result.value("netrc-path").toString();
    globaloption.no_conf  = result.value("no-conf").toString();
    globaloption.no_file_allocation_limit  = result.value("no-file-allocation-limit").toString();
    globaloption.no_netrc  = result.value("no-netrc").toString();
    globaloption.optimize_concurrent_downloads  = result.value("optimize-concurrent-downloads").toString();
    globaloption.parameterized_uri  = result.value("parameterized-uri").toString();
    globaloption.pause_metadata  = result.value("pause-metadata").toString();
    globaloption.peer_id_prefix  = result.value("peer-id-prefix").toString();
    globaloption.piece_length  = result.value("piece-length").toString();
    globaloption.proxy_method  = result.value("proxy-method").toString();
    globaloption.quiet  = result.value("quiet").toString();
    globaloption.realtime_chunk_checksum  = result.value("realtime-chunk-checksum").toString();
    globaloption.remote_time  = result.value("remote-time").toString();
    globaloption.remove_control_file  = result.value("remove-control-file").toString();
    globaloption.retry_wait = result.value("retry-wait").toString();
    globaloption.reuse_uri  = result.value("reuse-uri").toString();
    globaloption.rlimit_nofile  = result.value("rlimit-nofile").toString();
    globaloption.rpc_allow_origin_all  = result.value("rpc-allow-origin-all").toString();
    globaloption.rpc_listen_all  = result.value("rpc-listen-all").toString();
    globaloption.rpc_listen_port  = result.value("rpc-listen-port").toString();
    globaloption.rpc_max_request_size  = result.value("rpc-max-request-size").toString();
    globaloption.rpc_save_upload_metadata  = result.value("rpc-save-upload-metadata").toString();
    globaloption.rpc_secure  = result.value("rpc-secure").toString();
    globaloption.save_not_found  = result.value("save-not-found").toString();
    globaloption.save_session  = result.value("save-session").toString();
    globaloption.save_session_interval  = result.value("save-session-interval").toString();
    globaloption.seed_ratio  = result.value("seed-ratio").toString();
    globaloption.server_stat_timeout  = result.value("server-stat-timeout").toString();
    globaloption.show_console_readout  = result.value("show-console-readout").toString();
    globaloption.show_files  = result.value("show-files").toString();
    globaloption.socket_recv_buffer_size  = result.value("socket-recv-buffer-size").toString();
    globaloption.split  = result.value("split").toString();
    globaloption.stderr  = result.value("stderr").toString();
    globaloption.stop  = result.value("stop").toString();
    globaloption.stream_piece_selector  = result.value("stream-piece-selector").toString();
    globaloption.summary_interval  = result.value("summary-interval").toString();
    globaloption.timeout  = result.value("timeout").toString();
    globaloption.truncate_console_readout  = result.value("truncate-console-readout").toString();
    globaloption.uri_selector  = result.value("uri-selector").toString();
    globaloption.use_head  = result.value("use-head").toString();
    globaloption.user_agent  = result.value("user-agent").toString();

    //qDebug() << globaloption.allow_overwrite;
    //qDebug() << globaloption.allow_piece_length_change ;
    //qDebug() << globaloption.always_resume ;
    //qDebug() << globaloption.async_dns ;
    //qDebug() << globaloption.auto_file_renaming ;
    //qDebug() << globaloption.auto_save_interval ;
    //qDebug() << globaloption.bt_detach_seed_only ;
    //qDebug() << globaloption.bt_enable_hook_after_hash_check ;
    //qDebug() << globaloption.bt_enable_lpd ;
    //qDebug() << globaloption.bt_force_encryption ;
    //qDebug() << globaloption.bt_hash_check_seed ;
    //qDebug() << globaloption.bt_max_open_files ;
    //qDebug() << globaloption.bt_max_peers ;
    //qDebug() << globaloption.bt_metadata_only ;
    //qDebug() << globaloption.bt_min_crypto_level ;
    //qDebug() << globaloption.bt_remove_unselected_file ;
    //qDebug() << globaloption.bt_request_peer_speed_limit ;
    //qDebug() << globaloption.bt_require_crypto ;
    //qDebug() << globaloption.bt_save_metadata ;
    //qDebug() << globaloption.bt_seed_unverified ;
    //qDebug() << globaloption.bt_stop_timeout ;
    //qDebug() << globaloption.bt_tracker_connect_timeout ;
    //qDebug() << globaloption.bt_tracker_interval ;
    //qDebug() << globaloption.bt_tracker_timeout ;
    //qDebug() << globaloption.ca_certificate ;
    //qDebug() << globaloption.check_certificate ;
    //qDebug() << globaloption.check_integrity ;
    //qDebug() << globaloption.conditional_get ;
    //qDebug() << globaloption.conf_path ;
    //qDebug() << globaloption.connect_timeout ;
    //qDebug() << globaloption.console_log_level ;
    //qDebug() << globaloption.content_disposition_default_utf8 ;
    //qDebug() << globaloption._continue ;
    //qDebug() << globaloption.daemon ;
    //qDebug() << globaloption.deferred_input ;
    //qDebug() << globaloption.dht_file_path ;
    //qDebug() << globaloption.dht_file_path6 ;
    //qDebug() << globaloption.dht_listen_port ;
    //qDebug() << globaloption.dht_message_timeout ;
    //qDebug() << globaloption.dir ;
    //qDebug() << globaloption.disable_ipv6 ;
    //qDebug() << globaloption.disk_cache ;
    //qDebug() << globaloption.download_result ;
    //qDebug() << globaloption.dry_run ;
    //qDebug() << globaloption.dscp ;
    //qDebug() << globaloption.enable_color ;
    //qDebug() << globaloption.enable_dht ;
    //qDebug() << globaloption.enable_dht6 ;
    //qDebug() << globaloption.enable_http_keep_alive ;
    //qDebug() << globaloption.enable_http_pipelining ;
    //qDebug() << globaloption.enable_mmap ;
    //qDebug() << globaloption.enable_peer_exchange ;
    //qDebug() << globaloption.enable_rpc ;
    //qDebug() << globaloption.event_poll ;
    //qDebug() << globaloption.file_allocation ;
    //qDebug() << globaloption.follow_metalink ;
    //qDebug() << globaloption.follow_torrent ;
    //qDebug() << globaloption.force_save ;
    //qDebug() << globaloption.ftp_pasv ;
    //qDebug() << globaloption.ftp_reuse_connection ;
    //qDebug() << globaloption.ftp_type ;
    //qDebug() << globaloption.hash_check_only ;
    //qDebug() << globaloption.help ;
    //qDebug() << globaloption.http_accept_gzip ;
    //qDebug() << globaloption.http_auth_challenge ;
    //qDebug() << globaloption.http_no_cache ;
    //qDebug() << globaloption.human_readable ;
    //qDebug() << globaloption.keep_unfinished_download_result ;
    //qDebug() << globaloption.listen_port ;
    //qDebug() << globaloption.log_level;
    //qDebug() << globaloption.lowest_speed_limit ;
    //qDebug() << globaloption.max_concurrent_downloads ;
    //qDebug() << globaloption.max_connection_per_server ;
    //qDebug() << globaloption.max_download_limit ;
    //qDebug() << globaloption.max_download_result ;
    //qDebug() << globaloption.max_file_not_found ;
    //qDebug() << globaloption.max_mmap_limit ;
    //qDebug() << globaloption.max_overall_download_limit ;
    //qDebug() << globaloption.max_overall_upload_limit ;
    //qDebug() << globaloption.max_resume_failure_tries ;
    //qDebug() << globaloption.max_tries ;
    //qDebug() << globaloption.max_upload_limit ;
    //qDebug() << globaloption.metalink_enable_unique_protocol ;
    //qDebug() << globaloption.metalink_preferred_protocol ;
    //qDebug() << globaloption.min_split_size ;
    //qDebug() << globaloption.min_tls_version ;
    //qDebug() << globaloption.netrc_path ;
    //qDebug() << globaloption.no_conf ;
    //qDebug() << globaloption.no_file_allocation_limit ;
    //qDebug() << globaloption.no_netrc ;
    //qDebug() << globaloption.optimize_concurrent_downloads ;
    //qDebug() << globaloption.parameterized_uri ;
    //qDebug() << globaloption.pause_metadata ;
    //qDebug() << globaloption.peer_id_prefix ;
    //qDebug() << globaloption.piece_length ;
    //qDebug() << globaloption.proxy_method ;
    //qDebug() << globaloption.quiet ;
    //qDebug() << globaloption.realtime_chunk_checksum ;
    //qDebug() << globaloption.remote_time ;
    //qDebug() << globaloption.remove_control_file ;
    //qDebug() << globaloption.retry_wait;
    //qDebug() << globaloption.reuse_uri ;
    //qDebug() << globaloption.rlimit_nofile ;
    //qDebug() << globaloption.rpc_allow_origin_all ;
    //qDebug() << globaloption.rpc_listen_all ;
    //qDebug() << globaloption.rpc_listen_port ;
    //qDebug() << globaloption.rpc_max_request_size ;
    //qDebug() << globaloption.rpc_save_upload_metadata ;
    //qDebug() << globaloption.rpc_secure ;
    //qDebug() << globaloption.save_not_found ;
    //qDebug() << globaloption.save_session ;
    //qDebug() << globaloption.save_session_interval ;
    //qDebug() << globaloption.seed_ratio ;
    //qDebug() << globaloption.server_stat_timeout ;
    //qDebug() << globaloption.show_console_readout ;
    //qDebug() << globaloption.show_files ;
    //qDebug() << globaloption.socket_recv_buffer_size ;
    //qDebug() << globaloption.split ;
    //qDebug() << globaloption.stderr ;
    //qDebug() << globaloption.stop ;
    //qDebug() << globaloption.stream_piece_selector ;
    //qDebug() << globaloption.summary_interval ;
    //qDebug() << globaloption.timeout ;
    //qDebug() << globaloption.truncate_console_readout ;
    //qDebug() << globaloption.uri_selector ;
    //qDebug() << globaloption.use_head ;
    //qDebug() << globaloption.user_agent ;



}

//"aria2.changeGlobalOption"
void Aria2cRPCMsg::Aria2cRMsg_changeGlobalOption( QJsonObject nObj ){

    /** OK: "{\"id\":\"0\",\"jsonrpc\":\"2.0\",\"result\":\"OK\"}" */

    QString result = nObj.value("result").toString();
    qDebug()<< "result" << result;

}

//"aria2.purgeDownloadResult"
void Aria2cRPCMsg::Aria2cRMsg_purgeDownloadResult( QJsonObject nObj ){

   /** OK: "{"id":"100","jsonrpc":"2.0","result":"OK"}" */
   qDebug()<< "result "<< nObj.value("result").toString();

}

//"aria2.removeDownloadResult"
void Aria2cRPCMsg::Aria2cRMsg_removeDownloadResult( QJsonObject nObj ){

   /** OK: "{"id":"100","jsonrpc":"2.0","result":"OK"}" */
   qDebug()<< "result "<< nObj.value("result").toString();

}

//"aria2.getVersion"
void Aria2cRPCMsg::Aria2cRMsg_getVersion( QJsonObject nObj ){

  /**
    {
      "id": "100",
      "jsonrpc": "2.0",
      "result": {
        "enabledFeatures": [
          "Async DNS",
          "BitTorrent",
          "Firefox3 Cookie",
          "GZip",
          "HTTPS",
          "Message Digest",
          "Metalink",
          "XML-RPC"
        ],
        "version": "1.32.0"
      }
    }
  */

     QJsonObject result = nObj.value("result").toObject();
     //qDebug() << "version" << result.value("version").toString();
     QJsonArray enabledFeatures = result.value("enabledFeatures").toArray();

     for( int i = 0 ; i < enabledFeatures.size(); i++ ){

         //qDebug() << "enabledFeatures " << enabledFeatures.at(i).toString();
     }


}

//"aria2.getSessionInfo"
void Aria2cRPCMsg::Aria2cRMsg_getSessionInfo( QJsonObject nObj ){

    /**
       {
           "id": "100",
           "jsonrpc": "2.0",
           "result": {
               "sessionId": "ce786af1b36a88ed277da7d5cbc397ccf5bf4254"
            }
        }
     */

    QString sessionId = nObj.value("result").toObject().value("sessionId").toString();
    //qDebug() <<  sessionId;

}

//"aria2.shutdown"
void Aria2cRPCMsg::Aria2cRMsg_shutdown( QJsonObject nObj ){

    /** OK: "{"id":"0","jsonrpc":"2.0","result":"OK"}" */

    QString result = nObj.value("result").toString();
    //qDebug() << result;
}

//"aria2.forceShutdown"
void Aria2cRPCMsg::Aria2cRMsg_forceShutdown( QJsonObject nObj ){

   /** OK: "{"id":"0","jsonrpc":"2.0","result":"OK"}" */

   QString result = nObj.value("result").toString();
   //qDebug() << result;

}

//"aria2.getGlobalStat"
void Aria2cRPCMsg::Aria2cRMsg_getGlobalStat( QJsonObject nObj ){

    /**
        {
          "id": "100",
          "jsonrpc": "2.0",
          "result": {
            "downloadSpeed": "0",
            "numActive": "0",
            "numStopped": "5",
            "numStoppedTotal": "6",
            "numWaiting": "0",
            "uploadSpeed": "0"
          }
        }
    */

   QJsonObject result =  nObj.value( "result" ).toObject();
   //qDebug() << result.value("downloadSpeed").toString();
   //qDebug() << result.value("numActive").toString();
   //qDebug() << result.value("numStopped").toString();
   //qDebug() << result.value("numStoppedTotal").toString();
   //qDebug() << result.value("numWaiting").toString();
   //qDebug() << result.value("uploadSpeed").toString();

}

//"aria2.saveSession"
void Aria2cRPCMsg::Aria2cRMsg_saveSession( QJsonObject nObj ){

    /** OK: "{"id":"0","jsonrpc":"2.0","result":"OK"}" */

    QString result = nObj.value("result").toString();
    qDebug()<< "result" << result;

}

//"system.multicall"
void Aria2cRPCMsg::Aria2cRMsg_system_multicall( QJsonObject nObj ){

    /** OK: "{"id":"0","jsonrpc":"2.0","result":[["75cb2fe5fd57573b"]]}" */

    QJsonArray  resultss = nObj.value( "result" ).toArray();

    for( int i = 0 ; i < resultss.size() ; i++ ){

        QJsonArray results = resultss.at(i).toArray();

        for( int j = 0 ; i < results.size(); j++ ){

            QString result = results.at(j).toString();
            //qDebug() << "result " << result;
        }
    }

}

//"system.listMethods"
void Aria2cRPCMsg::Aria2cRMsg_system_listMethods( QJsonObject nObj ){

    /**
    {
      "id": "0",
      "jsonrpc": "2.0",
      "result": [
        "aria2.addUri",
        "aria2.addTorrent",
        "aria2.getPeers",
        "aria2.addMetalink",
        "aria2.remove",
        "aria2.pause",
        "aria2.forcePause",
        "aria2.pauseAll",
        "aria2.forcePauseAll",
        "aria2.unpause",
        "aria2.unpauseAll",
        "aria2.forceRemove",
        "aria2.changePosition",
        "aria2.tellStatus",
        "aria2.getUris",
        "aria2.getFiles",
        "aria2.getServers",
        "aria2.tellActive",
        "aria2.tellWaiting",
        "aria2.tellStopped",
        "aria2.getOption",
        "aria2.changeUri",
        "aria2.changeOption",
        "aria2.getGlobalOption",
        "aria2.changeGlobalOption",
        "aria2.purgeDownloadResult",
        "aria2.removeDownloadResult",
        "aria2.getVersion",
        "aria2.getSessionInfo",
        "aria2.shutdown",
        "aria2.forceShutdown",
        "aria2.getGlobalStat",
        "aria2.saveSession",
        "system.multicall",
        "system.listMethods",
        "system.listNotifications"
      ]
    }
    */

    QJsonArray results = nObj.value("result").toArray();
    for( int i = 0 ; i < results.size() ; i++ ){

       qDebug()<< results.at(i).toString();
    }


}

//"system.listNotifications"
void Aria2cRPCMsg::Aria2cRMsg_system_listNotifications( QJsonObject nObj ){
  /**
    {
      "id": "0",
      "jsonrpc": "2.0",
      "result": [
        "aria2.onDownloadStart",
        "aria2.onDownloadPause",
        "aria2.onDownloadStop",
        "aria2.onDownloadComplete",
        "aria2.onDownloadError",
        "aria2.onBtDownloadComplete"
      ]
    }
  */

    QJsonArray results = nObj.value("result").toArray();
    for( int i = 0 ; i < results.size() ; i++ ){

       qDebug()<< results.at(i).toString();
    }

}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////
/*
"aria2.tellActive",
"aria2.tellWaiting",
"aria2.tellStopped",
三个返回消息结构相同，集中统一处理向UI 返回
*/
void Aria2cRPCMsg::Aria2cRMsg_tellMessage( QJsonObject nObj ){

    /**
      "id": "0",
      "jsonrpc": "2.0",
      "result": [
        {
          "completedLength": "0",
          "connections": "1",
          "dir": "/home/gaochong/Desktop",
          "downloadSpeed": "0",
          "files": [
            {
              "completedLength": "0",
              "index": "1",
              "length": "0",
              "path": ",
              "selected": "true",
              "uris": [
                {
                  "status": "used",
                  "uri": "http://sw.bos.baidu.com/sw-search-sp/software/16d5a98d3e034/QQ_8.9.5.22062_setup.exe"
                }
              ]
            }
          ],
          "gid": "0fd8fc5100c8648a",
          "numPieces": "0",
          "pieceLength": "1048576",
          "status": "active",
          "totalLength": "0",
          "uploadLength": "0",
          "uploadSpeed": "0"
        }]
    */

        QList<TBItem> tbList;

        QJsonArray  resultList = nObj.value("result").toArray();

        for(int i = 0; i < resultList.size(); i++) {

             QJsonObject result = resultList.at(i).toObject();

             TBItem tbitem;
/*
             //qDebug() << result.value( "bitfield" ).toString();
             //qDebug() <<  "completedLength"<< result.value( "completedLength" ).toString();
             //qDebug() <<  "connections"<< result.value( "connections" ).toString();
             //qDebug() <<  "dir"<< result.value( "dir" ).toString();
             //qDebug() <<  "downloadSpeed"<< result.value( "downloadSpeed" ).toString();
*/
             QJsonArray  files = result.value("files").toArray();

             for(int j = 0; j < files.size(); j++) {

                 QJsonObject file = files.at(j).toObject();
/*
                 //qDebug() << "completedLength" << file.value( "completedLength" ).toString();
                 //qDebug() << "index" <<  file.value( "index" ).toString();
                 //qDebug() << "length" <<  file.value( "length" ).toString();
                 //qDebug() << "path" <<  file.value( "path" ).toString();
                 //qDebug() << "selected" <<  file.value( "selected" ).toString();
*/
                 tbitem.savepath = file.value( "path" ).toString();

                 QJsonArray  uris = file.value("uris").toArray();
                 for(int k = 0; k < uris.size(); k++ ) {
                     QJsonObject uri = uris.at(k).toObject();

                     //qDebug() <<  "status" << uri.value( "status" ).toString();
                     //qDebug() <<  "uri" << uri.value( "uri" ).toString();

                     tbitem.uri = uri.value( "uri" ).toString();
                 }

                 if ( uris.size() == 0 ){

                     tbitem.uri = tbitem.savepath;
                 }
             }
/*
             //qDebug() << "gid"<<  result.value( "gid" ).toString();
             //qDebug() << "numPieces"<<  result.value( "numPieces" ).toString();
             //qDebug() << "pieceLength"<<  result.value( "pieceLength" ).toString();
             //qDebug() << "status"<<  result.value( "status" ).toString();
             //qDebug() << "totalLength"<<  result.value( "totalLength" ).toString();
             //qDebug() << "uploadLength"<<  result.value( "uploadLength" ).toString();
             //qDebug() << "uploadSpeed"<<  result.value( "uploadSpeed" ).toString();
*/

             tbitem.gid = result.value( "gid" ).toString();

             QString totalLength = result.value("totalLength").toString();
             QString completedLength = result.value( "completedLength" ).toString();

             bool ok;
             long totalLength_long = totalLength.toLong( &ok,10 );
             long completedLength_long = completedLength.toLong( &ok,10 );
/*
             //qDebug() << "totalLengthr_long " << totalLength_long;
             //qDebug() << "completedLength_long " << completedLength_long;
*/
             int  bitfield = 0;
             if ( completedLength_long >0 ){

               bitfield = qRound( completedLength_long * 100.0 / totalLength_long );
               //ui->textEdit->append( "bitfield " + QString::number( bitfield ,10 ) );
             }

             tbitem.RestTime = totalLength + "|" + completedLength;

             tbitem.Progress = QString::number( bitfield ,10 );  //进度
             tbitem.Speed = result.value( "downloadSpeed" ).toString(); //下载速度
             tbitem.State = result.value( "status" ).toString();    //状态

             if ( tbitem.uri == "" && tbitem.Progress == "100" ){

                 continue;
             }

             tbList.append( tbitem );

        }

        this->mainUI->UpdateGUI_StatusMsg( tbList );

}


////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void Aria2cRPCMsg::ReturnError( QString error_t ){

    if( this->Errot_U < 3 ){

        mainUI->ShowMessageTip(  "与Aria2 通讯失败.." );
        this->Errot_U++;
    }
}



////////////////////////////////////////////////////////////////////////////////////////////////////////////////

QString Aria2cRPCMsg::GetFileName( QString path ){

    QString m_FilePath = path; //"/usr/local/src/images/Verify/i/1.jpg";
    int first = m_FilePath.lastIndexOf ("/");
    QString filename = m_FilePath.right( m_FilePath.length() - first - 1 );
    //qDebug() << filename;

    return filename;

}











