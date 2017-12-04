#ifndef NEWDOWN_H
#define NEWDOWN_H

#include <QWidget>
#include <QDialog>
#include <QLabel>
#include <QPushButton>
#include <QTextEdit>
//#include <QLineEdit>

class MainWindow;
#include "mainwindow.h"

class NewDown : public QDialog
{
    Q_OBJECT
public:
    explicit NewDown( MainWindow *mainUI , QWidget *parent = nullptr);

    void SetDownloadEdit( QString urlStr );
    void ClearEdit();
private:

    MainWindow  *mainUI;

    QTextEdit   *Edit1;
    //QLabel      *Label1;
    QLabel      *msg;

    //QPushButton *button1;
    //QPushButton *button2;

signals:

private slots:

    void Button1Click();
    void Button2Click();

};

#endif // NEWDOWN_H
