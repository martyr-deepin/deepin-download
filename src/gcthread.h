#ifndef GCTHREAD_H
#define GCTHREAD_H

#include <QThread>

/** ======================================= */

class MainWindow;
#include "mainwindow.h"
/** ======================================= */


class GCThread : public QThread
{
    Q_OBJECT

public:
   GCThread( MainWindow  *mainUI );
   void setFunction( int fCode );
   void stop();

protected:

   void run();
   //void printMessage();

private:

   MainWindow  *mainUI;
   volatile bool stopped;
   volatile int  fCode;
};

#endif // GCTHREAD_H
