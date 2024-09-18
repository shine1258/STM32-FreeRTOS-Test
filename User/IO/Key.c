#include "Key.h"
#include "Common.h"
#include "cmsis_os.h"
#include "main.h"

static const struct {
    GPIO_TypeDef* GPIOx;
    uint16_t GPIO_Pin;
    uint8_t keyNum;
} keyMap[] = {
    { KEY_GPIO_Port, KEY_Pin, 1 },
    { KEY2_GPIO_Port, KEY2_Pin, 2 }
};

/// @brief 扫描按键
/// @return 按键编号, -1表示没有按键按下
int8_t KeyScan(void)
{
    int8_t keyNum = -1;

    for (uint8_t i = 0; i < ARRAY_SIZE(keyMap); i++) {
        if (HAL_GPIO_ReadPin(keyMap[i].GPIOx, keyMap[i].GPIO_Pin) == GPIO_PIN_RESET) {
            osDelay(20); // Debounce delay

            while (HAL_GPIO_ReadPin(keyMap[i].GPIOx, keyMap[i].GPIO_Pin) == GPIO_PIN_RESET) {
                osDelay(1); // Wait for key release
            }

            osDelay(20); // Debounce delay

            keyNum = keyMap[i].keyNum;
            break;
        }
    }

    return keyNum;
}
