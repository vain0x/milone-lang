#include <stdio.h>
#include <stdlib.h>
#include <milone.h>

typedef int32_t(*VoidConstPtrVoidConstPtrInt32FunPtr2)(void const *, void const *);

typedef int32_t(*Int32FunPtr0)(void);

typedef int32_t(*Int32Int32FunPtr1)(int32_t);

typedef void(*Int32VoidFunPtr1)(int32_t);

typedef int32_t(*Int32Int32Int32FunPtr2)(int32_t, int32_t);

void *milone_region_alloc(uint32_t, uint32_t);

void *native_fun_ptr_native_fun_ptr_memAlloc(uint32_t len_, uint32_t size_);

int32_t native_fun_ptr_native_fun_ptr_sortIntArray_intCompare(void const *l_, void const *r_);

void qsort(void *, uintptr_t, uintptr_t, VoidConstPtrVoidConstPtrInt32FunPtr2);

void native_fun_ptr_native_fun_ptr_sortIntArray(int32_t *array_, uint32_t len_1);

void native_fun_ptr_native_fun_ptr_testSort(void);

int32_t native_fun_ptr_native_fun_ptr_testUnitFun_answer(void);

void native_fun_ptr_native_fun_ptr_testUnitFun(void);

int32_t native_fun_ptr_native_fun_ptr_testUnaryFun_inc(int32_t n_);

void native_fun_ptr_native_fun_ptr_testUnaryFun(void);

void native_fun_ptr_native_fun_ptr_testVoidFun_log(int32_t n_1);

void native_fun_ptr_native_fun_ptr_testVoidFun(void);

int32_t native_fun_ptr_native_fun_ptr_testFunPtrCanBeResult_plus(int32_t x_, int32_t y_);

Int32Int32Int32FunPtr2 native_fun_ptr_native_fun_ptr_testFunPtrCanBeResult_getFunPtr(void);

void native_fun_ptr_native_fun_ptr_testFunPtrCanBeResult(void);

int main(int argc, char **argv);

void *native_fun_ptr_native_fun_ptr_memAlloc(uint32_t len_, uint32_t size_) {
    void *milone_region_alloc_result;
    milone_region_alloc_result = milone_region_alloc(len_, size_);
    return milone_region_alloc_result;
}

int32_t native_fun_ptr_native_fun_ptr_sortIntArray_intCompare(void const *l_, void const *r_) {
    return milone_int32_compare((*(((int32_t const *)l_))), (*(((int32_t const *)r_))));
}

void native_fun_ptr_native_fun_ptr_sortIntArray(int32_t *array_, uint32_t len_1) {
    qsort(((void *)array_), ((uintptr_t)len_1), (size_t)4ULL, native_fun_ptr_native_fun_ptr_sortIntArray_intCompare);
    return;
}

void native_fun_ptr_native_fun_ptr_testSort(void) {
    uint32_t len_2;
    int32_t *array_1;
    int32_t const *array_2;
    void *call_;
    len_2 = (uint32_t)5U;
    call_ = native_fun_ptr_native_fun_ptr_memAlloc(len_2, ((uint32_t)sizeof(int32_t)));
    array_1 = ((int32_t *)call_);
    array_1[0] = 3;
    array_1[1] = 1;
    array_1[2] = 4;
    array_1[3] = 1;
    array_1[4] = 5;
    native_fun_ptr_native_fun_ptr_sortIntArray(array_1, len_2);
    array_2 = ((int32_t const *)array_1);
    if ((array_2[0] != 1)) milone_assert_error("native_fun_ptr/native_fun_ptr.milone", 31, 2);
    if ((array_2[1] != 1)) milone_assert_error("native_fun_ptr/native_fun_ptr.milone", 32, 2);
    if ((array_2[2] != 3)) milone_assert_error("native_fun_ptr/native_fun_ptr.milone", 33, 2);
    if ((array_2[3] != 4)) milone_assert_error("native_fun_ptr/native_fun_ptr.milone", 34, 2);
    if ((array_2[4] != 5)) milone_assert_error("native_fun_ptr/native_fun_ptr.milone", 35, 2);
    return;
}

int32_t native_fun_ptr_native_fun_ptr_testUnitFun_answer(void) {
    return 42;
}

void native_fun_ptr_native_fun_ptr_testUnitFun(void) {
    Int32FunPtr0 fp_;
    int32_t value_;
    fp_ = ((Int32FunPtr0)native_fun_ptr_native_fun_ptr_testUnitFun_answer);
int (*unit_fun)(void) = fp_;    value_ = unit_fun();
    if ((value_ != 42)) milone_assert_error("native_fun_ptr/native_fun_ptr.milone", 46, 2);
    return;
}

int32_t native_fun_ptr_native_fun_ptr_testUnaryFun_inc(int32_t n_) {
    return (n_ + 1);
}

void native_fun_ptr_native_fun_ptr_testUnaryFun(void) {
    Int32Int32FunPtr1 fp_1;
    int32_t value_1;
    fp_1 = native_fun_ptr_native_fun_ptr_testUnaryFun_inc;
int (*unary_fun)(int) = fp_1;    value_1 = unary_fun(41);
    if ((value_1 != 42)) milone_assert_error("native_fun_ptr/native_fun_ptr.milone", 57, 2);
    return;
}

void native_fun_ptr_native_fun_ptr_testVoidFun_log(int32_t n_1) {
printf("f is called: n=%d.\n", n_1);    return;
}

void native_fun_ptr_native_fun_ptr_testVoidFun(void) {
    Int32VoidFunPtr1 fp_2;
    fp_2 = ((Int32VoidFunPtr1)native_fun_ptr_native_fun_ptr_testVoidFun_log);
void(*void_fun)(int) = fp_2; void_fun(42);    return;
}

int32_t native_fun_ptr_native_fun_ptr_testFunPtrCanBeResult_plus(int32_t x_, int32_t y_) {
    return (x_ + y_);
}

Int32Int32Int32FunPtr2 native_fun_ptr_native_fun_ptr_testFunPtrCanBeResult_getFunPtr(void) {
    return native_fun_ptr_native_fun_ptr_testFunPtrCanBeResult_plus;
}

void native_fun_ptr_native_fun_ptr_testFunPtrCanBeResult(void) {
    Int32Int32Int32FunPtr2 p_;
    Int32Int32Int32FunPtr2 call_1;
    call_1 = native_fun_ptr_native_fun_ptr_testFunPtrCanBeResult_getFunPtr();
    p_ = call_1;
    if ((p_ == ((Int32Int32Int32FunPtr2)NULL))) milone_assert_error("native_fun_ptr/native_fun_ptr.milone", 73, 2);
    return;
}

int main(int argc, char **argv) {
    milone_start(argc, argv);
    native_fun_ptr_native_fun_ptr_testSort();
    native_fun_ptr_native_fun_ptr_testUnitFun();
    native_fun_ptr_native_fun_ptr_testUnaryFun();
    native_fun_ptr_native_fun_ptr_testVoidFun();
    native_fun_ptr_native_fun_ptr_testFunPtrCanBeResult();
    return 0;
}
