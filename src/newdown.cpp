#include "newdown.h"

#include <QApplication>
#include <QLayout>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QFormLayout>
#include <QDebug>
#include <QMessageBox>
#include <QComboBox>
#include <QFileDialog>

#include "base64.h"

NewDown::NewDown( MainWindow *mainUI ,QWidget *parent) : QDialog(parent){

    qDebug() << "NewDown::NewDown( MainWindow *mainUI )";

    this->setWindowTitle( tr("New download") );

    QWidget *form = new QWidget;       
    QVBoxLayout  *vbLayout = new QVBoxLayout;

    form->setLayout( vbLayout );

    Edit1 = new QTextEdit;
    Edit1->setFixedHeight( 240 );
    Edit1->setStyleSheet("QTextEdit{border:1px solid #101000;}");

    QPushButton *openFileDlg = new QPushButton( tr("torrent　|　metalink　Down file"));

    vbLayout->addWidget( Edit1 );
    vbLayout->addWidget( openFileDlg );


    QWidget *buttonGroup = new QWidget;
    QHBoxLayout *Blayout = new QHBoxLayout;
    QPushButton *button1 = new QPushButton( tr("cancel") );
    QPushButton *button2 = new QPushButton( tr("Start downloading") );

    //QPushButton *button3 = new QPushButton("测试");
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

    this->setFixedSize( 540,400 );
    setWindowFlags( /**Qt::FramelessWindowHint  | */ Qt::WindowStaysOnTopHint );


    connect( button1, &QPushButton::clicked,this,&NewDown::Button1Click );
    connect( button2, &QPushButton::clicked,this,&NewDown::Button2Click );
    connect( openFileDlg, &QPushButton::clicked,this,&NewDown::openFileDlg );

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

       if( dtype != 0  ){

           switch ( dtype ) {

               case 1:

                   mainUI->AppendDownMetalink( this->dPath );
                   break;

               case 2:

                   mainUI->AppendDownBT( this->dPath );
                   break;

               //default:
               //    break;
           }


       }else{

         QStringList urlStrList =  urlStrs.split("\n");

         foreach ( QString url ,  urlStrList) {

              qDebug() << "url :"  << url;

              if ( url.left( 7 ) == "thunder" ){

                  url = GetThunderUrl( url );
                  //QMessageBox::information( NULL, "",   url );
                  if( url == "" ){
                      this->msg->setText( tr("Download the address illegally...") );
                      return;
                  }
              }

              if ( url.trimmed() != "" ){

                  mainUI->AppendDownUrl(  url );
              }
          }
       }
       this->Edit1->setText("");
       this->msg->setText( "" );
       this->close();

   }else{

       msg->setText( tr("Download address download address can not be empty...") );
   }


}

void NewDown::ClearEdit(){

    this->Edit1->setText("");
}


void NewDown::SetDownloadEdit( QString urlStr ){

    this->Edit1->setText( urlStr );
}

void NewDown::Button3Click(){


}

void NewDown::openFileDlg(){

    dtype = 0;
    QString path = QFileDialog::getOpenFileName(this, tr("Open BitTorrent | Metalink file"), ".", "BTorrent Metalink Files(*.torrent *.metalink)" );

    if( path.length() != 0 ) {

        qDebug() << "path " << path;

        int i =  path.lastIndexOf(".");
        QString zName = path.mid( i , path.length() - i );

        if( zName != ".torrent" && zName !=".metalink"   ){


        }else{

            this->dPath = path;
            this->Edit1->setText( path );

            if ( zName == ".torrent"  )  dtype = 1 ;
            if ( zName == ".metalink" )  dtype = 2 ;
        }
    }

}

QString NewDown::GetThunderUrl(  QString thunder_url ){


    //迅雷链接
    //thunder://QUFodHRwOi8vdG9vbC5sdS90ZXN0LnppcFpa
    //QString thunder_url = "thunder://QUFodHRwOi8vdG9vbC5sdS90ZXN0LnppcFpa";
    qDebug() << "thunder_url" << thunder_url;

    QString _url = "";
    try{

        _url = Base64::decode( thunder_url.replace( "thunder://" ,"" ) );
    }catch(...){

        return "";
    }


    qDebug() << "thunder_url" << _url   ;
    QString urlStr = "";
    if ( _url.left(2) == "AA" && _url.right(2) == "ZZ"  ){

       urlStr = _url.mid( 2, _url.length() - 4  );
    }

    return urlStr;

}

















