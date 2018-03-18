#if TEST_NUM == 601

#include "cdictglobal"
#include "cdict"

#include <cassert>
#include <cstddef>
#include <cstring>

namespace {
    int streq(const char* s1, const char* s2, size_t len) {
        if (s1 == s2)
            return 1;

        if (s1 == NULL || s2 == NULL)
            return 0;

        return strncmp(s1, s2, len) == 0;
    }

    unsigned long test() {
        unsigned long id = ::jnp1::dict_new();
        ::jnp1::dict_insert(id, "k0", "a");
        return id;
    }

    unsigned long id1 = test();
    unsigned long id2 = ::jnp1::dict_global();

}

int main() {
    const char* str = ::jnp1::dict_find(id1, "k0");
    assert(streq(str, "a", 2));
    ::jnp1::dict_delete(id1);
    return id1 == id2;
}

#endif

#if TEST_NUM == 602

#include "cdict"

int main() {
    // To ma się nie kompilować.
    dict_new();
}

#endif

#if TEST_NUM == 603

#include "cdict"

int main() {
    // To ma się nie kompilować.
    dict_delete(0);
}

#endif

#if TEST_NUM == 604

#include "cdict"

int main() {
    // To ma się nie kompilować.
    dict_size(0);
}

#endif

#if TEST_NUM == 605

#include "cdict"

int main() {
    // To ma się nie kompilować.
    dict_insert(0, "", "");
}

#endif

#if TEST_NUM == 606

#include "cdict"

int main() {
    // To ma się nie kompilować.
    dict_remove(0, "");
}

#endif

#if TEST_NUM == 607

#include "cdict"

int main() {
    // To ma się nie kompilować.
    dict_find(0, "");
}

#endif

#if TEST_NUM == 608

#include "cdict"

int main() {
    // To ma się nie kompilować.
    dict_clear(0);
}

#endif

#if TEST_NUM == 609

#include "cdict"

int main() {
    // To ma się nie kompilować.
    dict_copy(0, 0);
}

#endif

#if TEST_NUM == 610

#include "cdictglobal"

int main() {
    // To ma się nie kompilować.
    dict_global();
}

#endif
