#include <stddef.h>
#include <stdint.h>
#include <string.h>
#include <stdio.h>

#include "kernel/tty.h"
#include "kernel/debug.h"

void kernel_main(void)
{
	terminal_initialize();
	LOG_INFO("Hello, kernel World!\n");
    char buff[20] = {'\0'};
    char *name = "chris";
    int date = 1026;
    char letter = 'd';
    sprintf(buff, "%s/%d/%c", name, date, letter);
    printf("%s", buff);
    while(1);
}
