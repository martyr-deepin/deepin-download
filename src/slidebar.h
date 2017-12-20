#ifndef SLIDEBAR_H
#define SLIDEBAR_H

#include "slideitem.h"
#include <QListWidget>

class SlideBar : public QListWidget
{
    Q_OBJECT
    
public:
    SlideBar(QListWidget *parent=0);
	~SlideBar(); 
    
public slots:
    void monitorActiveItem(int activeItemRow);
    
private:
    void addSlideItem(SlideItem *item);
    
    SlideItem *selectAllItem;
    SlideItem *selectDownloadingItem;    
    SlideItem *selectTaskItem;
    SlideItem *selectDoneItem;
    SlideItem *selectfileItem;
    SlideItem *selectDocumentItem;
    SlideItem *selectTrashItem;
    
    int activeRow;

signals:
    void SelSlideItem( int row );

};	

#endif

