#include <stdio.h>
#include <stdlib.h>
#include <milone.h>

struct IntList;

struct IntList;

int fun_pipeline_operator_fun_pipeline_operator_inc(int x_);

int fun_pipeline_operator_fun_pipeline_operator_twice(int x_1);

int fun_pipeline_operator_fun_pipeline_operator_sub(int x_2, int y_);

bool fun_pipeline_operator_fun_pipeline_operator_between(int l_, int r_, int x_3);

int fun_pipeline_operator_fun_pipeline_operator_main_len(struct IntList const* xs_);

int main(int argc, char** argv);

struct IntList {
    int head;
    struct IntList const* tail;
};

int fun_pipeline_operator_fun_pipeline_operator_inc(int x_) {
    return (x_ + 1);
}

int fun_pipeline_operator_fun_pipeline_operator_twice(int x_1) {
    return (x_1 * x_1);
}

int fun_pipeline_operator_fun_pipeline_operator_sub(int x_2, int y_) {
    return (x_2 - y_);
}

bool fun_pipeline_operator_fun_pipeline_operator_between(int l_, int r_, int x_3) {
    bool if_;
    if ((x_3 >= l_)) {
        goto then_2;
    } else {
        goto else_3;
    }
then_2:;
    if_ = (x_3 < r_);
    goto if_next_1;
else_3:;
    if_ = false;
    goto if_next_1;
if_next_1:;
    return if_;
}

int fun_pipeline_operator_fun_pipeline_operator_main_len(struct IntList const* xs_) {
    int if_1;
    if ((!(xs_))) {
        goto nil_cl_5;
    } else {
        goto cons_cl_6;
    }
nil_cl_5:;
    if_1 = 0;
    goto if_next_4;
cons_cl_6:;
    if_1 = 1;
    goto if_next_4;
if_next_4:;
    return if_1;
}

int main(int argc, char** argv) {
    milone_start(argc, argv);
    int n_;
    int call_;
    int call_1;
    int call_2;
    int call_3;
    bool call_4;
    struct IntList const* list_;
    int call_5;
    call_ = fun_pipeline_operator_fun_pipeline_operator_inc(1);
    call_1 = fun_pipeline_operator_fun_pipeline_operator_twice(call_);
    call_2 = fun_pipeline_operator_fun_pipeline_operator_twice(call_1);
    n_ = call_2;
    milone_assert((n_ == 16), (struct String){.ptr = "fun_pipeline_operator/fun_pipeline_operator.milone", .len = 50}, 9, 2);
    call_3 = fun_pipeline_operator_fun_pipeline_operator_sub(100, 98);
    call_4 = fun_pipeline_operator_fun_pipeline_operator_between(2, 3, call_3);
    milone_assert(call_4, (struct String){.ptr = "fun_pipeline_operator/fun_pipeline_operator.milone", .len = 50}, 11, 2);
    list_ = ((struct IntList const*)milone_region_alloc(1, sizeof(struct IntList)));
    (*(((struct IntList*)list_))) = (struct IntList){.head = 1, .tail = NULL};
    call_5 = fun_pipeline_operator_fun_pipeline_operator_main_len(list_);
    milone_assert((call_5 != 0), (struct String){.ptr = "fun_pipeline_operator/fun_pipeline_operator.milone", .len = 50}, 19, 2);
    return 0;
}
