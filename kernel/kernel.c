#include "../drivers/keyboard.h"
#include "../drivers/pit.h"
#include "../drivers/screen.h"

#include "gdt.h"
#include "idt.h"
#include "isr.h"
#include "irq.h"


char *k_prompt_str = "root@proos#> ";


static void k_intro(void)
{
    /* Finishing "Booting... " message */
    k_screen_prints("done.\r\n");

    k_screen_prints_ex("Loaded ProOS " VERSION "\r\n\a", VGA_TEXT_FG(VGA_LIGHT_CYAN));
}


void k_prompt(void)
{
    k_screen_prints_ex(k_prompt_str, VGA_TEXT_FG(VGA_LIGHT_GREEN));
}


void k_init(void)
{
    k_gdt_init();
    k_idt_init();
    k_isr_exceptions_init();
    k_irq_init();
    k_pit_timer_init();
    k_keyboard_init();

    __asm__ volatile ("sti");
}


void k_main(void)
{
    k_init();
    k_intro();
    k_prompt();

    /* Keyboard input loop */
    while (1) {
        __asm__ volatile ("sti\n\t"
                          "hlt");
    }
}
