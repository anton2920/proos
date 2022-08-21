/* <sys/ioctl.h> - All ioctl() command codes.
 * This header file includes all other ioctl command code headers.
 */

#ifndef _IOCTL_H
#define _IOCTL_H


/* A driver that uses ioctls claims a character for its series of commands.
 * For instance:  #define TCGETS  _IOR('T',  8, struct termios)
 * This is a terminal ioctl that uses the character 'T'. The character(s)
 * used in each header file are shown in the comment following.
 */
/*#include <sys/ioc_tty.h>    *//* 'T' 't' 'k' */
/*#include <net/ioctl.h>      *//* 'n' */
#include <sys/ioc_disk.h>   /* 'd' */
/*#include <sys/ioc_file.h>   *//* 'f' */
/*#include <sys/ioc_memory.h> *//* 'm' */
/*#include <sys/ioc_cmos.h>   *//* 'c' */
/*#include <sys/ioc_tape.h>   *//* 'M' */
/*#include <sys/ioc_scsi.h>   *//* 'S' */
/*#include <sys/ioc_sound.h>  *//* 's' */

#endif /* _IOCTL_H */
