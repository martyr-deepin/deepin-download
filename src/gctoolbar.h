#ifndef GCTOOLBAR_H
#define GCTOOLBAR_H

#include <QWidget>
#include <QToolBar>
#include <QAction>
#include <QIcon>

class GCToolBar : public QToolBar
{

public:
    GCToolBar( QWidget *parent = Q_NULLPTR );

slots
   private:
   void ToolBtnClick( QAction *action );

};

#endif // GCTOOLBAR_H
