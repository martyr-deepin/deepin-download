#include "gcsystemtrayicon.h"

GCSystemTrayIcon::GCSystemTrayIcon( QObject *parent ):QSystemTrayIcon( parent ){


    /** 气泡窗　暂弃用**/
    m_tooltip =  new GCToolTips;
    m_tooltip->ShowMessage( "测试启动" );




    //托盘菜单
    m_menu = new QMenu;
    QAction *m_action1 = new QAction( m_menu );
    QAction *m_action2 = new QAction( m_menu );
    QAction *m_action3 = new QAction( m_menu );
    QAction *m_action4 = new QAction( m_menu );

    QAction *m_action5 = new QAction( m_menu );
    QAction *m_action6 = new QAction( m_menu );

    QAction *m_action7 = new QAction( m_menu );


    m_action1->setText( tr("about") );
    m_action1->setData( 1 );

    m_action2->setText( tr("Quit") );
    m_action2->setData( 2 );

    m_action3->setText( tr("Option Configuration") );
    m_action3->setData( 3 );
    m_action3->setVisible( false );


    m_action4->setText( tr("Main Window") );
    m_action4->setData( 4 );

    m_action5->setText( tr("Hidden suspension window"));
    m_action5->setData( 5 );

    m_action6->setText( tr("Show suspension window"));
    m_action6->setData( 6 );

    m_action7->setText( tr("Clear Aria2c Cache"));
    m_action7->setData( 8 );

    m_menu->addAction( m_action7 );
    m_menu->addAction( m_action4 );
    m_menu->addAction( m_action5 );
    m_menu->addAction( m_action6 );
    m_menu->addAction( m_action3 );
    m_menu->addAction( m_action1 );
    m_menu->addAction( m_action2 );


    m_action3->setVisible( false );
    m_action5->setVisible( false );
    m_action6->setVisible( false );

    //connect(m_action1, &QAction::triggered, this, &GCSystemTrayIcon::ShowWindow);
    //connect(m_action2, &QAction::triggered, this, &GCSystemTrayIcon::ShowTrayMessage);

    this->setContextMenu(m_menu);

    //新建托盘要显示的icon
    this->setIcon( QIcon(":Resources/images/logo@2x.png") );
    this->setToolTip( tr("deepin download") );
    this->show();    

    //connect(this, &QSystemTrayIcon::activated, this, &GCSystemTrayIcon::ActiveTray);//点击托盘，执行相应的动作
    //connect(this, &QSystemTrayIcon::messageClicked, this, &GCSystemTrayIcon::ShowWindow);//点击消息框，显示主窗口

}

GCSystemTrayIcon::~GCSystemTrayIcon(){
    //
    delete m_menu;
    delete m_tooltip;

}

void GCSystemTrayIcon::ActiveTray( QSystemTrayIcon::ActivationReason reason ){

    switch (reason){

        case QSystemTrayIcon::Context:
            ShowTrayMenu();
            break;
        case QSystemTrayIcon::DoubleClick:
            ShowWindow();
            break;
        case QSystemTrayIcon::Trigger:
            //ShowTrayMessage();
            break;
    }
}

void GCSystemTrayIcon::ShowTrayMenu(){

    m_menu->show();
}

void GCSystemTrayIcon::ShowWindow(){

    this->show();
}


