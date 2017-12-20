#ifndef DOWNRECORD_H
#define DOWNRECORD_H
#include <QString>


/**
* 刷到ListView 上的结构
*/
struct TBItem {

    QString uri;        // 文件名
    QString Progress;   // 大小和进度
    QString Speed;      // 速度
    QString RestTime;   // 剩余时间
    QString State;      // 状态
    QString gid;        // gid
    QString savepath;   // 保存路径
};

/**
* 存在数据库中的记录结构
*/
struct DDRecord {

    QString id;
    QString url;
    QString gid;
    QString type;
    QString classn;
    QString savepath;

};

#endif // DOWNRECORD_H
