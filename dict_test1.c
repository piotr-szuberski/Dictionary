#include <assert.h>
#include <string.h>
#include "dict.h"
#include "dictglobal.h"

static int streq(const char* s1, const char* s2, size_t len) {
    if (s1 == s2)
        return 1;

    if (s1 == NULL || s2 == NULL)
        return 0;

    return strncmp(s1, s2, len) == 0;
}

int main() {
    unsigned long d1, d2, d3;

    assert(dict_size(dict_global()) == 0);

    d1 = dict_new();

    dict_insert(d1, "k0", "a");
    assert(streq(dict_find(d1, "k0"), "a", 2));

    dict_insert(d1, "k1", "aa");
    assert(streq(dict_find(d1, "k1"), "aa", 3));
    assert(dict_size(d1) == 2);

    dict_remove(d1, "k1");
    assert(dict_find(d1, "k1") == NULL);
    assert(streq(dict_find(d1, "k0"), "a", 2));
    assert(dict_size(d1) == 1);

    dict_insert(d1, "k0", NULL);
    assert(streq(dict_find(d1, "k0"), "a", 2));
    assert(dict_size(d1) == 1);

    dict_insert(d1, NULL, NULL);
    assert(dict_size(d1) == 1);

    dict_remove(d1, "k1");
    assert(dict_size(d1) == 1);

    dict_delete(d1);
    dict_insert(d1, "k0", "b");
    assert(dict_size(d1) == 0);
    assert(dict_find(d1, "k0") == NULL);

    d2 = dict_new();
    d3 = dict_new();
    dict_insert(d2, "k0", "c");
    dict_insert(d2, "k1", "cc");
    dict_insert(d2, "k2", "ccc");
    dict_copy(d2, d3);
    assert(dict_size(d3) == 3);

    dict_clear(d3);
    assert(dict_size(d3) == 0);

    dict_insert(dict_global(), "g0", "d");
    assert(dict_size(dict_global()) == 1);
    assert(streq(dict_find(d1, "g0"), "d", 2));

    dict_delete(dict_global());
    assert(dict_size(dict_global()) == 1);

    dict_clear(dict_global());

    return 0;
}
