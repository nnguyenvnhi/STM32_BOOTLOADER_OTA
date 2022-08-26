#include "CRC32.h"

uint32_t crc32( const uint8_t *buf, uint32_t len) {
    const uint8_t *p;
    int nr;
    uint32_t crc;

    crc = 0;
    for (nr = len, p = buf; nr--; ++p) {
        COMPUTE(crc, *p);
    }

    for (; len != 0; len >>= 8) {
        COMPUTE(crc, len & 0xff);
    }
    buf-=len;
    return(~crc);
}