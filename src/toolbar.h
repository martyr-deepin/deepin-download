#ifndef TOOLBAR_H
#define TOOLBAR_H
#include <QWidget>
#include <QToolBar>
#include <QHBoxLayout>
#include "dsearchedit.h"

class ToolBar : public QWidget{

    Q_OBJECT
    
private:
    QToolBar *toolsG  = NULL;
    Dtk::Widget::DSearchEdit *searchedit;
    QHBoxLayout *layout = NULL;
    //QHBoxLayout *layout2 = NULL;

public:
    ToolBar(QWidget *parent=0);
	~ToolBar(); 

    void SetToolButton();
    void SetToolSearch();

private slots:

   void ToolBtnClick( QAction *action );
   void returnPressed();

signals:
   void SelToolItem( int btn );
   void SearchChang( QString text );

};
#endif
