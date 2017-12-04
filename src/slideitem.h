#ifndef SLIDEITEM_H
#define SLIDEITEM_H

#include <QSvgWidget>
#include <QLabel>
#include <QWidget>
#include <QListWidgetItem>
#include <QHBoxLayout>

class SlideItem : public QWidget
{
    Q_OBJECT
    
public:
    SlideItem(QString name, QString displayName, QWidget *parent=0);
	~SlideItem(); 
    
    QListWidgetItem* getItem();
    
    void active();
    void inactive();
    
private:
    QListWidgetItem *item;
    QString itemName;
    QString itemDisplayName;
    
    QHBoxLayout *layout;
    
    QSvgWidget *icon;
    QLabel *label;
    
    QWidget *activeLine;
};	

#endif

