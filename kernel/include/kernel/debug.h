#ifndef __KERNEL_DEBUG_H__
#define __KERNEL_DEBUG_H__

#include <stdio.h>
#include <stdarg.h>


#include "kernel/tty.h"



#define LOG_LEVEL_FATAL 1
#define LOG_LEVEL_ERROR 2
#define LOG_LEVEL_WARN  3
#define LOG_LEVEL_INFO  4
#define LOG_LEVEL_DEBUG 5


#define PRINT_MSG(fmt, level, ...) do { \
                        printf("%s:%d:%s(): kernel-%s: " fmt, __FILE__, \
                        __LINE__, __func__, level, ##__VA_ARGS__ ); \
                    } while(0)


#if (LOG_LEVEL >= LOG_LEVEL_FATAL) 
    #define LOG_FATAL(fmt, ...) PRINT_MSG(fmt, "FATAL", ##__VA_ARGS__ )
#else
    #define LOG_FATAL(fmt, ...)
#endif

#if (LOG_LEVEL >= LOG_LEVEL_ERROR)
    #define LOG_ERROR(fmt, ...) PRINT_MSG(fmt, "ERROR", ##__VA_ARGS__ )
#else
    #define LOG_ERROR(fmt, ...)
#endif

#if (LOG_LEVEL >= LOG_LEVEL_WARN)
    #define LOG_WARN(fmt, ...) PRINT_MSG(fmt, "WARN", ##__VA_ARGS__ )
#else
    #define LOG_WARN(fmt, ...)
#endif

#if (LOG_LEVEL >= LOG_LEVEL_INFO)
    #define LOG_INFO(fmt, ...) PRINT_MSG(fmt, "INFO", ##__VA_ARGS__ )
#else
    #define LOG_INFO(fmt, ...)
#endif

#if (LOG_LEVEL >= LOG_LEVEL_DEBUG)
    #define LOG_DEBUG(fmt, ...) PRINT_MSG(fmt, "DEBUG", ##__VA_ARGS__ )
#else
    #define LOG_DEBUG(fmt, ...)
#endif


#endif
