/* sys/ioc_disk.h - Disk ioctl() command codes. */

#ifndef _IOC_DISK_H
#define _IOC_DISK_H

#include <proos/ioctl.h>

#define DIOCSETP    _IOW('d', 3, struct partition)
#define DIOCGETP    _IOR('d', 4, struct partition)
#define DIOCEJECT   _IO ('d', 5)
#define DIOCTIMEOUT _IOW('d', 6, int)
#define DIOCOPENCT  _IOR('d', 7, int)

#endif /* _IOC_DISK_H */
