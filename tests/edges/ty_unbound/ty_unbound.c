#include "milone.h"

struct UnitList;

bool isEmpty_(struct UnitList const*);

char assertIsEmpty_(struct UnitList const* xs_64);

int milone_main();

char assertIsEmpty_(struct UnitList const* xs_64) {
    bool call_ = isEmpty_(xs_64);
    milone_assert(call_, 4, 23);
    return 0;
}

int milone_main() {
    char call_1 = assertIsEmpty_(NULL);
    return 0;
}
