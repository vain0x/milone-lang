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

struct LazyList_ makeTail_(int n_2, int prev_, int arg_3);

int main();

enum LazyList_Tag {
    Nil_,
    Cons_,
};

struct LazyList_ {
    enum LazyList_Tag tag;
    union {
        struct IntUnitLazyList_Fun1Tuple2* Cons_;
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
    struct IntUnitLazyList_Fun1Tuple2* payload_ = (struct IntUnitLazyList_Fun1Tuple2*)milone_mem_alloc(1, sizeof(struct IntUnitLazyList_Fun1Tuple2));
    (*(((struct IntUnitLazyList_Fun1Tuple2*)payload_))) = tuple_;
    struct LazyList_ variant_ = (struct LazyList_){.tag = Cons_, .Cons_ = payload_};
    return variant_;
}

int go_(int n_1, struct LazyList_ xs_1) {
    int match_;
    if ((0 >= n_1)) goto next_2;
    int match_1;
    if ((xs_1.tag != Nil_)) goto next_5;
    match_1 = 0;
    goto end_match_4;
next_5:;
    if ((xs_1.tag != Cons_)) goto next_6;
    int head_1 = (*(xs_1.Cons_)).t0;
    struct UnitLazyList_Fun1 tail_1 = (*(xs_1.Cons_)).t1;
    printf("%d\n", head_1);
    int call_ = 0;
    struct LazyList_ app_ = tail_1.fun(tail_1.env, 0);
    int call_1 = go_((n_1 - 1), app_);
    match_1 = 0;
    goto end_match_4;
next_6:;
end_match_4:;
    match_ = 0;
    goto end_match_1;
next_2:;
    if ((0 < n_1)) goto next_3;
    match_ = 0;
    goto end_match_1;
next_3:;
    exit(1);
end_match_1:;
    return 0;
}

int lazyListPrint_(int n_, struct LazyList_ xs_) {
    int call_2 = go_(n_, xs_);
    return 0;
}

struct IntIntTuple2 {
    int t0;
    int t1;
};

struct LazyList_ fun_(void* env_, int arg_) {
    int arg_1 = (*(((struct IntIntTuple2*)env_))).t0;
    int arg_2 = (*(((struct IntIntTuple2*)env_))).t1;
    struct LazyList_ call_3 = makeTail_(arg_1, arg_2, 0);
    return call_3;
}

struct LazyList_ makeTail_(int n_2, int prev_, int arg_3) {
    int head_2 = (n_2 * prev_);
    struct IntIntTuple2 tuple_1;
    tuple_1.t0 = (n_2 + 1);
    tuple_1.t1 = head_2;
    void* box_ = (void*)milone_mem_alloc(1, sizeof(struct IntIntTuple2));
    (*(((struct IntIntTuple2*)box_))) = tuple_1;
    void* env_1 = box_;
    struct UnitLazyList_Fun1 fun_1 = (struct UnitLazyList_Fun1){.fun = fun_, .env = env_1};
    struct LazyList_ call_4 = cons_(fun_1, head_2);
    return call_4;
}

int main() {
    struct LazyList_ call_5 = makeTail_(1, 1, 0);
    struct LazyList_ fact_ = call_5;
    int call_6 = lazyListPrint_(5, fact_);
    return 0;
}
