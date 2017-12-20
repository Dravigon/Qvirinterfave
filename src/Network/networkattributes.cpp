#include "networkattributes.h"

networkAttributes::networkAttributes()
{

}

QString Nat::getStart() const
{
  //qDebug()<<QStringLiteral("start is  as")<<start;
    return start;
}

void Nat::setStart(const QString &value)
{
    this->start = value;
    //qDebug()<<"start is set as"<<start;
}

QString Nat::getEnd() const
{
    return end;
}

void Nat::setEnd(const QString &value)
{
    this->end = value;
}

Nat::Nat(QObject *parent):QObject (parent)
{

}

Nat::Nat(const Nat &value){
  this->start=value.getStart();
  this->end=value.getEnd();
}

QString Nat::xml(){
  QString xml="";
  QXmlStreamWriter stream(&xml);
  stream.setAutoFormatting(true);
  stream.writeStartElement("nat");
  stream.writeEmptyElement("port");
  qDebug()<<"\n \n Nat Start:"+start;
  stream.writeAttribute("start", start);
  stream.writeAttribute("end", end);
  stream.writeEndElement();
  return xml;
}

bool Nat::natExist(){
  return (start.isEmpty())&&(end.isEmpty());
}

QString Forward::getMode() const
{
  return mode;
}

void Forward::setMode(const QString &value)
{
    mode = value;
}

QString Forward::getDev() const
{
    return dev;
}

void Forward::setDev(const QString &value)
{
    dev = value;
}

Nat * Forward::getNat() const
{
    return nat.data();
}

void Forward::setNat(const Nat &value)
{
  qDebug()<<"Nat exist:"<<nat->natExist()<<"\n Nat start"<<nat->getStart()<<" Nat end"<<nat->getEnd();
  nat.clear();
  QSharedPointer<Nat> temp=QSharedPointer<Nat>(new Nat(value), &QObject::deleteLater);
  nat.swap(temp);
}

QString Forward::xml()
{
    QString xml="";
    QXmlStreamWriter stream(&xml);
    stream.setAutoFormatting(true);

    stream.writeStartElement("forward");
    stream.writeAttribute("mode", mode);
    qDebug()<<"mode::"<< mode;

    if(dev!=nullptr)
      stream.writeAttribute("dev", dev);
    if(!nat->natExist()){
        stream.writeDTD(nat->xml());
      }
    stream.writeEndElement();
    qDebug()<<"ohh yeah"<<xml;

    return xml;
}
QString Bridge::getName() const
{
    return name;
}

void Bridge::setName(const QString &value)
{
    name = value;
}

QString Bridge::getStp() const
{
    return stp;
}

void Bridge::setStp(const QString &value)
{
    stp = value;
}

QString Bridge::getDelay() const
{
    return delay;
}

void Bridge::setDelay(const QString &value)
{
    delay = value;
}

QString Bridge::xml(){
    QString xml="";
    QXmlStreamWriter stream(&xml);
    stream.setAutoFormatting(true);
    stream.writeStartElement("bridge");
  stream.writeAttribute("name", name);
  stream.writeAttribute("stp", stp);
  stream.writeAttribute("delay",delay);
  stream.writeEndElement();
  return xml;
}
QString Qos::getAverage() const
{
    return average;
}

void Qos::setAverage(const QString &value)
{
    average = value;
}

QString Qos::getPeak() const
{
    return peak;
}

void Qos::setPeak(const QString &value)
{
    peak = value;
}

QString Qos::getBurst() const
{
    return burst;
}

void Qos::setBurst(const QString &value)
{
    burst = value;
}

Qos::Qos(const Qos &value)
{
  this->average=value.getAverage();
  this->burst=value.getBurst();
  this->peak=value.getPeak();
}

QString Qos::xml(QString type){
    QString xml="";
    QXmlStreamWriter stream(&xml);
    stream.setAutoFormatting(true);
    stream.writeEmptyElement(type);
  if(!average.isEmpty())
  stream.writeAttribute("average", average);
  if(!peak.isEmpty())
  stream.writeAttribute("peak", peak);
  if(!burst.isEmpty())
  stream.writeAttribute("burst", burst);
  stream.writeEndElement();
  return xml;
}
Qos* bw::getInbound() const
{
    return inbound.data();
}

void bw::setInbound(const Qos &value)
{
  inbound.clear();
  QSharedPointer<Qos> temp=QSharedPointer<Qos>(new Qos(value), &QObject::deleteLater);
  inbound.swap(temp);

}

Qos* bw::getOutbound() const
{
    return outbound.data();
}

void bw::setOutbound(const Qos &value)
{
  outbound.clear();
  QSharedPointer<Qos> temp=QSharedPointer<Qos>(new Qos(value), &QObject::deleteLater);
  outbound.swap(temp);
}



QString bw::xml(){
  QString xml="";
  QXmlStreamWriter stream(&xml);
  stream.setAutoFormatting(true);
  stream.writeStartElement("bandwidth");
  if(!inbound->isEmpty())
  stream.writeDTD(inbound->xml("inbound"));
  if(!outbound->isEmpty())
  stream.writeDTD(outbound->xml("outbound"));
  stream.writeEndElement();
  return xml;
}

QString Dhcp::xml(QString ForwardMode){
  QString xml="";
  QXmlStreamWriter stream(&xml);
  stream.writeStartElement("dhcp");
  if(rangeExist()){
      stream.writeEmptyElement("range");
      stream.writeAttribute("start", getRange()->start);
      stream.writeAttribute("end", getRange()->end);
    }
  if (hasHost&&(ForwardMode.toLower()=="route")) {
      int k=0;
      while (numberOfHost()>k) {
          QString id,ip,name,mac;
          id=(getHost()->data(getHost()->index(k,0),HostModel::IdRole)).toString();
          ip=(getHost()->data(getHost()->index(k,0),HostModel::IpRole)).toString();
          name=(getHost()->data(getHost()->index(k,0),HostModel::NameRole)).toString();
          mac=(getHost()->data(getHost()->index(k,0),HostModel::MacRole)).toString();
          // HOST *Host=new HOST(id,name,mac,ip);
          stream.writeEmptyElement("host");
          if(id!=nullptr)
            stream.writeAttribute("id", id);
          if(mac!=nullptr)
            stream.writeAttribute("mac",mac);
          if(name!=nullptr)
            stream.writeAttribute("name", name);
          if(ip!=nullptr)
            stream.writeAttribute("ip",ip);
          k++;
        }

    }
  stream.writeEndElement();
  return xml;
}

Range *Dhcp::getRange() const
{
  return range.data();
}

void Dhcp::setRange(const Range&value)
{
  range.clear();
  QSharedPointer<Range> temp=QSharedPointer<Range>(new Range(value), &QObject::deleteLater);
  range.swap(temp);
}




HostModel *Dhcp::getHost() const
{
  return host;
}

void Dhcp::setHost(HostModel *value)
{
  host = value;
}

bool Dhcp::getHasHost() const
{
  return hasHost;
}

void Dhcp::setHasHost(bool value)
{
  hasHost = value;
}



QString IP4::getFamily() const
{
  return family;
}

void IP4::setFamily(const QString &value)
{
  family = value;
}

QString IP4::getAddress() const
{
  return address;
}

void IP4::setAddress(const QString &value)
{
  address = value;
}

QString IP4::getNetmask() const
{
  return netmask;
}

void IP4::setNetmask(const QString &value)
{
  netmask = value;
}

bool IP4::getHasDhcp() const
{
  return hasDhcp;
}

void IP4::setHasDhcp(bool value)
{
  hasDhcp = value;
}

Dhcp IP4::getDhcp() const
{
  return dhcp;
}

void IP4::setDhcp(const Dhcp &value)
{
  dhcp = value;
}

bool IP4::getExist() const
{
  return exist;
}

void IP4::setExist(bool value)
{
  exist = value;
}

QString IP6::getAddress() const
{
  return address;
}

void IP6::setAddress(const QString &value)
{
  address = value;
}

QString IP6::getPrefix() const
{
    return prefix;
}

void IP6::setPrefix(const QString &value)
{
    prefix = value;
}

bool IP6::getHasDhcp() const
{
    return hasDhcp;
}

void IP6::setHasDhcp(bool value)
{
    hasDhcp = value;
}

Dhcp IP6::getDhcp() const
{
    return dhcp;
}

void IP6::setDhcp(const Dhcp &value)
{
    dhcp = value;
}

bool IP6::getExist() const
{
    return exist;
}

void IP6::setExist(bool value)
{
    exist = value;
}

QString IP6::getFamily() const
{
    return family;
}

void IP6::setFamily(const QString &value)
{
    family = value;
}

Range::Range()
{

}

Range::Range(const Range &value)
{
  this->exist=value.exist;
  this->start=value.start;
  this->end=value.end;
}
