#ifndef USER_H
#define USER_H

#include <QObject>
#include <QDebug>
#include <libvirt/libvirt.h>
#include <libvirt/virterror.h>


class User : public QObject
{
  Q_OBJECT
  virConnectPtr m_conn=NULL;
  static int authCb(virConnectCredentialPtr cred, unsigned int ncred, void *cbdata);
  virConnectAuth auth;
public:
  explicit User(QObject *parent = 0);
  ~User();


  //This returns the connection object
  virConnectPtr getConn(){
    return m_conn;
  }
  Q_PROPERTY(QString username READ username WRITE setUsername)
  QString username() const{
      return m_username;
  }
  void setUsername(QString usr){
      m_username=usr;
  }

  Q_PROPERTY(QString password READ password WRITE setPassword)
  QString password() const{
      return m_password;
  }
  void setPassword(QString pwd){
      m_password=pwd;
  }

  QString m_hostaddress;//to fix the selected host address for connection

  Q_INVOKABLE QString authenticate(QString type);//to autenticate the user
  Q_INVOKABLE void close();
  Q_INVOKABLE QString err();

private:
  QString m_username;
  QString m_password;

signals:


public slots:

};

#endif // USER_H
