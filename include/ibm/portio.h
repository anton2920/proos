#ifndef _PORTIO_H
#define _PORTIO_H

#include <sys/types.h>


_PROTOTYPE( unsigned inb, (U16_t _port) );
_PROTOTYPE( unsigned inw, (U16_t _port) );
_PROTOTYPE( unsigned inl, (U32_t _port) );
_PROTOTYPE( void outb, (U16_t _port, U8_t _value) );
_PROTOTYPE( void outw, (U16_t _port, U16_t _value) );
_PROTOTYPE( void outl, (U16_t _port, U32_t _value) );
_PROTOTYPE( void insb, (U16_t _port, void *_buf, size_t _count) );
_PROTOTYPE( void insw, (U16_t _port, void *_buf, size_t _count) );
_PROTOTYPE( void insl, (U16_t _port, void *_buf, size_t _count) );
_PROTOTYPE( void outsb, (U16_t _port, void *_buf, size_t _count) );
_PROTOTYPE( void outsw, (U16_t _port, void *_buf, size_t _count) );
_PROTOTYPE( void outsl, (U16_t _port, void *_buf, size_t _count) );
_PROTOTYPE( void intr_disable, (void) );
_PROTOTYPE( void intr_enable, (void) );

#endif /* _PORTIO_H */
