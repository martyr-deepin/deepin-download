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

    QVBoxLayout *xx = new QVBoxLayout;
    xx->addWidget( outLabel1 );
    //xx->addWidget( button1 );

    this->setLayout( xx );
    this->setFixedSize( 350,100 );
    this->setWindowFlags(Qt::FramelessWindowHint | Qt::WindowStaysOnTopHint);
    this->setStyleSheet("QDialog{border:2px solid green;}");

    m_pCloseTimer = new QTimer(this);

    connect( m_pCloseTimer, SIGNAL( timeout() ), this, SLOT( HideMessageBox() ));

}

GCToolTips::~GCToolTips(){

}

void GCToolTips::ShowMessage( QString text ){

    this->hide();

    outLabel1->setText( text );
    this->show();

    QRect rect = QApplication::desktop()->availableGeometry();
    m_point.setX(rect.width() - width());
    m_point.setY(rect.height() - height());
    move( m_point.x(), m_point.y() );

    m_pCloseTimer->start( 5000 );

}

void GCToolTips::HideMessageBox(){

    m_pCloseTimer->stop();

    this->hide();
}






