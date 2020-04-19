#include "milone.h"

void* f_(int arg_);

static void* boxedValue_;

int main();

void* f_(int arg_) {
    void* box_ = (void*)malloc(sizeof(int));
    (*(((int*)box_))) = 1;
    return box_;
}

// static boxedValue_;

int main() {
    void* box_1 = (void*)malloc(sizeof(int));
    (*(((int*)box_1))) = 1;
    boxedValue_ = box_1;
    void* call_ = f_(0);
    milone_assert(((*(((int*)call_))) == 1), 8, 2);
    int call_1 = 0;
    return 0;
}
