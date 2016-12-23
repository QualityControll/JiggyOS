#include <string.h>
#include <stdarg.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include <stdbool.h>
#include <limits.h>


//for speed!
int num_digits (int val) {
    //only supports 32 bit numbers
    if (val < 0) val = (val == INT_MIN) ? INT_MAX: -val;
    if (val < 10) return 1;
    if (val < 100) return 2;
    if (val < 1000) return 3;
    if (val < 10000) return 4;
    if (val < 100000) return 5;
    if (val < 1000000) return 6;
    if (val < 10000000) return 7;
    if (val < 100000000) return 8;
    if (val < 1000000000) return 9;

    return 10;
}




//convert decimal to string
void dec_to_str (char * str, size_t len, unsigned int val) {

    unsigned int c;

    for (c = 1; c <= len; c++) {
        str[len-c] = (char) ((val % 10) + '0');
        val /= 10;
    }

    str[c-1] = '\0';
}




int sprintf (char *s, const char * restrict format, ...)
{
    va_list parameters;
    va_start(parameters, format);

    int written = 0;
    size_t amount;
    bool rejected_bad_specifier = false;

    while ( *format != '\0' )
    {
        if ( *format != '%' )
        {
        write_buff:
            amount = 1;
            while (format[amount] && format[amount] != '%' ) 
                amount++;

            for (size_t i = 0; i < amount; i++) {
                s[written] = format[i];
                written++;
            }

            format += amount;
            continue;
        }

        const char * format_begun_at = format;

        if ( *(++format) == '%') 
            goto write_buff;

        if ( rejected_bad_specifier )
        {
        incomprehensible_conversion:
            rejected_bad_specifier = true;
            format = format_begun_at;
            goto write_buff;
        }
        
        if (*format == 'c') 
        {
            format++;
            char c = (char) va_arg(parameters, int);
            s[written] = c;
            written++;
        }

        else if (*format == 'd')
        {
            format++;
            const int d = va_arg(parameters, int);
            char buff[11] = {'\0'};
            int num_places = num_digits(d); 
            dec_to_str(buff, num_places, d);

            for (int i = 0; i < 11; i++){
                if (buff[i] != '\0') {
                    s[written] = buff[i];
                    written++;
                }
            }

        }
        else if ( *format == 's' ) 
        {
            format++;
            const char * strBuff = va_arg(parameters, const char *);
            
            for (size_t i = 0; i < strlen(strBuff); i++) {
                s[written] = strBuff[i];
                written++;
            }
        }
        else
        {
            goto incomprehensible_conversion;
        }
        
    }

    s[written] = '\0';
    written++;

    va_end(parameters);

    return written;
}



