#ifndef GCTHREAD_H
#define GCTHREAD_H
#include <QObject>
#include <QThread>

#include <QJsonObject>
#include <QJsonDocument>
#include <QJsonArray>

/** ======================================= */

class MainWindow;
#include "mainwindow.h"
/** ======================================= */

class GCThread : public QThread
{
    Q_OBJECT

public:

   GCThread( MainWindow  *mainUI  );
   void setFunction( int fCode );
   void stop();
   //QNetworkAccessManager *manager;

protected:
//public slots:
   void run();
   //void printMessage();

private:
   MainWindow  *mainUI;
   volatile bool stopped;
   volatile int  fCode;

private:

   void GetWaitList();
   void GetStopList();
   void GetActiveList();

   void GCNetworkReply( QNetworkReply* reply,const QString method );
   void SendMessage( QString jsonrpc ,QString id ,QString method, QJsonArray params );

signals:
    void OnNotifyQAMTest( QNetworkAccessManager *manager );

};

#endif // GCTHREAD_H
