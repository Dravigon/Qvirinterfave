#include "dns.h"

Txt *Dns::txt()
{
    return m_txt;
}
//TODO
void Dns::setTxt(Txt &txt)
{
    m_txt=&txt;
}

Forwarder *Dns::forwarder()
{
    return m_forwarder;
}

void Dns::setForwarder(  Forwarder & forwarder)
{
    m_forwarder=&forwarder;
}

Srv *Dns::srv()
{
    return m_srv;
}

void Dns::setSrv(Srv & srv)
{
    m_srv=&srv;
}

Dns::Dns()
{

}

Txt::Txt(QObject *parent):
    VStandardItemModel (parent)
{

}

Srv::Srv(QObject *parent):
    VStandardItemModel (parent)
{

}

Forwarder::Forwarder(QObject *parent):
    VStandardItemModel(parent)
{

}
