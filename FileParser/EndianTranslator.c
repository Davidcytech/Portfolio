#include "EndianTranslator.h"

uint16_t read_uint16_le(const unsigned char bytes[2])
{
    return (uint16_t)bytes[0] |
           ((uint16_t)bytes[1] << 8);
}

uint32_t read_uint32_le(const unsigned char bytes[4])
{
    return (uint32_t)bytes[0] |
           ((uint32_t)bytes[1] << 8) |
           ((uint32_t)bytes[2] << 16) |
           ((uint32_t)bytes[3] << 24);
}

uint64_t read_uint64_le(const unsigned char bytes[8])
{
    return (uint64_t)bytes[0] |
           ((uint64_t)bytes[1] << 8) |
           ((uint64_t)bytes[2] << 16) |
           ((uint64_t)bytes[3] << 24) |
           ((uint64_t)bytes[4] << 32) |
           ((uint64_t)bytes[5] << 40) |
           ((uint64_t)bytes[6] << 48) |
           ((uint64_t)bytes[7] << 56);
}

uint16_t read_uint16_be(const unsigned char bytes[2])
{
    return ((uint16_t)bytes[0] << 8) |
           (uint16_t)bytes[1];
}

uint32_t read_uint32_be(const unsigned char bytes[4])
{
    return ((uint32_t)bytes[0] << 24) |
           ((uint32_t)bytes[1] << 16) |
           ((uint32_t)bytes[2] << 8) |
           (uint32_t)bytes[3];
}

uint64_t read_uint64_be(const unsigned char bytes[8])
{
    return ((uint64_t)bytes[0] << 56) |
           ((uint64_t)bytes[1] << 48) |
           ((uint64_t)bytes[2] << 40) |
           ((uint64_t)bytes[3] << 32) |
           ((uint64_t)bytes[4] << 24) |
           ((uint64_t)bytes[5] << 16) |
           ((uint64_t)bytes[6] << 8) |
           (uint64_t)bytes[7];
}