#include <milone.h>

int main(int argc, char** argv);

int main(int argc, char** argv) {
    milone_start(argc, argv);
    void* mutNull_ = ((void*)(size_t)0ULL);
    void const* constNull_ = ((void const*)mutNull_);
    int const* constIntPtr_ = ((int const*)constNull_);
    int* intPtr_ = ((int*)constIntPtr_);
    intptr_t address_ = ((intptr_t)intPtr_);
    milone_assert((address_ == 0LL), (struct String){.str = "native_cast/native_cast.milone", .len = 30}, 11, 2);
    return 0;
}
