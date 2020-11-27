#include "milone.h"

struct F64BoolFun1;

struct F64List;

int go_1(struct F64BoolFun1 pred_, struct F64List* xs_1);

int all_1(struct F64BoolFun1 pred_, struct F64List* xs_);

int fun_(double x_1);

int fun_2(void* env_, double arg_);

int fun_1(double x_2);

int fun_3(void* env_1, double arg_1);

int main();

struct F64BoolFun1 {
    int(*fun)(void*, double);
    void* env;
};

struct F64List {
    double head;
    struct F64List* tail;
};

int go_1(struct F64BoolFun1 pred_, struct F64List* xs_1) {
tailrec_1:;
    int match_;
    if ((!((!(xs_1))))) goto next_3;
    match_ = 1;
    goto end_match_2;
next_3:;
    if ((!(xs_1))) goto next_4;
    double x_ = xs_1->head;
    struct F64List* xs_2 = xs_1->tail;
    int app_ = pred_.fun(pred_.env, x_);
    int if_;
    if (app_) {
        goto then_6;
    } else {
        goto else_7;
    }
then_6:;
    struct F64BoolFun1 arg_2 = pred_;
    struct F64List* arg_3 = xs_2;
    pred_ = arg_2;
    xs_1 = arg_3;
    goto tailrec_1;
    if_ = 0;
    goto if_next_5;
else_7:;
    if_ = 0;
    goto if_next_5;
if_next_5:;
    match_ = if_;
    goto end_match_2;
next_4:;
    exit(1);
end_match_2:;
    return match_;
}

int all_1(struct F64BoolFun1 pred_, struct F64List* xs_) {
    int call_ = go_1(pred_, xs_);
    return call_;
}

int fun_(double x_1) {
    return (x_1 == 0.0);
}

int fun_2(void* env_, double arg_) {
    int call_1 = fun_(arg_);
    return call_1;
}

int fun_1(double x_2) {
    return (0.0 < x_2);
}

int fun_3(void* env_1, double arg_1) {
    int call_2 = fun_1(arg_1);
    return call_2;
}

int main() {
    struct F64List* list_7 = (struct F64List*)milone_mem_alloc(1, sizeof(struct F64List));
    list_7->head = 00.00e-00;
    list_7->tail = NULL;
    struct F64List* list_6 = (struct F64List*)milone_mem_alloc(1, sizeof(struct F64List));
    list_6->head = 0E-9;
    list_6->tail = list_7;
    struct F64List* list_5 = (struct F64List*)milone_mem_alloc(1, sizeof(struct F64List));
    list_5->head = 0E+9;
    list_5->tail = list_6;
    struct F64List* list_4 = (struct F64List*)milone_mem_alloc(1, sizeof(struct F64List));
    list_4->head = 0E0;
    list_4->tail = list_5;
    struct F64List* list_3 = (struct F64List*)milone_mem_alloc(1, sizeof(struct F64List));
    list_3->head = 0e0;
    list_3->tail = list_4;
    struct F64List* list_2 = (struct F64List*)milone_mem_alloc(1, sizeof(struct F64List));
    list_2->head = 000.000;
    list_2->tail = list_3;
    struct F64List* list_1 = (struct F64List*)milone_mem_alloc(1, sizeof(struct F64List));
    list_1->head = 0.;
    list_1->tail = list_2;
    struct F64List* list_ = (struct F64List*)milone_mem_alloc(1, sizeof(struct F64List));
    list_->head = 0.0;
    list_->tail = list_1;
    struct F64List* zeros_ = list_;
    void* box_ = (void*)milone_mem_alloc(1, sizeof(int));
    (*(((int*)box_))) = 0;
    void* env_2 = box_;
    struct F64BoolFun1 fun_4 = (struct F64BoolFun1){.fun = fun_2, .env = env_2};
    int call_3 = all_1(fun_4, zeros_);
    milone_assert(call_3, 24, 2);
    struct F64List* list_18 = (struct F64List*)milone_mem_alloc(1, sizeof(struct F64List));
    list_18->head = 6.02e-23;
    list_18->tail = NULL;
    struct F64List* list_17 = (struct F64List*)milone_mem_alloc(1, sizeof(struct F64List));
    list_17->head = 1e-23;
    list_17->tail = list_18;
    struct F64List* list_16 = (struct F64List*)milone_mem_alloc(1, sizeof(struct F64List));
    list_16->head = 1e+23;
    list_16->tail = list_17;
    struct F64List* list_15 = (struct F64List*)milone_mem_alloc(1, sizeof(struct F64List));
    list_15->head = 1E-9;
    list_15->tail = list_16;
    struct F64List* list_14 = (struct F64List*)milone_mem_alloc(1, sizeof(struct F64List));
    list_14->head = 1e-9;
    list_14->tail = list_15;
    struct F64List* list_13 = (struct F64List*)milone_mem_alloc(1, sizeof(struct F64List));
    list_13->head = 1E+9;
    list_13->tail = list_14;
    struct F64List* list_12 = (struct F64List*)milone_mem_alloc(1, sizeof(struct F64List));
    list_12->head = 1e+9;
    list_12->tail = list_13;
    struct F64List* list_11 = (struct F64List*)milone_mem_alloc(1, sizeof(struct F64List));
    list_11->head = 1E9;
    list_11->tail = list_12;
    struct F64List* list_10 = (struct F64List*)milone_mem_alloc(1, sizeof(struct F64List));
    list_10->head = 1e9;
    list_10->tail = list_11;
    struct F64List* list_9 = (struct F64List*)milone_mem_alloc(1, sizeof(struct F64List));
    list_9->head = 42.195;
    list_9->tail = list_10;
    struct F64List* list_8 = (struct F64List*)milone_mem_alloc(1, sizeof(struct F64List));
    list_8->head = 1.0;
    list_8->tail = list_9;
    struct F64List* values_ = list_8;
    void* box_1 = (void*)milone_mem_alloc(1, sizeof(int));
    (*(((int*)box_1))) = 0;
    void* env_3 = box_1;
    struct F64BoolFun1 fun_5 = (struct F64BoolFun1){.fun = fun_3, .env = env_3};
    int call_4 = all_1(fun_5, values_);
    milone_assert(call_4, 39, 2);
    milone_assert((6.0 < (2.3 + 4.5)), 42, 2);
    milone_assert(((44.0 - 2.0) == 42.0), 43, 2);
    milone_assert(((2.25 * 2.0) == 4.5), 44, 2);
    milone_assert(((8.0 / 2.0) == 4.0), 45, 2);
    milone_assert((0.0 == 0.0), 48, 2);
    milone_assert((0.0 != 1.0), 49, 2);
    milone_assert((2.0 < 3.0), 51, 2);
    milone_assert((2.0 >= 2.0), 52, 2);
    milone_assert((3.0 >= 2.0), 53, 2);
    milone_assert((2.0 < 3.0), 55, 2);
    milone_assert((2.0 >= 2.0), 56, 2);
    milone_assert((3.0 >= 2.0), 57, 2);
    milone_assert((((int)3.14) == 3), 60, 2);
    milone_assert((((double)3) == 3.0), 61, 2);
    struct String call_5 = str_of_double(3.14);
    milone_assert((str_cmp(call_5, (struct String){.str = "3.140000", .len = 8}) == 0), 65, 2);
    double call_6 = str_to_double((struct String){.str = "3.14", .len = 4});
    milone_assert((call_6 == 3.14), 68, 2);
    printf("Assume PI is %f.\n", 3.14);
    return 0;
}
