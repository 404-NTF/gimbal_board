#ifndef CODE_H
#define CODE_H
#include "struct_typedef.h"

typedef struct {
    uint8_t *value;
    uint8_t length;
    uint8_t curser;
} data_t;

typedef union {
  uint8_t byte[4];
  fp32 val;
} CharAryfp32;

typedef union {
  uint8_t byte[8];
  fp32 val;
} CharAryfp64;

#endif