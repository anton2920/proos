#include "stdlib.h"


/* TODO: redefine with intrinsics */
void *memcpy(void *_dest, const void *_src, unsigned long size)
{
    const char *src = _src;
    char *dest = _dest;
    void *ret = _dest;

    while (size--) {
        *dest++ = *src++;
    }

    return ret;
}
