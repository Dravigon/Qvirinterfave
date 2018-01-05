#ifndef NETWORKSTATEMONITORING_H
#define NETWORKSTATEMONITORING_H
#include "Network/networkmodel.h"
#include <QThread>

class NetworkStateMonitoring:public QThread
{
  Q_OBJECT
  NetworkModel *temp;
public:

  void run() override {
      QString result;
      temp->addNetworks();
      qDebug()<<"executed once";
      emit resultReady((QString)temp->rowCount());
  }
  NetworkStateMonitoring();
  NetworkStateMonitoring(NetworkModel *a){
    temp=a;
  }
signals:
  void resultReady(const QString &s);
};

#endif // NETWORKSTATEMONITORING_H
