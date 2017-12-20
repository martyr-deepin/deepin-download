#ifndef GCLISTVIEW_H
#define GCLISTVIEW_H
#include <QApplication>
#include <DApplication>
#include <QWidget>
#include <QTableView>
#include <QHeaderView>
#include <QModelIndex>
#include <QHeaderView>
#include <QProgressBar>
#include <QStyleOptionViewItem>
#include <QStyledItemDelegate>
#include <QStandardItemModel>
#include <QPainter>
#include <QMenu>
#include <QSize>
#include <QStyle>
#include <QDebug>

#include "downrecord.h"

/**
*
================================================= */
class MainWindow;
#include "mainwindow.h"

/** ============================================= */

class DownListView : public QTableView
{    
    Q_OBJECT

private:
    MainWindow *mainUI;
    QHeaderView *tableHead;

public:    
    explicit DownListView(  MainWindow *mainUI,QWidget *parent = Q_NULLPTR);

    QMenu *m_ContextMenu;

    void SetItemData( int row ,TBItem tbitem  );
    void SetItemData( int row,int col,QString vStr  );
    void InsertItem( int row ,TBItem tbitem  );
    void UpdateTable(  QList<TBItem> tbList );
    void SetHeadWidth( int col , int widthV );

    void UpdateItem( TBItem tbitem  );
    void AppendItem( TBItem tbitem  );

    void DeleteItem( int iRow );
    void ClearAllItem();
    QStandardItemModel *m_dataModel;

    void SetTableWidth( int MainWidth );

protected:

    //int sizeHintForColumn(int column) const;
    //void paintEvent(QPaintEvent *event);


private:

    void initTable(  QStringList tbHeader ,QList<TBItem> tbList  );

signals:
private slots:
    void Itemlick( QModelIndex index );
    void ItemDBClick( QModelIndex index);
    void ShowContextMenu( const QPoint &point );
    void view_sort(int column);

};

class ProgressBarDelegate : public QStyledItemDelegate
{
    Q_OBJECT
    public:
        explicit ProgressBarDelegate( QObject *parent = 0 );
        void paint( QPainter *painter, const QStyleOptionViewItem &option, const QModelIndex &index ) const;
    signals:
    public slots:

};

#endif // GCLISTVIEW_H
