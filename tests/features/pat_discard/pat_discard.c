#include "milone.h"

struct UnitUnitTuple2;

char f_(char arg_);

int milone_main();

struct UnitUnitTuple2 {
    char t0;
    char t1;
};

char f_(char arg_) {
    printf("hello\n");
    return 0;
}

int milone_main() {
    char call_ = f_(0);
    char call_1 = f_(0);
    struct UnitUnitTuple2 tuple_ = ((struct UnitUnitTuple2){.t0 = 0, .t1 = 0});
    return 0;
}
