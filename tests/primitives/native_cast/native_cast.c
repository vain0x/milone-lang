#include "milone.h"

int milone_main(void);

int milone_main(void) {
    void* mutNull_ = ((void*)(size_t)0ULL);
    void const* constNull_ = ((void const*)mutNull_);
    int const* constIntPtr_ = ((int const*)constNull_);
    int* intPtr_ = ((int*)constIntPtr_);
    intptr_t address_ = ((intptr_t)intPtr_);
    milone_assert((address_ == 0LL), 11, 2);
    return 0;
}
