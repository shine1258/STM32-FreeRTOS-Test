#ifndef __SERIAL_H
#define __SERIAL_H

#include <stdint.h>

void Serial_Init(void);
void Serial_WriteBytes(uint8_t* bytes, uint16_t length);
void Serial_ReadBytes(uint8_t* bytes, uint16_t length, uint32_t timeout);

#endif