#ifndef GCSYSTEMTRAYICON_H
#define GCSYSTEMTRAYICON_H

#include <QObject>
#include <QSystemTrayIcon>
#include <QMenu>
#include <QAction>

#include "gctooltips.h"

class GCSystemTrayIcon : public QSystemTrayIcon
{
public:

    GCSystemTrayIcon( QObject *parent = Q_NULLPTR );
    ~GCSystemTrayIcon();

    QMenu       *m_menu;
    GCToolTips  *m_tooltip;

private:

public:
    //void ShowTrayMessage( QString title = "深度下载", QString outText = "" );

slots
private:
    void ShowTrayMenu();
    void ShowWindow();
    void ActiveTray( QSystemTrayIcon::ActivationReason reason );


};

#endif // GCSYSTEMTRAYICON_H
