#include "milone.h"

void* milone_mem_alloc(int, uintptr_t);

void* memAlloc_(int len_, int size_);

int intCompare_(void const* l_, void const* r_);

void qsort(void*, uintptr_t, uintptr_t, int(*)(void const*, void const*));

int sortIntArray_(int* array_, int len_1);

int main();

void* memAlloc_(int len_, int size_) {
    void* milone_mem_alloc_result_ = milone_mem_alloc(len_, ((uintptr_t)size_));
    return milone_mem_alloc_result_;
}

int intCompare_(void const* l_, void const* r_) {
    return int_compare((*(((int*)((void*)l_)))), (*(((int*)((void*)r_)))));
}

int sortIntArray_(int* array_, int len_1) {
    qsort(((void*)array_), ((uintptr_t)len_1), ((uintptr_t)4), intCompare_);
    return 0;
}

int main() {
    int len_2 = 5;
    void* call_ = memAlloc_(len_2, sizeof(int));
    int* array_1 = ((int*)call_);
    (*(array_1)) = 3;
    array_1[1] = 1;
    array_1[2] = 4;
    array_1[3] = 1;
    array_1[4] = 5;
    int call_1 = sortIntArray_(array_1, len_2);
    int const* array_2 = ((int const*)array_1);
    int read_ = (*(array_2));
    milone_assert((read_ == 1), 28, 2);
    int read_1 = array_2[1];
    milone_assert((read_1 == 1), 29, 2);
    int read_2 = array_2[2];
    milone_assert((read_2 == 3), 30, 2);
    int read_3 = array_2[3];
    milone_assert((read_3 == 4), 31, 2);
    int read_4 = array_2[4];
    milone_assert((read_4 == 5), 32, 2);
    return 0;
}
