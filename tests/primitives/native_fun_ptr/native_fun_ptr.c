#include "milone.h"

void* milone_mem_alloc(int , uintptr_t );

void* native_fun_ptr_native_fun_ptr_memAlloc(int len_, int size_);

int native_fun_ptr_native_fun_ptr_sortIntArray_intCompare(void const* l_, void const* r_);

void qsort(void* , uintptr_t , uintptr_t , int(*)(void const*, void const*) );

void native_fun_ptr_native_fun_ptr_sortIntArray(int* array_, int len_1);

void native_fun_ptr_native_fun_ptr_testSort(void);

int native_fun_ptr_native_fun_ptr_testUnitFun_answer(void);

void native_fun_ptr_native_fun_ptr_testUnitFun(void);

int native_fun_ptr_native_fun_ptr_testUnaryFun_inc(int n_);

void native_fun_ptr_native_fun_ptr_testUnaryFun(void);

void native_fun_ptr_native_fun_ptr_testVoidFun_log(int n_1);

void native_fun_ptr_native_fun_ptr_testVoidFun(void);

int milone_main(void);

void* native_fun_ptr_native_fun_ptr_memAlloc(int len_, int size_) {
    void* milone_mem_alloc_result = milone_mem_alloc(len_, ((uintptr_t)size_));
    return milone_mem_alloc_result;
}

int native_fun_ptr_native_fun_ptr_sortIntArray_intCompare(void const* l_, void const* r_) {
    int read_ = (*(((int const*)l_)));
    int read_1 = (*(((int const*)r_)));
    return int_compare(read_, read_1);
}

void native_fun_ptr_native_fun_ptr_sortIntArray(int* array_, int len_1) {
    qsort(((void*)array_), ((uintptr_t)len_1), ((uintptr_t)4), native_fun_ptr_native_fun_ptr_sortIntArray_intCompare);
    return;
}

void native_fun_ptr_native_fun_ptr_testSort(void) {
    int len_2 = 5;
    void* call_ = native_fun_ptr_native_fun_ptr_memAlloc(len_2, sizeof(int));
    int* array_1 = ((int*)call_);
    (*(array_1)) = 3;
    array_1[1] = 1;
    array_1[2] = 4;
    array_1[3] = 1;
    array_1[4] = 5;
    native_fun_ptr_native_fun_ptr_sortIntArray(array_1, len_2);
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

int native_fun_ptr_native_fun_ptr_testUnitFun_answer(void) {
    return 42;
}

void native_fun_ptr_native_fun_ptr_testUnitFun(void) {
    int(*fp_)(void) = ((int(*)(void))native_fun_ptr_native_fun_ptr_testUnitFun_answer);
int (*unit_fun)(void) = fp_;    int value_ = unit_fun();
    milone_assert((value_ == 42), 55, 2);
    return;
}

int native_fun_ptr_native_fun_ptr_testUnaryFun_inc(int n_) {
    return (n_ + 1);
}

void native_fun_ptr_native_fun_ptr_testUnaryFun(void) {
    int(*fp_1)(int) = native_fun_ptr_native_fun_ptr_testUnaryFun_inc;
int (*unary_fun)(int) = fp_1;    int value_1 = unary_fun(41);
    milone_assert((value_1 == 42), 66, 2);
    return;
}

void native_fun_ptr_native_fun_ptr_testVoidFun_log(int n_1) {
printf("f is called: n=%d.\n", n_1);    return;
}

void native_fun_ptr_native_fun_ptr_testVoidFun(void) {
    void(*fp_2)(int) = ((void(*)(int))native_fun_ptr_native_fun_ptr_testVoidFun_log);
void(*void_fun)(int) = fp_2; void_fun(42);    return;
}

int milone_main(void) {
    native_fun_ptr_native_fun_ptr_testSort();
    native_fun_ptr_native_fun_ptr_testUnitFun();
    native_fun_ptr_native_fun_ptr_testUnaryFun();
    native_fun_ptr_native_fun_ptr_testVoidFun();
    return 0;
}
