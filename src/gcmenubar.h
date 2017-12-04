#ifndef GCMENUBAR_H
#define GCMENUBAR_H

#include <QWidget>
#include <QMenuBar>
#include <QMenu>
#include <QAction>


class GCMenuBar : public QMenuBar
{
public:
    GCMenuBar( QWidget *parent = Q_NULLPTR );

slots
  private:
    void MenuItemClick( QAction *action );

};

#endif // GCMENUBAR_H
