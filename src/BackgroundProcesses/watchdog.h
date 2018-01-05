#ifndef WATCHDOG_H
#define WATCHDOG_H
#include <QThread>
#include "networkstatemonitoring.h"
#include "vmstatemonitoring.h"
#include "Network/networkmodel.h"

class WatchDog:public QThread {
  Q_OBJECT
  NetworkStateMonitoring *workerThread;
public:
  void startWorkInAThread();
  void run() override {
    while(true){
        if(workerThread->isRunning()){
          sleep(10);
          continue;
          }

        startWorkInAThread();
      }
  }

signals:
  void resultReady(const QString &s);

  //  QThread* thread = new QThread;
  //  Worker* worker = new Worker();
  //  worker->moveToThread(thread);
  //  connect(worker, SIGNAL(error(QString)), this, SLOT(errorString(QString)));
  //  connect(thread, SIGNAL(started()), worker, SLOT(process()));
  //  connect(worker, SIGNAL(finished()), thread, SLOT(quit()));
  //  connect(worker, SIGNAL(finished()), worker, SLOT(deleteLater()));
  //  connect(thread, SIGNAL(finished()), thread, SLOT(deleteLater()));
  //  thread->start();
public:
  WatchDog();
  WatchDog(NetworkModel *a){
    workerThread = new NetworkStateMonitoring(a);
  }
  ~WatchDog() override{
    workerThread->quit();
    this->quit();
  }

};

#endif // WATCHDOG_H
