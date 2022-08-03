#include "../drivers/screen.h"

#include "stdlib.h"


void abort(void)
{
    k_screen_prints("Aborted\r\n");
    halt();
}


void *memset(void *dest, int c, unsigned long n)
{
    __asm__ volatile ("cld\n\t"
                      "rep stosb"
        :
        : "D"(dest), "a"(c), "c"(n));

    return dest;
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


int memcmp(const void *s1, const void *s2, unsigned long n)
{
    const unsigned char *str1 = s1, *str2 = s2;

    while (n--) {
        if (*str1 < *str2) {
            return -1;
        } else if (*str1 > *str2) {
            return 1;
        }
        ++str1;
        ++str2;
    }

    return 0;
}
