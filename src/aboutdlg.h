#ifndef ABOUTDLG_H
#define ABOUTDLG_H

#include <QWidget>
#include <QDialog>

class AboutDlg : public QDialog
{
    Q_OBJECT
public:
    explicit AboutDlg(QWidget *parent = nullptr);
    ~AboutDlg();

signals:

public slots:
};

#endif // ABOUTDLG_H
