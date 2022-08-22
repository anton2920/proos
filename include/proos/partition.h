/* <proos/partition.h> - Place of a partition on disk and the disk geometry,
 * for use with the DIOCGETP and DIOCSETP ioctl's.
 */

#ifndef _PARTITION_H
#define _PARTITION_H

#include <sys/types.h>


struct partition {
    u64_t       base;       /* byte offset to the partition start */
    u64_t       size;       /* number of bytes in the partition */
    unsigned    cylinders;  /* disk geometry */
    unsigned    heads;
    unsigned    sectors;
};

#endif /* _PARTITION_H */
