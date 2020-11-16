#include "milone.h"

int getAnswer_(int arg_);

static int answer_;

int main();

int getAnswer_(int arg_) {
    return 42;
}

// static answer_;

int main() {
    answer_ = 42;
    milone_assert((answer_ == 42), 8, 2);
    int call_ = 0;
    int call_1 = getAnswer_(0);
    milone_assert((call_1 == 42), 11, 2);
    int call_2 = 0;
    void* box_ = (void*)milone_mem_alloc(1, sizeof(int));
    (*(((int*)box_))) = 42;
    void* myAnswer_ = box_;
    return 0;
}
