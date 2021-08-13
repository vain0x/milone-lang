#include "milone.h"

struct UnitUnitTuple2_;

void const* dup_(void const* arg_);

void const* bug_(void const* b_);

int milone_main(void);

struct UnitUnitTuple2_ {
    char t0;
    char t1;
};

void const* dup_(void const* arg_) {
    char x_ = 0;
    struct UnitUnitTuple2_ UnitUnitTuple2_ = (struct UnitUnitTuple2_){.t0 = 0, .t1 = 0};
    void const* box_ = milone_mem_alloc(1, sizeof(struct UnitUnitTuple2_));
    (*(((struct UnitUnitTuple2_*)box_))) = UnitUnitTuple2_;
    return box_;
}

void const* bug_(void const* b_) {
    void const* call_ = dup_(b_);
    return call_;
}

int milone_main(void) {
    printf("x1 = \'a\'\n");
    printf("x2 = \'a\'\n");
    return 0;
}
