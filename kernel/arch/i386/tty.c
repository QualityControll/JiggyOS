#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>
#include <string.h>

#include <kernel/vga.h>
#include <kernel/phys_virt.h>

size_t terminal_row;
size_t terminal_column;
size_t terminal_pane = 0;
uint8_t terminal_color;
uint16_t* terminal_buffer;
bool initFlag = false;

char vga_buffer[NUM_SCREENS][VGA_WIDTH * VGA_HEIGHT];

void terminal_initialize(void)
{
	terminal_row = 0;
	terminal_column = 0;
	terminal_color = make_color(COLOR_LIGHT_GREY, COLOR_BLACK);
	terminal_buffer = (uint16_t *)(VIRT(VGA_MEMORY));
	for ( size_t y = 0; y < VGA_HEIGHT; y++ )
	{
		for ( size_t x = 0; x < VGA_WIDTH; x++ )
		{
			const size_t index = y * VGA_WIDTH + x;
			terminal_buffer[index] = make_vgaentry(' ', terminal_color);
		}
	}
}

void terminal_setcolor(uint8_t color)
{
	terminal_color = color;
}

void terminal_putentryat(char c, uint8_t color, size_t x, size_t y)
{
	const size_t index = y * VGA_WIDTH + x;
	terminal_buffer[index] = make_vgaentry(c, color);
}

void terminal_scrolldown() 
{
    
    terminal_row = 0;
    terminal_column = 0;
    if ( (terminal_pane+1) == NUM_SCREENS) {
        for (size_t i = 0; i < NUM_SCREENS-1; i++) {

            for (size_t k = 0; k < VGA_HEIGHT; k++) {
                for (size_t j = 0; j < VGA_WIDTH; j++) {
                    vga_buffer[i][k * VGA_WIDTH + j] = vga_buffer[i+1][k * VGA_WIDTH + j];
                }
            }
        }
        for (size_t k = 0; k < VGA_HEIGHT; k++) {
            for (size_t j = 0; j < VGA_WIDTH; j++) {
                vga_buffer[NUM_SCREENS-1][k * VGA_WIDTH + j] = '\0'; 
            }
        }
 
    }
    else {
        terminal_pane++;
    }
}



void terminal_putchar(char c)
{
    if (c == '\0') {
        return;
    }

    
    if (initFlag) {
        terminal_initialize();
        initFlag = false;
    }

    if (c == '\n') {
        if (  ++terminal_row == VGA_HEIGHT ) 
        {
            initFlag = true;
            terminal_scrolldown();
        }
        else {
            terminal_column = 0;
        }
        return;
    }

    if (c == '\t') {
        if ( terminal_column+3 >= VGA_WIDTH ) 
        {
            return;
        }
        else 
        {
            terminal_column += 3;
        }
        return;
    }
    
    vga_buffer[terminal_pane][terminal_row * VGA_WIDTH + terminal_column] = c;
	terminal_putentryat(c, terminal_color, terminal_column, terminal_row);
	if ( ++terminal_column == VGA_WIDTH )
	{
		terminal_column = 0;
		if ( ++terminal_row == VGA_HEIGHT )
		{
			terminal_row = 0;
		}
	}
}

void terminal_write(const char* data, size_t size)
{
	for ( size_t i = 0; i < size; i++ )
		terminal_putchar(data[i]);
}

void terminal_writestring(const char* data)
{
	terminal_write(data, strlen(data));
}
