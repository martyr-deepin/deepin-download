#ifndef GCSTATUSBAR_H
#define GCSTATUSBAR_H

#include <QWidget>
#include <QStatusBar>
#include <QLabel>
#include <QProgressBar>

class GCStatusBar : public QStatusBar
{

private:
    QLabel        *label;
    QProgressBar  *progressbar;

public:
    GCStatusBar( QWidget *parent = Q_NULLPTR );
};

#endif // GCSTATUSBAR_H
