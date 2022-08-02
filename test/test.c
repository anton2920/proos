void k_test_vga_text_palette(void);
void k_test_scrolling(void);
void k_test_divz(void);

void k_init(void);


void k_test(void)
{
    k_init();

    k_test_vga_text_palette();
    k_test_scrolling();
    k_test_divz();
}
