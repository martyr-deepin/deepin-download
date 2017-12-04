#include "gcthread.h"

#include <QDebug>

GCThread::GCThread( MainWindow  *mainUI ){

    this->mainUI = mainUI;
    this->stopped = false;
}

void GCThread::run(){

    while( !stopped ){

        switch ( this->fCode ) {

        case 1:
            //mainUI->GetActiveList();
            break;

        case 2:
            //mainUI->GetStopList();
            break;

        case 3:
            //mainUI->GetWaitList();
            break;

        default:
            break;
        }

        //this->mainUI->UpdateDownStatus();
        sleep( 2 );
    }

    this->stopped = false;
}

void GCThread::setFunction( int fCode ){

    this->fCode = fCode;
}

void GCThread::stop(){

    this->stopped = true;
}

