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
    
    QHBoxLayout *layout = new QHBoxLayout(this);
    layout->setContentsMargins(0, 0, 0, 0);
    
    QSvgWidget *icon = new QSvgWidget(QString(":Resources/images/logo_24.svg"));
    icon->setFixedSize(24, 24);
    
    QAction *tBtn1 = new QAction(QIcon(":Resources/images/task_new_normal.svg"), "", parent );
    tBtn1->setData( "1" );

    QAction *tBtn2 = new QAction(QIcon(":Resources/images/task_new_normal.svg"), "", parent );
    tBtn2->setData( "2" );

    QAction *tBtn3 = new QAction(QIcon(":Resources/images/task_new_normal.svg"), "", parent );
    tBtn3->setData( "3" );

    QAction *tBtn4 = new QAction(QIcon(":Resources/images/task_start_normal.svg"), "", parent );
    tBtn4->setData( "4" );

    QAction *tBtn5 = new QAction(QIcon(":Resources/images/task_pause_normal.svg"), "", parent );
    tBtn5->setData( "5" );

    QAction *tBtn6 = new QAction(QIcon(":Resources/images/task_delete_normal.svg"), "", parent );
    tBtn6->setData( "6" );

    QAction *tBtn7 = new QAction(QIcon(":Resources/images/search_normal.svg"), "", parent );
    tBtn7->setData( "7" );

    QToolBar *toolsG = new QToolBar;
    toolsG->addAction( tBtn1 );
    toolsG->addAction( tBtn2 );
    toolsG->addAction( tBtn3 );
    toolsG->addAction( tBtn4 );
    toolsG->addAction( tBtn5 );
    toolsG->addAction( tBtn6 );
    toolsG->addAction( tBtn7 );

    layout->addWidget(icon);
    layout->addSpacing(90);
    layout->addStretch();

    layout->addWidget( toolsG, 0, Qt::AlignHCenter);
    //layout->setSpacing( 25 );
    layout->addStretch();

    connect( toolsG , &QToolBar::actionTriggered, this, &ToolBar::ToolBtnClick );

}

void ToolBar::ToolBtnClick( QAction *action ){

   qDebug() << "ToolBtnClick " << action->data().toString();

   emit SelToolItem(  action->data().toInt() );
}

ToolBar::~ToolBar() 
{
    
}



