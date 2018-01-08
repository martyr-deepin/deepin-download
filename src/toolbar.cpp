#include "toolbar.h"
#include <QHBoxLayout>
#include <QPainter>
#include <QDebug>
#include <QLabel>
#include <QSvgWidget>
#include "utils.h"
#include <QToolBar>
#include "QAction"


ToolBar::ToolBar(QWidget *parent) : QWidget(parent)
{

    this->setFixedHeight(24);
    layout = new QHBoxLayout(this);
    layout->setContentsMargins(0, 0, 0, 0);
    
    QSvgWidget *icon = new QSvgWidget(QString(":Resources/images/logo_24.svg"));
    //icon->setFixedSize(24, 24);
    
    tBtn1 = new QAction(QIcon(":Resources/images/task_new_normal.svg"), "", parent );
    tBtn1->setData( "1" );
/**
    QAction *tBtn2 = new QAction(QIcon(":Resources/images/task_new_normal.svg"), "", parent );
    tBtn2->setData( "2" );

    QAction *tBtn3 = new QAction(QIcon(":Resources/images/task_new_normal.svg"), "", parent );
    tBtn3->setData( "3" );
**/
    tBtn4 = new QAction(QIcon(":Resources/images/task_start_normal.svg"), "", parent );
    tBtn4->setData( "4" );

    tBtn5 = new QAction(QIcon(":Resources/images/task_pause_normal.svg"), "", parent );
    tBtn5->setData( "5" );

    tBtn6 = new QAction(QIcon(":Resources/images/task_delete_normal.svg"), "", parent );
    tBtn6->setData( "6" );

    tBtn7 = new QAction(QIcon(":Resources/images/search_normal.svg"), "", parent );
    tBtn7->setData( "7" );

    toolsG = new QToolBar;
    toolsG->addAction( tBtn1 );
//    toolsG->addAction( tBtn2 );
//    toolsG->addAction( tBtn3 );
    toolsG->addAction( tBtn4 );
    toolsG->addAction( tBtn5 );
    toolsG->addAction( tBtn6 );
    toolsG->addAction( tBtn7 );

    searchedit = new Dtk::Widget::DSearchEdit;

    layout->addWidget( icon );
    layout->addSpacing( 150 );

    layout->addStretch();
    layout->addWidget( toolsG );
    layout->addWidget( searchedit );
    layout->addStretch();

    //layout->setSpacing( 25 );
    //tBtn2->setVisible( false );
    //tBtn3->setVisible( false );
    tBtn4->setEnabled( false );
    tBtn5->setEnabled( false );
    tBtn6->setEnabled( false );

    searchedit->setVisible( false );

    QHBoxLayout *layout2 = new QHBoxLayout(this);
    setLayout( layout2 );

    connect( toolsG , &QToolBar::actionTriggered, this, &ToolBar::ToolBtnClick );

    connect( searchedit , &Dtk::Widget::DSearchEdit::returnPressed, this, &ToolBar::returnPressed );    

    connect( searchedit , &Dtk::Widget::DSearchEdit::focusOut, this, &ToolBar::focusOut );
}

ToolBar::~ToolBar(){
    
}


void ToolBar::SetToolSearch(){

    //searchedit->setVisible( false );
    //toolsG->setVisible( true );

}

void ToolBar::SetToolButton(){

    //searchedit->setVisible( true );
    //toolsG->setVisible( false );
}

void ToolBar::ToolBtnClick( QAction *action ){

   qDebug() << "ToolBtnClick " << action->data().toString();


   emit SelToolItem(  action->data().toInt() );
}

void ToolBar::returnPressed(){

    //qDebug() << "searchedit->text: ==> " << searchedit->text() ;

    emit SearchChang( searchedit->text() );
}


void ToolBar::focusOut(){

    //qDebug() << "textChanged:: ==> " << searchedit->text() ;

    emit SearchfocusOut();
}


