#include "slideitem.h"
#include "utils.h"
#include <QLabel>
#include <QSvgWidget>

#include <QDebug>

SlideItem::SlideItem(QString name, QString displayName, QWidget *parent) : QWidget(parent)
{
    itemName = name;
    itemDisplayName = displayName;
    
    layout = new QHBoxLayout(this);
    layout->setContentsMargins(0, 0, 0, 0);
    
    icon = new QSvgWidget(QString(":Resources/images/%1_normal.svg").arg(name));
    icon->setFixedSize(16, 16);
    
    label = new QLabel();
    label->setText(itemDisplayName);
    
    activeLine = new QWidget;
    activeLine->setFixedSize(3, 32);
    activeLine->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
    activeLine->setStyleSheet(QString("background-color: #2CA7F8;"));
    
    layout->addSpacing(10);
    layout->addWidget(icon);
    layout->addSpacing(2);
    layout->addWidget(label);
    layout->addWidget(activeLine);

    activeLine->hide();
    
    item = new QListWidgetItem();
}

SlideItem::~SlideItem()
{
}

QListWidgetItem* SlideItem::getItem()
{
    return item;
}

void SlideItem::active()
{
    icon->load(QString(":Resources/images/%1_active.svg").arg(itemName));
    label->setStyleSheet("QLabel { color : #31A7F8; }");
    activeLine->show();
}

void SlideItem::inactive()
{
    icon->load(QString(":Resources/images/%1_normal.svg").arg(itemName));
    label->setStyleSheet("QLabel { color : black; }");
    activeLine->hide();
}
