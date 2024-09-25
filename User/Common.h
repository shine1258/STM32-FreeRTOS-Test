#ifndef __COMMON_H
#define __COMMON_H

#include <stdint.h>
#include <stdio.h>

#ifdef __cplusplus
extern "C" {
#endif

#define ARRAY_SIZE(arr) (sizeof(arr) / sizeof(arr[0]))

#define MALLOC_FAILED_CHECK(x)                       \
    if (!x) {                                        \
        printf("Failed to create %s\n", #x);         \
        vAssertCalled((uint8_t*)__FILE__, __LINE__); \
    }

#define BIT_0 (1 << 0)
#define BIT_1 (1 << 1)
#define BIT_2 (1 << 2)
#define BIT_3 (1 << 3)
#define BIT_4 (1 << 4)
#define BIT_5 (1 << 5)
#define BIT_6 (1 << 6)
#define BIT_7 (1 << 7)
#define BIT_8 (1 << 8)
#define BIT_9 (1 << 9)
#define BIT_10 (1 << 10)
#define BIT_11 (1 << 11)
#define BIT_12 (1 << 12)
#define BIT_13 (1 << 13)
#define BIT_14 (1 << 14)
#define BIT_15 (1 << 15)
#define BIT_16 (1 << 16)
#define BIT_17 (1 << 17)
#define BIT_18 (1 << 18)
#define BIT_19 (1 << 19)
#define BIT_20 (1 << 20)
#define BIT_21 (1 << 21)
#define BIT_22 (1 << 22)
#define BIT_23 (1 << 23)

void vAssertCalled(uint8_t* file, uint32_t line);
uint32_t getExecutionTickCount(uint32_t startTick);

#ifdef __cplusplus
}
#endif

#endif /* __COMMON_H */