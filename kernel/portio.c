unsigned char inb(unsigned short port)
{
    unsigned char result;
    __asm__ volatile ("in %%dx, %%al"
        : "=a" (result)
        : "d" (port));
    return result;
}


void outb(unsigned short port, unsigned char data)
{
    __asm__ volatile ("out %%al , %%dx "
        :
        : "a" (data), "d" (port));
}


unsigned short inw(unsigned short port)
{
    unsigned short result;
    __asm__ volatile ("inw %%dx, %%ax"
        : "=a" (result)
        : "d" (port));
    return result;
}


void outw(unsigned short port, unsigned short data)
{
    __asm__ volatile ("outw %%ax, %%dx"
        :
        : "a" (data), "d" (port));
}
