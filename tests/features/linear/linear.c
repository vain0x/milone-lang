#include <stdio.h>
#include <stdlib.h>
#include <milone.h>

typedef int32_t(*VoidConstPtrInt32Int32FunPtr2)(void const *, int32_t);

struct Int32Int32Fun1;

struct Int32Int32Tuple2_;

struct Int32Cons;

struct Int32Cons;

struct Int32Int32Tuple2option1_;

int32_t linear_linear_Int32Int32Fun1Int32Int32Fun2_linearMap(struct Int32Int32Fun1 mapping_, int32_t l_1);

int32_t linear_linear_create(int32_t init_);

struct Int32Int32Tuple2_ linear_linear_increment(int32_t counter_);

void linear_linear_drop(int32_t counter_1);

void linear_linear_acquireAndThenDispose(void);

void linear_linear_acquireAndUse(void);

void linear_linear_transfer(void);

void linear_linear_branchCase(void);

void linear_linear_multipleMatches(void);

void linear_linear_nestedMatches(void);

struct Int32Cons const *linear_linear_loopCase_acquireMany_go(int32_t n_6, struct Int32Cons const *acc_, int32_t i_);

struct Int32Cons const *linear_linear_loopCase_acquireMany(int32_t n_6);

void linear_linear_genericWrapperCase(void);

void linear_linear_genericLinearCase(void);

int32_t linear_linear_genericLinearFunCase_fun(int32_t x_1);

int32_t linear_linear_eta2_genericLinearFunCase_fun(void const *env_, int32_t arg_);

void linear_linear_genericLinearFunCase(void);

void linear_linear_optionOfLinearCase(void);

void linear_linear_nestedLinearCase(void);

void linear_linear_linearWrapperCase(void);

int main(int argc, char **argv);

struct Int32Int32Fun1 {
    VoidConstPtrInt32Int32FunPtr2 fun;
    void const *env;
};

struct Int32Int32Tuple2_ {
    int32_t t0;
    int32_t t1;
};

struct Int32Cons {
    int32_t head;
    struct Int32Cons const *tail;
};

enum Int32Int32Tuple2option1_Discriminant {
    None_,
    Some_,
};

struct Int32Int32Tuple2option1_ {
    enum Int32Int32Tuple2option1_Discriminant discriminant;
    union {
        struct Int32Int32Tuple2_ Some_;
    };
};

int32_t linear_linear_Int32Int32Fun1Int32Int32Fun2_linearMap(struct Int32Int32Fun1 mapping_, int32_t l_1) {
    int32_t l_2;
    int32_t app_;
    l_2 = l_1;
    app_ = mapping_.fun(mapping_.env, l_2);
    return app_;
}

int32_t linear_linear_create(int32_t init_) {
    return init_;
}

struct Int32Int32Tuple2_ linear_linear_increment(int32_t counter_) {
    int32_t n_;
    int32_t n_1;
    struct Int32Int32Tuple2_ Int32Int32Tuple2_;
    n_ = counter_;
    n_1 = (n_ + 1);
    Int32Int32Tuple2_ = (struct Int32Int32Tuple2_){.t0 = n_1, .t1 = n_1};
    return Int32Int32Tuple2_;
}

void linear_linear_drop(int32_t counter_1) {
    int32_t n_2;
    n_2 = counter_1;
    return;
}

void linear_linear_acquireAndThenDispose(void) {
    int32_t counter_2;
    int32_t call_;
    call_ = linear_linear_create(0);
    counter_2 = call_;
    linear_linear_drop(counter_2);
    return;
}

void linear_linear_acquireAndUse(void) {
    int32_t counter_3;
    int32_t n_3;
    int32_t counter_4;
    int32_t n_4;
    int32_t counter_5;
    int32_t call_1;
    struct Int32Int32Tuple2_ call_2;
    struct Int32Int32Tuple2_ call_3;
    call_1 = linear_linear_create(0);
    counter_3 = call_1;
    call_2 = linear_linear_increment(counter_3);
    n_3 = call_2.t0;
    counter_4 = call_2.t1;
    if ((n_3 != 1)) milone_assert_error("linear/linear.milone", 24, 2);
    call_3 = linear_linear_increment(counter_4);
    n_4 = call_3.t0;
    counter_5 = call_3.t1;
    linear_linear_drop(counter_5);
    return;
}

void linear_linear_transfer(void) {
    int32_t counter_6;
    int32_t other_;
    int32_t call_4;
    call_4 = linear_linear_create(0);
    counter_6 = call_4;
    other_ = counter_6;
    linear_linear_drop(other_);
    return;
}

void linear_linear_branchCase(void) {
    int32_t counter_7;
    int32_t n_5;
    int32_t counter_8;
    int32_t counter_9;
    int32_t counter_10;
    int32_t call_5;
    struct Int32Int32Tuple2_ call_6;
    int32_t switch_;
    struct Int32Int32Tuple2_ call_7;
    call_5 = linear_linear_create(0);
    counter_7 = call_5;
    call_6 = linear_linear_increment(counter_7);
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
    call_7 = linear_linear_increment(counter_8);
    counter_9 = call_7.t1;
    switch_ = counter_9;
    goto switch_next_1;
switch_next_1:;
    counter_10 = switch_;
    linear_linear_drop(counter_10);
    return;
}

void linear_linear_multipleMatches(void) {
    int32_t first_;
    int32_t second_;
    int32_t call_8;
    int32_t call_9;
    char switch_1;
    char switch_2;
    call_8 = linear_linear_create(1);
    first_ = call_8;
    call_9 = linear_linear_create(2);
    second_ = call_9;
    switch (1) {
        default:
            goto clause_5;
    }
clause_5:;
    linear_linear_drop(first_);
    switch_1 = 0;
    goto switch_next_4;
switch_next_4:;
    switch (2) {
        default:
            goto clause_7;
    }
clause_7:;
    linear_linear_drop(second_);
    switch_2 = 0;
    goto switch_next_6;
switch_next_6:;
    return;
}

void linear_linear_nestedMatches(void) {
    int32_t root_;
    int32_t inner_;
    int32_t call_10;
    char switch_3;
    int32_t call_11;
    char switch_4;
    call_10 = linear_linear_create(1);
    root_ = call_10;
    switch (1) {
        default:
            goto clause_9;
    }
clause_9:;
    call_11 = linear_linear_create(2);
    inner_ = call_11;
    switch (2) {
        default:
            goto clause_11;
    }
clause_11:;
    linear_linear_drop(inner_);
    linear_linear_drop(root_);
    switch_4 = 0;
    goto switch_next_10;
switch_next_10:;
    switch_3 = 0;
    goto switch_next_8;
switch_next_8:;
    return;
}

struct Int32Cons const *linear_linear_loopCase_acquireMany_go(int32_t n_6, struct Int32Cons const *acc_, int32_t i_) {
    struct Int32Cons const *if_;
    struct Int32Cons const *list_;
    int32_t call_12;
    if ((i_ < n_6)) {
        goto then_13;
    } else {
        goto else_14;
    }
then_13:;
    call_12 = linear_linear_create(i_);
    list_ = ((struct Int32Cons const *)milone_region_alloc(1, sizeof(struct Int32Cons)));
    (*(((struct Int32Cons *)list_))) = (struct Int32Cons){.head = call_12, .tail = acc_};
    if_ = list_;
    goto if_next_12;
else_14:;
    if_ = acc_;
    goto if_next_12;
if_next_12:;
    return if_;
}

struct Int32Cons const *linear_linear_loopCase_acquireMany(int32_t n_6) {
    struct Int32Cons const *call_13;
    call_13 = linear_linear_loopCase_acquireMany_go(n_6, NULL, 0);
    return call_13;
}

void linear_linear_genericWrapperCase(void) {
    struct String w_;
    struct String value_;
    w_ = (struct String){.ptr = "contents", .len = 8};
    value_ = w_;
    if ((string_compare(value_, (struct String){.ptr = "contents", .len = 8}) != 0)) milone_assert_error("linear/linear.milone", 91, 2);
    return;
}

void linear_linear_genericLinearCase(void) {
    struct Int32Int32Tuple2_ linear_;
    struct Int32Int32Tuple2_ l_;
    int32_t x_;
    int32_t y_;
    struct Int32Int32Tuple2_ Int32Int32Tuple2_1;
    bool if_1;
    Int32Int32Tuple2_1 = (struct Int32Int32Tuple2_){.t0 = 2, .t1 = 3};
    linear_ = Int32Int32Tuple2_1;
    l_ = linear_;
    x_ = l_.t0;
    y_ = l_.t1;
    if ((x_ == 2)) {
        goto then_16;
    } else {
        goto else_17;
    }
then_16:;
    if_1 = (y_ == 3);
    goto if_next_15;
else_17:;
    if_1 = false;
    goto if_next_15;
if_next_15:;
    if ((!(if_1))) milone_assert_error("linear/linear.milone", 100, 2);
    return;
}

int32_t linear_linear_genericLinearFunCase_fun(int32_t x_1) {
    return (x_1 + 1);
}

int32_t linear_linear_eta2_genericLinearFunCase_fun(void const *env_, int32_t arg_) {
    int32_t call_14;
    call_14 = linear_linear_genericLinearFunCase_fun(arg_);
    return call_14;
}

void linear_linear_genericLinearFunCase(void) {
    int32_t l_3;
    int32_t l_4;
    int32_t n_7;
    struct Int32Int32Fun1 fun_;
    int32_t call_15;
    fun_ = (struct Int32Int32Fun1){.fun = linear_linear_eta2_genericLinearFunCase_fun, .env = NULL};
    call_15 = linear_linear_Int32Int32Fun1Int32Int32Fun2_linearMap(fun_, 2);
    l_3 = call_15;
    l_4 = l_3;
    n_7 = l_4;
    if ((n_7 != 3)) milone_assert_error("linear/linear.milone", 113, 2);
    return;
}

void linear_linear_optionOfLinearCase(void) {
    struct Int32Int32Tuple2option1_ linearOpt_;
    struct Int32Int32Tuple2_ l_5;
    int32_t x_2;
    int32_t y_1;
    struct Int32Int32Tuple2_ Int32Int32Tuple2_2;
    struct Int32Int32Tuple2option1_ variant_;
    char match_;
    bool if_2;
    Int32Int32Tuple2_2 = (struct Int32Int32Tuple2_){.t0 = 5, .t1 = 7};
    variant_ = (struct Int32Int32Tuple2option1_){.discriminant = Some_, .Some_ = Int32Int32Tuple2_2};
    linearOpt_ = variant_;
    if ((linearOpt_.discriminant != Some_)) goto next_19;
    l_5 = linearOpt_.Some_;
    x_2 = l_5.t0;
    y_1 = l_5.t1;
    if ((x_2 == 5)) {
        goto then_22;
    } else {
        goto else_23;
    }
then_22:;
    if_2 = (y_1 == 3);
    goto if_next_21;
else_23:;
    if_2 = false;
    goto if_next_21;
if_next_21:;
    if ((!(if_2))) milone_assert_error("linear/linear.milone", 121, 4);
    match_ = 0;
    goto end_match_18;
next_19:;
    if ((linearOpt_.discriminant != None_)) goto next_20;
    match_ = 0;
    goto end_match_18;
next_20:;
    exit(1);
end_match_18:;
    return;
}

void linear_linear_nestedLinearCase(void) {
    int32_t nested_;
    int32_t unwrapped_;
    nested_ = 2;
    unwrapped_ = nested_;
    return;
}

void linear_linear_linearWrapperCase(void) {
    int32_t w_1;
    int32_t c_1;
    int32_t call_16;
    call_16 = linear_linear_create(0);
    w_1 = call_16;
    c_1 = w_1;
    linear_linear_drop(c_1);
    return;
}

int main(int argc, char **argv) {
    milone_start(argc, argv);
    linear_linear_acquireAndThenDispose();
    linear_linear_acquireAndUse();
    linear_linear_transfer();
    linear_linear_branchCase();
    linear_linear_multipleMatches();
    linear_linear_nestedMatches();
    linear_linear_genericWrapperCase();
    linear_linear_genericLinearCase();
    linear_linear_genericLinearFunCase();
    linear_linear_nestedLinearCase();
    linear_linear_linearWrapperCase();
    return 0;
}
