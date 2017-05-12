#include "domainmodel.h"
#include "task.h"

Domain::Domain(const int &id,virDomainPtr dom,QString username)
  : m_dom(dom),m_id(id)
{
  m_name=QString(virDomainGetName(m_dom)).replace((username+"*"),"");
}

int Domain::id() const
{
  return m_id;
}

QString Domain::name() const
{
  return m_name;
}

DomainModel::DomainModel(QObject *parent)
  : QAbstractListModel(parent)
{
}

DomainModel::DomainModel(User *user)
{
  usr=user;
}

void DomainModel::addDomains()
{
  virDomainPtr *domains=NULL;

virConnectPtr conn=usr->getConn();
QString username=usr->username();

  int ret;
  unsigned int flags = VIR_CONNECT_LIST_DOMAINS_ACTIVE|
      VIR_CONNECT_LIST_DOMAINS_INACTIVE;

  ret = virConnectListAllDomains(conn, &domains, flags);
  if (ret < 0)
    qDebug()<<"error";
  int i=0;
  while(domains[i]){
      qDebug()<<i<<virDomainGetName(domains[i])<<"0.2"<<"\n row count="<<rowCount();
      if((i+1)>rowCount()){
      beginInsertRows(QModelIndex(), rowCount(), rowCount());
      m_domain.append(*new Domain(i,domains[i],username));
      endInsertRows();
        }
      i++;
    }
  if(domains!=NULL)
    delete [] domains;
}

void DomainModel::refresh(){
  qDebug()<<"refreshed";
  addDomains();
}

int DomainModel::rowCount(const QModelIndex & parent) const {
  Q_UNUSED(parent);
  return m_domain.count();
}

QVariant DomainModel::data(const QModelIndex & index, int role) const {
  if (index.row() < 0 || index.row() >= m_domain.count())
    return QVariant();

  const Domain &domain = m_domain[index.row()];
  if (role == IdRole)
    return domain.id();
  else if (role == NameRole)
    return domain.name();
  return QVariant();
}

QString DomainModel::task(QString task, int index)
{
return doTask(task,index,m_domain.at(index));
}

QHash<int, QByteArray> DomainModel::roleNames() const {
  QHash<int, QByteArray> roles;
  roles[IdRole] = "id";
  roles[NameRole] = "name";
  return roles;
}


