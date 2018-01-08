#include "downlistview.h"
#include <QHeaderView>
#include <QScrollBar>

DownListView::DownListView( MainWindow *mainUI, QWidget *parent): QTableView( parent ){

    /**
    QString filename;   // 文件名
    QString Progress;   // 大小和进度
    QString Speed;      // 速度
    QString RestTime;   // 剩余时间
    QString State;      // 状态
    */

    this->mainUI = mainUI;

    QStringList tbHeader;
    //tbHeader << "文件名" << "大小和进度" << "速度" << "剩余" << "状态" << "gid";
    tbHeader << tr("File name") << tr("Size") << tr("Speed") << tr("Remaining time") << tr("Status") << "gid" << "status" << "dtime" <<"progress";

    QList<TBItem> tbList;

    initTable( tbHeader ,tbList );

}

void DownListView::initTable( QStringList tbHeader ,QList<TBItem> tbList ){

    //允许右键表格
    this->setContextMenuPolicy( Qt::CustomContextMenu );
/*
    //右键激活菜单
    connect( this,
             SIGNAL( customContextMenuRequested( QPoint )),
             this,
             SLOT( ShowContextMenu( QPoint )) );


    //单击
    connect( this,
             SIGNAL(clicked(QModelIndex)),
             this,
             SLOT(  Itemlick(QModelIndex) ));

    //双击
    connect( this,
             SIGNAL(doubleClicked(QModelIndex)),
             this,
             SLOT( ItemDBClick(QModelIndex)));
*/

    //整行选择
    this->setSelectionBehavior( QAbstractItemView::SelectRows );
    //不允许编辑
    this->setEditTriggers( QAbstractItemView::NoEditTriggers );

    //表头字体
    //this->horizontalHeader()->setFont(QFont ("Simsun" , 12));

    //设置行交替颜色
    this->setAlternatingRowColors(true);

    //只能单选一个项
    //this->setSelectionMode(QAbstractItemView::SingleSelection);

    //表头信息显示居左
    this->horizontalHeader()->setDefaultAlignment( Qt::AlignLeft );

    //隐藏垂直表头
    this->verticalHeader()->setVisible( false );


    //this->horizontalScrollBar()->setEnabled( false );
    this->horizontalScrollBar()->setVisible( false );

    //隐藏行头
    //this->verticalHeader()->hide();

    //背景网格线设置

    //显示
    //this->setShowGrid(true);

    //不显示
    this->setShowGrid(false);

    //网格背景画笔
    /**
    常量	                值   描述
    Qt::NoPen	        0	 无线
    Qt::SolidLine       1	 实线
    Qt::DashLine	    2    虚线
    Qt::DotLine	        3	 点线
    Qt::DashDotLine	    4	 虚点线
    Qt::DashDotDotLine	5	 虚点点线
    Qt::CustomDashLine	6	 自定义虚线
    */
    this->setGridStyle( Qt::DotLine );

    //
    m_dataModel = new QStandardItemModel();

    //设置标题
    //m_dataModel->setHeaderData(0,Qt::Horizontal,"标题");

    //设置列数
    //m_dataModel->setColumnCount (8 );

    //设置表头
   m_dataModel->setHorizontalHeaderLabels( tbHeader );

   int nRow = m_dataModel->rowCount();

   //填充数据表
   for( int i = 0 ; i < tbList.size() ; i++  ){

       InsertItem( nRow,tbList.at(i) );
       nRow++ ;
   }


   this->setModel(  m_dataModel );

   /** 列宽自适应大小 */
//this->horizontalHeader()->setSectionResizeMode( QHeaderView::ResizeToContents );
//   QFont hfont;
//   hfont.setBold(false);
//   hfont.setStyleName("Normal");
//   hfont.setWeight(1);
//   this->horizontalHeader()->setFont( hfont );

  //verticalHeader()->setDefaultSectionSize(15);


   /** 初始列宽定义 */
   this->setColumnWidth( 0 ,300 );
   this->setColumnWidth( 1 ,300 );
   this->setColumnWidth( 2 ,100 );
   this->setColumnWidth( 3 ,100 );
   this->setColumnWidth( 4 ,100 );



   //this->setColumnHidden( 5,true );
   //this->setColumnHidden( 6,true );
   //this->setColumnHidden( 7,true );


   /** 代理 进度条 */
   ProgressBarDelegate *progressbar = new ProgressBarDelegate;
   this->setItemDelegate( progressbar );

   /**
    * 初始化右键菜单
    */
   m_ContextMenu = new QMenu();

   tableHead  = this->horizontalHeader();
   tableHead->setSortIndicator(1,Qt::AscendingOrder);

   tableHead->setHighlightSections(false);

   //tableHead->setSortIndicatorShown(true);
   connect( tableHead, SIGNAL(sectionClicked(int)), this, SLOT(view_sort(int)));

}

void DownListView::SetTableWidth( int MainWidth ){

    //qDebug() << "new Width " << z0;

    if ( MainWidth >= 1024 ){

        int z0 = MainWidth * 0.30;
        int z1 = MainWidth * 0.25;
        int z2 = MainWidth * 0.10;
        int z3 = MainWidth * 0.5;
        int z4 = MainWidth - z0 - z1 - z3;


        this->setColumnWidth( 0 ,z0 );
        this->setColumnWidth( 1 ,z1 );
        this->setColumnWidth( 2 ,z2 );
        this->setColumnWidth( 3 ,z3 );
        this->setColumnWidth( 4 ,z4 );

    }else{

        this->setColumnWidth( 0 ,300 );
        this->setColumnWidth( 1 ,100 );
        this->setColumnWidth( 2 ,100 );
        this->setColumnWidth( 3 ,100 );
        this->setColumnWidth( 4 ,100 );

    }

}

void DownListView::UpdateItem( TBItem tbitem  ){



}

void DownListView::AppendItem( TBItem tbitem  ){

    //if(  tbitem.savepath != "" ){
        //忽略错误项
        if( tbitem.State != "error" ){

            //m_dataModel->insertRow( row );
            //SetItemData( row ,tbitem );
            int nRow = m_dataModel->rowCount();
            m_dataModel->insertRow( nRow );
            SetItemData( nRow ,tbitem );
        }
    //}
}



void DownListView::InsertItem( int row ,TBItem tbitem  ){

    if(  tbitem.uri != ""  ){


            m_dataModel->insertRow( row );
            SetItemData( row ,tbitem );


    }else{

        qDebug() << tbitem.savepath;
    }

}

void DownListView::SetItemData( int row ,TBItem tbitem  ){

    QString filename = "";
    if( tbitem.uri.lastIndexOf ("%2F") != -1 ){

        filename = tbitem.uri.right( tbitem.uri.length() - tbitem.uri.lastIndexOf ("%2F") - 3 );

    }else if ( tbitem.uri.lastIndexOf ("/") != -1 ){

        filename = tbitem.uri.right( tbitem.uri.length() - tbitem.uri.lastIndexOf ("/") - 1 );
    }else{

        filename = tbitem.uri;
    }


    if( filename.indexOf( "%" ) != -1 ){

        //转码 url 编码 ==> 中文
        QByteArray urlEncoding = QByteArray::fromPercentEncoding( filename.toUtf8() );
        QString urlCNstr =  QString( urlEncoding );

        qDebug() << "urlCNstr " << urlCNstr;
        filename = urlCNstr;

    }

    qDebug() << "filename: " << filename;
    SetItemData( row, 0,  filename );

    int speedInt = 0;
    QString Speed = "";
    if( tbitem.Speed.toInt(NULL,10) > 0 ){
       Speed =  QString::number( tbitem.Speed.toInt(NULL,10) / 1024 ) + " Kb/S";
       speedInt = tbitem.Speed.toInt(NULL,10);
    }

    QString RestTime = "";
    int ssSize = 0;
    if( tbitem.RestTime.split("|").size() == 2   ){

        QStringList t = tbitem.RestTime.split("|");
        if(  t.at(1).toInt(NULL,10) >0  && t.at(0).toInt(NULL,10) >0 ){
          RestTime = QString::number( t.at(1).toInt(NULL,10) / 1024 / 1024 )+ " MB / "+QString::number( t.at(0).toInt(NULL,10) / 1024 / 1024 ) + " MB";
          ssSize = t.at(0).toInt(NULL,10) - t.at(1).toInt(NULL,10);
        }
    }

    QString OutProgress = "";
    if( tbitem.Progress == "0" ){

        SetItemData( row, 1,  "");
    }else{

        OutProgress = RestTime +"    "+ tbitem.Progress + " %";

        int w =  this->columnWidth( 1 );
        int O = OutProgress.length() * 12 - 20;
        if ( w < O ){

            this->setColumnWidth(  1,O );
        }
        SetItemData( row, 1, OutProgress );
    }


    SetItemData( row, 2,  Speed );

    //qDebug() << "ssSize " << ssSize;
    //qDebug() << "speed " << speedInt;
    if( ssSize >0 && speedInt >0  ){

        //ssSize =  ssSize / 1024 / 1024 ;
        //speedInt = speedInt /1024;
        int rt = ssSize / speedInt;

        //qDebug()<< "RTime: " << rt;
        //qDebug()<< "RTime: " << SDTime( rt );

        QString RTime = SDTime( rt );

        SetItemData( row, 3,  RTime );
    }else{
        //SetItemData( row, 3,  RestTime );
    }




 /**
    文案：
    【全部任务】【All tasks】
    【下载中】【Downloading】
    【已暂停】【Paused】
    【已完成】【Finished】
    【回收站】【Trash】
    【文件名】【File name】
    【大小】【Size】
    【速度】【Speed】
    【剩余时间】【Remaining time】
    【状态】【Status】
    【已删除】【Deleted】
 **/

    QString StateStr = "";
    if( tbitem.State == "active" ){

        StateStr = tr( "Downloading" );

    } else if ( tbitem.State == "waiting" ){

        StateStr = tr( "Paused" );

    } else if ( tbitem.State == "paused" ){

        StateStr = tr( "Paused" );

    } else if ( tbitem.State == "error" ){

        StateStr = tr( "error" );

    } else if ( tbitem.State == "complete" ){

        StateStr = tr( "Finished" );

    } else if ( tbitem.State == "removed" ){

        StateStr = tr( "Deleted" );

    }else{

        //StateStr = tr( "Deleted" );
    }

    SetItemData( row, 4,  StateStr );

    SetItemData( row, 5,  tbitem.gid );
    SetItemData( row, 6,  tbitem.State );

    SetItemData( row, 7,  tbitem.dtime );
    SetItemData( row, 8,  tbitem.Progress );

    m_dataModel->item( row , 1 )->setTextAlignment(Qt::AlignCenter);
    //m_dataModel->item( row , 2 )->setTextAlignment(Qt::AlignCenter);
    //m_dataModel->item( row , 3 )->setTextAlignment(Qt::AlignCenter);
    //m_dataModel->item( row , 4 )->setTextAlignment(Qt::AlignCenter);

    this->setColumnHidden( 5,true );
    this->setColumnHidden( 6,true );
    this->setColumnHidden( 7,true );
    this->setColumnHidden( 8,true );

    //this->setRowHeight( row, 25   );
}

void DownListView::SetItemData( int row,int col,QString vStr  ){

    m_dataModel->setItem( row, col, new QStandardItem( vStr ) );
    //m_dataModel->item( row,col )->setText( vStr );

}

void DownListView::SetHeadWidth( int col,int widthV ){

    this->setColumnWidth( col ,widthV );
}


void DownListView::Itemlick( QModelIndex index ){

   qDebug() << "Itemlick: " <<  index;

}

void DownListView::ItemDBClick( QModelIndex index){

   qDebug() << "ItemDBClick: " << index;
}


void DownListView::UpdateTable(  QList<TBItem>  tbList ){

    qDebug() << "UpdateTable(  QList<TBItem>  tbList ) " ;
    /** 记录下此时 listView 中已选择的行 */
    const QModelIndexList selected = this->selectionModel()->selectedRows();

    //ClearAllItem();
    //填充数据表

    for( int i = 0 ; i < tbList.size() ; i++  ){
        InsertItem( i,tbList.at(i) );
        //nRow++ ;
    }

    /**
     * 恢复此前 listView 已选择行的高亮
     */
    QItemSelection sel;
    foreach( const QModelIndex & index, selected){

        QItemSelectionRange readSel( index );
        sel.append( readSel );

    }
    this->selectionModel()->select( sel ,QItemSelectionModel::Select|QItemSelectionModel::Rows );
}

void DownListView::DeleteItem( int iRow ){

   m_dataModel->removeRow( iRow );

}


void DownListView::ClearAllItem(){

   m_dataModel->removeRows(0, m_dataModel->rowCount() );

}

void DownListView::ShowContextMenu( const QPoint &point ){

    /**
    qDebug() << "ShowContextMenu: " << point;

    QModelIndex  modelindex = this->indexAt( point );    
    qDebug() << "ROW ======> " << modelindex.row() + 1;


    QAction *RMenuItem[8];

    m_ContextMenu->clear();

    RMenuItem[0] =  new QAction( tr("Paused") ,this);
    RMenuItem[0]->setData( "1");

    RMenuItem[1] = new QAction( tr("Continue") ,this);
    RMenuItem[1]->setData( "2");

    RMenuItem[2] = new QAction( tr("Remove") ,this);
    RMenuItem[2]->setData( "3");

    RMenuItem[3] = new QAction( tr("property") ,this);
    RMenuItem[3]->setData( "4");

    m_ContextMenu->addSeparator();

    RMenuItem[4] = new QAction( tr("Redownload") ,this);
    RMenuItem[4]->setData( "5");

    RMenuItem[5] = new QAction( tr("Show in folder") ,this);
    RMenuItem[5]->setData( "6");

    RMenuItem[6] = new QAction( tr("Copy download link") ,this);
    RMenuItem[6]->setData( "7");

    RMenuItem[7] = new QAction( tr("Delete download records") ,this);
    RMenuItem[7]->setData( "8");

    RMenuItem[8] = new QAction( tr("Clean up caching") ,this);
    RMenuItem[8]->setData( "9");

    bool x = false;

    for( int i = 0 ; i < 9 ; i++){
        m_ContextMenu->addAction( RMenuItem[i]  );
    }

    if( modelindex.row() < 0){

        //x = true;
        for( int i = 0 ; i < 9 ; i++ ){
            RMenuItem[i]->setDisabled( x );
        }
    }


    qDebug() << "GetSelectRow: " << mainUI->GetSlideSelRow();

    int SlideSelRow = mainUI->GetSlideSelRow();

        switch ( SlideSelRow ) {
            case 0:
                break;
            case 1:
            //    break;
            case 2:
                RMenuItem[3]->setDisabled(true);
                RMenuItem[4]->setDisabled(true);
                RMenuItem[5]->setDisabled(true);
                RMenuItem[7]->setDisabled(true);
                break;
            case 3:   //已完成
                RMenuItem[0]->setDisabled(true);
                RMenuItem[1]->setDisabled(true);
                RMenuItem[2]->setDisabled(true);
                RMenuItem[7]->setDisabled(true);
                break;
            case 4:   //历史记录
                RMenuItem[0]->setDisabled(true);
                RMenuItem[1]->setDisabled(true);
                RMenuItem[2]->setDisabled(true);
                break;
            case 5:  //
                break;
            case 6:
                break;
            default:

                break;

        }

    m_ContextMenu->exec( QCursor::pos() ); // 当前鼠标位置
    **/
}

void DownListView::view_sort(int column) {

    int i   = tableHead->sortIndicatorOrder();

    if( 0 == i ) {

        m_dataModel->sort(column, Qt::AscendingOrder);

    }else {

        m_dataModel->sort(column, Qt::DescendingOrder);
    }

}

QString DownListView::SDTime( int sec ) {

       int day = 0;
       int hour = 0;
       int min = 0;
/**
       hour = sec / 3600;

       if( hour > 24) {

           day = hour / 24;
           hour =( sec /  3600 ) % 24 % 60;
           min = ( sec %  3600 ) / 60;
           sec = ( sec %  3600 ) % 60;

       }else{*/

           hour = sec / 3600;
           min = ( sec %  3600 ) / 60;
           sec = ( sec %  3600 ) % 60;
/*
       }
*/
       //printf("%d D %d H:%d M:%d S\n",day,hour,min,sec );
       QString rtStr;
       //rtStr = QString("%1 %2 %3 %4").arg( day ).arg( hour ).arg( min ).arg( sec );

       rtStr = QString("%1:%2:%3").arg( hour ).arg( min ).arg( sec );

       char buffer[20];
       memset( buffer,0, sizeof(buffer)*sizeof(char));
       sprintf( buffer, "%.2d:%.2d:%.2d",hour,min,sec);
       QString Z = QString(QLatin1String(buffer));


       return Z;//rtStr;

}

/**
* 进度条 处理
*/
//////////////////////////////////////////////////////////////////////////////////////////
ProgressBarDelegate::ProgressBarDelegate(QObject *parent) :QStyledItemDelegate(parent){

    //
}

void ProgressBarDelegate::paint( QPainter *painter, const QStyleOptionViewItem &option, const QModelIndex &index ) const{


        QStyleOptionViewItem viewOption(option);

        initStyleOption(&viewOption, index);

        if ( option.state.testFlag( QStyle::State_HasFocus ) ){
            viewOption.state = viewOption.state ^ QStyle::State_HasFocus;
        }

        QStyledItemDelegate::paint( painter, viewOption, index );



        if ( index.column() == 1 ){


            //int nProgress = index.model()->data( index,Qt::DisplayRole ).toInt();
            int nProgress = index.sibling( index.row(),8 ).data().toInt();

            //int nProgress = index.model()->data( index ).toString().replace("%","").trimmed().toInt(NULL);
            int nLeft = 0;
            int nTop = 28;
            int nWidth = option.rect.width() - 2 * nLeft;
            int nHeight = 2;//option.rect.height() - 2  * nTop;

            // 设置进度条的风格
            QStyleOptionProgressBar *progressBarOption = new QStyleOptionProgressBar;
            progressBarOption->initFrom(option.widget);
            // 设置进度条显示的区域
            progressBarOption->rect = QRect( option.rect.left() + nLeft, option.rect.top() + nTop ,  nWidth, nHeight);
            // 设置最小值
            progressBarOption->minimum = 0;
            // 设置最大值
            progressBarOption->maximum = 100;
            // 设置对齐方式
            progressBarOption->textAlignment = Qt::AlignCenter;
            // 设置进度
            progressBarOption->progress = nProgress;
            // 设置文本（百分比）
            //progressBarOption->text = QString("%1%").arg( nProgress );
            // 设置文本可见
            //progressBarOption->textVisible = true;

            QProgressBar *progressBar = new QProgressBar;
            //绘制进度条
            //CE_ProgressBarGroove,
            //CE_ProgressBarContents,
            DApplication::style()->drawControl( QStyle::CE_ProgressBarContents, progressBarOption, painter, progressBar );

        }else{
            //否则调用默认委托
            QStyledItemDelegate::paint(painter, option, index);
        }
}

