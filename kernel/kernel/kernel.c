#include <stddef.h>
#include <stdint.h>
#include <string.h>
#include <stdio.h>

#include "kernel/tty.h"
#include "kernel/debug.h"

void kernel_main(void)
{
	terminal_initialize();
    for (int i = 0; i < 100; i++) {
        LOG_INFO("Hello, kernel World! - %d\n", i);
    }


    while(1);
}
