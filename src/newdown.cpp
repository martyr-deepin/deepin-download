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
    //QLabel *title = new QLabel( tr("New task") );
    //this->titlebar()->setCustomWidget(title, Qt::AlignVCenter, false);

    QWidget *form = new QWidget;
    QVBoxLayout  *vbLayout = new QVBoxLayout;
    form->setLayout( vbLayout );
    Edit1 = new QTextEdit;
    Edit1->setFixedHeight( 180 );
    Edit1->setStyleSheet("QTextEdit{border:1px solid #f3f3f3;}");


    QPushButton *openFileDlg = new QPushButton( QIcon( ":Resources/images/torrent.svg" ), "torrent　|　metalink　Down file" );

    openFileDlg->setObjectName("openFileDlg");
    // openFileDlg->setIcon(QIcon(":/Resources/images/logo@2x.png"));
    openFileDlg->setText(" " + QString("open Torrent file"));
    openFileDlg->setStyleSheet("#openFileDlg{ qproperty-icon: url(:Resources/images/torrent.svg);qproperty-iconSize:32px 32px;color:#0000FF;}");
    qDebug() << openFileDlg;
/**
    QPixmap *pixmap = NULL;
    pixmap = new QPixmap(64, 64);
    pixmap->load( ":Resources/images/torrent.svg" );
    QIcon *icon = new QIcon(*pixmap);
    QPushButton *button = new QPushButton(*icon, "");
    button->setIconSize(QSize(64, 64));
**/

    QWidget *SaveSetup = new QWidget;
    QFormLayout *SS = new QFormLayout;
    SaveSetup->setLayout( SS );
    QLabel *text = new QLabel(tr("Save to"));
    selSavePath = new QComboBox;
    QString HomeDir = QDir::homePath();
    QString Downloads = HomeDir + "/Downloads";
    QString Desktop = HomeDir + "/Desktop";
    selSavePath->addItem( QIcon( ":Resources/images/folder-downloads.svg" ), "Downloads",Downloads  );
    selSavePath->addItem( QIcon( ":Resources/images/folder-desktop.svg" ),"Desktop",Desktop );
    selSavePath->addItem( "...","..." );
    SS->addRow( text ,selSavePath );

    selSavePath->setCurrentIndex( 0 );

    vbLayout->addWidget( Edit1 );
    //vbLayout->addWidget( button );
    vbLayout->addWidget( openFileDlg );
    vbLayout->addWidget( SaveSetup );

    msg = new QLabel;
    msg->setText("");

    addContent( form );
    addContent( msg );
    int btn1 = addButton( tr("Cancel"), false);
    int btn2 = addButton( tr("Download"), true, DDialog::ButtonRecommend );

    setOnButtonClickedClose( false );

    this->setFixedSize( 540,400 );
    setWindowFlags( /**Qt::FramelessWindowHint  | */ Qt::WindowStaysOnTopHint );

    connect( this, &Dtk::Widget::DDialog::buttonClicked,this,&NewDown::buttonClicked );
    //connect( button1, &QPushButton::clicked,this,&NewDown::Button1Click );
    //connect( button2, &QPushButton::clicked,this,&NewDown::Button2Click );
    connect( openFileDlg, &QPushButton::clicked,this,&NewDown::openFileDlg );


    connect( selSavePath, static_cast<void (QComboBox::*)(int)>(&QComboBox::currentIndexChanged),[=](int index){
/**
            QString SelPathStr = selSavePath->currentData().toString();
            qDebug()<< index << SelPathStr;

            if( SelPathStr == "..."){

                SelectSaveDir();

            }else{
                msg->setText( "保存路径：" + SelPathStr );
            }
**/
     });


    connect( selSavePath, static_cast<void (QComboBox::*)(int)>(&QComboBox::activated),[=](int index){

            //QString SelPathStr = selSavePath->currentData().toString();
            QString SelPathStr = selSavePath->currentData().toString();
            qDebug()<< index << SelPathStr;

            if( SelPathStr == "..."){

                SelectSaveDir();

            }else{
                msg->setText( "保存路径：" + SelPathStr );
            }

     });



    msg->setText( "保存路径：" + Downloads );

    this->SavePath = Downloads;

}

void NewDown::SelectSaveDir(){

    QString dir = QFileDialog::getExistingDirectory( this,
                                                     tr("Open Directory"),
                                                     "/home",
                                                     QFileDialog::ShowDirsOnly | QFileDialog::DontResolveSymlinks );

   //msg->setText( dir );

   QFile file( dir + "/testcreate.gc" );
   if ( file.open( QIODevice::ReadWrite | QIODevice::Text ) ){

       qDebug() << "OK";

       //selSavePath->setCurrentText( dir );
       msg->setText( "保存路径：" + dir );

       this->SavePath = dir;

   }else{
       qDebug() << "Error....";
       /**
        * 创建打开测试文件失败，选择的这个路径有可能不能写无权限等
        **/
       msg->setText( "该路径不能用于保存下载文件" );

       this->SavePath = "";
   }
   file.close();
   QFile::remove( dir + "/testcreate.gc" );


   //selSavePath->setCurrentIndex( -1 );

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
                      this->msg->setText( tr("The address cannot be analyzed, please retry!") );
                      return -1;
                  }
              }

              //ed2k://
              if ( url.left( 4 ) == "ed2k" ){

                //【您输入的地址不能被正确解析，请重试！】【The address cannot be analyzed, please retry!】
                this->msg->setText( tr("The address cannot be analyzed, please retry!") );
                return -1;
              }

              if ( url.trimmed() != "" ){

                  mainUI->AppendDownUrl( url ,this->SavePath );
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


   Edit1->setText("");
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

















