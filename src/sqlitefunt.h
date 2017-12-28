#ifndef SQLITEFUNT_H
#define SQLITEFUNT_H

#include <QDebug>
#include <QList>
#include <QSql>
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QSqlError>

#include "downrecord.h"


class SQLiteFunt
{
public:

    SQLiteFunt( QString fullPath  );

    QString AppendDTask( TBItem tbItem  );
    QString AppendDTask( QString url ,QString classn = "1" );
    void AppendBTask( TBItem tbItem );
    void DeleteDTask( QString gid  );
    QList<DDRecord> ReadALLTask();
    QList<DDRecord> ReadRecycleList();
    QList<DDRecord> ReadDDTask( int type = 4);
    DDRecord GetDTaskInfo( QString gid );

    void SetDTaskGid( DDRecord t );
    void SetDTaskStatus( DDRecord d );

    bool findATaskI( QString urlStr );
    void SetDownSavePath( QString gid , QString dirPath );

    QString GetDownUrlPath( QString gid );
    QString GetDownSavePath( QString gid );

private:
    QSqlDatabase m_dbconn;
    void initDBTable();


};

#endif // SQLITEFUNT_H
