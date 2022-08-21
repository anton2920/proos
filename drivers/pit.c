#include "../kernel/irq.h"
#include "../libs/stdio.h"

#include "pit.h"


/* This will keep track of how many ticks that the system has been running for */
static volatile unsigned long timer_ticks = 0;


void k_pit_timer_phase(int hz)
{
    int divisor;

    divisor = 1193180 / hz;       /* Calculate our divisor */

    outb(0x43, 0x34);             /* Set our command byte 0x36 */
    outb(0x40, divisor & 0xFF);   /* Set low byte of divisor */
    outb(0x40, divisor >> 8);     /* Set high byte of divisor */
}


void k_pit_timer_wait(unsigned long ticks)
{
    unsigned int eticks;

    eticks = timer_ticks + ticks;
    while (timer_ticks < eticks) {
        __asm__ volatile ("sti\n\t"
                          "hlt\n\t"
                          "cli");
    }
}


/* Handles the timer. In this case, it's very simple: We
 * increment the 'timer_ticks' variable every time the
 * timer fires. By default, the timer fires 18.222 times
 * per second. Why 18.222Hz? Some engineer at IBM must've
 * been smoking something funky
 */
static void k_pit_timer_handler(k_irq_registers_t *regs __attribute__ ((unused)))
{
    /* Increment our 'tick count' */
    ++timer_ticks;
}


/* Sets up the system clock by installing the timer handler into IRQ0 */
void k_pit_timer_init(void)
{
    k_irq_install_handler_cb(0, k_pit_timer_handler);
}
