#ifndef __SERIAL_H
#define __SERIAL_H

#include <array>
#include <stdint.h>

namespace IO::Serial {

enum class Status {
    OK = 0,
    TIMEOUT = 1,
    ERROR = 2
};

Status writeBytes(const uint8_t* bytes, const uint16_t length);
Status readBytes(uint8_t* bytes, const uint16_t length, const uint32_t timeout);

template <uint16_t N>
Status readBytes(std::array<uint8_t, N>& bytes, const uint32_t timeout)
{
    return readBytes(bytes.data(), N, timeout);
}

void clearReadBuffer();

}

#endif /* __SERIAL_H */