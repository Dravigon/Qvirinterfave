#include "cpu.h"

QString Cpu::featureXml(){
  QString xml;
  QXmlStreamWriter stream(&xml);
  for(int i=0;i<feature->size();i++){
      stream.writeEmptyElement("feature");
      stream.writeAttribute("policy",feature->data(feature->index(i,0),FeatureModel::PolicyRole).toString());
      stream.writeAttribute("name",feature->data(feature->index(i,0),FeatureModel::NameRole).toString());
    }
  return xml;
}

QString Cpu::xml(){
  QString xml;
  QXmlStreamWriter stream(&xml);
  stream.setAutoFormatting(true);
  stream.writeStartElement("cpu");
  if(!match.isEmpty())
    stream.writeAttribute("match",match);
  if(!check.isEmpty())
    stream.writeAttribute("check",check);
  if(!mode.isEmpty())
    stream.writeAttribute("mode",mode);
  if(!vendor.isEmpty())
    stream.writeAttribute("vendor",vendor);
  if(!topology.isEmpty())
    stream.writeDTD(topology.xml());
  stream.writeDTD(featureXml());
  if(!topology.isEmpty())
    stream.writeDTD(topology.xml());
  stream.writeEndElement();
  return xml;
}

Cpu::Cpu()
{

}

bool Model::isEmpty(){
  return value.isEmpty();
}

QString Model::xml(){
  QString xml="<model";
  if(!fallback.isEmpty()){
      xml.append(" fallback="+fallback);
    }
  if(!vendor_id.isEmpty()){
      xml.append(" vendor_id="+vendor_id);
    }
  xml.append(">"+value+"</model>");
  return xml;
}

QString Topology::xml(){
  QString xml="<topology";
  if(!sockets.isEmpty()){
      xml.append(" sockets="+sockets);
    }
  if(!cores.isEmpty()){
      xml.append(" cores="+cores);
    }
  if(!threads.isEmpty()){
      xml.append(" threads="+threads);
    }
  xml.append(">");
  return xml;
}

bool Topology::isEmpty(){
  return sockets.isEmpty()&&cores.isEmpty()&&threads.isEmpty();
}

bool Cache::isEmpty(){
  return mode.isEmpty();
}

QString Cache::xml(){
  QString xml="<cache";
  if(!level.isEmpty()){
      xml.append(" level='"+level+"' ");
    }
  xml.append(" mode='"+mode+"'/>");
  return xml;
}
