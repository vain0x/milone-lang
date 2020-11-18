#include "milone.h"

struct UnitList;

int isEmpty_1(struct UnitList* xs_1);

int assertIsEmpty_1(struct UnitList* xs_);

int main();

struct UnitList {
    int head;
    struct UnitList* tail;
};

int isEmpty_1(struct UnitList* xs_1) {
    int if_;
    if ((!(xs_1))) {
        goto nil_cl_2;
    } else {
        goto cons_cl_3;
    }
nil_cl_2:;
    if_ = 1;
    goto if_next_1;
cons_cl_3:;
    if_ = 0;
    goto if_next_1;
if_next_1:;
    return if_;
}

int assertIsEmpty_1(struct UnitList* xs_) {
    int call_ = isEmpty_1(xs_);
    milone_assert(call_, 6, 23);
    int call_1 = 0;
    return 0;
}

int main() {
    int call_2 = assertIsEmpty_1(NULL);
    return 0;
}
