#include "milone.h"

struct LazyList_;

struct UnitLazyList_Fun1;

struct IntUnitLazyList_Fun1Tuple2;

struct IntIntTuple2;

struct LazyList_ cons_(struct UnitLazyList_Fun1 tail_, int head_);

char go_(int n_1, struct LazyList_ xs_1);

char lazyListPrint_(int n_, struct LazyList_ xs_);

struct LazyList_ fun_(void const* env_, char arg_);

struct LazyList_ makeTail_(int n_2, int prev_, char arg_5);

int milone_main();

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
    struct LazyList_(*fun)(void const*, char);
    void const* env;
};

struct IntUnitLazyList_Fun1Tuple2 {
    int t0;
    struct UnitLazyList_Fun1 t1;
};

struct IntIntTuple2 {
    int t0;
    int t1;
};

struct LazyList_ cons_(struct UnitLazyList_Fun1 tail_, int head_) {
    struct IntUnitLazyList_Fun1Tuple2 tuple_ = (struct IntUnitLazyList_Fun1Tuple2){.t0 = head_, .t1 = tail_};
    void const* box_ = milone_mem_alloc(1, sizeof(struct IntUnitLazyList_Fun1Tuple2));
    (*(((struct IntUnitLazyList_Fun1Tuple2*)box_))) = tuple_;
    struct LazyList_ variant_ = (struct LazyList_){.discriminant = Cons_, .Cons_ = box_};
    return variant_;
}

char go_(int n_1, struct LazyList_ xs_1) {
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
    head_1 = (*(((struct IntUnitLazyList_Fun1Tuple2 const*)xs_1.Cons_))).t0;
    tail_1 = (*(((struct IntUnitLazyList_Fun1Tuple2 const*)xs_1.Cons_))).t1;
    printf("%d\n", head_1);
    int arg_3 = (n_1 - 1);
    struct LazyList_ app_ = tail_1.fun(tail_1.env, 0);
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
    return 0;
}

char lazyListPrint_(int n_, struct LazyList_ xs_) {
    char call_ = go_(n_, xs_);
    return 0;
}

struct LazyList_ fun_(void const* env_, char arg_) {
    int arg_1 = (*(((struct IntIntTuple2 const*)env_))).t0;
    int arg_2 = (*(((struct IntIntTuple2 const*)env_))).t1;
    struct LazyList_ call_1 = makeTail_(arg_1, arg_2, 0);
    return call_1;
}

struct LazyList_ makeTail_(int n_2, int prev_, char arg_5) {
    int head_2 = (n_2 * prev_);
    struct IntIntTuple2 tuple_1 = (struct IntIntTuple2){.t0 = (n_2 + 1), .t1 = head_2};
    void const* box_1 = milone_mem_alloc(1, sizeof(struct IntIntTuple2));
    (*(((struct IntIntTuple2*)box_1))) = tuple_1;
    struct UnitLazyList_Fun1 fun_1 = (struct UnitLazyList_Fun1){.fun = fun_, .env = box_1};
    struct LazyList_ call_2 = cons_(fun_1, head_2);
    return call_2;
}

int milone_main() {
    struct LazyList_ call_3 = makeTail_(1, 1, 0);
    struct LazyList_ fact_ = call_3;
    char call_4 = lazyListPrint_(5, fact_);
    return 0;
}
