#include "domainattributes.h"

domainAttributes::domainAttributes()
{

}


QString Memory::xml(){
  QString xml="";
  QXmlStreamWriter stream(&xml);
  stream.setAutoFormatting(true);
  stream.writeStartElement(tag);
  if(Slots.isEmpty()){
      stream.writeAttribute("slots",Slots);
    }
  if(unit.isEmpty()){
      stream.writeAttribute("unit",unit);
    }
  stream.writeCharacters(value);
  stream.writeEndElement();
  return xml;
}
