#include <stdio.h>
#include <stdlib.h>
#include <milone.h>

struct Int32Int32Tuple2_;

void const* fun_monomorphization_bug_fun_monomorphization_bug_Int32Int32Tuple2ObjectFun1_myFst(struct Int32Int32Tuple2_ pair_);

void const* fun_monomorphization_bug_fun_monomorphization_bug_myFst_ObjectObjectFun1_g(void const* pair_1);

int main(int argc, char** argv);

struct Int32Int32Tuple2_ {
    int32_t t0;
    int32_t t1;
};

void const* fun_monomorphization_bug_fun_monomorphization_bug_Int32Int32Tuple2ObjectFun1_myFst(struct Int32Int32Tuple2_ pair_) {
    void const* box_;
    void const* call_;
    box_ = ((void const*)milone_region_alloc(1, sizeof(struct Int32Int32Tuple2_)));
    (*(((struct Int32Int32Tuple2_*)box_))) = pair_;
    call_ = fun_monomorphization_bug_fun_monomorphization_bug_myFst_ObjectObjectFun1_g(box_);
    return call_;
}

void const* fun_monomorphization_bug_fun_monomorphization_bug_myFst_ObjectObjectFun1_g(void const* pair_1) {
    int32_t x_;
    x_ = (*(((struct Int32Int32Tuple2_ const*)pair_1))).t0;
    return ((void const*)((intptr_t)x_));
}

int main(int argc, char** argv) {
    milone_start(argc, argv);
    struct Int32Int32Tuple2_ Int32Int32Tuple2_;
    void const* call_1;
    Int32Int32Tuple2_ = (struct Int32Int32Tuple2_){.t0 = 2, .t1 = 3};
    call_1 = fun_monomorphization_bug_fun_monomorphization_bug_Int32Int32Tuple2ObjectFun1_myFst(Int32Int32Tuple2_);
    milone_assert((((int32_t)((intptr_t)call_1)) == 2), (struct String){.ptr = "fun_monomorphization_bug/fun_monomorphization_bug.milone", .len = 56}, 18, 2);
    return 0;
}
