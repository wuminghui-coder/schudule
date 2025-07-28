#ifndef __LOG_H__
#define __LOG_H__
#include <stdio.h>
#include "timestamp.h"

enum {
    LOG_LEVEL_ALL,
    LOG_LEVEL_DEBUG,
    LOG_LEVEL_INFO,
    LOG_LEVEL_WAR,
    LOG_LEVEL_ERR,
};

#ifndef LOG_LEVEL
#define LOG_LEVEL  LOG_LEVEL_ERR
#endif

#define RED_COLOR "\033[0;31m"
#define RED_COLOR1 "\033[0;32m"
#define RED_COLOR2 "\033[0;33m"
#define RED_COLOR3 "\033[0;37m"
#define GREEN_COLOR "\033[1;32m"   

#define LOG_LEVEL_PRINTF(color, fmt, ...) \
    do { \
        char date_buffer[100]; \
        get_now_ms_date(date_buffer, sizeof(date_buffer)); \
        fprintf(stderr, "%s[%s] [%s:%d]: " fmt "\n\033[0;39m", \
               color, date_buffer, __FUNCTION__, __LINE__, ##__VA_ARGS__); \
    } while (0)

#define ERR(fmt, ...) if (LOG_LEVEL <=  LOG_LEVEL_ERR) LOG_LEVEL_PRINTF(RED_COLOR, fmt, ##__VA_ARGS__)
#define WAR(fmt, ...) if (LOG_LEVEL <=  LOG_LEVEL_WAR) LOG_LEVEL_PRINTF(RED_COLOR1, fmt, ##__VA_ARGS__)
#define LOG(fmt, ...) if (LOG_LEVEL <=  LOG_LEVEL_INFO) LOG_LEVEL_PRINTF(RED_COLOR2, fmt, ##__VA_ARGS__)
#define DBG(fmt, ...) if (LOG_LEVEL <=  LOG_LEVEL_DEBUG) LOG_LEVEL_PRINTF(GREEN_COLOR, fmt, ##__VA_ARGS__)

static inline void printfChar(uint8_t *data, int len)
{
    for (int i = 0; i < len; i++) {
        fprintf(stderr, "%02x ", data[i]);
        if ((i + 1) % 8 == 0 && i != 0)
            fprintf(stderr, "    ");

        if ((i+1) % 16 == 0 && i != 0)
            fprintf(stderr, " [%d]\n", i + 1);
    }
    fprintf(stderr, "\n");
}
#endif // !__LOG_H__
