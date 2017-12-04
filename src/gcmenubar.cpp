#include "gcmenubar.h"

#include <QDebug>


GCMenuBar::GCMenuBar( QWidget *parent ):QMenuBar( parent )
{

    QMenu* menu[10];
    QAction* act[10];
    //QMenuBar* menuBar ;

    menu[0] = new QMenu("文件(&F)");
    menu[0]->addAction("编辑");
    menu[0]->addAction("查看");
    menu[0]->addAction("工具");

    act[0] = new QAction("新建", this );
    act[0]->setShortcut( Qt::CTRL | Qt::Key_A );
    act[1] = new QAction("打开",this );

    menu[1] = new QMenu("测试");
    menu[1]->addAction( act[0]  );

    this->addMenu( menu[0] );
    this->addMenu( menu[1] );

    //connect( this, &QMenuBar::triggered,this,&GCMenuBar::MenuItemClick  );

}

void GCMenuBar::MenuItemClick( QAction *action ){

    qDebug() << "MenuItemClick " << action;
}
