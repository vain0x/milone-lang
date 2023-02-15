#include <stdio.h>
#include <stdlib.h>
#include <milone.h>

struct Int32Int32Tuple2_;

struct Int32Cons;

struct Int32Cons;

typedef int32_t(*VoidConstPtrInt32Int32FunPtr2)(void const *, int32_t);

struct Int32Int32Fun1;

struct Int32Int32Tuple2option1_;

int32_t own_own_create(int32_t init_);

struct Int32Int32Tuple2_ own_own_increment(int32_t counter_);

void own_own_drop(int32_t counter_1);

void own_own_acquireAndThenDispose(void);

void own_own_acquireAndUse(void);

void own_own_transfer(void);

void own_own_branchCase(void);

void own_own_multipleMatches(void);

void own_own_nestedMatches(void);

struct Int32Cons const *own_own_loopCase_acquireMany_go(int32_t n_6, struct Int32Cons const *acc_, int32_t i_);

struct Int32Cons const *own_own_loopCase_acquireMany(int32_t n_6);

void own_own_genericWrapperCase(void);

void own_own_genericOwnCase(void);

int32_t own_own_Int32Int32Fun1Int32Int32Fun2_ownMap(struct Int32Int32Fun1 mapping_, int32_t l_1);

int32_t own_own_genericOwnFunCase_fun(int32_t x_1);

int32_t own_own_eta2_genericOwnFunCase_fun(void const *env_, int32_t arg_);

void own_own_genericOwnFunCase(void);

void own_own_optionOfOwnCase(void);

void own_own_nestedOwnCase(void);

void own_own_counterWrapperCase(void);

int main(int argc, char **argv);

struct Int32Int32Tuple2_ {
    int32_t t0;
    int32_t t1;
};

struct Int32Cons {
    int32_t head;
    struct Int32Cons const *tail;
};

struct Int32Int32Fun1 {
    VoidConstPtrInt32Int32FunPtr2 fun;
    void const *env;
};

enum Int32Int32Tuple2option1_Discriminant {
    Int32Int32Tuple2option1_None,
    Int32Int32Tuple2option1_Some,
};

struct Int32Int32Tuple2option1_ {
    enum Int32Int32Tuple2option1_Discriminant discriminant;
    union {
        struct Int32Int32Tuple2_ Int32Int32Tuple2option1_Some;
    };
};

int32_t own_own_create(int32_t init_) {
    return init_;
}

struct Int32Int32Tuple2_ own_own_increment(int32_t counter_) {
    int32_t n_;
    int32_t n_1;
    struct Int32Int32Tuple2_ Int32Int32Tuple2_;
    n_ = counter_;
    n_1 = (n_ + 1);
    Int32Int32Tuple2_ = (struct Int32Int32Tuple2_){.t0 = n_1, .t1 = n_1};
    return Int32Int32Tuple2_;
}

void own_own_drop(int32_t counter_1) {
    int32_t n_2;
    n_2 = counter_1;
    return;
}

void own_own_acquireAndThenDispose(void) {
    int32_t counter_2;
    int32_t call_;
    call_ = own_own_create(0);
    counter_2 = call_;
    own_own_drop(counter_2);
    return;
}

void own_own_acquireAndUse(void) {
    int32_t counter_3;
    int32_t n_3;
    int32_t counter_4;
    int32_t n_4;
    int32_t counter_5;
    int32_t call_1;
    struct Int32Int32Tuple2_ call_2;
    struct Int32Int32Tuple2_ call_3;
    call_1 = own_own_create(0);
    counter_3 = call_1;
    call_2 = own_own_increment(counter_3);
    n_3 = call_2.t0;
    counter_4 = call_2.t1;
    if ((n_3 != 1)) milone_assert_error("own/own.milone", 26, 2);
    call_3 = own_own_increment(counter_4);
    n_4 = call_3.t0;
    counter_5 = call_3.t1;
    own_own_drop(counter_5);
    return;
}

void own_own_transfer(void) {
    int32_t counter_6;
    int32_t other_;
    int32_t call_4;
    call_4 = own_own_create(0);
    counter_6 = call_4;
    other_ = counter_6;
    own_own_drop(other_);
    return;
}

void own_own_branchCase(void) {
    int32_t counter_7;
    int32_t n_5;
    int32_t counter_8;
    int32_t counter_9;
    int32_t counter_10;
    int32_t call_5;
    struct Int32Int32Tuple2_ call_6;
    int32_t switch_;
    struct Int32Int32Tuple2_ call_7;
    call_5 = own_own_create(0);
    counter_7 = call_5;
    call_6 = own_own_increment(counter_7);
    n_5 = call_6.t0;
    counter_8 = call_6.t1;
    switch (n_5) {
        case 0:
            goto clause_2;

        default:
            goto clause_3;
    }
clause_2:;
    switch_ = counter_8;
    goto switch_next_1;
clause_3:;
    call_7 = own_own_increment(counter_8);
    counter_9 = call_7.t1;
    switch_ = counter_9;
    goto switch_next_1;
switch_next_1:;
    counter_10 = switch_;
    own_own_drop(counter_10);
    return;
}

void own_own_multipleMatches(void) {
    int32_t first_;
    int32_t second_;
    int32_t call_8;
    int32_t call_9;
    char switch_1;
    char switch_2;
    call_8 = own_own_create(1);
    first_ = call_8;
    call_9 = own_own_create(2);
    second_ = call_9;
    switch (1) {
        default:
            goto clause_2;
    }
clause_2:;
    own_own_drop(first_);
    switch_1 = 0;
    goto switch_next_1;
switch_next_1:;
    switch (2) {
        default:
            goto clause_4;
    }
clause_4:;
    own_own_drop(second_);
    switch_2 = 0;
    goto switch_next_3;
switch_next_3:;
    return;
}

void own_own_nestedMatches(void) {
    int32_t root_;
    int32_t inner_;
    int32_t call_10;
    char switch_3;
    int32_t call_11;
    char switch_4;
    call_10 = own_own_create(1);
    root_ = call_10;
    switch (1) {
        default:
            goto clause_2;
    }
clause_2:;
    call_11 = own_own_create(2);
    inner_ = call_11;
    switch (2) {
        default:
            goto clause_4;
    }
clause_4:;
    own_own_drop(inner_);
    own_own_drop(root_);
    switch_4 = 0;
    goto switch_next_3;
switch_next_3:;
    switch_3 = 0;
    goto switch_next_1;
switch_next_1:;
    return;
}

struct Int32Cons const *own_own_loopCase_acquireMany_go(int32_t n_6, struct Int32Cons const *acc_, int32_t i_) {
    struct Int32Cons const *if_;
    struct Int32Cons const *list_;
    int32_t call_12;
    if ((i_ < n_6)) {
        goto then_2;
    } else {
        goto else_3;
    }
then_2:;
    call_12 = own_own_create(i_);
    list_ = ((struct Int32Cons const *)milone_region_alloc(1, sizeof(struct Int32Cons)));
    (*(((struct Int32Cons *)list_))) = (struct Int32Cons){.head = call_12, .tail = acc_};
    if_ = list_;
    goto if_next_1;
else_3:;
    if_ = acc_;
    goto if_next_1;
if_next_1:;
    return if_;
}

struct Int32Cons const *own_own_loopCase_acquireMany(int32_t n_6) {
    struct Int32Cons const *call_13;
    call_13 = own_own_loopCase_acquireMany_go(n_6, NULL, 0);
    return call_13;
}

void own_own_genericWrapperCase(void) {
    struct String w_;
    struct String value_;
    w_ = (struct String){.ptr = "contents", .len = 8};
    value_ = w_;
    if ((string_compare(value_, (struct String){.ptr = "contents", .len = 8}) != 0)) milone_assert_error("own/own.milone", 93, 2);
    return;
}

void own_own_genericOwnCase(void) {
    struct Int32Int32Tuple2_ Own_;
    struct Int32Int32Tuple2_ l_;
    int32_t x_;
    int32_t y_;
    struct Int32Int32Tuple2_ Int32Int32Tuple2_1;
    bool if_1;
    Int32Int32Tuple2_1 = (struct Int32Int32Tuple2_){.t0 = 2, .t1 = 3};
    Own_ = Int32Int32Tuple2_1;
    l_ = Own_;
    x_ = l_.t0;
    y_ = l_.t1;
    if ((x_ == 2)) {
        goto then_2;
    } else {
        goto else_3;
    }
then_2:;
    if_1 = (y_ == 3);
    goto if_next_1;
else_3:;
    if_1 = false;
    goto if_next_1;
if_next_1:;
    if ((!(if_1))) milone_assert_error("own/own.milone", 102, 2);
    return;
}

int32_t own_own_Int32Int32Fun1Int32Int32Fun2_ownMap(struct Int32Int32Fun1 mapping_, int32_t l_1) {
    int32_t l_2;
    int32_t app_;
    l_2 = l_1;
    app_ = mapping_.fun(mapping_.env, l_2);
    return app_;
}

int32_t own_own_genericOwnFunCase_fun(int32_t x_1) {
    return (x_1 + 1);
}

int32_t own_own_eta2_genericOwnFunCase_fun(void const *env_, int32_t arg_) {
    int32_t call_14;
    call_14 = own_own_genericOwnFunCase_fun(arg_);
    return call_14;
}

void own_own_genericOwnFunCase(void) {
    int32_t l_3;
    int32_t l_4;
    int32_t n_7;
    struct Int32Int32Fun1 fun_;
    int32_t call_15;
    fun_ = (struct Int32Int32Fun1){.fun = own_own_eta2_genericOwnFunCase_fun, .env = NULL};
    call_15 = own_own_Int32Int32Fun1Int32Int32Fun2_ownMap(fun_, 2);
    l_3 = call_15;
    l_4 = l_3;
    n_7 = l_4;
    if ((n_7 != 3)) milone_assert_error("own/own.milone", 115, 2);
    return;
}

void own_own_optionOfOwnCase(void) {
    struct Int32Int32Tuple2option1_ ownOpt_;
    struct Int32Int32Tuple2_ l_5;
    int32_t x_2;
    int32_t y_1;
    struct Int32Int32Tuple2_ Int32Int32Tuple2_2;
    struct Int32Int32Tuple2option1_ variant_;
    char match_;
    bool if_2;
    Int32Int32Tuple2_2 = (struct Int32Int32Tuple2_){.t0 = 5, .t1 = 7};
    variant_ = (struct Int32Int32Tuple2option1_){.discriminant = Int32Int32Tuple2option1_Some, .Int32Int32Tuple2option1_Some = Int32Int32Tuple2_2};
    ownOpt_ = variant_;
    if ((ownOpt_.discriminant != Int32Int32Tuple2option1_Some)) goto next_2;
    l_5 = ownOpt_.Int32Int32Tuple2option1_Some;
    x_2 = l_5.t0;
    y_1 = l_5.t1;
    if ((x_2 == 5)) {
        goto then_5;
    } else {
        goto else_6;
    }
then_5:;
    if_2 = (y_1 == 3);
    goto if_next_4;
else_6:;
    if_2 = false;
    goto if_next_4;
if_next_4:;
    if ((!(if_2))) milone_assert_error("own/own.milone", 123, 4);
    match_ = 0;
    goto end_match_1;
next_2:;
    if ((ownOpt_.discriminant != Int32Int32Tuple2option1_None)) goto next_3;
    match_ = 0;
    goto end_match_1;
next_3:;
    milone_exhaust_error("own/own.milone", 120, 2);
end_match_1:;
    return;
}

void own_own_nestedOwnCase(void) {
    int32_t nested_;
    int32_t unwrapped_;
    nested_ = 2;
    unwrapped_ = nested_;
    return;
}

void own_own_counterWrapperCase(void) {
    int32_t w_1;
    int32_t c_1;
    int32_t call_16;
    call_16 = own_own_create(0);
    w_1 = call_16;
    c_1 = w_1;
    own_own_drop(c_1);
    return;
}

int main(int argc, char **argv) {
    milone_start(argc, argv);
    own_own_acquireAndThenDispose();
    own_own_acquireAndUse();
    own_own_transfer();
    own_own_branchCase();
    own_own_multipleMatches();
    own_own_nestedMatches();
    own_own_genericWrapperCase();
    own_own_genericOwnCase();
    own_own_genericOwnFunCase();
    own_own_nestedOwnCase();
    own_own_counterWrapperCase();
    return 0;
}
