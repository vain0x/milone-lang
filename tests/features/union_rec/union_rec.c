#include "milone.h"

enum LazyList_Tag;

struct LazyList_;

struct UnitLazyList_Fun1;

struct IntUnitLazyList_Fun1Tuple2;

struct LazyList_ cons_(struct UnitLazyList_Fun1 tail_, int head_);

int go_(int n_1, struct LazyList_ xs_1);

int lazyListPrint_(int n_, struct LazyList_ xs_);

struct IntIntTuple2;

struct LazyList_ fun_(void* env_, int arg_);

struct LazyList_ makeTail_(int n_2, int prev_, int arg_5);

int main();

enum LazyList_Tag {
    Nil_,
    Cons_,
};

struct LazyList_ {
    enum LazyList_Tag tag;
    union {
        void* Cons_;
    };
};

struct UnitLazyList_Fun1 {
    struct LazyList_(*fun)(void*, int);
    void* env;
};

struct IntUnitLazyList_Fun1Tuple2 {
    int t0;
    struct UnitLazyList_Fun1 t1;
};

struct LazyList_ cons_(struct UnitLazyList_Fun1 tail_, int head_) {
    struct IntUnitLazyList_Fun1Tuple2 tuple_;
    tuple_.t0 = head_;
    tuple_.t1 = tail_;
    void* box_ = (void*)milone_mem_alloc(1, sizeof(struct IntUnitLazyList_Fun1Tuple2));
    (*(((struct IntUnitLazyList_Fun1Tuple2*)box_))) = tuple_;
    struct LazyList_ variant_ = (struct LazyList_){.tag = Cons_, .Cons_ = box_};
    return variant_;
}

int go_(int n_1, struct LazyList_ xs_1) {
tailrec_1:;
    int match_;
    if ((0 >= n_1)) goto next_3;
    int match_1;
    if ((xs_1.tag != Nil_)) goto next_6;
    match_1 = 0;
    goto end_match_5;
next_6:;
    if ((xs_1.tag != Cons_)) goto next_7;
    int head_1 = (*(((struct IntUnitLazyList_Fun1Tuple2*)xs_1.Cons_))).t0;
    struct UnitLazyList_Fun1 tail_1 = (*(((struct IntUnitLazyList_Fun1Tuple2*)xs_1.Cons_))).t1;
    printf("%d\n", head_1);
    int call_ = 0;
    int arg_3 = (n_1 - 1);
    struct LazyList_ app_ = tail_1.fun(tail_1.env, 0);
    struct LazyList_ arg_4 = app_;
    n_1 = arg_3;
    xs_1 = arg_4;
    goto tailrec_1;
    match_1 = 0;
    goto end_match_5;
next_7:;
end_match_5:;
    match_ = 0;
    goto end_match_2;
next_3:;
    if ((0 < n_1)) goto next_4;
    match_ = 0;
    goto end_match_2;
next_4:;
    exit(1);
end_match_2:;
    return 0;
}

int lazyListPrint_(int n_, struct LazyList_ xs_) {
    int call_1 = go_(n_, xs_);
    return 0;
}

struct IntIntTuple2 {
    int t0;
    int t1;
};

struct LazyList_ fun_(void* env_, int arg_) {
    int arg_1 = (*(((struct IntIntTuple2*)env_))).t0;
    int arg_2 = (*(((struct IntIntTuple2*)env_))).t1;
    struct LazyList_ call_2 = makeTail_(arg_1, arg_2, 0);
    return call_2;
}

struct LazyList_ makeTail_(int n_2, int prev_, int arg_5) {
    int head_2 = (n_2 * prev_);
    struct IntIntTuple2 tuple_1;
    tuple_1.t0 = (n_2 + 1);
    tuple_1.t1 = head_2;
    void* box_1 = (void*)milone_mem_alloc(1, sizeof(struct IntIntTuple2));
    (*(((struct IntIntTuple2*)box_1))) = tuple_1;
    void* env_1 = box_1;
    struct UnitLazyList_Fun1 fun_1 = (struct UnitLazyList_Fun1){.fun = fun_, .env = env_1};
    struct LazyList_ call_3 = cons_(fun_1, head_2);
    return call_3;
}

int main() {
    struct LazyList_ call_4 = makeTail_(1, 1, 0);
    struct LazyList_ fact_ = call_4;
    int call_5 = lazyListPrint_(5, fact_);
    return 0;
}
