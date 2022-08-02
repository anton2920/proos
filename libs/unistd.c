#include "../drivers/pit.h"

#include "unistd.h"


int usleep(unsigned int usec)
{
    if ((usec) && (usec >= 1000000)) {
        return -1;
    }

    k_pit_timer_phase(1000000 / (int) usec);
    k_pit_timer_wait(1);

    return 0;
}


unsigned int sleep(unsigned int seconds)
{
    k_pit_timer_phase(19);
    k_pit_timer_wait((int) seconds * 19);

    return 0;
}
