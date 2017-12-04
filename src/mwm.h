#ifndef MWM_H
#define MWM_H

#include <QWidget>
#include <QDialog>
#include <QPoint>
#include <QPainter>
#include <QMouseEvent>
#include <QPaintEvent>
#include <QContextMenuEvent>

class MainWindow;
#include "mainwindow.h"


class MWM : public QDialog {

    Q_OBJECT

private:
    MainWindow  *mainUI;

    QWidget     *HHTip;

    int x1 = 0;
    int y1 = 1;
    int x2 = 64;
    int y2 = 1;

public:

    MWM( MainWindow  *mainUI, QWidget *parent = 0 );
    ~MWM();

    void ShowMWM();
    void HideMWM();
    void CloseMWM();
    void UpdateMWM( QString text  );


protected:

    virtual void mousePressEvent(QMouseEvent *event);
    virtual void mouseMoveEvent(QMouseEvent *event);
    virtual void mouseReleaseEvent(QMouseEvent *event);

    void paintEvent(QPaintEvent *event);
    void mouseDoubleClickEvent(QMouseEvent* event);
    void contextMenuEvent( QContextMenuEvent * event  );

    void enterEvent(QEvent *);
    void leaveEvent(QEvent *);

    void dragEnterEvent( QDragEnterEvent *e );
    void dropEvent( QDropEvent *e );

private:
    bool        mMoveing;
    QPoint      mMovePosition;
    QString     mwmText;

};

#endif // MWM_H
