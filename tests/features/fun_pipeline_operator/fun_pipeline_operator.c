#include "milone.h"

struct IntList;

struct IntList;

int inc_(int x_);

int twice_(int x_1);

int sub_(int x_2, int y_);

bool between_(int l_, int r_, int x_3);

int len_(struct IntList const* xs_);

int milone_main();

struct IntList {
    int head;
    struct IntList const* tail;
};

int inc_(int x_) {
    return (x_ + 1);
}

int twice_(int x_1) {
    return (x_1 * x_1);
}

int sub_(int x_2, int y_) {
    return (x_2 - y_);
}

bool between_(int l_, int r_, int x_3) {
    bool if_;
    if ((x_3 >= l_)) {
        goto then_2;
    } else {
        goto else_3;
    }
then_2:;
    if_ = (x_3 < r_);
    goto if_next_1;
else_3:;
    if_ = false;
    goto if_next_1;
if_next_1:;
    return if_;
}

int len_(struct IntList const* xs_) {
    int if_1;
    if ((!(xs_))) {
        goto nil_cl_5;
    } else {
        goto cons_cl_6;
    }
nil_cl_5:;
    if_1 = 0;
    goto if_next_4;
cons_cl_6:;
    if_1 = 1;
    goto if_next_4;
if_next_4:;
    return if_1;
}

int milone_main() {
    int call_ = inc_(1);
    int call_1 = twice_(call_);
    int call_2 = twice_(call_1);
    int n_ = call_2;
    milone_assert((n_ == 16), 9, 2);
    int call_3 = sub_(100, 98);
    bool call_4 = between_(2, 3, call_3);
    milone_assert(call_4, 11, 2);
    struct IntList const* list_ = milone_mem_alloc(1, sizeof(struct IntList));
    (*(((struct IntList*)list_))) = ((struct IntList){.head = 1, .tail = NULL});
    int call_5 = len_(list_);
    milone_assert((call_5 != 0), 19, 2);
    return 0;
}
