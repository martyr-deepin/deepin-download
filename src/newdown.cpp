#include "newdown.h"

#include <QApplication>
#include <QLayout>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QFormLayout>
#include <QDebug>

#include <QComboBox>


NewDown::NewDown( MainWindow *mainUI ,QWidget *parent) : QDialog(parent){

    qDebug() << "NewDown::NewDown( MainWindow *mainUI )";

    this->setWindowTitle( "新建下载" );

    QWidget *form = new QWidget;
    QFormLayout *Flayout = new QFormLayout;
    Edit1 = new QTextEdit;
    Edit1->setStyleSheet("QTextEdit{border:1px solid green;}");

    QLabel  *Label1 = new QLabel("下载地址：");
    Flayout->addRow( Label1 ,Edit1 );
    form->setLayout( Flayout );

    QWidget *buttonGroup = new QWidget;
    QHBoxLayout *Blayout = new QHBoxLayout;
    QPushButton *button1 = new QPushButton("取消");
    QPushButton *button2 = new QPushButton("确定");
    Blayout->addWidget( button1 );
    Blayout->addWidget( button2 );
    buttonGroup->setLayout( Blayout );

    msg = new QLabel;
    msg->setText("");

    QVBoxLayout *x = new QVBoxLayout;
    x->addWidget( form );
    x->addWidget( msg );
    x->addWidget( buttonGroup );

    this->setLayout( x );

    this->mainUI = mainUI;

    this->setFixedSize( 500,200 );

    setWindowFlags( /*Qt::FramelessWindowHint  |*/ Qt::WindowStaysOnTopHint );


    connect( button1, &QPushButton::clicked,this,&NewDown::Button1Click );
    connect( button2, &QPushButton::clicked,this,&NewDown::Button2Click );


}



void NewDown::Button1Click(){

    qDebug() <<"Button1Click";

    this->Edit1->setText("");
    this->msg->setText( "" );

    this->close();

}

void NewDown::Button2Click(){

   QString urlStrs =  Edit1->toPlainText();

   if ( urlStrs.trimmed().length() != 0  ){

       qDebug() << "Button2Click: GetEdit1 :"  << urlStrs;

       QStringList urlStrList =  urlStrs.split("\n");

       foreach ( QString url ,  urlStrList) {

          qDebug() << "url :"  << url;

          if ( url.trimmed() != "" ){

              mainUI->AppendDownUrl(  url );
          }
       }

       this->Edit1->setText("");
       this->msg->setText( "" );
       this->close();

   }else{
       msg->setText( "下载地址不能为空..." );

   }
}

void NewDown::ClearEdit(){

    this->Edit1->setText("");
}


void NewDown::SetDownloadEdit( QString urlStr ){

    this->Edit1->setText( urlStr );
}








