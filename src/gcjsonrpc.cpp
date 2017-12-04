#include "gcjsonrpc.h"
//#include "detection.h"
#include <QProcess>


GCJsonRPC::GCJsonRPC()
{

}

GCJsonRPC::GCJsonRPC(QString actionResult ,Aria2cRPCMsg* aria2c_rpc_msg )
{
    this->aria2c_rpc_msg = aria2c_rpc_msg;
    this->actionResult = actionResult;
}

void GCJsonRPC::SendMessage( QString jsonrpc ,QString id ,QString method )
{

    QJsonArray params;
    this->SendMessage( jsonrpc,id,method ,params );
}

void GCJsonRPC::SendMessage( QString jsonrpc ,QString id ,QString method, QJsonArray params )
{

    qDebug() << "======================= SendMessage === "+ method +" =================================== ";

    QNetworkAccessManager* manager  = new QNetworkAccessManager;

    QJsonObject obj;

    obj.insert("jsonrpc", jsonrpc );
    obj.insert("id", id );
    obj.insert("method", method );

    if ( ! params.isEmpty() ){

        obj.insert("params", params );
    }

    QNetworkRequest request;
    request.setUrl(QUrl( actionResult ) );

    request.setHeader(QNetworkRequest::ContentTypeHeader, "application/json" );

    manager->post( request, QJsonDocument( obj ).toJson() );

    connect( manager,
             &QNetworkAccessManager::finished,
             this ,
             [=](QNetworkReply *reply){

                 this->GCNetworkReply(reply, method );
                 manager->deleteLater();
                 manager->destroyed();
             });
}

void GCJsonRPC::GCNetworkReply( QNetworkReply* reply,const QString method ){

      qDebug() << "======================= GCNetworkReply === "+ method +" ================================ ";

       if( reply->error() != QNetworkReply::NoError ){

           qDebug() << "Error:" << reply->errorString();
           aria2c_rpc_msg->ReturnError( reply->errorString() );

       }else{

           QByteArray buf = reply->readAll();
           qDebug() << "OK:"<< buf;

           QJsonDocument rmsgobj = QJsonDocument::fromJson( buf );
           QJsonObject rconsole = rmsgobj.object();

           if ( !rconsole.isEmpty()  ){

               /**
               * 回调返回消息分发
               */
               aria2c_rpc_msg->UpdateUIMsg(  rconsole , method );

           }else{

              qDebug() <<"非标准 JSON 格式返回";
           }

       }
       //this->deleteLater();
}
















