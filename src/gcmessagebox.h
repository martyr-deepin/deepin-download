#ifndef MOVETOTRASHCONFLICTDIALOG_H
#define MOVETOTRASHCONFLICTDIALOG_H

#include <QString>
#include <QWidget>
#include "dtkwidget_global.h"
#include <ddialog.h>

//#include "interfaces/durl.h"
//DWIDGET_USE_NAMESPACE

class GCMessageBox :public Dtk::Widget::DDialog
{
   Q_OBJECT
   public:
     explicit GCMessageBox( QWidget *parent ,QString title , QString text );
};

#endif // MOVETOTRASHCONFLICTDIALOG_H
