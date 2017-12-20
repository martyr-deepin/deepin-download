#include "gcslidebar.h"

#include <QDebug>

GCSlideBar::GCSlideBar( QWidget *parent ) : QListWidget(parent){


    QIcon allICON(":Resources/images/nav_alltask_normal.svg");
    QIcon completeICON(":Resources/images/nav_downloading_normal.svg");
    QIcon pauseICON(":Resources/images/task_pause_normal.svg");
    QIcon downloadingICON(":Resources/images/nav_done_normal.svg");
    QIcon recycleICON(":Resources/images/trash_normal.svg");

    QListWidgetItem* lst1 = new QListWidgetItem( allICON, "全部任务", this);
    QListWidgetItem* lst2 = new QListWidgetItem( completeICON, "下载中", this);
    QListWidgetItem* lst5 = new QListWidgetItem( pauseICON, "队列中", this);
    QListWidgetItem* lst3 = new QListWidgetItem( downloadingICON, "已完成", this);
    QListWidgetItem* lst4 = new QListWidgetItem( downloadingICON, "历史记录", this);

    //QListWidgetItem* lst6 = new QListWidgetItem( recycleICON, "回收站", this);

    lst1->setSizeHint(QSize(40,40));
    lst2->setSizeHint(QSize(40,40));
    lst3->setSizeHint(QSize(40,40));
    lst4->setSizeHint(QSize(40,40));
    lst5->setSizeHint(QSize(40,40));
    //lst6->setSizeHint(QSize(40,40));

    this->insertItem(1, lst1);
    this->insertItem(2, lst2);
    this->insertItem(5, lst5);
    this->insertItem(3, lst3);
    this->insertItem(4, lst4);


    lst1->setHidden( true );

    //this->insertItem(6, lst5);

    this->setIconSize(QSize(20,20));


    //connect( this, &QListWidget::currentItemChanged, this, &GCSlideBar::ItemSelected );
    //connect( this, &QListWidget::currentRowChanged, this, &GCSlideBar::RowSelected );

}

GCSlideBar::~GCSlideBar(){

}


void GCSlideBar::RowSelected( int currentRow ){

    qDebug()<< currentRow;
}

void GCSlideBar::ItemSelected( QListWidgetItem *current, QListWidgetItem *previous ){

   qDebug()<< current ;

}

void GCSlideBar::SetSelectRow( int row ){

    this->setCurrentRow( row );
}

int GCSlideBar::GetSelectRow(){

    return this->currentRow();

}

