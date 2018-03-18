#ifndef DICT_H
#define DICT_H

#ifdef __cplusplus
extern "C" {
#endif

#include <stddef.h>

unsigned long dict_new();
void dict_delete(unsigned long id);
size_t dict_size(unsigned long id);
void dict_insert(unsigned long id, const char* key, const char* value);
void dict_remove(unsigned long id, const char* key);
const char* dict_find(unsigned long id, const char* key);
void dict_clear(unsigned long id);
void dict_copy(unsigned long src_id, unsigned long dst_id);

#ifdef __cplusplus
}  // extern "C"
#endif

#endif  // DICT_H