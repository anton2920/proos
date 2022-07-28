enum vga_colors {
	VGA_WHITE = 0xF
};

void print_vga(const char *text, char start_row, char start_col, char color)
{
	short *vga_text_buffer = (short *) ((char *) 0xB8000 + 2 * (start_row * 80 + start_col));

	while (*text != '\0') {
		*vga_text_buffer = (color << 8) | (*text);
		++vga_text_buffer;

		++text;
	}
}

#define BASE_LINE 8

void kernel_main()
{
	print_vga("done. Now in Intel's protected mode.", BASE_LINE, 11, VGA_WHITE);
	print_vga("Loaded ProOS alpha 0.1", BASE_LINE + 1, 0, VGA_WHITE);
}
