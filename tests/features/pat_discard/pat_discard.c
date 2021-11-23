#include <milone.h>

struct UnitUnitTuple2_;

void pat_discard_pat_discard_main_f(void);

int main(int argc, char** argv);

struct UnitUnitTuple2_ {
    char t0;
    char t1;
};

void pat_discard_pat_discard_main_f(void) {
    printf("hello\n");
    return;
}

int main(int argc, char** argv) {
    milone_start(argc, argv);
    pat_discard_pat_discard_main_f();
    pat_discard_pat_discard_main_f();
    struct UnitUnitTuple2_ UnitUnitTuple2_ = (struct UnitUnitTuple2_){.t0 = 0, .t1 = 0};
    return 0;
}
