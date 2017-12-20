#include "networkxml.h"

void networkxml::setnet(networkxml temp)
{
    name=temp.name;
    isforwardExist=temp.isforwardExist;
    forward=temp.forward;
    bridge=temp.bridge;
    bandwidth=temp.bandwidth;
    ip4=temp.ip4;
    ip6=temp.ip6;
    route=temp.route;
    device=temp.device;
}

void networkxml::setXml(QIODevice *dev)
{
    //    qDebug()<<"__Network_:"<<dev->readAll();
    //    qDebug()<<"____________";
    device=dev;
}

networkxml::networkxml(QIODevice *dev)
{
    device=dev;
    isforwardExist=false;
}
int networkxml::read(){
    QIODevice *dev=device;
    QXmlStreamReader stream1(dev);
    // qDebug()<<device->readAll();
    while (!stream1.atEnd()) {
        if(stream1.isEndElement()){
            qDebug()<<"reached end element";
            stream1.readNext();
            continue;
        }
        if(stream1.isStartElement()){

            if(stream1.name()=="name"){
                stream1.readNext();
                name=stream1.text().toString();
            }
            else if(stream1.name()=="uuid"){
                stream1.readNext();
                UUID=stream1.text().toString();
            }
            else if(stream1.name()=="domain"){
                stream1.readNext();
                domainName=stream1.attributes().value("name").toString();
                localOnly=stream1.attributes().value("localOnly").toString();

            }
            else if(stream1.name()=="bridge"){
                bridge.exist=true;
                QString name=stream1.attributes().value("name").toString();
                QString stp=stream1.attributes().value("stp").toString()!=""?stream1.attributes().value("stp").toString():"on";
                QString delay=stream1.attributes().value("delay").toString()!=""?stream1.attributes().value("delay").toString():"0";
                bridge = Bridge(name,stp,delay);
            }
            else if(stream1.name()=="forward"){
                isforwardExist=true;
                forward.setMode(stream1.attributes().value("mode").toString());
                forward.setDev(stream1.attributes().value("dev").toString()!=""?stream1.attributes().value("dev").toString():nullptr);
                QString natStart=nullptr;
                QString natEnd=nullptr;
                Nat *tempNat=new Nat;
                qDebug()<<"Forward is nat?:"<<forward.isNat();
                if((forward.isNat())&&(!stream1.isEndElement())){
                    qDebug()<<"nat def is present"<<stream1.isEndElement();
                    stream1.readNextStartElement();
                    if(!stream1.isEndElement()){
                        stream1.readNextStartElement();
                        qDebug()<<stream1.name();
//                        forward.natExist=true;
                        natStart=stream1.attributes().value("start").toString();
                        natEnd=stream1.attributes().value("end").toString();
                        tempNat->setStart(natStart);
                        tempNat->setEnd(natEnd);
                    }
                }
                forward.setNat(*tempNat);
                delete tempNat;
            }
            else if(stream1.name()=="bandwidth"){
                bandwidth.exist=true;
                stream1.readNextStartElement();
                if(stream1.name()=="inbound"){
                    QString average=stream1.attributes().value("average").toString();
                    QString peak=stream1.attributes().value("peak").toString();
                    QString burst=stream1.attributes().value("burst").toString();
                    bandwidth.setInbound(Qos(average,peak,burst));
                }
                stream1.readNextStartElement();
                stream1.readNextStartElement();
                if(stream1.name()=="outbound"){
                    QString average=stream1.attributes().value("average").toString();
                    QString peak=stream1.attributes().value("peak").toString();
                    QString burst=stream1.attributes().value("burst").toString();
                    bandwidth.setOutbound(Qos(average,peak,burst));
                }
            }
            else if(stream1.name()=="ip"){
                IP4 temp;
                IP6 temp1;
                temp.setHasDhcp(false);
                temp1.setHasDhcp(false);
                while(stream1.isEndElement()){
                    stream1.readNextStartElement();
                    qDebug()<<"end string"<<stream1.attributes().value("family").toString();
                }
                qDebug()<<stream1.attributes().value("family").toString();


                if((stream1.attributes().value("family").toString()=="ipv4")||(stream1.attributes().value("family").toString()=="")){
                    temp.setExist(true);
                    qDebug()<<"true ip4";
                }
                else if(stream1.attributes().value("family").toString()=="ipv6"){
                    temp1.setExist(true);
                }


                if(stream1.attributes().value("family").toString()=="ipv6"){
                    qDebug()<<"ip6";
                    ip6.setExist(true);
                    temp1.setFamily(stream1.attributes().value("family").toString());
                    temp1.setPrefix(stream1.attributes().value("prefix").toString());
                    if(stream1.attributes().value("address").toString()!=""){
                        temp1.setAddress(stream1.attributes().value("address").toString());
                    }
                    stream1.readNextStartElement();
                    if(stream1.name()=="dhcp"){
                        qDebug()<<stream1.name();
                        temp1.setHasDhcp(true);
                        stream1.readNextStartElement();
                        if(stream1.name()=="range"){
                            QString start=stream1.attributes().value("start").toString();
                            QString end=stream1.attributes().value("end").toString();
                            temp1.setDhcp(Dhcp(start,end));
                        }

                        while ((stream1.name()=="host")&&(stream1.name()!="")&&(!stream1.atEnd())) {

                            temp.getDhcp().setHasHost(true);
                            bool flag=false;
                            //HOST *htemp=new HOST();
                            QString ip,mac,id,name;
                            if((temp1.getFamily()=="ipv4")||(temp1.getFamily()=="")){
                                mac=(stream1.attributes().value("mac").toString());
                                flag=true;
                            }
                            if(stream1.attributes().value("id").toString()!=""){
                                id=(stream1.attributes().value("id").toString());
                                flag=true;
                            }
                            if(stream1.attributes().value("name").toString()!=""){
                                name=(stream1.attributes().value("name").toString());
                                flag=true;
                            }
                            if(stream1.attributes().value("ip").toString()!=""){
                                ip=(stream1.attributes().value("ip").toString());
                                flag=true;
                            }
                            if(flag){
                                QStandardItem* item=new QStandardItem();
                                item->setData(id,HostModel::IdRole);
                                item->setData(mac,HostModel::MacRole);
                                item->setData(name,HostModel::NameRole);
                                item->setData(ip,HostModel::IpRole);
                                temp1.getDhcp().append(item);

                                qDebug()<<stream1.name()<<" name:"<<stream1.attributes().value("name").toString();
                            }
                            stream1.readNextStartElement();
                            while(stream1.isEndElement())
                                stream1.readNextStartElement();
                        }
                    }
                    ip6=temp1;

                    qDebug()<<"size is:"<<ip6.getDhcp().numberOfHost();
                }
                else if((stream1.attributes().value("family").toString()=="ipv4")||(stream1.attributes().value("family").toString()=="")){
                    temp.setExist(true);
                    qDebug()<<"ip \n \n ip4 \n \n"<<ip4.getExist();
                    (temp.setAddress(stream1.attributes().value("family").toString()));
                    temp.setNetmask(stream1.attributes().value("netmask").toString());
                    if(stream1.attributes().value("address").toString()!=""){
                        temp.setAddress(stream1.attributes().value("address").toString());
                        qDebug()<<"address"<<stream1.attributes().value("address").toString();
                    }
                    stream1.readNextStartElement();
                    if(stream1.name()=="dhcp"){
                        qDebug()<<stream1.name();
                        temp.setHasDhcp(true);
                        stream1.readNextStartElement();
                        if(stream1.name()=="range"){

                            QString start=stream1.attributes().value("start").toString();
                            QString end=stream1.attributes().value("end").toString();
                            temp.setDhcp(Dhcp(start,end));
                        }

                        while ((stream1.name()=="host")&&(stream1.name()!="")&&(!stream1.atEnd())) {

                            temp.getDhcp().setHasHost(true);
                            bool flag=false;
                            QString id,name,mac,ip;

                            if((temp.getAddress()=="ipv4")||(temp.getAddress()=="")){
                                mac=(stream1.attributes().value("mac").toString());
                                flag=true;
                            }
                            if(stream1.attributes().value("id").toString()!=""){
                                id=(stream1.attributes().value("id").toString());
                                flag=true;
                            }
                            if(stream1.attributes().value("name").toString()!=""){
                                name=(stream1.attributes().value("name").toString());
                                flag=true;
                            }
                            if(stream1.attributes().value("ip").toString()!=""){
                                ip=(stream1.attributes().value("ip").toString());
                                flag=true;
                            }
                            if(flag){
                                //explicit HOST(QString &id,QString &mac,QString &name,QString &ip);
                                QStandardItem* item=new QStandardItem();
                                item->setData(id,HostModel::IdRole);
                                item->setData(mac,HostModel::MacRole);
                                item->setData(name,HostModel::NameRole);
                                item->setData(ip,HostModel::IpRole);
                                temp.getDhcp().append(item);

                                qDebug()<<stream1.name()<<" name:"<<stream1.attributes().value("name").toString();
                            }
                            stream1.readNextStartElement();
                            while(stream1.isEndElement())
                                stream1.readNextStartElement();
                        }
                    }
                    ip4=temp;
                }
                continue;
            }
            else if(stream1.name()=="route"){
                Route temp;
                qDebug()<<stream1.name();
                if(stream1.attributes().value("family").toString()!="ipv6"){
                    temp.family=stream1.attributes().value("family").toString();
                    temp.prefix=stream1.attributes().value("prefix").toString();
                }
                if((stream1.attributes().value("family").toString()!="ipv4")||(stream1.attributes().value("family").toString()!="")){
                    temp.family=stream1.attributes().value("family").toString();
                    temp.netmask=stream1.attributes().value("netmask").toString();
                }
                if(stream1.attributes().value("address").toString()!=""){
                    temp.address=stream1.attributes().value("address").toString();
                }
                if(stream1.attributes().value("gateway").toString()!=""){
                    temp.gateway=stream1.attributes().value("gateway").toString();
                }
                route.append(temp);
            }
        }
        stream1.readNext();

    }
    dev->close();
    return 0;
}

//TODO add the writecharater and give user a custom entry feature where he can
//add his own xml from qml

QString networkxml::write(){

    QString xml;

    QXmlStreamWriter stream(&xml);
    stream.setAutoFormatting(true);


    stream.writeStartElement("network");
    stream.writeTextElement("name",name);
    if(nullptr!=UUID)
     stream.writeTextElement("uuid",UUID);

    if(bridge.exist){
        stream.writeDTD(bridge.xml());
    }

    if(isforwardExist){
      stream.writeDTD(forward.xml());
    }
    //domain
   stream.writeEmptyElement("domain");
   stream.writeAttribute("name",domainName.isEmpty()?name:domainName);
   if(nullptr!=localOnly)
   stream.writeAttribute("localOnly",localOnly);


    if(bandwidth.exist){
        stream.writeDTD(bandwidth.xml());
    }
    int i=0;

    qDebug()<<"i="<<i;

    if(ip4.getExist()){
        stream.writeStartElement("ip");
        stream.writeAttribute("address", ip4.getAddress());
        if(ip4.getNetmask()!=nullptr)
            stream.writeAttribute("netmask",ip4.getNetmask());
        if(ip4.getHasDhcp()){
            stream.writeDTD(ip4.getDhcp().xml(forward.getMode()));
        }
        stream.writeEndElement();
    }

    if(ip6.getExist()){
        stream.writeStartElement("ip");
        if(ip6.getFamily()!=nullptr)
            stream.writeAttribute("family", ip6.getFamily());
        stream.writeAttribute("address", ip6.getAddress());
        if(ip6.getPrefix()!=nullptr)
            stream.writeAttribute("prefix", ip6.getPrefix());
        if(ip6.getHasDhcp()){
            stream.writeDTD(ip6.getDhcp().xml(forward.getMode()));
        }
        stream.writeEndElement();
    }


    i=0;
    while (route.size()>i){
        Route Rou=route.at(i);
        stream.writeStartElement("route");
        if(Rou.family!=nullptr)
            stream.writeAttribute("family", Rou.family);
        stream.writeAttribute("address", Rou.address);
        if(Rou.prefix!=nullptr)
            stream.writeAttribute("prefix", Rou.prefix);
        if(Rou.netmask!=nullptr)
            stream.writeAttribute("netmask", Rou.netmask);
        if(Rou.gateway!=nullptr)
            stream.writeAttribute("gateway", Rou.gateway);
        stream.writeEndElement();
        i++;
    }


    stream.writeEndElement();
    //    stream.writeEndDocument();

    qDebug()<<"this is war!!!!!"<<QString(xml);
    return xml;
}
