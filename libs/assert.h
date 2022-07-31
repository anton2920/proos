#ifndef ASSERT_H
#define ASSERT_H

#include "../drivers/screen.h"


extern void __assert_fail(const char *assertion, const char *file, unsigned int line);


#define assert(expr)                                    \
    do                                                  \
        if (!(expr)) {                                  \
            __assert_fail(#expr, __FILE__, __LINE__);   \
        }                                               \
    while (0)

#endif // ASSERT_H
