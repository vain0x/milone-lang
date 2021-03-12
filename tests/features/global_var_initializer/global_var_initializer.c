#include "milone.h"

void const* f_(char arg_);

int milone_main();

static void const* boxedValue_;

void const* f_(char arg_) {
    void const* box_ = milone_mem_alloc(1, sizeof(int));
    (*(((int*)box_))) = 1;
    return box_;
}

int milone_main() {
    void const* box_1 = milone_mem_alloc(1, sizeof(int));
    (*(((int*)box_1))) = 1;
    boxedValue_ = box_1;
    void const* call_ = f_(0);
    milone_assert(((*(((int const*)call_))) == 1), 10, 2);
    return 0;
}
