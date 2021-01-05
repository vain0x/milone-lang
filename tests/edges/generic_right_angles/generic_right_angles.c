#include "milone.h"

struct IntList;

struct IntListList;

struct IntListListList;

int main();

struct IntList {
    int head;
    struct IntList const* tail;
};

struct IntListList {
    struct IntList const* head;
    struct IntListList const* tail;
};

struct IntListListList {
    struct IntListList const* head;
    struct IntListListList const* tail;
};

int main() {
    struct IntListListList const* n_ = NULL;
    bool if_;
    if ((!(n_))) {
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
    bool ok_ = if_;
    milone_assert(ok_, 16, 2);
    milone_assert((3 >= 2), 19, 2);
    milone_assert(((2 << 3) == 16), 22, 2);
    return 0;
}
