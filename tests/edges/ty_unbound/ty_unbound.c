#include "milone.h"

struct UnitList;

bool isEmpty_1(struct UnitList const* xs_1);

int assertIsEmpty_1(struct UnitList const* xs_);

int main();

struct UnitList {
    int head;
    struct UnitList const* tail;
};

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

int assertIsEmpty_1(struct UnitList const* xs_) {
    bool call_ = isEmpty_1(xs_);
    milone_assert(call_, 6, 23);
    return 0;
}

int main() {
    int call_1 = assertIsEmpty_1(NULL);
    return 0;
}
