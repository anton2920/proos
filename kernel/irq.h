#ifndef IRQ_H
#define IRQ_H


struct k_isr_registers;
typedef struct k_isr_registers k_irq_registers_t;

typedef void (*k_irq_handler_cb_t)(k_irq_registers_t *);


void k_irq_init(void);

void k_irq_install_handler_cb(int irq, k_irq_handler_cb_t cb);
void k_irq_uninstall_handler_cb(int irq);

#endif // IRQ_H
