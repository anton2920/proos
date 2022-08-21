#ifndef _SYSUTIL_H
#define _SYSUTIL_H

/*==========================================================================*
 *                     Miscellaneous helper functions.                      *
 *==========================================================================*/

/* Environment parsing return values. */
#define EP_BUF_SIZE     128     /* local buffer for env value */
#define EP_UNSET        0       /* variable not set */
#define EP_OFF          1       /* var = off */
#define EP_ON           2       /* var = on (or field left blank) */
#define EP_SET          3       /* var = 1:2:3 (nonblank field) */
#define EP_EGETKENV     4       /* sys_getkenv() failed ... */


_PROTOTYPE( void env_setargs, (int argc, char *argv[]) );
_PROTOTYPE( int env_get_param, (char *key, char *value, int max_size) );
_PROTOTYPE( int env_prefix, (char *env, char *prefix) );
_PROTOTYPE( void env_panic, (char *key) );
_PROTOTYPE( int env_parse, (char *env, char *fmt, int field, long *param, long min, long max) );


#define fkey_map(fkeys, sfkeys)     fkey_ctl(FKEY_MAP, (fkeys), (sfkeys))
#define fkey_unmap(fkeys, sfkeys)   fkey_ctl(FKEY_UNMAP, (fkeys), (sfkeys))
#define fkey_events(fkeys, sfkeys)  fkey_ctl(FKEY_EVENTS, (fkeys), (sfkeys))
_PROTOTYPE( int fkey_ctl, (int req, int *fkeys, int *sfkeys) );


_PROTOTYPE( int printf, (const char *fmt, ...) );
_PROTOTYPE( void kputc, (int c) );
_PROTOTYPE( void report, (char *who, char *mess, int num) );
_PROTOTYPE( void panic, (char *who, char *mess, int num) );
_PROTOTYPE( int getuptime, (clock_t *ticks) );
_PROTOTYPE( int tickdelay, (clock_t ticks) );

#endif /* _SYSUTIL_H */
