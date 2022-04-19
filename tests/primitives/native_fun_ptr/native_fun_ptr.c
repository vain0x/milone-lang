#include <stdio.h>
#include <stdlib.h>
#include <milone.h>

typedef int(*VoidConstPtrVoidConstPtrIntFunPtr2)(void const*, void const*);

typedef int(*IntFunPtr0)(void);

typedef int(*IntIntFunPtr1)(int);

typedef void(*IntVoidFunPtr1)(int);

typedef int(*IntIntIntFunPtr2)(int, int);

void* milone_region_alloc(int , uintptr_t );

void* native_fun_ptr_native_fun_ptr_memAlloc(int len_, int size_);

int native_fun_ptr_native_fun_ptr_sortIntArray_intCompare(void const* l_, void const* r_);

void qsort(void* , uintptr_t , uintptr_t , VoidConstPtrVoidConstPtrIntFunPtr2 );

void native_fun_ptr_native_fun_ptr_sortIntArray(int* array_, int len_1);

void native_fun_ptr_native_fun_ptr_testSort(void);

int native_fun_ptr_native_fun_ptr_testUnitFun_answer(void);

void native_fun_ptr_native_fun_ptr_testUnitFun(void);

int native_fun_ptr_native_fun_ptr_testUnaryFun_inc(int n_);

void native_fun_ptr_native_fun_ptr_testUnaryFun(void);

void native_fun_ptr_native_fun_ptr_testVoidFun_log(int n_1);

void native_fun_ptr_native_fun_ptr_testVoidFun(void);

int native_fun_ptr_native_fun_ptr_testFunPtrCanBeResult_plus(int x_, int y_);

IntIntIntFunPtr2 native_fun_ptr_native_fun_ptr_testFunPtrCanBeResult_getFunPtr(void);

void native_fun_ptr_native_fun_ptr_testFunPtrCanBeResult(void);

int main(int argc, char** argv);

void* native_fun_ptr_native_fun_ptr_memAlloc(int len_, int size_) {
    void* milone_region_alloc_result;
    milone_region_alloc_result = milone_region_alloc(len_, ((uintptr_t)size_));
    return milone_region_alloc_result;
}

int native_fun_ptr_native_fun_ptr_sortIntArray_intCompare(void const* l_, void const* r_) {
    return int_compare((*(((int const*)l_))), (*(((int const*)r_))));
}

void native_fun_ptr_native_fun_ptr_sortIntArray(int* array_, int len_1) {
    qsort(((void*)array_), ((uintptr_t)len_1), (size_t)4ULL, native_fun_ptr_native_fun_ptr_sortIntArray_intCompare);
    return;
}

void native_fun_ptr_native_fun_ptr_testSort(void) {
    int len_2;
    int* array_1;
    int const* array_2;
    void* call_;
    len_2 = 5;
    call_ = native_fun_ptr_native_fun_ptr_memAlloc(len_2, sizeof(int));
    array_1 = ((int*)call_);
    array_1[0] = 3;
    array_1[1] = 1;
    array_1[2] = 4;
    array_1[3] = 1;
    array_1[4] = 5;
    native_fun_ptr_native_fun_ptr_sortIntArray(array_1, len_2);
    array_2 = ((int const*)array_1);
    milone_assert((array_2[0] == 1), (struct String){.ptr = "native_fun_ptr/native_fun_ptr.milone", .len = 36}, 31, 2);
    milone_assert((array_2[1] == 1), (struct String){.ptr = "native_fun_ptr/native_fun_ptr.milone", .len = 36}, 32, 2);
    milone_assert((array_2[2] == 3), (struct String){.ptr = "native_fun_ptr/native_fun_ptr.milone", .len = 36}, 33, 2);
    milone_assert((array_2[3] == 4), (struct String){.ptr = "native_fun_ptr/native_fun_ptr.milone", .len = 36}, 34, 2);
    milone_assert((array_2[4] == 5), (struct String){.ptr = "native_fun_ptr/native_fun_ptr.milone", .len = 36}, 35, 2);
    return;
}

int native_fun_ptr_native_fun_ptr_testUnitFun_answer(void) {
    return 42;
}

void native_fun_ptr_native_fun_ptr_testUnitFun(void) {
    IntFunPtr0 fp_;
    int value_;
    fp_ = ((IntFunPtr0)native_fun_ptr_native_fun_ptr_testUnitFun_answer);
int (*unit_fun)(void) = fp_;    value_ = unit_fun();
    milone_assert((value_ == 42), (struct String){.ptr = "native_fun_ptr/native_fun_ptr.milone", .len = 36}, 46, 2);
    return;
}

int native_fun_ptr_native_fun_ptr_testUnaryFun_inc(int n_) {
    return (n_ + 1);
}

void native_fun_ptr_native_fun_ptr_testUnaryFun(void) {
    IntIntFunPtr1 fp_1;
    int value_1;
    fp_1 = native_fun_ptr_native_fun_ptr_testUnaryFun_inc;
int (*unary_fun)(int) = fp_1;    value_1 = unary_fun(41);
    milone_assert((value_1 == 42), (struct String){.ptr = "native_fun_ptr/native_fun_ptr.milone", .len = 36}, 57, 2);
    return;
}

void native_fun_ptr_native_fun_ptr_testVoidFun_log(int n_1) {
printf("f is called: n=%d.\n", n_1);    return;
}

void native_fun_ptr_native_fun_ptr_testVoidFun(void) {
    IntVoidFunPtr1 fp_2;
    fp_2 = ((IntVoidFunPtr1)native_fun_ptr_native_fun_ptr_testVoidFun_log);
void(*void_fun)(int) = fp_2; void_fun(42);    return;
}

int native_fun_ptr_native_fun_ptr_testFunPtrCanBeResult_plus(int x_, int y_) {
    return (x_ + y_);
}

IntIntIntFunPtr2 native_fun_ptr_native_fun_ptr_testFunPtrCanBeResult_getFunPtr(void) {
    return native_fun_ptr_native_fun_ptr_testFunPtrCanBeResult_plus;
}

void native_fun_ptr_native_fun_ptr_testFunPtrCanBeResult(void) {
    IntIntIntFunPtr2 p_;
    IntIntIntFunPtr2 call_1;
    call_1 = native_fun_ptr_native_fun_ptr_testFunPtrCanBeResult_getFunPtr();
    p_ = call_1;
    milone_assert((p_ != ((IntIntIntFunPtr2)NULL)), (struct String){.ptr = "native_fun_ptr/native_fun_ptr.milone", .len = 36}, 73, 2);
    return;
}

int main(int argc, char** argv) {
    milone_start(argc, argv);
    native_fun_ptr_native_fun_ptr_testSort();
    native_fun_ptr_native_fun_ptr_testUnitFun();
    native_fun_ptr_native_fun_ptr_testUnaryFun();
    native_fun_ptr_native_fun_ptr_testVoidFun();
    native_fun_ptr_native_fun_ptr_testFunPtrCanBeResult();
    return 0;
}
