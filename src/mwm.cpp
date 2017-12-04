#include "mwm.h"
#include <QApplication>
#include <QDesktopWidget>
#include <QScreen>
#include <QGuiApplication>
#include <QMimeData>
#include <QDragEnterEvent>

MWM::MWM( MainWindow  *mainUI,  QWidget *parent){

    mMoveing = false;

    setWindowFlags( Qt::FramelessWindowHint  | Qt::WindowStaysOnTopHint );
    this->setStyleSheet("QDialog{border:2px solid green;}");
    this->setFixedSize( 64,64 );

    this->mwmText = "0";
    this->mainUI =  mainUI;

    this->setContextMenuPolicy( Qt::DefaultContextMenu );

    HHTip = new QWidget;
    HHTip->setWindowOpacity(0.5);
    HHTip->setWindowFlags( Qt::FramelessWindowHint );
    HHTip->setStyleSheet("QWidget{background-color:#101010;}");
    //HHTip->setAttribute(Qt::WA_TranslucentBackground ,true);
    HHTip->setFixedSize( 250,300 );

}

MWM::~MWM(){


}

void MWM::ShowMWM(){

    this->show();

    QScreen *screen = QGuiApplication::primaryScreen();
    QRect screenGeometry = screen->geometry();
    move(( screenGeometry.width() - width()) - 128,  128 );

    this->setAcceptDrops( true );

}

void MWM::HideMWM(){

    this->hide();
}

void MWM::CloseMWM(){

    this->close();
}

void MWM::mousePressEvent(QMouseEvent *event){

    mMoveing = true;
    mMovePosition = event->globalPos() - pos();

    HHTip->hide();

    return QDialog::mousePressEvent(event);
}


void MWM::mouseMoveEvent(QMouseEvent *event){

    if (mMoveing && (event->buttons() && Qt::LeftButton)
        && (event->globalPos()-mMovePosition).manhattanLength() > QApplication::startDragDistance()){

        move(event->globalPos()-mMovePosition);
        mMovePosition = event->globalPos() - pos();

    }

    return QDialog::mouseMoveEvent(event);
}


void MWM::mouseReleaseEvent(QMouseEvent *event){

    mMoveing = false;
}

void MWM::mouseDoubleClickEvent(QMouseEvent* event){

    this->show();
    this->mainUI->activateWindow();

}

void MWM::paintEvent(QPaintEvent *event)
{
    Q_UNUSED(event);

    QPainter painter(this);
    painter.setPen(QColor(0, 160, 230));
    //painter.setPen( Qt::red );

    painter.drawLine( x1, y1, x2, y2);

    QFont font;
    font.setPointSize( 11 );
    painter.setFont(font);
    painter.drawText( rect(), Qt::AlignCenter,  this->mwmText +" %" );

}

void MWM::UpdateMWM( QString text  ){

    this->mwmText = text;

    if( y1 < 64){

       y1 +=10 ;
       y2 = y1;

    }else{

       y1 = 0;
       y2 = y1;
    }

    update();
}

void MWM::contextMenuEvent( QContextMenuEvent * event  ){

     if( mainUI->ShareRMenu() != NULL ){

         mainUI->ShareRMenu()->exec( QCursor::pos() );
     }
}


void MWM::dragEnterEvent( QDragEnterEvent *e ){

    qDebug() << "dragEnterEvent ";

    if( e->mimeData()->hasFormat("text/uri-list") || e->mimeData()->hasFormat("torrent/uri-list") ){
        e->acceptProposedAction();
    }

}

void MWM::dropEvent( QDropEvent *e ){

    qDebug() << "dropEvent ";


    QList<QUrl> urls = e->mimeData()->urls();
    if(urls.isEmpty()) return ;

    foreach ( QUrl u, urls ) {
       qDebug()<< "FileName: " <<  u.toString();
       mainUI->OpenLinkFile( u.toString() );
    }
}

void MWM::enterEvent( QEvent *e ){


    //HHTip->show();
    //HHTip->move( QCursor::pos() );
}

void MWM::leaveEvent( QEvent *e ){


    //HHTip->hide();
}

















