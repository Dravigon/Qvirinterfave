#include "networkmodel.h"


Network::Network(const int &id,virNetworkPtr dom)
    : m_net(dom),m_id(id)
{
    m_name=QString(virNetworkGetName(m_net));
}

int Network::id() const
{
    return m_id;
}

QString Network::name() const
{
    return m_name;
}

NetworkModel::NetworkModel(QObject *parent)
    : QAbstractListModel(parent)
{
}

NetworkModel::NetworkModel(User *user)
{
    usr=user;
}

void NetworkModel::addNetworks()
{
    virNetworkPtr *networks=NULL;


    virConnectPtr conn=usr->getConn();
    QString username=usr->username();

    int ret;
    unsigned int flags = VIR_CONNECT_LIST_NETWORKS_ACTIVE|
            VIR_CONNECT_LIST_NETWORKS_INACTIVE;
    if(conn!=NULL){
        ret = virConnectListAllNetworks(conn, &networks, flags);
        if (ret < 0)
            qDebug()<<"error";
        int i=0;
        while(networks[i]){
            qDebug()<<i<<virNetworkGetName(networks[i])<<"0.2"<<"\n row count="<<rowCount();
            if((i+1)>rowCount()){
                qDebug()<<i<<">"<<rowCount();
                beginInsertRows(QModelIndex(), rowCount(), rowCount());
                m_network.append(*new Network(i,networks[i]));
                endInsertRows();
            }
            i++;
        }
    }
    if(networks!=NULL)
        delete [] networks;
}

void NetworkModel::refresh(){
    qDebug()<<"refreshed";
    addNetworks();
}

int NetworkModel::rowCount(const QModelIndex & parent) const {
    Q_UNUSED(parent);
    return m_network.count();
}

QVariant NetworkModel::data(const QModelIndex & index, int role) const {
    if (index.row() < 0 || index.row() >= m_network.count())
        return QVariant();

    const Network &network = m_network[index.row()];
    if (role == IdRole)
        return network.id();
    else if (role == NameRole)
        return network.name();
    return QVariant();
}

QString NetworkModel::task(QString task, int index)
{
    QString ret="nil";
    if(task=="start"){
        if(!(virNetworkIsActive(m_network.at(index).m_net))){
            virNetworkCreate(m_network.at(index).m_net);
            ret="started";
        }
    }
    else if(task=="stop"){
        if((virNetworkIsActive(m_network.at(index).m_net))){
            virNetworkDestroy(m_network.at(index).m_net);
            ret="stopped";
        }
    }
    else if(task=="state"){
        if((virNetworkIsActive(m_network.at(index).m_net))){
            ret="started";
        }
        else
           ret="stopped";
    }

    ////return doTask(task,index,m_network.at(index));
    return ret;
}

QHash<int, QByteArray> NetworkModel::roleNames() const {
    QHash<int, QByteArray> roles;
    roles[IdRole] = "id";
    roles[NameRole] = "name";
    return roles;
}


