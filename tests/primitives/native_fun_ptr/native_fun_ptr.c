#include <stdio.h>
#include <stdlib.h>
#include <milone.h>

typedef int32_t(*VoidConstPtrVoidConstPtrInt32FunPtr2)(void const *, void const *);

typedef int32_t(*Int32Int32Int32FunPtr2)(int32_t, int32_t);

struct Int32Int32Tuple2_;

void *milone_region_alloc(int32_t, int32_t);

void *native_fun_ptr_native_fun_ptr_memAlloc(int32_t len_, int32_t size_);

int32_t native_fun_ptr_native_fun_ptr_intCompare(void const *l_, void const *r_);

void qsort(void *, uintptr_t, uintptr_t, VoidConstPtrVoidConstPtrInt32FunPtr2);

void native_fun_ptr_native_fun_ptr_sortIntArray(int32_t *array_, int32_t len_1);

void native_fun_ptr_native_fun_ptr_testSort(void);

int32_t native_fun_ptr_native_fun_ptr_answer(void);

void native_fun_ptr_native_fun_ptr_testUnitFun(void);

int32_t native_fun_ptr_native_fun_ptr_inc(int32_t n_);

void native_fun_ptr_native_fun_ptr_testUnaryFun(void);

void native_fun_ptr_native_fun_ptr_log(int32_t n_1);

void native_fun_ptr_native_fun_ptr_testVoidFun(void);

int32_t native_fun_ptr_native_fun_ptr_plus(int32_t x_, int32_t y_);

Int32Int32Int32FunPtr2 native_fun_ptr_native_fun_ptr_testFunPtrCanBeResult_getFunPtr(void);

void native_fun_ptr_native_fun_ptr_testFunPtrCanBeResult(void);

void native_fun_ptr_native_fun_ptr_testFunPtrInvoke(void);

int main(int argc, char **argv);

struct Int32Int32Tuple2_ {
    int32_t t0;
    int32_t t1;
};

void *native_fun_ptr_native_fun_ptr_memAlloc(int32_t len_, int32_t size_) {
    void *milone_region_alloc_result;
    milone_region_alloc_result = milone_region_alloc(len_, size_);
    return milone_region_alloc_result;
}

int32_t native_fun_ptr_native_fun_ptr_intCompare(void const *l_, void const *r_) {
    return milone_int32_compare((*(((int32_t const *)l_))), (*(((int32_t const *)r_))));
}

void native_fun_ptr_native_fun_ptr_sortIntArray(int32_t *array_, int32_t len_1) {
    qsort(((void *)array_), ((uintptr_t)len_1), (size_t)4ULL, native_fun_ptr_native_fun_ptr_intCompare);
    return;
}

void native_fun_ptr_native_fun_ptr_testSort(void) {
    int32_t len_2;
    int32_t *array_1;
    int32_t const *array_2;
    void *call_;
    len_2 = 5;
    call_ = native_fun_ptr_native_fun_ptr_memAlloc(len_2, sizeof(int32_t));
    array_1 = ((int32_t *)call_);
    array_1[0] = 3;
    array_1[1] = 1;
    array_1[2] = 4;
    array_1[3] = 1;
    array_1[4] = 5;
    native_fun_ptr_native_fun_ptr_sortIntArray(array_1, len_2);
    array_2 = ((int32_t const *)array_1);
    if ((array_2[0] != 1)) milone_assert_error("native_fun_ptr/native_fun_ptr.milone", 32, 2);
    if ((array_2[1] != 1)) milone_assert_error("native_fun_ptr/native_fun_ptr.milone", 33, 2);
    if ((array_2[2] != 3)) milone_assert_error("native_fun_ptr/native_fun_ptr.milone", 34, 2);
    if ((array_2[3] != 4)) milone_assert_error("native_fun_ptr/native_fun_ptr.milone", 35, 2);
    if ((array_2[4] != 5)) milone_assert_error("native_fun_ptr/native_fun_ptr.milone", 36, 2);
    return;
}

int32_t native_fun_ptr_native_fun_ptr_answer(void) {
    return 42;
}

void native_fun_ptr_native_fun_ptr_testUnitFun(void) {
    int32_t value_;
int (*unit_fun)(void) = native_fun_ptr_native_fun_ptr_answer;    value_ = unit_fun();
    if ((value_ != 42)) milone_assert_error("native_fun_ptr/native_fun_ptr.milone", 45, 2);
    return;
}

int32_t native_fun_ptr_native_fun_ptr_inc(int32_t n_) {
    return (n_ + 1);
}

void native_fun_ptr_native_fun_ptr_testUnaryFun(void) {
    int32_t value_1;
int (*unary_fun)(int) = native_fun_ptr_native_fun_ptr_inc;    value_1 = unary_fun(41);
    if ((value_1 != 42)) milone_assert_error("native_fun_ptr/native_fun_ptr.milone", 55, 2);
    return;
}

void native_fun_ptr_native_fun_ptr_log(int32_t n_1) {
printf("f is called: n=%d.\n", n_1);    return;
}

void native_fun_ptr_native_fun_ptr_testVoidFun(void) {
void(*void_fun)(int) = native_fun_ptr_native_fun_ptr_log; void_fun(42);    return;
}

int32_t native_fun_ptr_native_fun_ptr_plus(int32_t x_, int32_t y_) {
    return (x_ + y_);
}

Int32Int32Int32FunPtr2 native_fun_ptr_native_fun_ptr_testFunPtrCanBeResult_getFunPtr(void) {
    return native_fun_ptr_native_fun_ptr_plus;
}

void native_fun_ptr_native_fun_ptr_testFunPtrCanBeResult(void) {
    Int32Int32Int32FunPtr2 p_;
    Int32Int32Int32FunPtr2 call_1;
    call_1 = native_fun_ptr_native_fun_ptr_testFunPtrCanBeResult_getFunPtr();
    p_ = call_1;
    if ((p_ == ((Int32Int32Int32FunPtr2)NULL))) milone_assert_error("native_fun_ptr/native_fun_ptr.milone", 70, 2);
    return;
}

void native_fun_ptr_native_fun_ptr_testFunPtrInvoke(void) {
    int32_t app_;
    int32_t app_1;
    struct Int32Int32Tuple2_ Int32Int32Tuple2_;
    int32_t app_2;
    app_ = native_fun_ptr_native_fun_ptr_answer();
    if ((app_ != 42)) milone_assert_error("native_fun_ptr/native_fun_ptr.milone", 73, 2);
    app_1 = native_fun_ptr_native_fun_ptr_inc(2);
    if ((app_1 != 3)) milone_assert_error("native_fun_ptr/native_fun_ptr.milone", 74, 2);
    Int32Int32Tuple2_ = (struct Int32Int32Tuple2_){.t0 = 2, .t1 = 3};
    app_2 = native_fun_ptr_native_fun_ptr_plus(Int32Int32Tuple2_.t0, Int32Int32Tuple2_.t1);
    if ((app_2 != 5)) milone_assert_error("native_fun_ptr/native_fun_ptr.milone", 75, 2);
    return;
}

int main(int argc, char **argv) {
    milone_start(argc, argv);
    native_fun_ptr_native_fun_ptr_testSort();
    native_fun_ptr_native_fun_ptr_testUnitFun();
    native_fun_ptr_native_fun_ptr_testUnaryFun();
    native_fun_ptr_native_fun_ptr_testVoidFun();
    native_fun_ptr_native_fun_ptr_testFunPtrCanBeResult();
    native_fun_ptr_native_fun_ptr_testFunPtrInvoke();
    return 0;
}
