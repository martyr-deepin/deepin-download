#ifndef GCTHREAD_H
#define GCTHREAD_H
#include <QObject>
#include <QThread>
#include <QJsonObject>
#include <QJsonDocument>
#include <QJsonArray>
#include <sqlitefunt.h>
/** ======================================= */

class MainWindow;
#include "mainwindow.h"
/** ======================================= */

class GCThread : public  QObject //QThread
{
    Q_OBJECT

public:

   GCThread( SQLiteFunt *downDB );
   void SetControl( int code  );

private:
   SQLiteFunt *downDB;
   int  control = 0;
   void GetWaitList();
   void GetStopList();
   void GetActiveList();
   void UpdateDownStatus();

   void GCNetworkReply( QNetworkReply* reply,const QString method );
   void SendMessage( QString jsonrpc ,QString id ,QString method, QJsonArray params );

   void Aria2cRMsg_tellMessage( QJsonObject nObj );
   void Aria2cRMsg_tellStatus( QJsonObject nObj );

protected:
   void run();

signals:
   void NetworkReply( QList<TBItem*> *tbList );
   void NetworkReplyNode( TBItem* tbItem );

private slots:
   void work();

};

#endif // GCTHREAD_H
