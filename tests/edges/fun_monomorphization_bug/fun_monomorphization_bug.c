#include <milone.h>

struct IntIntTuple2_;

void const* fun_monomorphization_bug_fun_monomorphization_bug_IntIntTuple2ObjectFun1_myFst(struct IntIntTuple2_ pair_);

void const* fun_monomorphization_bug_fun_monomorphization_bug_myFst_ObjectObjectFun1_g(void const* pair_1);

int main(int argc, char** argv);

struct IntIntTuple2_ {
    int t0;
    int t1;
};

void const* fun_monomorphization_bug_fun_monomorphization_bug_IntIntTuple2ObjectFun1_myFst(struct IntIntTuple2_ pair_) {
    void const* box_;
    void const* call_;
    box_ = ((void const*)milone_mem_alloc(1, sizeof(struct IntIntTuple2_)));
    (*(((struct IntIntTuple2_*)box_))) = pair_;
    call_ = fun_monomorphization_bug_fun_monomorphization_bug_myFst_ObjectObjectFun1_g(box_);
    return call_;
}

void const* fun_monomorphization_bug_fun_monomorphization_bug_myFst_ObjectObjectFun1_g(void const* pair_1) {
    int x_;
    x_ = (*(((struct IntIntTuple2_ const*)pair_1))).t0;
    return ((void const*)((intptr_t)x_));
}

int main(int argc, char** argv) {
    milone_start(argc, argv);
    struct IntIntTuple2_ IntIntTuple2_;
    void const* call_1;
    IntIntTuple2_ = (struct IntIntTuple2_){.t0 = 2, .t1 = 3};
    call_1 = fun_monomorphization_bug_fun_monomorphization_bug_IntIntTuple2ObjectFun1_myFst(IntIntTuple2_);
    milone_assert((((int)((intptr_t)call_1)) == 2), (struct String){.str = "fun_monomorphization_bug/fun_monomorphization_bug.milone", .len = 56}, 18, 2);
    return 0;
}
