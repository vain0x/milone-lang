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
    milone_assert((answer_ == 42), 7, 2);
    int call_ = 0;
    int call_1 = getAnswer_(0);
    milone_assert((call_1 == 42), 8, 2);
    int call_2 = 0;
    return 0;
}
