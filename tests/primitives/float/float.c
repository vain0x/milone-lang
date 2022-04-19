#include <stdio.h>
#include <stdlib.h>
#include <milone.h>

typedef bool(*VoidConstPtrF64BoolFunPtr2)(void const*, double);

struct F64BoolFun1;

struct F64List;

struct F64List;

bool float_float_F64BoolFun1F64ListBoolFun2_all(struct F64BoolFun1 pred_, struct F64List const* xs_);

bool float_float_all_F64BoolFun1F64ListBoolFun2_go(struct F64BoolFun1 pred_, struct F64List const* xs_1);

bool float_float_main_fun(double x_1);

bool float_float_eta2_main_fun(void const* env_, double arg_);

bool float_float_main_fun_1(double x_2);

bool float_float_eta2_main_fun_1(void const* env_1, double arg_1);

int main(int argc, char** argv);

struct F64BoolFun1 {
    VoidConstPtrF64BoolFunPtr2 fun;
    void const* env;
};

struct F64List {
    double head;
    struct F64List const* tail;
};

bool float_float_F64BoolFun1F64ListBoolFun2_all(struct F64BoolFun1 pred_, struct F64List const* xs_) {
    bool call_;
    call_ = float_float_all_F64BoolFun1F64ListBoolFun2_go(pred_, xs_);
    return call_;
}

bool float_float_all_F64BoolFun1F64ListBoolFun2_go(struct F64BoolFun1 pred_, struct F64List const* xs_1) {
    double x_;
    struct F64List const* xs_2;
    bool match_;
    bool app_;
    bool if_;
    struct F64BoolFun1 arg_2;
    struct F64List const* arg_3;
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

bool float_float_eta2_main_fun(void const* env_, double arg_) {
    bool call_1;
    call_1 = float_float_main_fun(arg_);
    return call_1;
}

bool float_float_main_fun_1(double x_2) {
    return (0.0 < x_2);
}

bool float_float_eta2_main_fun_1(void const* env_1, double arg_1) {
    bool call_2;
    call_2 = float_float_main_fun_1(arg_1);
    return call_2;
}

int main(int argc, char** argv) {
    milone_start(argc, argv);
    struct F64List const* zeros_;
    struct F64List const* values_;
    struct F64List const* list_;
    struct F64List const* list_1;
    struct F64List const* list_2;
    struct F64List const* list_3;
    struct F64List const* list_4;
    struct F64List const* list_5;
    struct F64List const* list_6;
    struct F64List const* list_7;
    struct F64BoolFun1 fun_;
    bool call_3;
    struct F64List const* list_8;
    struct F64List const* list_9;
    struct F64List const* list_10;
    struct F64List const* list_11;
    struct F64List const* list_12;
    struct F64List const* list_13;
    struct F64List const* list_14;
    struct F64List const* list_15;
    struct F64List const* list_16;
    struct F64List const* list_17;
    struct F64List const* list_18;
    struct F64BoolFun1 fun_1;
    bool call_4;
    struct String call_5;
    double call_6;
    list_7 = ((struct F64List const*)milone_region_alloc(1, sizeof(struct F64List)));
    (*(((struct F64List*)list_7))) = (struct F64List){.head = 00.00e-00, .tail = NULL};
    list_6 = ((struct F64List const*)milone_region_alloc(1, sizeof(struct F64List)));
    (*(((struct F64List*)list_6))) = (struct F64List){.head = 0E-9, .tail = list_7};
    list_5 = ((struct F64List const*)milone_region_alloc(1, sizeof(struct F64List)));
    (*(((struct F64List*)list_5))) = (struct F64List){.head = 0E+9, .tail = list_6};
    list_4 = ((struct F64List const*)milone_region_alloc(1, sizeof(struct F64List)));
    (*(((struct F64List*)list_4))) = (struct F64List){.head = 0E0, .tail = list_5};
    list_3 = ((struct F64List const*)milone_region_alloc(1, sizeof(struct F64List)));
    (*(((struct F64List*)list_3))) = (struct F64List){.head = 0e0, .tail = list_4};
    list_2 = ((struct F64List const*)milone_region_alloc(1, sizeof(struct F64List)));
    (*(((struct F64List*)list_2))) = (struct F64List){.head = 000.000, .tail = list_3};
    list_1 = ((struct F64List const*)milone_region_alloc(1, sizeof(struct F64List)));
    (*(((struct F64List*)list_1))) = (struct F64List){.head = 0., .tail = list_2};
    list_ = ((struct F64List const*)milone_region_alloc(1, sizeof(struct F64List)));
    (*(((struct F64List*)list_))) = (struct F64List){.head = 0.0, .tail = list_1};
    zeros_ = list_;
    fun_ = (struct F64BoolFun1){.fun = float_float_eta2_main_fun, .env = NULL};
    call_3 = float_float_F64BoolFun1F64ListBoolFun2_all(fun_, zeros_);
    milone_assert(call_3, (struct String){.ptr = "float/float.milone", .len = 18}, 24, 2);
    list_18 = ((struct F64List const*)milone_region_alloc(1, sizeof(struct F64List)));
    (*(((struct F64List*)list_18))) = (struct F64List){.head = 6.02e-23, .tail = NULL};
    list_17 = ((struct F64List const*)milone_region_alloc(1, sizeof(struct F64List)));
    (*(((struct F64List*)list_17))) = (struct F64List){.head = 1e-23, .tail = list_18};
    list_16 = ((struct F64List const*)milone_region_alloc(1, sizeof(struct F64List)));
    (*(((struct F64List*)list_16))) = (struct F64List){.head = 1e+23, .tail = list_17};
    list_15 = ((struct F64List const*)milone_region_alloc(1, sizeof(struct F64List)));
    (*(((struct F64List*)list_15))) = (struct F64List){.head = 1E-9, .tail = list_16};
    list_14 = ((struct F64List const*)milone_region_alloc(1, sizeof(struct F64List)));
    (*(((struct F64List*)list_14))) = (struct F64List){.head = 1e-9, .tail = list_15};
    list_13 = ((struct F64List const*)milone_region_alloc(1, sizeof(struct F64List)));
    (*(((struct F64List*)list_13))) = (struct F64List){.head = 1E+9, .tail = list_14};
    list_12 = ((struct F64List const*)milone_region_alloc(1, sizeof(struct F64List)));
    (*(((struct F64List*)list_12))) = (struct F64List){.head = 1e+9, .tail = list_13};
    list_11 = ((struct F64List const*)milone_region_alloc(1, sizeof(struct F64List)));
    (*(((struct F64List*)list_11))) = (struct F64List){.head = 1E9, .tail = list_12};
    list_10 = ((struct F64List const*)milone_region_alloc(1, sizeof(struct F64List)));
    (*(((struct F64List*)list_10))) = (struct F64List){.head = 1e9, .tail = list_11};
    list_9 = ((struct F64List const*)milone_region_alloc(1, sizeof(struct F64List)));
    (*(((struct F64List*)list_9))) = (struct F64List){.head = 42.195, .tail = list_10};
    list_8 = ((struct F64List const*)milone_region_alloc(1, sizeof(struct F64List)));
    (*(((struct F64List*)list_8))) = (struct F64List){.head = 1.0, .tail = list_9};
    values_ = list_8;
    fun_1 = (struct F64BoolFun1){.fun = float_float_eta2_main_fun_1, .env = NULL};
    call_4 = float_float_F64BoolFun1F64ListBoolFun2_all(fun_1, values_);
    milone_assert(call_4, (struct String){.ptr = "float/float.milone", .len = 18}, 39, 2);
    milone_assert((6.0 < (2.3 + 4.5)), (struct String){.ptr = "float/float.milone", .len = 18}, 42, 2);
    milone_assert(((44.0 - 2.0) == 42.0), (struct String){.ptr = "float/float.milone", .len = 18}, 43, 2);
    milone_assert(((2.25 * 2.0) == 4.5), (struct String){.ptr = "float/float.milone", .len = 18}, 44, 2);
    milone_assert(((8.0 / 2.0) == 4.0), (struct String){.ptr = "float/float.milone", .len = 18}, 45, 2);
    milone_assert((0.0 == 0.0), (struct String){.ptr = "float/float.milone", .len = 18}, 48, 2);
    milone_assert((0.0 != 1.0), (struct String){.ptr = "float/float.milone", .len = 18}, 49, 2);
    milone_assert((2.0 < 3.0), (struct String){.ptr = "float/float.milone", .len = 18}, 51, 2);
    milone_assert((2.0 >= 2.0), (struct String){.ptr = "float/float.milone", .len = 18}, 52, 2);
    milone_assert((3.0 >= 2.0), (struct String){.ptr = "float/float.milone", .len = 18}, 53, 2);
    milone_assert((2.0 < 3.0), (struct String){.ptr = "float/float.milone", .len = 18}, 55, 2);
    milone_assert((2.0 >= 2.0), (struct String){.ptr = "float/float.milone", .len = 18}, 56, 2);
    milone_assert((3.0 >= 2.0), (struct String){.ptr = "float/float.milone", .len = 18}, 57, 2);
    milone_assert((((int32_t)3.14) == 3), (struct String){.ptr = "float/float.milone", .len = 18}, 60, 2);
    milone_assert((((double)3) == 3.0), (struct String){.ptr = "float/float.milone", .len = 18}, 61, 2);
    call_5 = string_of_float64(3.14);
    milone_assert((string_compare(call_5, (struct String){.ptr = "3.140000", .len = 8}) == 0), (struct String){.ptr = "float/float.milone", .len = 18}, 65, 2);
    call_6 = string_to_float64((struct String){.ptr = "3.14", .len = 4});
    milone_assert((call_6 == 3.14), (struct String){.ptr = "float/float.milone", .len = 18}, 68, 2);
    printf("Assume PI is %f.\n", 3.14);
    return 0;
}
