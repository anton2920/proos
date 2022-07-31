#include "../drivers/screen.h"

#include "stdlib.h"


_Noreturn void abort(void)
{
    k_screen_prints("Aborted\r\n");
    while (1);
}


void *memcpy(void *dest, const void *src, unsigned long n)
{
    void *ret = dest;

    __asm__ volatile ("cld\n\t"
                      "rep movsl"
        : "=D"(dest), "=S"(src)
        : "0"(dest), "1"(src), "c"(n >> 2));
    __asm__ volatile ("rep movsb"
        :
        : "D"(dest), "S"(src), "c"(n & 3));

    return ret;
}
