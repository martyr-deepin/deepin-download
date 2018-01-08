#ifndef GCTOOLTIPS_H
#define GCTOOLTIPS_H

#include <QString>
#include <QDialog>
#include <QWidget>
#include <QTimer>
#include <QPoint>

#include <QPushButton>
#include <QLabel>

class GCToolTips : public QDialog {

    Q_OBJECT
public:
    explicit GCToolTips( QWidget *parent = nullptr );
    ~GCToolTips();

    void ShowMessage( QString text );

private slots:
    void HideMessageBox();

private:
   QPoint   m_point;

private:
   QLabel         *outLabel1;
   QPushButton    *button1;
   QTimer         *m_pCloseTimer;

//signals:
//public slots:

};

#endif // GCTOOLTIPS_H
