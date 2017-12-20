#include "os.h"


QString Os::Type::xml(){
  if(arch.isEmpty()&&machine.isEmpty()){
      return "<type></type>";
    }
  else if (arch.isEmpty()){
      return  "<type machine='"+machine+"'>"+value+"</type>";
    }
  else if(machine.isEmpty()){
      return  "<type arch='"+arch+"'>"+value+"</type>";
    }
  else{
      if(value.isEmpty()){
          return "<type arch='"+arch+"' machine='"+machine+" />";
        }
      return  "<type arch='"+arch+"' machine='"+machine+"'>"+value+"</type>";

    }
}

QString Os::Loader::xml(){
  QString xml="<loader";
  if(!readOnly.isEmpty()){
      xml.append(" readonly='"+readOnly+"' ");
    }
  if(!secure.isEmpty()){
      xml.append(" secure='"+secure+"' ");
    }
  if(!type.isEmpty()){
      xml.append(+" type='"+type+"' ");
    }
  if(value.isEmpty()){
      xml.append(" />");
      return xml;
    }
  xml.append(">"+value+"</loader>");
  return xml;
}

QString Os::NVRam::xml(){
  QString xml="<nvram ";
  if(!Template.isEmpty()){
      xml.append(" template='"+Template+"' ");
    }
  xml.append(">"+value+"</nvram>");
  return xml;
}

QString Os::Bootmenu::xml(){
  QString xml="<bootmenu ";
  if(!enable.isEmpty()){
      xml.append(" enable='"+enable+"' ");
    }
  if(!timeout.isEmpty()){
      xml.append(" timeout='"+timeout+"' ");
    }
  xml.append("/>");
  return xml;
}

QString Os::Bios::xml(){
  QString xml="<bios ";
  if(!useSerial.isEmpty()){
      xml.append(" useserial='"+useSerial+"' ");
    }
  if(!rebootTimeout.isEmpty()){
      xml.append(" rebootimeout='"+rebootTimeout+"' ");
    }
  xml.append("/>");
  return  xml;
}

QString SmbiosSystemInformation::Bios::xml(){
  QString xml;
  QXmlStreamWriter stream(&xml);
  stream.setAutoFormatting(true);
  stream.writeStartElement("bios");
  stream.writeDTD(entryXml(&biosEntry));
  stream.writeEndElement();
  return xml;
}

QString SmbiosSystemInformation::System::xml(){
  QString xml;
  QXmlStreamWriter stream(&xml);
  stream.setAutoFormatting(true);
  stream.writeStartElement("system");
  stream.writeDTD(entryXml(&systemEntry));
  stream.writeEndElement();
  return xml;
}

QString SmbiosSystemInformation::BaseBoard::xml(){
  QString xml;
  QXmlStreamWriter stream(&xml);
  stream.setAutoFormatting(true);
  stream.writeStartElement("system");
  stream.writeDTD(entryXml(&baseboardEntry));
  stream.writeEndElement();
  return xml;
}

