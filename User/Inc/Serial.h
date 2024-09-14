#ifndef __SERIAL_H
#define __SERIAL_H

#ifdef __cplusplus
extern "C" {
#endif

#include <stdint.h>

typedef enum {
    SERIAL_OK = 0,
    SERIAL_TIMEOUT = 1,
    SERIAL_ERROR = 2
} SerialStatus_t;

void Serial_Init(void);
void Serial_WriteBytes(uint8_t* bytes, uint16_t length);
SerialStatus_t Serial_ReadBytes(uint8_t* bytes, uint16_t length, uint32_t timeout);
void Serial_ClearReadBuffer(void);

#ifdef __cplusplus
}
#endif

#endif /* __SERIAL_H */