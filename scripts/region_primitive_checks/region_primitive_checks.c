#include "milone.h"

struct IntList;

struct IntList* produce_(struct IntList* acc_, int t_, int i_);

int consume_(int h_, struct IntList* xs_);

int stress_(int i_1);

int fun_(int i_2, int arg_11);

struct IntTuple1;

int fun_2(void* env_, int arg_);

struct UnitIntFun1;

int go_(int h_1, int i_2);

int fun_1(int arg_14);

int fun_3(void* env_1, int arg_2);

int main();

struct IntList {
    int head;
    struct IntList* tail;
};

struct IntList* produce_(struct IntList* acc_, int t_, int i_) {
tailrec_1:;
    int if_;
    if ((t_ == 1)) {
        goto then_3;
    } else {
        goto else_4;
    }
then_3:;
    if_ = (0 >= i_);
    goto if_next_2;
else_4:;
    if_ = 0;
    goto if_next_2;
if_next_2:;
    struct IntList* if_1;
    if (if_) {
        goto then_6;
    } else {
        goto else_7;
    }
then_6:;
    if_1 = acc_;
    goto if_next_5;
else_7:;
    struct IntList* if_2;
    if (((t_ % 2) == 0)) {
        goto then_9;
    } else {
        goto else_10;
    }
then_9:;
    struct IntList* list_ = (struct IntList*)milone_mem_alloc(1, sizeof(struct IntList));
    list_->head = i_;
    list_->tail = acc_;
    struct IntList* arg_3 = list_;
    int arg_4 = (t_ / 2);
    int arg_5 = (i_ - 1);
    acc_ = arg_3;
    t_ = arg_4;
    i_ = arg_5;
    goto tailrec_1;
    if_2 = NULL;
    goto if_next_8;
else_10:;
    struct IntList* list_1 = (struct IntList*)milone_mem_alloc(1, sizeof(struct IntList));
    list_1->head = i_;
    list_1->tail = acc_;
    struct IntList* arg_6 = list_1;
    int arg_7 = ((t_ * 3) + 1);
    int arg_8 = (i_ - 1);
    acc_ = arg_6;
    t_ = arg_7;
    i_ = arg_8;
    goto tailrec_1;
    if_2 = NULL;
    goto if_next_8;
if_next_8:;
    if_1 = if_2;
    goto if_next_5;
if_next_5:;
    return if_1;
}

int consume_(int h_, struct IntList* xs_) {
tailrec_11:;
    int match_;
    if ((!((!(xs_))))) goto next_13;
    match_ = h_;
    goto end_match_12;
next_13:;
    if ((!(xs_))) goto next_14;
    int x_ = xs_->head;
    struct IntList* xs_1 = xs_->tail;
    int arg_9 = (h_ + x_);
    struct IntList* arg_10 = xs_1;
    h_ = arg_9;
    xs_ = arg_10;
    goto tailrec_11;
    match_ = 0;
    goto end_match_12;
next_14:;
    exit(1);
end_match_12:;
    return match_;
}

int stress_(int i_1) {
    struct IntList* call_ = produce_(NULL, i_1, i_1);
    int call_1 = consume_(i_1, call_);
    return call_1;
}

int fun_(int i_2, int arg_11) {
    int call_2 = stress_(i_2);
    return call_2;
}

struct IntTuple1 {
    int t0;
};

int fun_2(void* env_, int arg_) {
    int arg_1 = (*(((struct IntTuple1*)env_))).t0;
    int call_3 = fun_(arg_1, 0);
    return call_3;
}

struct UnitIntFun1 {
    int(*fun)(void*, int);
    void* env;
};

int go_(int h_1, int i_2) {
tailrec_15:;
    int if_3;
    if ((i_2 == 0)) {
        goto then_17;
    } else {
        goto else_18;
    }
then_17:;
    if_3 = h_1;
    goto if_next_16;
else_18:;
    printf("go i=%d\n", i_2);
    struct IntTuple1 tuple_;
    tuple_.t0 = i_2;
    void* box_ = (void*)milone_mem_alloc(1, sizeof(struct IntTuple1));
    (*(((struct IntTuple1*)box_))) = tuple_;
    void* env_2 = box_;
    struct UnitIntFun1 fun_4 = (struct UnitIntFun1){.fun = fun_2, .env = env_2};
    milone_enter_region();
    int region_result_ = fun_4.fun(fun_4.env, 0);
    milone_leave_region();
    int h_2 = (h_1 + region_result_);
    int arg_12 = h_2;
    int arg_13 = (i_2 - 1);
    h_1 = arg_12;
    i_2 = arg_13;
    goto tailrec_15;
    if_3 = 0;
    goto if_next_16;
if_next_16:;
    return if_3;
}

int fun_1(int arg_14) {
    int call_4 = go_(0, 10);
    return ((call_4 % 100) - 84);
}

int fun_3(void* env_1, int arg_2) {
    int call_5 = fun_1(0);
    return call_5;
}

int main() {
    void* box_1 = (void*)milone_mem_alloc(1, sizeof(int));
    (*(((int*)box_1))) = 0;
    void* env_3 = box_1;
    struct UnitIntFun1 fun_5 = (struct UnitIntFun1){.fun = fun_3, .env = env_3};
    milone_enter_region();
    int region_result_1 = fun_5.fun(fun_5.env, 0);
    milone_leave_region();
    return region_result_1;
}
