#include "MainTask.h"
#include "Serial.hpp"
// #include "cJSON.h"
#include "Common.h"
#include "cmsis_os.h"
#include "lfs.h"
#include "lfs_port.h"
#include "spi.h"
#include "spif.h"
#include "stm32f1xx.h"
#include <new>
#include <stdint.h>
#include <stdio.h>

SPIF_HandleTypeDef spif;

void MainTask_Run(void)
{
    // 初始化w25qxx驱动, 需要在挂载文件系统之前执行
    SPIF_Init(&spif, &hspi1, SPI1_CS_GPIO_Port, SPI1_CS_Pin);

    // 挂载lfs文件系统
    auto err = lfs_mount(&lfs, &cfg);

    // 出错时格式化文件系统并重新挂载
    if (err) {
        lfs_format(&lfs, &cfg);
        lfs_mount(&lfs, &cfg);
    }

    lfs_file_t file;

    uint32_t boot_count = 0;
    lfs_file_open(&lfs, &file, "boot_count", LFS_O_RDWR | LFS_O_CREAT);
    lfs_file_read(&lfs, &file, &boot_count, sizeof(boot_count));

    boot_count++;
    lfs_file_rewind(&lfs, &file);
    lfs_file_write(&lfs, &file, &boot_count, sizeof(boot_count));

    lfs_file_close(&lfs, &file);
    lfs_unmount(&lfs);

    printf("count: %ld\r\n", boot_count);

    // 重定向cJSON库的内存分配和释放函数
    // static cJSON_Hooks hooks;
    // hooks.malloc_fn = pvPortMalloc;
    // hooks.free_fn = vPortFree;
    // cJSON_InitHooks(&hooks);

    // auto jsonString = R"({"a": 1, "b": 2})";
    // auto json = cJSON_Parse(jsonString);

    // if (!json) {
    //     printf("Error parsing JSON\n");
    // } else {
    //     auto a = cJSON_GetObjectItem(json, "a");
    //     auto b = cJSON_GetObjectItem(json, "b");

    //     if (cJSON_IsNumber(a) && cJSON_IsNumber(b)) {
    //         printf("a: %d, b: %d\n", a->valueint, b->valueint);
    //     } else {
    //         printf("Error: a or b is not a number\n");
    //     }

    //     cJSON_Delete(json);
    // }

    while (true) {
        osDelay(1);
    }
}
