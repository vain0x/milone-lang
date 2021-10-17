#include "milone.h"

void* milone_mem_alloc(int , uintptr_t );

void* memAlloc_(int len_, int size_);

int intCompare_(void const* l_, void const* r_);

void qsort(void* , uintptr_t , uintptr_t , int(*)(void const*, void const*) );

void sortIntArray_(int* array_, int len_1);

void testSort_(void);

int answer_(void);

void testUnitFun_(void);

int inc_(int n_);

void testUnaryFun_(void);

void log_(int n_1);

void testVoidFun_(void);

int milone_main(void);

void* memAlloc_(int len_, int size_) {
    void* milone_mem_alloc_result = milone_mem_alloc(len_, ((uintptr_t)size_));
    return milone_mem_alloc_result;
}

int intCompare_(void const* l_, void const* r_) {
    int read_ = (*(((int const*)l_)));
    int read_1 = (*(((int const*)r_)));
    return int_compare(read_, read_1);
}

void sortIntArray_(int* array_, int len_1) {
    qsort(((void*)array_), ((uintptr_t)len_1), ((uintptr_t)4), intCompare_);
    return;
}

void testSort_(void) {
    int len_2 = 5;
    void* call_ = memAlloc_(len_2, sizeof(int));
    int* array_1 = ((int*)call_);
    (*(array_1)) = 3;
    array_1[1] = 1;
    array_1[2] = 4;
    array_1[3] = 1;
    array_1[4] = 5;
    sortIntArray_(array_1, len_2);
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
    return;
}

int answer_(void) {
    return 42;
}

void testUnitFun_(void) {
    int(*fp_)(void) = ((int(*)(void))answer_);
int (*unit_fun)(void) = fp_;    int value_ = unit_fun();
    milone_assert((value_ == 42), 55, 2);
    return;
}

int inc_(int n_) {
    return (n_ + 1);
}

void testUnaryFun_(void) {
    int(*fp_1)(int) = inc_;
int (*unary_fun)(int) = fp_1;    int value_1 = unary_fun(41);
    milone_assert((value_1 == 42), 66, 2);
    return;
}

void log_(int n_1) {
printf("f is called: n=%d.\n", n_1);    return;
}

void testVoidFun_(void) {
    void(*fp_2)(int) = ((void(*)(int))log_);
void(*void_fun)(int) = fp_2; void_fun(42);    return;
}

int milone_main(void) {
    testSort_();
    testUnitFun_();
    testUnaryFun_();
    testVoidFun_();
    return 0;
}
