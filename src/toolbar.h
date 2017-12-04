#ifndef TOOLBAR_H
#define TOOLBAR_H

#include <QWidget>

class ToolBar : public QWidget
{
    Q_OBJECT
    
public:
    ToolBar(QWidget *parent=0);
	~ToolBar(); 

private slots:

   void ToolBtnClick( QAction *action );

signals:
   void SelToolItem( int btn );

};
#endif
