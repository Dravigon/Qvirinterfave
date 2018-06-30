#ifndef CUSTOMLIBVIRT_H
#define CUSTOMLIBVIRT_H

#ifdef W_OS_LINUX
#include <libvirt/libvirt.h>
#include <libvirt/virterror.h>

#else
#include "../libvirt/libvirt.h"
#include "../libvirt/virterror.h"
#endif
#endif // CUSTOMLIBVIRT_H
