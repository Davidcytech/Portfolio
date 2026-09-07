#ifndef ENDIAN_TRANSLATOR_H
#define ENDIAN_TRANSLATOR_H

#include <stdint.h>

uint16_t read_uint16_le(const unsigned char bytes[2]);
uint32_t read_uint32_le(const unsigned char bytes[4]);
uint64_t read_uint64_le(const unsigned char bytes[8]);

uint16_t read_uint16_be(const unsigned char bytes[2]);
uint32_t read_uint32_be(const unsigned char bytes[4]);
uint64_t read_uint64_be(const unsigned char bytes[8]);

#endif