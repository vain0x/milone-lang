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
    int match_;
    if ((!((!(xs_1))))) goto next_2;
    match_ = 1;
    goto end_match_1;
next_2:;
    match_ = 0;
    goto end_match_1;
next_3:;
end_match_1:;
    return match_;
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
