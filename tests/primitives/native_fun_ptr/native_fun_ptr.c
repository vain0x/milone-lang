#include "milone.h"

void* milone_mem_alloc(int, uintptr_t);

void* native_fun_ptr_Program_memAlloc(int len_, int size_);

int intCompare_(void const* l_, void const* r_);

void qsort(void*, uintptr_t, uintptr_t, int(*)(void const*, void const*));

char native_fun_ptr_Program_sortIntArray(int* array_, int len_1);

int milone_main();

void* native_fun_ptr_Program_memAlloc(int len_, int size_) {
    void* milone_mem_alloc_result = milone_mem_alloc(len_, ((uintptr_t)size_));
    return milone_mem_alloc_result;
}

int intCompare_(void const* l_, void const* r_) {
    int read_ = (*(((int const*)l_)));
    int read_1 = (*(((int const*)r_)));
    return int_compare(read_, read_1);
}

char native_fun_ptr_Program_sortIntArray(int* array_, int len_1) {
    qsort(((void*)array_), ((uintptr_t)len_1), ((uintptr_t)4), intCompare_);
    return 0;
}

int milone_main() {
    int len_2 = 5;
    void* call_ = native_fun_ptr_Program_memAlloc(len_2, sizeof(int));
    int* array_1 = ((int*)call_);
    (*(array_1)) = 3;
    array_1[1] = 1;
    array_1[2] = 4;
    array_1[3] = 1;
    array_1[4] = 5;
    char call_1 = native_fun_ptr_Program_sortIntArray(array_1, len_2);
    int const* array_2 = ((int const*)array_1);
    int read_2 = (*(array_2));
    milone_assert((read_2 == 1), 40, 2);
    int read_3 = array_2[1];
    milone_assert((read_3 == 1), 41, 2);
    int read_4 = array_2[2];
    milone_assert((read_4 == 3), 42, 2);
    int read_5 = array_2[3];
    milone_assert((read_5 == 4), 43, 2);
    int read_6 = array_2[4];
    milone_assert((read_6 == 5), 44, 2);
    return 0;
}
