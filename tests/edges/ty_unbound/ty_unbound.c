#include "milone.h"

struct UnitList;

bool isEmpty_1(struct UnitList const* xs_1);

char assertIsEmpty_1(struct UnitList const* xs_);

int milone_main();


bool isEmpty_1(struct UnitList const* xs_1) {
    bool if_;
    if ((!(xs_1))) {
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

char assertIsEmpty_1(struct UnitList const* xs_) {
    bool call_ = isEmpty_1(xs_);
    milone_assert(call_, 4, 23);
    return 0;
}

int milone_main() {
    char call_1 = assertIsEmpty_1(NULL);
    return 0;
}
