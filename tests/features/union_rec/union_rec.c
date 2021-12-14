#include <milone.h>

struct LazyList_;

typedef struct LazyList_(*VoidConstPtrLazyList_FunPtr1)(void const*);

struct UnitLazyList_Fun1;

struct IntUnitLazyListFun1Tuple2_;

struct IntIntTuple2_;

struct LazyList_ union_rec_union_rec_main_cons(struct UnitLazyList_Fun1 tail_, int head_);

void union_rec_union_rec_main_lazyListPrint_go(int n_1, struct LazyList_ xs_1);

void union_rec_union_rec_main_lazyListPrint(int n_, struct LazyList_ xs_);

struct LazyList_ union_rec_union_rec_eta2_main_makeTail_makeTail(void const* env_);

struct LazyList_ union_rec_union_rec_main_makeTail(int n_2, int prev_);

int main(int argc, char** argv);

enum LazyList_Discriminant {
    Nil_,
    Cons_,
};

struct LazyList_ {
    enum LazyList_Discriminant discriminant;
    union {
        void const* Cons_;
    };
};

struct UnitLazyList_Fun1 {
    VoidConstPtrLazyList_FunPtr1 fun;
    void const* env;
};

struct IntUnitLazyListFun1Tuple2_ {
    int t0;
    struct UnitLazyList_Fun1 t1;
};

struct IntIntTuple2_ {
    int t0;
    int t1;
};

struct LazyList_ union_rec_union_rec_main_cons(struct UnitLazyList_Fun1 tail_, int head_) {
    struct IntUnitLazyListFun1Tuple2_ IntUnitLazyListFun1Tuple2_ = (struct IntUnitLazyListFun1Tuple2_){.t0 = head_, .t1 = tail_};
    void const* box_ = milone_mem_alloc(1, sizeof(struct IntUnitLazyListFun1Tuple2_));
    (*(((struct IntUnitLazyListFun1Tuple2_*)box_))) = IntUnitLazyListFun1Tuple2_;
    struct LazyList_ variant_ = (struct LazyList_){.discriminant = Cons_, .Cons_ = box_};
    return variant_;
}

void union_rec_union_rec_main_lazyListPrint_go(int n_1, struct LazyList_ xs_1) {
    struct UnitLazyList_Fun1 tail_1;
    int head_1;
tailrec_1:;
    char if_;
    if ((0 < n_1)) {
        goto then_3;
    } else {
        goto else_7;
    }
then_3:;
    char match_;
    if ((xs_1.discriminant != Nil_)) goto next_5;
    match_ = 0;
    goto end_match_4;
next_5:;
    if ((xs_1.discriminant != Cons_)) goto next_6;
    head_1 = (*(((struct IntUnitLazyListFun1Tuple2_ const*)xs_1.Cons_))).t0;
    tail_1 = (*(((struct IntUnitLazyListFun1Tuple2_ const*)xs_1.Cons_))).t1;
    printf("%d\n", head_1);
    struct LazyList_ app_ = tail_1.fun(tail_1.env);
    int arg_3 = (n_1 - 1);
    struct LazyList_ arg_4 = app_;
    n_1 = arg_3;
    xs_1 = arg_4;
    goto tailrec_1;
next_6:;
    exit(1);
end_match_4:;
    if_ = 0;
    goto if_next_2;
else_7:;
    if_ = 0;
    goto if_next_2;
if_next_2:;
    return;
}

void union_rec_union_rec_main_lazyListPrint(int n_, struct LazyList_ xs_) {
    union_rec_union_rec_main_lazyListPrint_go(n_, xs_);
    return;
}

struct LazyList_ union_rec_union_rec_eta2_main_makeTail_makeTail(void const* env_) {
    int arg_1 = (*(((struct IntIntTuple2_ const*)env_))).t0;
    int arg_2 = (*(((struct IntIntTuple2_ const*)env_))).t1;
    struct LazyList_ call_ = union_rec_union_rec_main_makeTail(arg_1, arg_2);
    return call_;
}

struct LazyList_ union_rec_union_rec_main_makeTail(int n_2, int prev_) {
    int head_2 = (n_2 * prev_);
    struct IntIntTuple2_ IntIntTuple2_ = (struct IntIntTuple2_){.t0 = (n_2 + 1), .t1 = head_2};
    void const* box_1 = milone_mem_alloc(1, sizeof(struct IntIntTuple2_));
    (*(((struct IntIntTuple2_*)box_1))) = IntIntTuple2_;
    struct UnitLazyList_Fun1 fun_ = (struct UnitLazyList_Fun1){.fun = union_rec_union_rec_eta2_main_makeTail_makeTail, .env = box_1};
    struct LazyList_ call_1 = union_rec_union_rec_main_cons(fun_, head_2);
    return call_1;
}

int main(int argc, char** argv) {
    milone_start(argc, argv);
    struct LazyList_ call_2 = union_rec_union_rec_main_makeTail(1, 1);
    struct LazyList_ fact_ = call_2;
    union_rec_union_rec_main_lazyListPrint(5, fact_);
    return 0;
}
