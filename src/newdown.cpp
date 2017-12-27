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

NewDown::NewDown( MainWindow *mainUI ,QWidget *parent) :Dtk::Widget::DDialog(parent){

    /*QDialog(parent)*/

    this->mainUI = mainUI;

    setTitle( tr("New task") );



    QWidget *form = new QWidget;
    QVBoxLayout  *vbLayout = new QVBoxLayout;

    form->setLayout( vbLayout );

    Edit1 = new QTextEdit;
    Edit1->setFixedHeight( 240 );
    Edit1->setStyleSheet("QTextEdit{border:1px solid #f3f3f3;}");

    QPushButton *openFileDlg = new QPushButton( "torrent　|　metalink　Down file" );

    vbLayout->addWidget( Edit1 );
    vbLayout->addWidget( openFileDlg );

    /**
     * @brief buttonGroup
     * 文案：
【新建任务】【New task】
【您输入的地址不能被正确解析，请重试！】【The address cannot be analyzed, please retry!】
【保存位置】【Save to】
【取消】【Cancel】
【开始下载】【Download】
     */
    /**
    QWidget *buttonGroup = new QWidget;
    QHBoxLayout *Blayout = new QHBoxLayout;
    QPushButton *button1 = new QPushButton( tr("Cancel") );
    QPushButton *button2 = new QPushButton( tr("Download") );


    //QPushButton *button3 = new QPushButton("测试");

    Blayout->addWidget( button1 );
    Blayout->addWidget( button2 );
    **/

    //buttonGroup->setLayout( Blayout );

    msg = new QLabel;
    msg->setText("");

    addContent( form );
    addContent( msg );
    int btn1 = addButton( tr("Cancel"), false);
    int btn2 = addButton( tr("Download"), true, DDialog::ButtonWarning);

    setOnButtonClickedClose( false );

    this->setFixedSize( 540,400 );
    //setWindowFlags( /**Qt::FramelessWindowHint  | */ Qt::WindowStaysOnTopHint );

    connect( this, &Dtk::Widget::DDialog::buttonClicked,this,&NewDown::buttonClicked );
    //connect( button1, &QPushButton::clicked,this,&NewDown::Button1Click );
    //connect( button2, &QPushButton::clicked,this,&NewDown::Button2Click );
    connect( openFileDlg, &QPushButton::clicked,this,&NewDown::openFileDlg );

}


void NewDown::buttonClicked(int index, const QString &text){

    qDebug() << index;

    if( index == 1 ){

        if (  Button2Click() != 0  ){

            return;
        }

        close();
    }else{

       Button1Click();
       close();
    }

}


void NewDown::Button1Click(){

    qDebug() <<"Button1Click";

    this->Edit1->setText("");
    this->msg->setText( "" );

    this->close();

}

int NewDown::Button2Click(){

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
                      //【您输入的地址不能被正确解析，请重试！】【The address cannot be analyzed, please retry!】
                      this->msg->setText( "The address cannot be analyzed, please retry!..." );
                      return -1;
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

       return 0;

   }else{

       msg->setText( "Download address download address can not be empty..." );

       return -2;
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
    QString path = QFileDialog::getOpenFileName(this, "Open BitTorrent | Metalink file", ".", "BTorrent Metalink Files(*.torrent *.metalink)" );

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

















