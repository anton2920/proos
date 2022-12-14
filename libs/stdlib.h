#ifndef STDLIB_H
#define STDLIB_H

extern void halt(void);
void abort(void);

void *memset(void *dest, int c, unsigned long n);
void *memcpy(void *_dest, const void *_src, unsigned long size);
int memcmp(const void *s1, const void *s2, unsigned long n);

#endif // STDLIB_H
