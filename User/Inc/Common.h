#ifndef __COMMON_H
#define __COMMON_H

#include <stdint.h>
#include <stdio.h>

#define ARRAY_SIZE(arr) (sizeof(arr) / sizeof(arr[0]))

#define MALLOC_FAILED_CHECK(x)                       \
    if (!x) {                                        \
        printf("Failed to create %s\n", #x);         \
        vAssertCalled((uint8_t*)__FILE__, __LINE__); \
    }

void vAssertCalled(uint8_t* file, uint32_t line);

#endif