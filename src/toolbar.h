#ifndef TOOLBAR_H
#define TOOLBAR_H
#include <QWidget>
#include <QToolBar>
#include <QHBoxLayout>
#include "dsearchedit.h"

class ToolBar : public QWidget{

    Q_OBJECT
    
private:


    QHBoxLayout *layout = NULL;
    //QHBoxLayout *layout2 = NULL;

public:
    ToolBar(QWidget *parent=0);
	~ToolBar(); 
    QToolBar *toolsG  = NULL;
    Dtk::Widget::DSearchEdit *searchedit = NULL;
    void SetToolButton();
    void SetToolSearch();

signals:
   void SelToolItem( int btn );
   void SearchChang( QString text );
   void SearchfocusOut();

private slots:

   void ToolBtnClick( QAction *action );
   void returnPressed();
   void focusOut();


};
#endif
