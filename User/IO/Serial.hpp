#ifndef __SERIAL_H
#define __SERIAL_H

#include <stdint.h>

namespace IO::Serial {

enum class Status {
    OK = 0,
    TIMEOUT = 1,
    ERROR = 2
};

Status writeBytes(const uint8_t* bytes, const uint16_t length);
Status readBytes(uint8_t* bytes, const uint16_t length, const uint32_t timeout);
void clearReadBuffer();

}

#endif /* __SERIAL_H */