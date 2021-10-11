#include "milone.h"

struct UnitList;

bool isEmpty_(struct UnitList const* );

void assertIsEmpty_(struct UnitList const* xs_64);

int milone_main(void);

void assertIsEmpty_(struct UnitList const* xs_64) {
    bool call_ = isEmpty_(xs_64);
    milone_assert(call_, 4, 23);
    return;
}

int milone_main(void) {
    assertIsEmpty_(NULL);
    return 0;
}
