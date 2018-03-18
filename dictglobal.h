#ifndef DICTGLOBAL_H
#define DICTGLOBAL_H

#ifdef __cplusplus
extern "C" {
#endif

#include <stddef.h>

static const size_t MAX_GLOBAL_DICT_SIZE = 42;
unsigned long dict_global();

#ifdef __cplusplus
}  // extern "C"
#endif

#endif  // DICT_H