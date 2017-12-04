#ifndef SLIDEBAR_H
#define SLIDEBAR_H

#include <QListWidget>
#include <QSvgWidget>
#include <QLabel>
#include <QWidget>
#include <QListWidgetItem>
#include <QHBoxLayout>


//class SlideItem;

class GCSlideBar : public QListWidget
{
    Q_OBJECT

public:
    GCSlideBar( QWidget *parent = Q_NULLPTR );
    ~GCSlideBar();

    void SetSelectRow( int row );
    int  GetSelectRow();

public slots:
    void ItemSelected( QListWidgetItem *current, QListWidgetItem *previous );
    void RowSelected( int currentRow );

private:

    int activeRow;
};



#endif // SLIDEBAR_H
