#include "milone.h"

bool id_1(bool);

int id_(int);

int milone_main();

int milone_main() {
    bool call_ = id_1(true);
    milone_assert(call_, 6, 2);
    int call_1 = id_(42);
    milone_assert((call_1 == 42), 7, 2);
    return 0;
}
