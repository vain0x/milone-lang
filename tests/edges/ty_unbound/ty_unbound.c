#include "milone.h"

struct UnitList;

static bool isEmpty_1(struct UnitList const* xs_);

static char assertIsEmpty_1(struct UnitList const* xs_60);

int milone_main();

static bool isEmpty_1(struct UnitList const* xs_) {
    bool if_;
    if ((!(xs_))) {
        goto nil_cl_2;
    } else {
        goto cons_cl_3;
    }
nil_cl_2:;
    if_ = true;
    goto if_next_1;
cons_cl_3:;
    if_ = false;
    goto if_next_1;
if_next_1:;
    return if_;
}

static char assertIsEmpty_1(struct UnitList const* xs_60) {
    bool call_ = isEmpty_1(xs_60);
    milone_assert(call_, 4, 23);
    return 0;
}

int milone_main() {
    char call_1 = assertIsEmpty_1(NULL);
    return 0;
}
