#include "sqlitefunt.h"

#include <QDebug>


SQLiteFunt::SQLiteFunt( QString fullPath  ){

    m_dbconn = QSqlDatabase::addDatabase("QSQLITE");

    m_dbconn.setDatabaseName( fullPath );

    if(!m_dbconn.open()){

        qDebug()<<"open "<<fullPath<<" failed!";

    }else{

        QSqlQuery query( m_dbconn );
        QString TableName = "downlist";
        QString  sql = "select count(*) from sqlite_master where type='table' and name='"+ TableName +"'";;

        if(  query.exec( sql ) ){

            if( query.next() ){

               if ( query.value(0).toInt() == 1){

                   qDebug() << "表已存在....";

                   //readDBTable();

               }else{

                   qDebug() << "表不存在....";

                   initDBTable();
               }

            }
        }

        query.finish();
    }
}

/**
* 初始化表
*/
void SQLiteFunt::initDBTable(){

    qDebug() << "initDBTable() " ;

    QSqlQuery sql_query( m_dbconn );
    QString create_sql = "create table downlist ( id        integer PRIMARY KEY autoincrement,"
                                                  "url      varchar(512),"    //下载地址、文件
                                                  "gid      varchar(18),"     // aria2 分配的gid
                                                  "type     int,"             // 状态  0 / 4
                                                  "classn   int,"             // 任务类型：下载url | BT | 磁力链
                                                  "savepath varchar(512))";   // 保存路径

    if ( ! sql_query.exec( create_sql ) ){

        qDebug() << "Error SQLiteFunt::initDBTable()";
    }


    sql_query.finish();

}

/**
* 设置 gid 到表中
* 初次发起的任务是没有gid 的，gid 由任务发送到aria2 成功之后返回 与 id 对应
*/
void SQLiteFunt::SetDTaskGid( DDRecord  t ){

    QSqlQuery query( m_dbconn );

    QString sql = "update downlist set gid='"+ t.gid +"' where id = " + QString::number( t.id ,10 );

    qDebug() << sql;

    if( ! query.exec( sql ) ){

       qDebug()<< "Error SQLiteFunt::SetDBRecord "<< sql;
    }
/*
    sql = "delete from downlist where id <> " + QString::number( t.id ,10 ) +" and  url = "+ t.url + " and gid <> '"+  t.gid +"'";

    qDebug() << sql;

    if( ! query.exec( sql ) ){

       qDebug()<< "Error SQLiteFunt::SetDBRecord "<< sql;
    }
*/
    query.finish();

}


/**
* 通过 gid 返回相应的结构消息
*/
DDRecord SQLiteFunt::GetDTaskInfo( QString gid ){

    QSqlQuery query( m_dbconn );

    QString sql="select * from downlist where gid = '" + gid +"'";

    query.exec( sql );

    DDRecord  t;

    if( query.next() ){

       t.id = query.value(0).toInt();
       t.url  = query.value(1).toString();
       t.gid = query.value(2).toString();
       t.type = query.value(3).toInt();
       t.classn = query.value(4).toInt();
       t.savepath = query.value(5).toString();

       qDebug()<< "read " << t.id + " "+ t.url << " "+ t.gid+ " "+ t.type + " " + t.classn;
    }

    query.finish();

    return t;

}

QList<DDRecord> SQLiteFunt::ReadDDTask( int type ){

    QSqlQuery query( m_dbconn );

    //QString sql= "select * from downlist where gid <>'0' and type <>4";
    QString sql= "select * from downlist where gid <>'0'";

    query.exec( sql );

    QList<DDRecord> ddlist;

    while( query.next() ){

       DDRecord  t;

       t.id = query.value(0).toInt();
       t.url  = query.value(1).toString();
       t.gid = query.value(2).toString();
       t.type = query.value(3).toInt();
       t.classn = query.value(4).toInt();
       t.savepath = query.value(5).toString();

       if( t.type != 1  ){
           t.url  = t.savepath;
       }

       qDebug()<< "read " << t.gid;

       ddlist.append( t );

    }
    query.finish();
    return ddlist;
}

/**
* type 标记为 3 被移除了的任务
*/
QList<DDRecord> SQLiteFunt::ReadRecycleList(){

    QSqlQuery query( m_dbconn );

    QString sql= "select * from downlist where type = 3 ORDER BY id DESC;";

    query.exec( sql );

    QList<DDRecord> ddlist;

    while( query.next() ){

       DDRecord  t;

       t.id = query.value(0).toInt();
       t.url  = query.value(1).toString();
       t.gid = query.value(2).toString();
       t.type = query.value(3).toInt();
       t.classn = query.value(4).toInt();
       t.savepath = query.value(5).toString();

       if( t.type != 1   ){
           t.url  = t.savepath;
       }

       qDebug()<< "read " << t.id + " "+ t.url << " "+ t.gid+ " "+ t.type + "  " + t.classn;

       ddlist.append( t );

    }
    query.finish();
    return ddlist;
}


/**
* 所有任务
*/
QList<DDRecord> SQLiteFunt::ReadALLTask(){

    QSqlQuery query( m_dbconn );

    QString sql= "select * from downlist ORDER BY id DESC;";

    query.exec( sql );

    QList<DDRecord> ddlist;

    while( query.next() ){

       if( query.value(2).toString() == "0" || query.value(5).toString() == "" ){

           qDebug() << "错误记录 " + query.value(0).toInt();
           continue;
       }


       DDRecord  t;

       t.id = query.value(0).toInt();
       t.url  = query.value(1).toString();
       t.gid = query.value(2).toString();
       t.type = query.value(3).toInt();
       t.classn = query.value(4).toInt();
       t.savepath = query.value(5).toString();

       if( t.type != 1   ){
           t.url  = t.savepath;
       }

       qDebug()<< "read " << t.id + " "+ t.url << " "+ t.gid+ " "+ t.type + "  " + t.classn;

       ddlist.append( t );

    }
    query.finish();
    return ddlist;
}



void SQLiteFunt::DeleteDTask( QString gid  ){

    QSqlQuery query( m_dbconn );

    QString sql ="delete from downlist where gid = '"+  gid +"'";

    qDebug() << " DeleteDTask" << sql;

    if ( ! query.exec( sql ) ){

        qDebug() << "Error : " << sql;
    }

    query.finish();
}


void SQLiteFunt::SetDTaskStatus( DDRecord d  ){

    QSqlQuery query( m_dbconn );

    QString sql ="update downlist set type ="+  QString::number( d.type,10 ) +" where gid='" + d.gid +"'";

    qDebug() << sql ;
    if ( ! query.exec( sql ) ){

        qDebug() << "Error : " << sql;
    }
    query.finish();
}

/**
* 添加下载任务
*/
QString SQLiteFunt::AppendDTask( QString url ,QString classn ){

    QSqlQuery query( m_dbconn );

    QString sql ="insert into downlist ( url ,gid,type,classn) values( '"+ url +"','0',0,"+ classn +" )";

    qDebug() << sql;

    if ( ! query.exec( sql ) ){

        qDebug() << "Error : " << sql;
    }

    sql = "SELECT last_insert_rowid()";

    query.exec( sql );

    QString id = "0";
    if( query.next() ){

        id = query.value(0).toString();
    }

    query.finish();

    return id;
}

/**
* 检查 url 是否已存在
*/
bool SQLiteFunt::findATaskI( QString urlStr ){

    bool x = false;
    QSqlQuery query( m_dbconn );
    QString sql= "select * from downlist where url ='"+ urlStr +"'";

    query.exec( sql );

    if ( query.next() ){

       x = true;
    }
    query.finish();

    return x;
}

/**
* 根据 gid 获取下载源地址
*/
QString SQLiteFunt::GetDownUrlPath( QString gid ){

    QSqlQuery query( m_dbconn );
    QString sql= "select url from downlist where gid ='"+ gid +"'";

    query.exec( sql );

    QString urlpath = "";

    if ( query.next() ){

       urlpath = query.value(0).toString();
    }
    query.finish();

    return urlpath;

}

/**
* 根据 gid 获取下载保存地址
*/
QString SQLiteFunt::GetDownSavePath( QString gid ){

    QSqlQuery query( m_dbconn );

    QString sql= "select savepath from downlist where gid ='"+ gid +"'";

    query.exec( sql );

    QString savepath = "";

    if ( query.next() ){

       savepath = query.value(0).toString();
    }
    query.finish();

    return savepath;
}

/**
* 将下载保存的地址记录到表中
*/
void SQLiteFunt::SetDownSavePath( QString gid , QString dirPath ){

    QSqlQuery query( m_dbconn );

    QString sql ="update downlist set savepath ='"+ dirPath +"' where gid='" + gid +"'";

    if ( ! query.exec( sql ) ){

        qDebug() << "Error : " << sql;
    }
    query.finish();
}




/**
* 检查并添加外部发起的任务，如百度网盘插件直接发起的下载
*/
void SQLiteFunt::AppendBTask( TBItem tbItem ){

    QSqlQuery query( m_dbconn );

    QString sql= "select * from downlist where gid ='"+ tbItem.gid +"'";

    query.exec( sql );

    if ( !query.next() ){

       AppendDTask( tbItem  );
    }

    query.finish();

    return;
}


QString SQLiteFunt::AppendDTask( TBItem tbItem  ){

    QSqlQuery query( m_dbconn );

    QString sql ="insert into downlist ( url ,gid,type,classn) values( '"+ tbItem.uri +"','"+ tbItem.gid +"',0,0 )";

    if ( ! query.exec( sql ) ){

        qDebug() << "Error : " << sql;
    }

    sql = "SELECT last_insert_rowid()";

    query.exec( sql );

    QString id = "0";
    if( query.next() ){

        id = query.value(0).toString();
    }

    query.finish();

    return id;
}


