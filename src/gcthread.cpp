#include "gcthread.h"

#include <QDebug>
#include <QApplication>

GCThread::GCThread( SQLiteFunt *downDB ){

    this->downDB = downDB;
}

void GCThread::SetControl( int code  ){

    this->control = code;
}

void GCThread::run(){

    work();
}

void GCThread::work(){

    //while( true ){


        switch ( this->control ) {

        case 0:
            UpdateDownStatus();
            break;
        case 1:
            GetActiveList();
            break;
        case 2:
            GetWaitList();
            break;

        case 3:
            GetStopList();
            break;
        default:
            //UpdateDownStatus();
            break;
        }


       // msleep(2000);

    //}

/**

**/
    //qDebug() << "Thread ID: " << QThread::currentThreadId();

}

void GCThread::GetWaitList(){

   //mainUI->aria2c->SendMsgAria2c_tellWaiting( 0 ,10 );

   QJsonArray item;
   item.append( 0 );   //offset
   item.append( 100 );  //num

   QString dz = "aria2.tellWaiting";

   SendMessage( "2.0", 0 , dz , item );

}

void GCThread::GetStopList(){

    //mainUI->aria2c->SendMsgAria2c_tellStopped( 0 , 10 );

    QJsonArray item;
    item.append( 0 );   //offset
    item.append( 100 );  //num

    QString dz = "aria2.tellStopped";

    SendMessage( "2.0", 0 , dz , item );
}

void GCThread::GetActiveList(){

    //mainUI->aria2c->SendMsgAria2c_tellActive();

    QJsonArray item;
    QString dz = "aria2.tellActive";

    SendMessage( "2.0", 0 , dz , item );

}

void GCThread::UpdateDownStatus(){

    qDebug() << "UpdateDownStatus()";

    /** 获取“所有下载任务”的状态 */
    QList<DDRecord> t = downDB->ReadDDTask();
    for (  int i = 0; i < t.size() ;i++){

        //this->aria2c->SendMsgAria2c_tellStatus( t.at(i).gid );
        QString gid =  t.at(i).gid;

        if ( gid != "0" ){

            QJsonArray params;
            params.append( gid );
            QString dz = "aria2.tellStatus";
            SendMessage( "2.0", 0, dz ,params  );
        }
    }

}

void GCThread::SendMessage( QString jsonrpc ,QString id ,QString method, QJsonArray params )
{

    qDebug() << "======================= SendMessage === "+ method +" =================================== ";

    QNetworkAccessManager *manager = new QNetworkAccessManager;

    QJsonObject obj;

    obj.insert("jsonrpc", jsonrpc );
    obj.insert("id", id );
    obj.insert("method", method );

    if ( ! params.isEmpty() ){

        obj.insert("params", params );
    }

    QNetworkRequest *request = new QNetworkRequest;
    request->setUrl(QUrl(  "http://localhost:19799/jsonrpc" ) );

    request->setHeader(QNetworkRequest::ContentTypeHeader, "application/json" );

    manager->post( *request, QJsonDocument( obj ).toJson() );


    connect( manager,
             &QNetworkAccessManager::finished,
             this,
             [=](QNetworkReply* reply){

                 this->GCNetworkReply(reply, method );
                 manager->deleteLater();
                 manager->destroyed();
             });

   //
}


void GCThread::GCNetworkReply( QNetworkReply* reply,const QString method ){

       qDebug() << "======================= GCNetworkReply === "+ method +" ================================ ";

       if( reply->error() != QNetworkReply::NoError ){

           qDebug() << "Error:" << reply->errorString();
           //aria2c_rpc_msg->ReturnError( reply->errorString() );

       }else{

           QByteArray buf = reply->readAll();
           qDebug() << "OK:"<< buf;

           QJsonDocument rmsgobj = QJsonDocument::fromJson( buf );
           QJsonObject rconsole = rmsgobj.object();

           if ( !rconsole.isEmpty()  ){

               /**
               * 回调返回消息处理
               */
               if( "aria2.tellStatus" == method ){

                   Aria2cRMsg_tellStatus( rconsole );

               }else{

                   Aria2cRMsg_tellMessage( rconsole );
               }

           }else{

              qDebug() <<"非标准 JSON 格式返回";
           }
       }
}


//"aria2.tellStatus"
void GCThread::Aria2cRMsg_tellStatus( QJsonObject nObj ){

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


        TBItem *tbitem = new TBItem;

        QJsonObject  result = nObj.value("result").toObject();

        QJsonArray files = result.value("files").toArray();

        for( int i = 0 ; i < files.size() ; i++ ){

            QJsonObject file = files.at(i).toObject();

            tbitem->savepath =  file.value("path").toString();

            QJsonArray uris = file.value("uris").toArray();
            for( int j = 0 ; j < uris.size() ; j++ ){

                QJsonObject uri = uris.at(j).toObject();
                tbitem->uri = uri.value("uri").toString();

            }

            if( uris.size() == 0 ){
                tbitem->uri = tbitem->savepath;
            }
        }

         tbitem->gid = result.value("gid").toString();

         QString totalLength = result.value("totalLength").toString();
         QString completedLength = result.value( "completedLength" ).toString();

         bool ok;
         long totalLength_long = totalLength.toLong( &ok,10 );
         long completedLength_long = completedLength.toLong( &ok,10 );


         int  bitfield = 0;
         if ( completedLength_long >0 ){

           bitfield = qRound( completedLength_long * 100.0 / totalLength_long );
         }

         tbitem->RestTime = totalLength + "|" + completedLength;
         tbitem->Progress = QString::number( bitfield ,10 );  //进度
         tbitem->Speed = result.value( "downloadSpeed" ).toString(); //下载速度
         tbitem->State = result.value( "status" ).toString();    //状态

         //qDebug() << tbitem->gid;
         //this->mainUI->UpdateGUI_StatusMsg( tbitem );

         emit NetworkReplyNode( tbitem );
}

/*
"aria2.tellActive",
"aria2.tellWaiting",
"aria2.tellStopped",
三个返回消息结构相同，集中统一处理向UI 返回
*/
void GCThread::Aria2cRMsg_tellMessage( QJsonObject nObj ){

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

        //QList<TBItem> tbList;
        QList<TBItem*> *tbList = new QList<TBItem*>;

        QJsonArray  resultList = nObj.value("result").toArray();

        for(int i = 0; i < resultList.size(); i++) {

             QJsonObject result = resultList.at(i).toObject();

             TBItem *tbitem = new TBItem;
             QJsonArray  files = result.value("files").toArray();

             for(int j = 0; j < files.size(); j++) {

                 QJsonObject file = files.at(j).toObject();

                 tbitem->savepath = file.value( "path" ).toString();

                 QJsonArray  uris = file.value("uris").toArray();
                 for(int k = 0; k < uris.size(); k++ ) {
                     QJsonObject uri = uris.at(k).toObject();
                     tbitem->uri = uri.value( "uri" ).toString();
                 }

                 if ( uris.size() == 0 ){

                     tbitem->uri = tbitem->savepath;
                 }
             }

             tbitem->gid = result.value( "gid" ).toString();

             QString totalLength = result.value("totalLength").toString();
             QString completedLength = result.value( "completedLength" ).toString();

             bool ok;
             long totalLength_long = totalLength.toLong( &ok,10 );
             long completedLength_long = completedLength.toLong( &ok,10 );

             int  bitfield = 0;
             if ( completedLength_long >0 ){
               bitfield = qRound( completedLength_long * 100.0 / totalLength_long );
             }

             tbitem->RestTime = totalLength + "|" + completedLength;

             tbitem->Progress = QString::number( bitfield ,10 );  //进度
             tbitem->Speed = result.value( "downloadSpeed" ).toString(); //下载速度
             tbitem->State = result.value( "status" ).toString();    //状态

             if ( tbitem->uri == "" && tbitem->Progress == "100" ){
                 continue;
             }

             tbList->append( tbitem );
        }

       // this->mainUI->UpdateGUI_StatusMsg( tbList );

      // QList<TBItem> *XList = new QList<TBItem>;
      // memcpy( XList ,&tbList,sizeof( tbList ) );

       emit NetworkReply( tbList );

}












