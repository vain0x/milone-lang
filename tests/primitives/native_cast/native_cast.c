#include <stdio.h>
#include <stdlib.h>
#include <milone.h>

int main(int argc, char **argv);

int main(int argc, char **argv) {
    milone_start(argc, argv);
    void *mutNull_;
    void const *constNull_;
    int32_t const *constIntPtr_;
    int32_t *intPtr_;
    intptr_t address_;
    mutNull_ = NULL;
    constNull_ = ((void const *)mutNull_);
    constIntPtr_ = ((int32_t const *)constNull_);
    intPtr_ = ((int32_t *)constIntPtr_);
    address_ = ((intptr_t)intPtr_);
    if ((address_ != 0LL)) milone_assert_error("native_cast/native_cast.milone", 14, 2);
    return 0;
}
