#include "milone.h"

int inc_(int x_);

int twice_(int x_1);

int sub_(int x_2, int y_);

int between_(int l_, int r_, int x_3);

struct IntList;

int len_(struct IntList* xs_);

int main();

int inc_(int x_) {
    return (x_ + 1);
}

int twice_(int x_1) {
    return (x_1 * x_1);
}

int sub_(int x_2, int y_) {
    return (x_2 - y_);
}

int between_(int l_, int r_, int x_3) {
    int if_;
    if ((x_3 >= l_)) {
        goto then_2;
    } else {
        goto else_3;
    }
then_2:;
    if_ = (x_3 < r_);
    goto if_next_1;
else_3:;
    if_ = 0;
    goto if_next_1;
if_next_1:;
    return if_;
}

struct IntList {
    int head;
    struct IntList* tail;
};

int len_(struct IntList* xs_) {
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

int main() {
    int call_ = inc_(1);
    int call_1 = twice_(call_);
    int call_2 = twice_(call_1);
    int n_ = call_2;
    milone_assert((n_ == 16), 7, 2);
    int call_3 = sub_(100, 98);
    int call_4 = between_(2, 3, call_3);
    milone_assert(call_4, 9, 2);
    struct IntList* list_ = (struct IntList*)milone_mem_alloc(1, sizeof(struct IntList));
    list_->head = 1;
    list_->tail = NULL;
    int call_5 = len_(list_);
    milone_assert((call_5 != 0), 17, 2);
    return 0;
}
