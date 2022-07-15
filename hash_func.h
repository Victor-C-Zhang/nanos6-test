//
// Created by victor on 7/14/22.
//

#ifndef TEST1_HASH_FUNC_H
#define TEST1_HASH_FUNC_H

#include <stdint.h>
uint64_t XXPMS64(const uint64_t input, uint64_t seed);

uint32_t XXPMS32(uint64_t x, uint64_t seed);

#endif //TEST1_HASH_FUNC_H
