#ifndef __COMMON_H
#define __COMMON_H

#ifdef __cplusplus
extern "C" {
#endif

#include <stdint.h>
#include <stdio.h>

#define ARRAY_SIZE(arr) (sizeof(arr) / sizeof(arr[0]))

#define MALLOC_FAILED_CHECK(x)                       \
    if (!x) {                                        \
        printf("Failed to create %s\n", #x);         \
        vAssertCalled((uint8_t*)__FILE__, __LINE__); \
    }

#define EVENT_BIT_0 (1 << 0)
#define EVENT_BIT_1 (1 << 1)
#define EVENT_BIT_2 (1 << 2)
#define EVENT_BIT_3 (1 << 3)
#define EVENT_BIT_4 (1 << 4)
#define EVENT_BIT_5 (1 << 5)
#define EVENT_BIT_6 (1 << 6)
#define EVENT_BIT_7 (1 << 7)
#define EVENT_BIT_8 (1 << 8)
#define EVENT_BIT_9 (1 << 9)
#define EVENT_BIT_10 (1 << 10)
#define EVENT_BIT_11 (1 << 11)
#define EVENT_BIT_12 (1 << 12)
#define EVENT_BIT_13 (1 << 13)
#define EVENT_BIT_14 (1 << 14)
#define EVENT_BIT_15 (1 << 15)
#define EVENT_BIT_16 (1 << 16)
#define EVENT_BIT_17 (1 << 17)
#define EVENT_BIT_18 (1 << 18)
#define EVENT_BIT_19 (1 << 19)
#define EVENT_BIT_20 (1 << 20)
#define EVENT_BIT_21 (1 << 21)
#define EVENT_BIT_22 (1 << 22)
#define EVENT_BIT_23 (1 << 23)

void vAssertCalled(uint8_t* file, uint32_t line);
uint32_t GetElapsedTickCount(uint32_t startTick);

#ifdef __cplusplus
}
#endif

#endif /* __COMMON_H */