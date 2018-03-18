#include "cdictglobal"

namespace {
    unsigned long id = ::jnp1::dict_global();
}

int main() {
    return id != 0;
}
