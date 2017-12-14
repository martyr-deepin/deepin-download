#include "slidebar.h"
#include "slideitem.h"
#include <QDebug>
#include <QPainter>

SlideBar::SlideBar(QListWidget *parent) : QListWidget(parent)
{
    /*
        1:下载中
        2:队列中
        3:已完成
        4:历史记录
        D:全部任务
    */

    selectAllItem = new SlideItem("nav_alltask", "全部任务");
    selectDownloadingItem = new SlideItem("nav_downloading", "下载中");
    selectTaskItem = new SlideItem("task_pause", "已暂停");
    selectDoneItem = new SlideItem("nav_done", "已完成");
    selectfileItem = new SlideItem("file", "历史记录");
    //selectDocumentItem = new SlideItem("document", "全部任务");
    //selectTrashItem = new SlideItem("trash", "垃圾箱");

    addSlideItem(selectAllItem);
    addSlideItem(selectDownloadingItem);
    addSlideItem(selectTaskItem);
    addSlideItem(selectDoneItem);
    addSlideItem(selectfileItem);
    //addSlideItem(selectDocumentItem);
    //addSlideItem(selectTrashItem);

    setFixedWidth(200);

    activeRow = -1;

    connect(this, &SlideBar::currentRowChanged, this, &SlideBar::monitorActiveItem);
    
    setCurrentRow(0);
}

SlideBar::~SlideBar(){

}

void SlideBar::monitorActiveItem(int activeItemRow)
{
    if (activeRow != -1) {
        switch(activeRow) {
        case 0:
            selectAllItem->inactive();
            break;
        case 1:
            selectDownloadingItem->inactive();
            break;
        case 2:

            selectTaskItem->inactive();
            break;
        case 3:
            selectDoneItem->inactive();
            break;
        case 4:
            selectfileItem->inactive();
            break;
        case 5:
            selectDocumentItem->inactive();
            break;
        case 6:
            selectTrashItem->inactive();
            break;
        }
    }

    switch(activeItemRow) {
    case 0:
        selectAllItem->active();
        break;
    case 1:
        selectDownloadingItem->active();
        break;
    case 2:
        selectTaskItem->active();
        break;
    case 3:
        selectDoneItem->active();
        break;
    case 4:
        selectfileItem->active();
        break;
    case 5:
        selectDocumentItem->active();
        break;
    case 6:
        selectTrashItem->active();
        break;
    }

    activeRow = activeItemRow;

    emit SelSlideItem( activeRow );
}

void SlideBar::addSlideItem( SlideItem *item )
{
    addItem( item->getItem() );
    item->getItem()->setSizeHint( QSize(-1, 32) );
    setItemWidget(item->getItem(), item);
}

