#include <stdio.h>
#include <stdlib.h>
#include <milone.h>

struct Int32Cons;

struct Int32Cons;

int32_t fun_pipeline_operator_fun_pipeline_operator_inc(int32_t x_);

int32_t fun_pipeline_operator_fun_pipeline_operator_twice(int32_t x_1);

int32_t fun_pipeline_operator_fun_pipeline_operator_sub(int32_t x_2, int32_t y_);

bool fun_pipeline_operator_fun_pipeline_operator_between(int32_t l_, int32_t r_, int32_t x_3);

int32_t fun_pipeline_operator_fun_pipeline_operator_main_len(struct Int32Cons const *xs_);

int main(int argc, char **argv);

struct Int32Cons {
    int32_t head;
    struct Int32Cons const *tail;
};

int32_t fun_pipeline_operator_fun_pipeline_operator_inc(int32_t x_) {
    return (x_ + 1);
}

int32_t fun_pipeline_operator_fun_pipeline_operator_twice(int32_t x_1) {
    return (x_1 * x_1);
}

int32_t fun_pipeline_operator_fun_pipeline_operator_sub(int32_t x_2, int32_t y_) {
    return (x_2 - y_);
}

bool fun_pipeline_operator_fun_pipeline_operator_between(int32_t l_, int32_t r_, int32_t x_3) {
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

int32_t fun_pipeline_operator_fun_pipeline_operator_main_len(struct Int32Cons const *xs_) {
    int32_t if_1;
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

int main(int argc, char **argv) {
    milone_start(argc, argv);
    int32_t n_;
    int32_t call_;
    int32_t call_1;
    int32_t call_2;
    int32_t call_3;
    bool call_4;
    struct Int32Cons const *list_;
    int32_t call_5;
    call_ = fun_pipeline_operator_fun_pipeline_operator_inc(1);
    call_1 = fun_pipeline_operator_fun_pipeline_operator_twice(call_);
    call_2 = fun_pipeline_operator_fun_pipeline_operator_twice(call_1);
    n_ = call_2;
    if ((n_ != 16)) milone_assert_error("fun_pipeline_operator/fun_pipeline_operator.milone", 9, 2);
    call_3 = fun_pipeline_operator_fun_pipeline_operator_sub(100, 98);
    call_4 = fun_pipeline_operator_fun_pipeline_operator_between(2, 3, call_3);
    if ((!(call_4))) milone_assert_error("fun_pipeline_operator/fun_pipeline_operator.milone", 11, 2);
    list_ = ((struct Int32Cons const *)milone_region_alloc(1, sizeof(struct Int32Cons)));
    (*(((struct Int32Cons *)list_))) = (struct Int32Cons){.head = 1, .tail = NULL};
    call_5 = fun_pipeline_operator_fun_pipeline_operator_main_len(list_);
    if ((call_5 == 0)) milone_assert_error("fun_pipeline_operator/fun_pipeline_operator.milone", 19, 2);
    return 0;
}
