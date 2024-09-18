#ifndef __SERIAL_H
#define __SERIAL_H

#include "cmsis_os.h"
#include <stdint.h>

namespace IO {

class Serial {
public:
    static Serial& instance()
    {
        static Serial instance;
        return instance;
    }

    enum class Status {
        OK = 0,
        TIMEOUT = 1,
        ERROR = 2
    };

    Status writeBytes(const uint8_t* bytes, const uint16_t length);
    Status readBytes(uint8_t* bytes, const uint16_t length, const uint32_t timeout);
    void clearReadBuffer();

private:
    Serial(); // Private constructor
    ~Serial(); // Private destructor
    Serial(const Serial&) = delete; // Prevent copy-construction
    Serial& operator=(const Serial&) = delete; // Prevent assignment
};

}

#endif /* __SERIAL_H */