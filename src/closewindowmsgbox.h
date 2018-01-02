#ifndef CLOSEWINDOWMSGBOX_H
#define CLOSEWINDOWMSGBOX_H


#include <QString>
#include <QWidget>
#include <QRadioButton>
#include <QCheckBox>
#include "dtkwidget_global.h"
#include <ddialog.h>

//#include "interfaces/durl.h"
//DWIDGET_USE_NAMESPACE
class CloseWindowMsgBox : public Dtk::Widget::DDialog
{

   Q_OBJECT
private:


public:
    CloseWindowMsgBox();
    QRadioButton *sel1;
    QRadioButton *sel2;
    QCheckBox    *checkBox;

private slots:
   void buttonClicked(int index, const QString &text);

};

#endif // CLOSEWINDOWMSGBOX_H
