#include "aboutdlg.h"
#include <QLayout>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QIcon>
#include <QLabel>
#include <QPushButton>
#include <QSvgWidget>

AboutDlg::AboutDlg(QWidget *parent) : QDialog(parent){

   setWindowIcon( QIcon(":Resources/images/logo@2x.png")  );

   QHBoxLayout *xyBox = new QHBoxLayout;
   this->setLayout( xyBox );

   QWidget *IL = new QWidget;
   QVBoxLayout *xBox = new QVBoxLayout;   
   QSvgWidget *logo = new QSvgWidget(QString(":Resources/images/logo_24.svg"));
   logo->setFixedSize( 128,128 );
   xBox->addWidget( logo );
   IL->setLayout( xBox );

   QWidget *TL = new QWidget;
   QVBoxLayout *yBox = new QVBoxLayout;
   QLabel *H1 = new QLabel("关于 深度下载");
   QLabel *HH1 = new QLabel("");
   QLabel *HH2 = new QLabel("");
   QLabel *H2 = new QLabel("gaochong");
   QLabel *H3 = new QLabel("2017-11-11 1.0.0");

   yBox->addWidget( H1 );
   yBox->addWidget( HH1 );
   yBox->addWidget( HH2 );
   yBox->addWidget( H2 );
   yBox->addWidget( H3 );


   TL->setLayout( yBox );

   xyBox->addWidget( IL );
   xyBox->addWidget( TL );

   setFixedSize( 640,280 );
   setWindowTitle( "关于 深度下载" );


}

AboutDlg::~AboutDlg(){

}

