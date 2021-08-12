#include "milone.h"

void* milone_mem_alloc(int, uintptr_t);

void* memAlloc_(int len_, int size_);

int intCompare_(void const* l_, void const* r_);

void qsort(void*, uintptr_t, uintptr_t, int(*)(void const*, void const*));

char sortIntArray_(int* array_, int len_1);

char testSort_(char arg_);

int answer_(char arg_1);

char testUnitFun_(char arg_2);

int inc_(int n_);

char testUnaryFun_(char arg_3);

char log_(int n_1);

char testVoidFun_(char arg_4);

int milone_main();

void* memAlloc_(int len_, int size_) {
    void* milone_mem_alloc_result = milone_mem_alloc(len_, ((uintptr_t)size_));
    return milone_mem_alloc_result;
}

int intCompare_(void const* l_, void const* r_) {
    int read_ = (*(((int const*)l_)));
    int read_1 = (*(((int const*)r_)));
    return int_compare(read_, read_1);
}

char sortIntArray_(int* array_, int len_1) {
    qsort(((void*)array_), ((uintptr_t)len_1), ((uintptr_t)4), intCompare_);
    return 0;
}

char testSort_(char arg_) {
    int len_2 = 5;
    void* call_ = memAlloc_(len_2, sizeof(int));
    int* array_1 = ((int*)call_);
    (*(array_1)) = 3;
    array_1[1] = 1;
    array_1[2] = 4;
    array_1[3] = 1;
    array_1[4] = 5;
    char call_1 = sortIntArray_(array_1, len_2);
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

int answer_(char arg_1) {
    return 42;
}

char testUnitFun_(char arg_2) {
    int(*fp_)() = ((int(*)())answer_);
int (*unit_fun)(void) = fp_;    int value_ = unit_fun();
    milone_assert((value_ == 42), 56, 2);
    return 0;
}

int inc_(int n_) {
    return (n_ + 1);
}

char testUnaryFun_(char arg_3) {
    int(*fp_1)(int) = inc_;
int (*unary_fun)(int) = fp_1;    int value_1 = unary_fun(41);
    milone_assert((value_1 == 42), 67, 2);
    return 0;
}

char log_(int n_1) {
printf("f is called: n=%d.\n", n_1);    return 0;
}

char testVoidFun_(char arg_4) {
    void(*fp_2)(int) = ((void(*)(int))log_);
void(*void_fun)(int) = fp_2; void_fun(42);    return 0;
}

int milone_main() {
    char call_2 = testSort_(0);
    char call_3 = testUnitFun_(0);
    char call_4 = testUnaryFun_(0);
    char call_5 = testVoidFun_(0);
    return 0;
}
