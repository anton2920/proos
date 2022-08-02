void k_test_divz(void)
{
    __asm__ volatile ("div %0" :: "r"(0));
}
