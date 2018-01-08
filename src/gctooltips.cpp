#include "gctooltips.h"

#include <QApplication>
#include <QDesktopWidget>
#include <QRect>
#include <QPushButton>
#include <QLayout>
#include <QHBoxLayout>
#include <QVBoxLayout>

GCToolTips::GCToolTips(QWidget *parent) : QDialog(parent){

    //button1   = new QPushButton;
    outLabel1 = new QLabel;

    QHBoxLayout *xx = new QHBoxLayout;

    xx->addWidget( outLabel1 );

    this->setLayout( xx );
    this->setFixedSize( 350,80 );

    //this->setWindowFlags( Qt::FramelessWindowHint | Qt::WindowStaysOnTopHint );
    //this->setAttribute( Qt::WA_TranslucentBackground ,true );
    //this->setStyleSheet( "QWidget{background-color:#101010;}" );

    //QPalette pa;
    //pa.setColor(QPalette::WindowText,Qt::red);
    //outLabel1->setPalette(pa);

    this->close();

    m_pCloseTimer = new QTimer(this);
    connect( m_pCloseTimer, SIGNAL( timeout() ), this, SLOT( HideMessageBox() ));

}

GCToolTips::~GCToolTips(){

}

void GCToolTips::ShowMessage( QString text ){

    this->close();

    m_pCloseTimer->start( 2000 );
    outLabel1->setText( text );

    this->exec();


}

void GCToolTips::HideMessageBox(){

    m_pCloseTimer->stop();
    this->close();
}






