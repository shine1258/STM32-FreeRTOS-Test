#ifndef __SERIAL_H
#define __SERIAL_H

#include "cmsis_os.h"
#include <stdint.h>

namespace IO {

enum class SerialResult {
    OK = 0,
    TIMEOUT = 1,
    ERROR = 2
};

class Serial {
public:
    static Serial& instance()
    {
        static Serial instance;
        return instance;
    }

    void writeBytes(uint8_t* bytes, uint16_t length);
    SerialResult readBytes(uint8_t* bytes, uint16_t length, uint32_t timeout);
    void clearReadBuffer();

private:
    Serial(); // Private constructor
    ~Serial(); // Private destructor
    Serial(const Serial&) = delete; // Prevent copy-construction
    Serial& operator=(const Serial&) = delete; // Prevent assignment
};

}

#endif /* __SERIAL_H */