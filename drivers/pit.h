#ifndef PIT_H
#define PIT_H

void k_pit_timer_phase(int hz);
void k_pit_timer_wait(unsigned long ticks);

void k_pit_timer_init(void);

#endif // PIT_H
