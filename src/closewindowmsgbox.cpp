#include "closewindowmsgbox.h"
#include <QLabel>
#include <QFontMetrics>
#include <QFont>
#include <QIcon>

#include <QDebug>

CloseWindowMsgBox::CloseWindowMsgBox()
{

    //QString titleStr = tr("Please select your operation");


    setIcon( QIcon(":Resources/images/logo_24.svg") );
    setTitle( tr("Please select your operation") ); //请选择您的操作

    sel1 =  new QRadioButton;
    sel2 =  new QRadioButton;
    checkBox = new QCheckBox;

    sel1->setText( "Exit" ); //退出
    sel2->setText( tr("Minimize to system tray") ); //Minimize to system tray
    checkBox->setText( tr("Never ask again") ); //不再询问

    sel2->setCheckable( true );
    sel2->setChecked( true );

    addContent(sel1);
    addContent(sel2);
    addContent(checkBox);

    addButton(tr("Cancel"), false);
    addButton(tr("OK"), true, DDialog::ButtonRecommend);

    setWindowFlags( /**Qt::FramelessWindowHint  | */ Qt::WindowStaysOnTopHint );

    connect( this,&Dtk::Widget::DDialog::buttonClicked,this,&CloseWindowMsgBox::buttonClicked );


}

void CloseWindowMsgBox::buttonClicked(int index, const QString &text){

     qDebug() << "CloseWindowMsgBox::buttonClicked" << index;

     qDebug() << "sel1->isChecked()" << sel1->isChecked();
     qDebug() << "sel2->isChecked()" << sel2->isChecked();
     qDebug() << "checkBox->isChecked()" << checkBox->isChecked();

     if( index == 1 ){

         if (  sel1->isChecked() ){
            //退出

         }else{
            //最小化到托盘

         }

         if( checkBox->isChecked() ){
            //不再提醒

         }
     }

     return;
}
