#include <stdio.h>
#include <stdlib.h>
#include <milone.h>

typedef bool(*VoidConstPtrF64BoolFunPtr2)(void const *, double);

struct F64BoolFun1;

struct F64Cons;

struct F64Cons;

bool float_float_F64BoolFun1F64ListBoolFun2_all(struct F64BoolFun1 pred_, struct F64Cons const *xs_);

bool float_float_all_F64BoolFun1F64ListBoolFun2_go(struct F64BoolFun1 pred_, struct F64Cons const *xs_1);

bool float_float_main_fun(double x_1);

bool float_float_eta2_main_fun(void const *env_, double arg_);

bool float_float_main_fun_1(double x_2);

bool float_float_eta2_main_fun_1(void const *env_1, double arg_1);

int main(int argc, char **argv);

struct F64BoolFun1 {
    VoidConstPtrF64BoolFunPtr2 fun;
    void const *env;
};

struct F64Cons {
    double head;
    struct F64Cons const *tail;
};

bool float_float_F64BoolFun1F64ListBoolFun2_all(struct F64BoolFun1 pred_, struct F64Cons const *xs_) {
    bool call_;
    call_ = float_float_all_F64BoolFun1F64ListBoolFun2_go(pred_, xs_);
    return call_;
}

bool float_float_all_F64BoolFun1F64ListBoolFun2_go(struct F64BoolFun1 pred_, struct F64Cons const *xs_1) {
    double x_;
    struct F64Cons const *xs_2;
    bool match_;
    bool app_;
    bool if_;
    struct F64BoolFun1 arg_2;
    struct F64Cons const *arg_3;
tailrec_1:;
    if ((!((!(xs_1))))) goto next_3;
    match_ = true;
    goto end_match_2;
next_3:;
    if ((!(xs_1))) goto next_4;
    x_ = xs_1->head;
    xs_2 = xs_1->tail;
    app_ = pred_.fun(pred_.env, x_);
    if (app_) {
        goto then_6;
    } else {
        goto else_7;
    }
then_6:;
    arg_2 = pred_;
    arg_3 = xs_2;
    pred_ = arg_2;
    xs_1 = arg_3;
    goto tailrec_1;
else_7:;
    if_ = false;
    goto if_next_5;
if_next_5:;
    match_ = if_;
    goto end_match_2;
next_4:;
    exit(1);
end_match_2:;
    return match_;
}

bool float_float_main_fun(double x_1) {
    return (x_1 == 0.0);
}

bool float_float_eta2_main_fun(void const *env_, double arg_) {
    bool call_1;
    call_1 = float_float_main_fun(arg_);
    return call_1;
}

bool float_float_main_fun_1(double x_2) {
    return (0.0 < x_2);
}

bool float_float_eta2_main_fun_1(void const *env_1, double arg_1) {
    bool call_2;
    call_2 = float_float_main_fun_1(arg_1);
    return call_2;
}

int main(int argc, char **argv) {
    milone_start(argc, argv);
    struct F64Cons const *zeros_;
    struct F64Cons const *values_;
    struct F64Cons const *list_;
    struct F64Cons const *list_1;
    struct F64Cons const *list_2;
    struct F64Cons const *list_3;
    struct F64Cons const *list_4;
    struct F64Cons const *list_5;
    struct F64Cons const *list_6;
    struct F64Cons const *list_7;
    struct F64BoolFun1 fun_;
    bool call_3;
    struct F64Cons const *list_8;
    struct F64Cons const *list_9;
    struct F64Cons const *list_10;
    struct F64Cons const *list_11;
    struct F64Cons const *list_12;
    struct F64Cons const *list_13;
    struct F64Cons const *list_14;
    struct F64Cons const *list_15;
    struct F64Cons const *list_16;
    struct F64Cons const *list_17;
    struct F64Cons const *list_18;
    struct F64BoolFun1 fun_1;
    bool call_4;
    struct String call_5;
    double call_6;
    list_7 = ((struct F64Cons const *)milone_region_alloc(1, sizeof(struct F64Cons)));
    (*(((struct F64Cons *)list_7))) = (struct F64Cons){.head = 00.00e-00, .tail = NULL};
    list_6 = ((struct F64Cons const *)milone_region_alloc(1, sizeof(struct F64Cons)));
    (*(((struct F64Cons *)list_6))) = (struct F64Cons){.head = 0E-9, .tail = list_7};
    list_5 = ((struct F64Cons const *)milone_region_alloc(1, sizeof(struct F64Cons)));
    (*(((struct F64Cons *)list_5))) = (struct F64Cons){.head = 0E+9, .tail = list_6};
    list_4 = ((struct F64Cons const *)milone_region_alloc(1, sizeof(struct F64Cons)));
    (*(((struct F64Cons *)list_4))) = (struct F64Cons){.head = 0E0, .tail = list_5};
    list_3 = ((struct F64Cons const *)milone_region_alloc(1, sizeof(struct F64Cons)));
    (*(((struct F64Cons *)list_3))) = (struct F64Cons){.head = 0e0, .tail = list_4};
    list_2 = ((struct F64Cons const *)milone_region_alloc(1, sizeof(struct F64Cons)));
    (*(((struct F64Cons *)list_2))) = (struct F64Cons){.head = 000.000, .tail = list_3};
    list_1 = ((struct F64Cons const *)milone_region_alloc(1, sizeof(struct F64Cons)));
    (*(((struct F64Cons *)list_1))) = (struct F64Cons){.head = 0., .tail = list_2};
    list_ = ((struct F64Cons const *)milone_region_alloc(1, sizeof(struct F64Cons)));
    (*(((struct F64Cons *)list_))) = (struct F64Cons){.head = 0.0, .tail = list_1};
    zeros_ = list_;
    fun_ = (struct F64BoolFun1){.fun = float_float_eta2_main_fun, .env = NULL};
    call_3 = float_float_F64BoolFun1F64ListBoolFun2_all(fun_, zeros_);
    if ((!(call_3))) milone_assert_error("float/float.milone", 24, 2);
    list_18 = ((struct F64Cons const *)milone_region_alloc(1, sizeof(struct F64Cons)));
    (*(((struct F64Cons *)list_18))) = (struct F64Cons){.head = 6.02e-23, .tail = NULL};
    list_17 = ((struct F64Cons const *)milone_region_alloc(1, sizeof(struct F64Cons)));
    (*(((struct F64Cons *)list_17))) = (struct F64Cons){.head = 1e-23, .tail = list_18};
    list_16 = ((struct F64Cons const *)milone_region_alloc(1, sizeof(struct F64Cons)));
    (*(((struct F64Cons *)list_16))) = (struct F64Cons){.head = 1e+23, .tail = list_17};
    list_15 = ((struct F64Cons const *)milone_region_alloc(1, sizeof(struct F64Cons)));
    (*(((struct F64Cons *)list_15))) = (struct F64Cons){.head = 1E-9, .tail = list_16};
    list_14 = ((struct F64Cons const *)milone_region_alloc(1, sizeof(struct F64Cons)));
    (*(((struct F64Cons *)list_14))) = (struct F64Cons){.head = 1e-9, .tail = list_15};
    list_13 = ((struct F64Cons const *)milone_region_alloc(1, sizeof(struct F64Cons)));
    (*(((struct F64Cons *)list_13))) = (struct F64Cons){.head = 1E+9, .tail = list_14};
    list_12 = ((struct F64Cons const *)milone_region_alloc(1, sizeof(struct F64Cons)));
    (*(((struct F64Cons *)list_12))) = (struct F64Cons){.head = 1e+9, .tail = list_13};
    list_11 = ((struct F64Cons const *)milone_region_alloc(1, sizeof(struct F64Cons)));
    (*(((struct F64Cons *)list_11))) = (struct F64Cons){.head = 1E9, .tail = list_12};
    list_10 = ((struct F64Cons const *)milone_region_alloc(1, sizeof(struct F64Cons)));
    (*(((struct F64Cons *)list_10))) = (struct F64Cons){.head = 1e9, .tail = list_11};
    list_9 = ((struct F64Cons const *)milone_region_alloc(1, sizeof(struct F64Cons)));
    (*(((struct F64Cons *)list_9))) = (struct F64Cons){.head = 42.195, .tail = list_10};
    list_8 = ((struct F64Cons const *)milone_region_alloc(1, sizeof(struct F64Cons)));
    (*(((struct F64Cons *)list_8))) = (struct F64Cons){.head = 1.0, .tail = list_9};
    values_ = list_8;
    fun_1 = (struct F64BoolFun1){.fun = float_float_eta2_main_fun_1, .env = NULL};
    call_4 = float_float_F64BoolFun1F64ListBoolFun2_all(fun_1, values_);
    if ((!(call_4))) milone_assert_error("float/float.milone", 39, 2);
    if ((6.0 >= (2.3 + 4.5))) milone_assert_error("float/float.milone", 42, 2);
    if (((44.0 - 2.0) != 42.0)) milone_assert_error("float/float.milone", 43, 2);
    if (((2.25 * 2.0) != 4.5)) milone_assert_error("float/float.milone", 44, 2);
    if (((8.0 / 2.0) != 4.0)) milone_assert_error("float/float.milone", 45, 2);
    if ((0.0 != 0.0)) milone_assert_error("float/float.milone", 48, 2);
    if ((0.0 == 1.0)) milone_assert_error("float/float.milone", 49, 2);
    if ((2.0 >= 3.0)) milone_assert_error("float/float.milone", 51, 2);
    if ((2.0 < 2.0)) milone_assert_error("float/float.milone", 52, 2);
    if ((3.0 < 2.0)) milone_assert_error("float/float.milone", 53, 2);
    if ((2.0 >= 3.0)) milone_assert_error("float/float.milone", 55, 2);
    if ((2.0 < 2.0)) milone_assert_error("float/float.milone", 56, 2);
    if ((3.0 < 2.0)) milone_assert_error("float/float.milone", 57, 2);
    if ((((int32_t)3.14) != 3)) milone_assert_error("float/float.milone", 60, 2);
    if ((((double)3) != 3.0)) milone_assert_error("float/float.milone", 61, 2);
    call_5 = string_of_float64(3.14);
    if ((string_compare(call_5, (struct String){.ptr = "3.140000", .len = 8}) != 0)) milone_assert_error("float/float.milone", 65, 2);
    call_6 = string_to_float64((struct String){.ptr = "3.14", .len = 4});
    if ((call_6 != 3.14)) milone_assert_error("float/float.milone", 68, 2);
    printf("Assume PI is %f.\n", 3.14);
    return 0;
}
