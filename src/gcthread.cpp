#include "gcthread.h"

#include <QDebug>


GCThread::GCThread( MainWindow  *mainUI ){

    this->mainUI = mainUI;
    this->stopped = false;
    //manager = new QNetworkAccessManager();
}

void GCThread::run(){

    while( !stopped ){

        switch ( this->fCode ) {

            case 1:  //活动任务
                GetActiveList();
                break;

            case 2:   //已完成了的任务
                GetStopList();
                break;

            case 3:   //停止了的任务( 包括了队列中的、暂停的　)
                GetWaitList();
                break;

            default:
                stopped = true;
                break;
        }

        //this->mainUI->UpdateDownStatus();

        QThread::msleep( 1000 );

    }
    //exec();
    //this->stopped = false;
}

void GCThread::setFunction( int fCode ){

    this->fCode = fCode;
    this->stopped = false;
    //qDebug() << isRunning();
    //if (!isRunning())
      start();
    //run();
}

void GCThread::stop(){

    this->stopped = true;
    //this->quit();
    //this->wait();
}

void GCThread::GetWaitList(){

  // mainUI->aria2c->SendMsgAria2c_tellWaiting( 0 ,10 );

   QJsonArray item;
   item.append( 0 );   //offset
   item.append( 10 );  //num

   QString dz = "aria2.11111";

   SendMessage( "2.0", 0 , dz , item );


}

void GCThread::GetStopList(){

  // mainUI->aria2c->SendMsgAria2c_tellStopped( 0 , 10 );

    QJsonArray item;
    item.append( 0 );   //offset
    item.append( 10 );  //num

    QString dz = "aria2.000000";

    SendMessage( "2.0", 0 , dz , item );
}

void GCThread::GetActiveList(){

  // mainUI->aria2c->SendMsgAria2c_tellActive();

    QJsonArray item;
    item.append( 0 );   //offset
    item.append( 10 );  //num

    QString dz = "aria2.3333";

    SendMessage( "2.0", 0 , dz , item );

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

    QNetworkReply  *UU = manager->post( *request, QJsonDocument( obj ).toJson() );

    qDebug() << "51"<<UU->error()<< UU->isRunning();


    connect( manager,
             &QNetworkAccessManager::finished,
             //this,
             [=](QNetworkReply* reply){

                 this->GCNetworkReply(reply, method );
                 //manager->deleteLater();
                 //manager->destroyed();
             });
//exec();
    //QThread::sleep( 5 );
    //emit OnNotifyQAMTest( manager );
    //exec();
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
               * 回调返回消息分发
               */
               //aria2c_rpc_msg->UpdateUIMsg(  rconsole , method );

           }else{

              qDebug() <<"非标准 JSON 格式返回";
           }

       }
       //this->deleteLater();
}
















