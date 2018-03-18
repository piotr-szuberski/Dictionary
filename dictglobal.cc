#include "dictglobal.h"

#include "dict.h"

unsigned long dict_global() {
    static unsigned long global_dict_id = dict_new();
    return global_dict_id;
}