/* <proos/u64.h>. Functions to manipulate 64 bit disk addresses. */

#ifndef _U64_H
#define _U64_H

#include <sys/types.h>

_PROTOTYPE( u64_t add64, (u64_t i, u64_t j) );
_PROTOTYPE( u64_t add64u, (u64_t i, unsigned j) );
_PROTOTYPE( u64_t add64ul, (u64_t i, unsigned long j) );
_PROTOTYPE( u64_t sub64, (u64_t i, u64_t j) );
_PROTOTYPE( u64_t sub64u ,(u64_t i, unsigned j) );
_PROTOTYPE( u64_t sub64ul ,(u64_t i, unsigned long j) );
_PROTOTYPE( unsigned diff64, (u64_t i, u64_t j) );
_PROTOTYPE( u64_t cvu64, (unsigned i) );
_PROTOTYPE( u64_t cvul64, (unsigned long i) );
_PROTOTYPE( unsigned cv64u, (u64_t i) );
_PROTOTYPE( unsigned long cv64ul, (u64_t i) );
_PROTOTYPE( unsigned long div64u, (u64_t i, unsigned j) );
_PROTOTYPE( unsigned rem64u, (u64_t i, unsigned j) );
_PROTOTYPE( u64_t mul64u, (unsigned long i, unsigned j) );
_PROTOTYPE( int cmp64, (u64_t i, u64_t j) );
_PROTOTYPE( int cmp64u, (u64_t i, unsigned j) );
_PROTOTYPE( int cmp64ul, (u64_t i, unsigned long j) );
_PROTOTYPE( unsigned long ex64lo, (u64_t i) );
_PROTOTYPE( unsigned long ex64hi, (u64_t i) );
_PROTOTYPE( u64_t make64, (unsigned long lo, unsigned long hi) );

#endif /* _U64_H */
