#include "watchdog.h"

void WatchDog::startWorkInAThread()
{
  qDebug()<<"started in thread";
  //connect(workerThread, &WorkerThread::resultReady, this, &MyObject::handleResults);
  workerThread->start();

}

WatchDog::WatchDog()
{
    connect(workerThread, &NetworkStateMonitoring::finished, workerThread, &QObject::deleteLater);

}
