#include <stddef.h>
#include <stdint.h>
#include <string.h>
#include <stdio.h>

#include "kernel/tty.h"
#include "kernel/debug.h"


char *jiggy_txt[16];


void init_jiggy_art(void) {

    jiggy_txt[0] = "                   ,---.\n";
    jiggy_txt[1] = "               `/oooooo:    '-\n";
    jiggy_txt[2] = "               :oooooooo..:/ooo/\n";
    jiggy_txt[3] = "               -oooooooooooooooo/\n";
    jiggy_txt[4] = "                -oooooooooooooooo:\n";
    jiggy_txt[5] = "           '-:+oooooooooooooo+-`\n";            
    jiggy_txt[6] = "           /oooooooooooooooo+\n";
    jiggy_txt[7] = "            /ooooooooooooooo:\n";
    jiggy_txt[8] = "             +ooooooooooooooo.     `/`\n";
    jiggy_txt[9] = "         .://ooooooooooooooooo+:---/oo+`\n";
   jiggy_txt[10] = "       `+oooooooooooooooo+-`   .:oooooo+`\n";
   jiggy_txt[11] = "       -oooooooooooooooo+`       -ooooo+-\n";
   jiggy_txt[12] = "        /oooooo:oooooooo/         +/:.\n";
   jiggy_txt[13] = "         `-::-`  -ooooooo.\n";
   jiggy_txt[14] = "                  -oooooo+:\n";
   jiggy_txt[15] = "                   :/:-`\n";

}

void kernel_title_banner(void) {

    printf("------------------------------------------\n");
    init_jiggy_art();
    for (size_t i = 0; i < 16; i++) {
        printf("%s", jiggy_txt[i]);
    }
    printf("\n\tJiggyOS - a custom microkernel\n");
    printf("\tARCH - x86 \n");
    printf("\tVERSION - 1.0\n");
    printf("\tPlatform - Qemu\n");
    printf("-----------------------------------------\n");
}



void kernel_main(void)
{
	terminal_initialize();
    kernel_title_banner();

    LOG_INFO("Kernel entry! - \n");


    while(1);
}
