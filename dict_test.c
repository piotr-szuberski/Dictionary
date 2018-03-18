#include "dictglobal.h"
#include "dict.h"
#include <assert.h>
#include <stdio.h>
#include <string.h>

inline static int streq(const char* s1, const char* s2, size_t len) {
    if (s1 == s2)
        return 1;

    if (s1 == NULL || s2 == NULL)
        return 0;

    return strncmp(s1, s2, len) == 0;
}

inline static void init(unsigned long id, size_t max) {
    for (size_t i = 0; i < max; i++) {
        char key[256];
        sprintf(key, "k%ld", i);
        dict_insert(id, key, "vvvvv");
        assert(streq(dict_find(id, key), "vvvvv", 6));
        assert(dict_size(id) == i + 1);
    };
}

int main(int argc, char *args[]) {
    // Obejście ostrzeżeń kompilatora o nieużywanych zmiennych.
    (void)argc;
    (void)args;

  #if TEST_NUM == 101
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
  #endif

  // Testy dict_insert oraz dict_size.
  #if TEST_NUM == 201
    unsigned long d1 = dict_new();

    dict_insert(d1, "k0", "xxxxxxx");
    assert(streq(dict_find(d1, "k0"), "xxxxxxx", 8));
  #endif

  #if TEST_NUM == 202
    unsigned long d1 = dict_new();

    dict_insert(d1, "k0", NULL);
    assert(dict_find(d1, "k0") == NULL);
    assert(dict_size(d1) == 0);
  #endif

  #if TEST_NUM == 203
    unsigned long d1 = dict_new();

    dict_insert(d1, NULL, "vvvvv");
    assert(dict_find(d1, NULL) == NULL);
    assert(dict_size(d1) == 0);
  #endif

  #if TEST_NUM == 204
    unsigned long d1 = dict_new();

    dict_insert(d1, "k0", "vvvvv");
    assert(dict_size(d1) == 1);
    dict_delete(d1);
    dict_insert(d1, "k0", "vvvvv");
    assert(dict_find(d1, "k0") == NULL);
    assert(dict_size(d1) == 0);
  #endif

  #if TEST_NUM == 205
    unsigned long d1 = dict_new();

    init(d1, MAX_GLOBAL_DICT_SIZE);
    dict_insert(d1, "kk", "vvvvv");

    assert(streq(dict_find(d1, "kk"), "vvvvv", 6));
    assert(dict_size(d1) == MAX_GLOBAL_DICT_SIZE + 1);
  #endif

  #if TEST_NUM == 206
    unsigned long d1 = dict_global();

    init(d1, MAX_GLOBAL_DICT_SIZE);
    dict_insert(d1, "kk", "vvvvv");

    assert(dict_find(d1, "kk") == NULL);
    assert(dict_size(d1) == MAX_GLOBAL_DICT_SIZE);
  #endif

  #if TEST_NUM == 207
    unsigned long d1 = dict_new();

    dict_insert(d1, "kk", "vvvvv");
    assert(dict_size(d1) == 1);
    assert(streq(dict_find(d1, "kk"), "vvvvv", 6));

    dict_insert(d1, "kk", "aaaaa");
    assert(streq(dict_find(d1, "kk"), "aaaaa", 6));
    assert(dict_size(d1) == 1);
  #endif

  // Testy dict_remove, dict_clear, dict_delete.
  #if TEST_NUM == 301
    unsigned long d1 = dict_new();

    dict_insert(d1, "0", "");
    dict_insert(d1, "0", "i");
    dict_insert(d1, "1000", "ii");
    dict_insert(d1, "3", "iii");

    assert(dict_size(d1) == 3);
    assert(streq(dict_find(d1, "0"), "i", 2));
    assert(streq(dict_find(d1, "1000"), "ii", 3));
    assert(streq(dict_find(d1, "3"), "iii", 4));

    dict_remove(d1, "0");
    assert(dict_size(d1) == 2);
    assert(dict_find(d1, "0") == NULL);
    assert(streq(dict_find(d1, "1000"), "ii", 3));
    assert(streq(dict_find(d1, "3"), "iii", 4));

    dict_remove(d1, "1000");
    assert(dict_size(d1) == 1);
    assert(dict_find(d1, "0") == NULL);
    assert(dict_find(d1, "1000") == NULL);
    assert(streq(dict_find(d1, "3"), "iii", 4));

    dict_remove(d1, "3");
    assert(dict_size(d1) == 0);
    assert(dict_find(d1, "0") == NULL);
    assert(dict_find(d1, "1000") == NULL);
    assert(dict_find(d1, "3") == NULL);
  #endif

  #if TEST_NUM == 302
    unsigned long d1 = dict_new();

    dict_insert(d1, "0", "vvvvvvvvvvvvvvvvvvvvvvvvvvvvvv");
    dict_insert(d1, "1", "vvvvvvvvvvvvvvvvvvvvvvvvvvvvvvv");
    dict_insert(d1, "2", "vvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvv");

    dict_remove(d1, "unknown");

    assert(dict_size(d1) == 3);
    assert(streq(dict_find(d1, "0"),"vvvvvvvvvvvvvvvvvvvvvvvvvvvvvv", 31));
    assert(streq(dict_find(d1, "1"),"vvvvvvvvvvvvvvvvvvvvvvvvvvvvvvv", 32));
    assert(streq(dict_find(d1, "2"),"vvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvv", 33));
  #endif

  #if TEST_NUM == 303
    unsigned long d1 = dict_new();

    dict_insert(d1, "0", "vvvvvvvvvvvvvvvvvvvvvvvvvvvvvv");
    dict_insert(d1, "1", "vvvvvvvvvvvvvvvvvvvvvvvvvvvvvvv");
    dict_insert(d1, "2", "vvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvv");

    dict_remove(d1, NULL);

    assert(dict_size(d1) == 3);
    assert(streq(dict_find(d1, "0"),"vvvvvvvvvvvvvvvvvvvvvvvvvvvvvv", 31));
    assert(streq(dict_find(d1, "1"),"vvvvvvvvvvvvvvvvvvvvvvvvvvvvvvv", 32));
    assert(streq(dict_find(d1, "2"),"vvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvv", 33));
  #endif

  #if TEST_NUM == 304
    unsigned long d1 = dict_new();

    dict_insert(d1, "0", "vvvvvvvvvvvvvvvvvvvvvvvvvvvvvv");
    dict_insert(d1, "1", "vvvvvvvvvvvvvvvvvvvvvvvvvvvvvvv");
    dict_insert(d1, "2", "vvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvv");
    dict_delete(d1);

    dict_remove(d1, "0");

    assert(dict_size(d1) == 0);
    assert(dict_find(d1, "0") == NULL);
    assert(dict_find(d1, "1") == NULL);
    assert(dict_find(d1, "2") == NULL);
   #endif

  #if TEST_NUM == 305
    unsigned long d1 = dict_new();

    dict_insert(d1, "0", "vvvvvvvvvvvvvvvvvvvvvvvvvvvvvv");
    dict_insert(d1, "1", "vvvvvvvvvvvvvvvvvvvvvvvvvvvvvvv");
    dict_insert(d1, "2", "vvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvv");

    dict_clear(d1);

    assert(dict_size(d1) == 0);
    assert(dict_find(d1, "0") == NULL);
    assert(dict_find(d1, "1") == NULL);
    assert(dict_find(d1, "2") == NULL);
  #endif

  #if TEST_NUM == 306
    unsigned long d1 = dict_new();

    dict_insert(d1, "0", "vvvvvvvvvvvvvvvvvvvvvvvvvvvvvv");
    dict_insert(d1, "1", "vvvvvvvvvvvvvvvvvvvvvvvvvvvvvvv");
    dict_insert(d1, "2", "vvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvv");
    dict_delete(d1);

    dict_clear(d1);

    assert(dict_size(d1) == 0);
    assert(dict_find(d1, "0") == NULL);
    assert(dict_find(d1, "1") == NULL);
    assert(dict_find(d1, "2") == NULL);
  #endif

  #if TEST_NUM == 307
    unsigned long d1 = dict_global();

    dict_insert(d1, "0", "vvvvvvvvvvvvvvvvvvvvvvvvvvvvvv");
    dict_insert(d1, "1", "vvvvvvvvvvvvvvvvvvvvvvvvvvvvvvv");
    dict_insert(d1, "2", "vvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvv");

    dict_remove(d1, "0");

    assert(dict_size(d1) == 2);
    assert(dict_find(d1, "0") == NULL);
    assert(streq(dict_find(d1, "1"),"vvvvvvvvvvvvvvvvvvvvvvvvvvvvvvv", 32));
    assert(streq(dict_find(d1, "2"),"vvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvv", 33));
  #endif

  #if TEST_NUM == 308
    unsigned long d1 = dict_global();

    dict_insert(d1, "0", "vvvvvvvvvvvvvvvvvvvvvvvvvvvvvv");
    dict_insert(d1, "1", "vvvvvvvvvvvvvvvvvvvvvvvvvvvvvvv");
    dict_insert(d1, "2", "vvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvv");

    dict_clear(d1);

    assert(dict_size(d1) == 0);
    assert(dict_find(d1, "0") == NULL);
    assert(dict_find(d1, "1") == NULL);
    assert(dict_find(d1, "2") == NULL);
  #endif

  #if TEST_NUM == 309
    unsigned long d1 = dict_new();

    dict_insert(d1, "0", "vvvvvvvvvvvvvvvvvvvvvvvvvvvvvv");
    dict_insert(d1, "1", "vvvvvvvvvvvvvvvvvvvvvvvvvvvvvvv");
    dict_insert(d1, "2", "vvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvv");

    dict_delete(d1);
    dict_insert(d1, "0", "vvvvvvvvvvvvvvvvvvvvvvvvvvvvvv");

    assert(dict_size(d1) == 0);
    assert(dict_find(d1, "0") == NULL);
    assert(dict_find(d1, "1") == NULL);
    assert(dict_find(d1, "2") == NULL);
  #endif

  #if TEST_NUM == 310
    unsigned long d1 = dict_global();

    dict_insert(d1, "0", "vvvvvvvvvvvvvvvvvvvvvvvvvvvvvv");
    dict_insert(d1, "1", "vvvvvvvvvvvvvvvvvvvvvvvvvvvvvvv");
    dict_insert(d1, "2", "vvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvv");

    dict_delete(d1);
    dict_insert(d1, "0", "aaaaaaaaaaaaaaaaaaaaaaaaaaaaaa");

    assert(dict_size(d1) == 3);
    assert(streq(dict_find(d1, "0"),"aaaaaaaaaaaaaaaaaaaaaaaaaaaaaa", 31));
    assert(streq(dict_find(d1, "1"),"vvvvvvvvvvvvvvvvvvvvvvvvvvvvvvv", 32));
    assert(streq(dict_find(d1, "2"),"vvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvv", 33));
  #endif

  // Testy dict_find.
  #if TEST_NUM == 401
    unsigned long dg, d1;

    d1 = dict_new();
    dg = dict_global();

    dict_insert(d1, "a", "aa");
    dict_insert(dg, "b", "bb");

    assert(dict_find(dg, "a") == NULL);
    assert(streq(dict_find(dg, "b"), "bb", 3));
    assert(dict_find(dg, "c") == NULL);
    assert(streq(dict_find(d1, "a"), "aa", 3));
    assert(streq(dict_find(d1, "b"), "bb", 3));
    assert(dict_find(d1, "c") == NULL);
  #endif

  #if TEST_NUM == 402
    unsigned long d1 = dict_new();

    dict_insert(d1, "a", "aa");

    assert(dict_find(d1, NULL) == NULL);
  #endif

  #if TEST_NUM == 403
    unsigned long d1 = dict_new();

    dict_insert(d1, "a", "aa");
    dict_delete(d1);

    assert(dict_find(d1, "a") == NULL);
  #endif

  #if TEST_NUM == 404
    unsigned long dg, d1;

    d1 = dict_new();
    dg = dict_global();

    dict_insert(d1, "a", "aa");
    dict_insert(dg, "a", "gg");
    dict_insert(dg, "b", "bb");

    assert(streq(dict_find(dg, "a"), "gg", 3));
    assert(streq(dict_find(d1, "a"), "aa", 3));
    assert(streq(dict_find(d1, "b"), "bb", 3));
  #endif

  // Testy dict_copy.
  #if TEST_NUM == 501
    unsigned long d1, d2;

    d1 = dict_new();
    d2 = dict_new();

    dict_copy(d1, d2);
    assert(dict_size(d1) == 0);
    assert(dict_size(d2) == 0);
  #endif

  #if TEST_NUM == 502
    unsigned long d1, d2;

    d1 = dict_new();
    d2 = dict_new();

    dict_insert(d1, "a", "aa");

    dict_copy(d1, d2);

    assert(dict_size(d2) == 1);
    assert(streq(dict_find(d2, "a"), "aa", 3));
  #endif

  #if TEST_NUM == 503
    unsigned long d1, d2;

    d1 = dict_new();
    d2 = dict_new();

    dict_insert(d1, "a", "aa");
    dict_insert(d2, "a", "22");

    dict_copy(d1, d2);

    assert(dict_size(d2) == 1);
    assert(streq(dict_find(d2, "a"), "aa", 3));
  #endif

  #if TEST_NUM == 504
    unsigned long d1, d2;

    d1 = dict_new();
    d2 = dict_new();

    dict_insert(d1, "a", "aa");
    dict_insert(d2, "a", "22");
    dict_insert(d2, "b", "bb");

    dict_copy(d1, d2);

    assert(dict_size(d2) == 2);
    assert(streq(dict_find(d2, "a"), "aa", 3));
  #endif

  #if TEST_NUM == 505
    unsigned long d1, d2;

    d1 = dict_new();
    d2 = dict_new();

    dict_delete(d1);
    dict_delete(d2);

    dict_copy(d1, d2);

    assert(dict_size(d1) == 0);
    assert(dict_size(d2) == 0);
  #endif

  #if TEST_NUM == 506
    unsigned long d1, d2;

    d1 = dict_global();
    d2 = dict_new();

    dict_insert(d1, "a", "aa");
    dict_insert(d2, "a", "22");
    dict_insert(d2, "b", "bb");

    dict_copy(d1, d2);

    assert(dict_size(d2) == 2);
    assert(streq(dict_find(d2, "a"), "aa", 3));
  #endif

  #if TEST_NUM == 507
    unsigned long d1, d2;

    d1 = dict_new();
    d2 = dict_global();

    dict_insert(d1, "a", "aa");
    dict_insert(d2, "a", "22");
    dict_insert(d2, "b", "bb");

    dict_copy(d1, d2);

    assert(dict_size(d2) == 2);
    assert(streq(dict_find(d2, "a"), "aa", 3));
  #endif

  #if TEST_NUM == 508
    unsigned long d1, d2;

    d1 = dict_new();
    d2 = dict_global();

    init(d1, MAX_GLOBAL_DICT_SIZE + 1);

    dict_copy(d1, d2);

    // Dopuszczamy dwie polityki kopiowania do słownika globalnego:
    // - wszystko albo nic
    // - ile się zmieści
    assert(dict_size(d1) == MAX_GLOBAL_DICT_SIZE + 1);
    assert(dict_size(d2) == MAX_GLOBAL_DICT_SIZE || dict_size(d2) == 0);
  #endif

  return 0;
}
