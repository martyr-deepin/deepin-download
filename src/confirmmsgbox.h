#ifndef CONFIRMMSGBOX_H
#define CONFIRMMSGBOX_H

#include <QString>
#include <QWidget>
#include "dtkwidget_global.h"
#include <ddialog.h>

//#include "interfaces/durl.h"
//DWIDGET_USE_NAMESPACE

class ConfirmMsgBox :public Dtk::Widget::DDialog
{
    Q_OBJECT

    public:
       explicit ConfirmMsgBox( QWidget *parent ,QString title , QString text );
};


#endif // CONFIRMMSGBOX_H
