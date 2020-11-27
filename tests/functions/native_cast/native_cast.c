#include "milone.h"

int main();

int main() {
    void* mutNull_ = ((void*)((uintptr_t)0));
    void const* constNull_ = ((void const*)mutNull_);
    int const* constIntPtr_ = ((int const*)constNull_);
    int* intPtr_ = ((int*)constIntPtr_);
    intptr_t address_ = ((intptr_t)intPtr_);
    milone_assert((((int)address_) == 0), 11, 2);
    return 0;
}
