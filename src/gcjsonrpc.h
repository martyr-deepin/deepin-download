#ifndef GCJSONRPC_H
#define GCJSONRPC_H
#include <QObject>
#include <QString>
#include <QtNetwork/QNetworkAccessManager>
#include <QtNetwork/QNetworkRequest>
#include <QtNetwork/QNetworkReply>

#include <QJsonObject>
#include <QJsonDocument>
#include <QJsonArray>

class Aria2cRPCMsg;
#include "aria2crpcmsg.h"


class GCJsonRPC : public QObject
{

private:

    Aria2cRPCMsg* aria2c_rpc_msg = NULL;
    QString actionResult = "http://localhost:6800/jsonrpc";

public:

    GCJsonRPC();
    GCJsonRPC( QString actionResult , Aria2cRPCMsg* aria2c_rpc_msg );

    void SendMessage(  QString jsonrpc ,QString id ,QString method );
    void SendMessage(  QString jsonrpc ,QString id ,QString method, QJsonArray params );

public slots:

    void GCNetworkReply( QNetworkReply* reply, const QString id );

};

#endif // GCJSONRPC_H
