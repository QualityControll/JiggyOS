#include <stddef.h>
#include <stdint.h>
#include <string.h>
#include <stdio.h>

#include <kernel/tty.h>


void kernel_main(void)
{
	terminal_initialize();
	printf("Hello, kernel World!\n");

    while(1);
}
