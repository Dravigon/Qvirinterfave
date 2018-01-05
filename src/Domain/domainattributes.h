#ifndef DOMAINATTRIBUTES_H
#define DOMAINATTRIBUTES_H
#include <QString>
#include <QXmlStreamWriter>
#include "CustomLibrary/vstringlist.h"
#include "CustomLibrary/vstandarditemmodel.h"
#include "./Elements/os.h"

/*<domain type='qemu'>
  <name>QEmu-fedora-i686</name>
  <uuid>c7a5fdbd-cdaf-9455-926a-d65c16db1809</uuid>
  <memory>219200</memory>
  <currentMemory>219200</currentMemory>
  <vcpu>2</vcpu>
  <os>
    <type arch='i686' machine='pc'>hvm</type>
    <boot dev='cdrom'/>
  </os>
  <devices>
    <emulator>/usr/bin/qemu-system-x86_64</emulator>
    <disk type='file' device='cdrom'>
      <source file='/home/user/boot.iso'/>
      <target dev='hdc'/>
      <readonly/>
    </disk>
    <disk type='file' device='disk'>
      <source file='/home/user/fedora.img'/>
      <target dev='hda'/>
    </disk>
    <interface type='network'>
      <source network='default'/>
    </interface>
    <graphics type='vnc' port='-1'/>
  </devices>
</domain>
*/
class VCpus{
  QString placement;
  QString cpuset;
  QString current;
  QString value;
};
struct Memory{
  QString tag;
  QString Slots;
  QString unit;
  QString value;
  QString xml();
};

struct Clock{
  QString offset;
  QString adjustment;
  QString timezone;
  vstringList timerXml;
};

class domainAttributes
{
  QString name;
  QString uuid;
  QString title;
  QString description;
  Os os;
  VCpus vcpu;
  QString vcpus;//get value from QML
  QString iothreads;
  //TODO impliment cputune feature when possible
  Memory memory={.tag="memory"};
  Memory maxMemory={.tag="maxMemory"};
  Memory currentMemory={.tag="currentMemory"};
  //TODO implimentation of memory backing
  //TODO implimentation of Memory Tuning.
  //TODO implimentation of NUMA Node tuning
  //TODO Block I/O tuning
  //TODO REsource Partition
  QString on_poweroff="destroy";
  QString on_reboot="restart";
  QString on_crash="restart";
  QString on_lockfailure="poweroff";
  //TODO power management
  //TODO hypervisor features



public:
  domainAttributes();
};

#endif // DOMAINATTRIBUTES_H
