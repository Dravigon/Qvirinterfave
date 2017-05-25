#include "user.h"

QString name;
QString pwd;

User::User(QObject *parent) : QObject(parent)
{

}

User::~User(){
  if(m_conn!=NULL)
    virConnectClose(m_conn);
}

//for libvirt authentication
static int authCreds[] = {
  VIR_CRED_AUTHNAME,
  VIR_CRED_PASSPHRASE,
};
int User:: authCb(virConnectCredentialPtr cred, unsigned int ncred, void *cbdata=NULL)
{
  unsigned int i;
  for (i = 0; i < ncred; i++) {
      if (cred[i].type == VIR_CRED_AUTHNAME) {

          qDebug()<<name;
          cred[i].result = strdup(name.toStdString().c_str());
          if (cred[i].result == NULL)
            return -1;
          cred[i].resultlen = strlen(cred[i].result);
        }
      else if (cred[i].type == VIR_CRED_PASSPHRASE) {
          qDebug()<<pwd;
          cred[i].result = strdup(pwd.toStdString().c_str());
          if (cred[i].result == NULL)
            return -1;
          cred[i].resultlen = strlen(cred[i].result);
        }
    }
  return 0;
}

QString User::authenticate(QString zone){
  name=m_username;
  pwd=m_password;

  QString ret_value="no";

  QString host_uri;

  if(zone=="Localhost"){
      m_hostaddress="localhost";
    }
  else {
      m_hostaddress=zone;
      qDebug()<<"remote host select";
    }
 // host_uri="qemu+libssh2://"+name+"@"+m_hostaddress+"/system";
  host_uri="qemu:///system";
  auth.credtype = authCreds;
  auth.ncredtype = sizeof(authCreds)/sizeof(int);
  auth.cb = authCb;
  auth.cbdata = NULL;

  qDebug()<<"okaut";
  m_conn = virConnectOpenAuth(host_uri.toStdString().c_str(), &auth, 0);
  if (m_conn == NULL) {
      virError err;
      virCopyLastError(&err);
      QString error=QString(err.message)+" Failed to open Connection to "+host_uri;
      qDebug()<<error;
      virResetError(&err);
      ret_value=error;
    }
  else{
      ret_value="connected";
      qDebug()<<"okaut2";
    }
  return ret_value;
}

void User::close()
{
  if(m_conn!=NULL)
      virConnectClose(m_conn);
}

QString User::err()
{
    return virGetLastErrorMessage();

}
