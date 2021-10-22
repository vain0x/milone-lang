#include "milone.h"

struct IntList;

struct IntList;

int fun_pipeline_operator_Program_inc(int x_);

int fun_pipeline_operator_Program_twice(int x_1);

int fun_pipeline_operator_Program_sub(int x_2, int y_);

bool fun_pipeline_operator_Program_between(int l_, int r_, int x_3);

int fun_pipeline_operator_fun_pipeline_operator_main_len(struct IntList const* xs_);

int milone_main(void);

struct IntList {
    int head;
    struct IntList const* tail;
};

int fun_pipeline_operator_Program_inc(int x_) {
    return (x_ + 1);
}

int fun_pipeline_operator_Program_twice(int x_1) {
    return (x_1 * x_1);
}

int fun_pipeline_operator_Program_sub(int x_2, int y_) {
    return (x_2 - y_);
}

bool fun_pipeline_operator_Program_between(int l_, int r_, int x_3) {
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

int milone_main(void) {
    int call_ = fun_pipeline_operator_Program_inc(1);
    int call_1 = fun_pipeline_operator_Program_twice(call_);
    int call_2 = fun_pipeline_operator_Program_twice(call_1);
    int n_ = call_2;
    milone_assert((n_ == 16), 9, 2);
    int call_3 = fun_pipeline_operator_Program_sub(100, 98);
    bool call_4 = fun_pipeline_operator_Program_between(2, 3, call_3);
    milone_assert(call_4, 11, 2);
    struct IntList const* list_ = milone_mem_alloc(1, sizeof(struct IntList));
    (*(((struct IntList*)list_))) = (struct IntList){.head = 1, .tail = NULL};
    int call_5 = fun_pipeline_operator_fun_pipeline_operator_main_len(list_);
    milone_assert((call_5 != 0), 19, 2);
    return 0;
}
