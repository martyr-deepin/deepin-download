#include "gctoolbar.h"

#include "mainwindow.h"



GCToolBar::GCToolBar( QWidget *parent ):QToolBar( parent )
{

    QAction *tBtn1 = new QAction(QIcon(":Resources/images/task_new_normal.svg"), "", parent );
    tBtn1->setData( "1" );

    QAction *tBtn2 = new QAction(QIcon(":Resources/images/task_new_normal.svg"), "", parent );
    tBtn2->setData( "2" );

    QAction *tBtn3 = new QAction(QIcon(":Resources/images/task_new_normal.svg"), "", parent );
    tBtn3->setData( "3" );


    QAction *tBtn4 = new QAction(QIcon(":Resources/images/task_start_insensitive.svg"), "", parent );
    tBtn4->setData( "4" );
    QAction *tBtn5 = new QAction(QIcon(":Resources/images/task_pause_normal.svg"), "", parent );
    tBtn5->setData( "5" );
    QAction *tBtn6 = new QAction(QIcon(":Resources/images/task_delete_normal.svg"), "", parent );
    tBtn6->setData( "6" );
    QAction *tBtn7 = new QAction(QIcon(":Resources/images/search_normal.svg"), "", parent );
    tBtn7->setData( "7" );

    this->addAction( tBtn1  );
    this->addAction( tBtn2  );
    this->addAction( tBtn3  );
    this->addAction( tBtn4  );
    this->addAction( tBtn5  );
    this->addAction( tBtn6  );
    this->addAction( tBtn7  );

    //connect( this , &QToolBar::actionTriggered, this, &GCToolBar::ToolBtnClick );

}

void GCToolBar::ToolBtnClick( QAction *action ){

   qDebug() << "ToolBtnClick " << action->data().toString();

}



