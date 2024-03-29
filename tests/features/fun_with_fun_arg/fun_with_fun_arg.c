#include <stdio.h>
#include <stdlib.h>
#include <milone.h>

typedef void(*VoidConstPtrInt32StringVoidFunPtr3)(void const *, int32_t, struct String);

struct Int32StringUnitFun2;

struct Int32StringUnitFun2Int32Tuple2_;

typedef void(*VoidConstPtrStringVoidFunPtr2)(void const *, struct String);

struct StringUnitFun1;

void fun_with_fun_arg_fun_with_fun_arg_eta2_obj(void const *env_, struct String arg_);

struct StringUnitFun1 fun_with_fun_arg_fun_with_fun_arg_bindInt(struct Int32StringUnitFun2 f_, int32_t x_);

void fun_with_fun_arg_fun_with_fun_arg_printInt(int32_t value_, struct String label_);

void fun_with_fun_arg_fun_with_fun_arg_eta3_main_printInt(void const *env_1, int32_t arg_3, struct String arg_4);

void fun_with_fun_arg_fun_with_fun_arg_main_der(struct String d_, int32_t n_, struct String f_1);

void fun_with_fun_arg_fun_with_fun_arg_eta3_main_der(void const *env_2, int32_t arg_5, struct String arg_6);

int main(int argc, char **argv);

struct Int32StringUnitFun2 {
    VoidConstPtrInt32StringVoidFunPtr3 fun;
    void const *env;
};

struct Int32StringUnitFun2Int32Tuple2_ {
    struct Int32StringUnitFun2 t0;
    int32_t t1;
};

struct StringUnitFun1 {
    VoidConstPtrStringVoidFunPtr2 fun;
    void const *env;
};

void fun_with_fun_arg_fun_with_fun_arg_eta2_obj(void const *env_, struct String arg_) {
    struct Int32StringUnitFun2 arg_1;
    int32_t arg_2;
    arg_1 = (*(((struct Int32StringUnitFun2Int32Tuple2_ const *)env_))).t0;
    arg_2 = (*(((struct Int32StringUnitFun2Int32Tuple2_ const *)env_))).t1;
    arg_1.fun(arg_1.env, arg_2, arg_);
    return;
}

struct StringUnitFun1 fun_with_fun_arg_fun_with_fun_arg_bindInt(struct Int32StringUnitFun2 f_, int32_t x_) {
    struct Int32StringUnitFun2 callee_;
    struct Int32StringUnitFun2Int32Tuple2_ Int32StringUnitFun2Int32Tuple2_;
    void const *box_;
    struct StringUnitFun1 fun_;
    callee_ = f_;
    Int32StringUnitFun2Int32Tuple2_ = (struct Int32StringUnitFun2Int32Tuple2_){.t0 = callee_, .t1 = x_};
    box_ = ((void const *)milone_region_alloc(1, sizeof(struct Int32StringUnitFun2Int32Tuple2_)));
    (*(((struct Int32StringUnitFun2Int32Tuple2_ *)box_))) = Int32StringUnitFun2Int32Tuple2_;
    fun_ = (struct StringUnitFun1){.fun = fun_with_fun_arg_fun_with_fun_arg_eta2_obj, .env = box_};
    return fun_;
}

void fun_with_fun_arg_fun_with_fun_arg_printInt(int32_t value_, struct String label_) {
    printf("%d: %s\n", value_, string_to_c_str(label_));
    return;
}

void fun_with_fun_arg_fun_with_fun_arg_eta3_main_printInt(void const *env_1, int32_t arg_3, struct String arg_4) {
    fun_with_fun_arg_fun_with_fun_arg_printInt(arg_3, arg_4);
    return;
}

void fun_with_fun_arg_fun_with_fun_arg_main_der(struct String d_, int32_t n_, struct String f_1) {
    char if_;
    struct String arg_8;
    int32_t arg_9;
    struct String arg_10;
tailrec_1:;
    if ((n_ == 0)) {
        goto then_3;
    } else {
        goto else_4;
    }
then_3:;
    printf("%s\n", string_to_c_str(f_1));
    if_ = 0;
    goto if_next_2;
else_4:;
    arg_8 = d_;
    arg_9 = (n_ - 1);
    arg_10 = string_add(f_1, d_);
    d_ = arg_8;
    n_ = arg_9;
    f_1 = arg_10;
    goto tailrec_1;
if_next_2:;
    return;
}

void fun_with_fun_arg_fun_with_fun_arg_eta3_main_der(void const *env_2, int32_t arg_5, struct String arg_6) {
    struct String arg_7;
    arg_7 = (*(((struct String const *)env_2)));
    fun_with_fun_arg_fun_with_fun_arg_main_der(arg_7, arg_5, arg_6);
    return;
}

int main(int argc, char **argv) {
    milone_start(argc, argv);
    struct StringUnitFun1 print42_;
    struct String d_;
    struct StringUnitFun1 der2_;
    struct Int32StringUnitFun2 fun_1;
    struct StringUnitFun1 call_;
    void const *box_1;
    struct Int32StringUnitFun2 fun_2;
    struct StringUnitFun1 call_1;
    fun_1 = (struct Int32StringUnitFun2){.fun = fun_with_fun_arg_fun_with_fun_arg_eta3_main_printInt, .env = NULL};
    call_ = fun_with_fun_arg_fun_with_fun_arg_bindInt(fun_1, 42);
    print42_ = call_;
    print42_.fun(print42_.env, (struct String){.ptr = "The answer", .len = 10});
    d_ = (struct String){.ptr = "\'", .len = 1};
    box_1 = ((void const *)milone_region_alloc(1, sizeof(struct String)));
    (*(((struct String *)box_1))) = d_;
    fun_2 = (struct Int32StringUnitFun2){.fun = fun_with_fun_arg_fun_with_fun_arg_eta3_main_der, .env = box_1};
    call_1 = fun_with_fun_arg_fun_with_fun_arg_bindInt(fun_2, 2);
    der2_ = call_1;
    der2_.fun(der2_.env, (struct String){.ptr = "f", .len = 1});
    return 0;
}
