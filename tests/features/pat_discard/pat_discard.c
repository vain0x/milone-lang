#include "milone.h"

struct UnitUnitTuple2_;

void f_(void);

int milone_main(void);

struct UnitUnitTuple2_ {
    char t0;
    char t1;
};

void f_(void) {
    printf("hello\n");
    return;
}

int milone_main(void) {
    f_();
    f_();
    struct UnitUnitTuple2_ UnitUnitTuple2_ = (struct UnitUnitTuple2_){.t0 = 0, .t1 = 0};
    return 0;
}
