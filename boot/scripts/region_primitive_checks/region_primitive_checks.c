#include "milone.h"

struct IntList;

struct IntList* produce_(struct IntList* acc_, int t_, int i_);

int consume_(int h_, struct IntList* xs_);

int stress_(int i_1);

int fun_(int i_2, int arg_3);

struct IntTuple1;

int fun_2(void* env_, int arg_);

struct UnitIntFun1;

int go_(int h_1, int i_2);

int fun_1(int arg_4);

int fun_3(void* env_1, int arg_2);

int main();

struct IntList {
    int head;
    struct IntList* tail;
};

struct IntList* produce_(struct IntList* acc_, int t_, int i_) {
    struct IntList* match_;
    int match_1;
    if ((t_ != 1)) goto next_3;
    match_1 = (0 >= i_);
    goto end_match_2;
next_3:;
    if ((t_ == 1)) goto next_4;
    match_1 = 0;
    goto end_match_2;
next_4:;
    exit(1);
end_match_2:;
    if ((!(match_1))) goto next_5;
    match_ = acc_;
    goto end_match_1;
next_5:;
    if (match_1) goto next_6;
    struct IntList* match_2;
    if (((t_ % 2) != 0)) goto next_8;
    struct IntList* list_ = (struct IntList*)milone_mem_alloc(1, sizeof(struct IntList));
    list_->head = i_;
    list_->tail = acc_;
    struct IntList* call_ = produce_(list_, (t_ / 2), (i_ - 1));
    match_2 = call_;
    goto end_match_7;
next_8:;
    if (((t_ % 2) == 0)) goto next_9;
    struct IntList* list_1 = (struct IntList*)milone_mem_alloc(1, sizeof(struct IntList));
    list_1->head = i_;
    list_1->tail = acc_;
    struct IntList* call_1 = produce_(list_1, ((t_ * 3) + 1), (i_ - 1));
    match_2 = call_1;
    goto end_match_7;
next_9:;
    exit(1);
end_match_7:;
    match_ = match_2;
    goto end_match_1;
next_6:;
    exit(1);
end_match_1:;
    return match_;
}

int consume_(int h_, struct IntList* xs_) {
    int match_3;
    if ((!((!(xs_))))) goto next_11;
    match_3 = h_;
    goto end_match_10;
next_11:;
    if ((!(xs_))) goto next_12;
    int x_ = xs_->head;
    struct IntList* xs_1 = xs_->tail;
    int call_2 = consume_((h_ + x_), xs_1);
    match_3 = call_2;
    goto end_match_10;
next_12:;
    exit(1);
end_match_10:;
    return match_3;
}

int stress_(int i_1) {
    struct IntList* call_3 = produce_(NULL, i_1, i_1);
    int call_4 = consume_(i_1, call_3);
    return call_4;
}

int fun_(int i_2, int arg_3) {
    int call_5 = stress_(i_2);
    return call_5;
}

struct IntTuple1 {
    int t0;
};

int fun_2(void* env_, int arg_) {
    int arg_1 = (*(((struct IntTuple1*)env_))).t0;
    int call_6 = fun_(arg_1, 0);
    return call_6;
}

struct UnitIntFun1 {
    int(*fun)(void*, int);
    void* env;
};

int go_(int h_1, int i_2) {
    int match_4;
    if ((i_2 != 0)) goto next_14;
    match_4 = h_1;
    goto end_match_13;
next_14:;
    if ((i_2 == 0)) goto next_15;
    printf("go i=%d\n", i_2);
    int call_7 = 0;
    struct IntTuple1 tuple_;
    tuple_.t0 = i_2;
    void* box_ = (void*)milone_mem_alloc(1, sizeof(struct IntTuple1));
    (*(((struct IntTuple1*)box_))) = tuple_;
    void* env_2 = box_;
    struct UnitIntFun1 fun_4 = (struct UnitIntFun1){.fun = fun_2, .env = env_2};
    milone_enter_region();
    int call_8 = fun_4.fun(fun_4.env, 0);
    milone_leave_region();
    int h_2 = (h_1 + call_8);
    int call_9 = go_(h_2, (i_2 - 1));
    match_4 = call_9;
    goto end_match_13;
next_15:;
    exit(1);
end_match_13:;
    return match_4;
}

int fun_1(int arg_4) {
    int call_10 = go_(0, 10);
    return (call_10 % 100);
}

int fun_3(void* env_1, int arg_2) {
    int call_11 = fun_1(0);
    return call_11;
}

int main() {
    void* box_1 = (void*)milone_mem_alloc(1, sizeof(int));
    (*(((int*)box_1))) = 0;
    void* env_3 = box_1;
    struct UnitIntFun1 fun_5 = (struct UnitIntFun1){.fun = fun_3, .env = env_3};
    milone_enter_region();
    int call_12 = fun_5.fun(fun_5.env, 0);
    milone_leave_region();
    return call_12;
}
