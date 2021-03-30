#include "milone.h"

struct IntStringUnitFun2;

struct IntStringUnitFun2IntTuple2;

struct StringUnitFun1;

struct StringTuple1;

char fun_(void const* env_, struct String arg_);

struct StringUnitFun1 fun_with_fun_arg_Program_bindInt(struct IntStringUnitFun2 f_, int x_);

char fun_with_fun_arg_Program_printInt(int value_, struct String label_);

char fun_1(void const* env_1, int arg_3, struct String arg_4);

char der_(struct String d_, int n_, struct String f_1);

char fun_2(void const* env_2, int arg_5, struct String arg_6);

int milone_main();

struct IntStringUnitFun2 {
    char(*fun)(void const*, int, struct String);
    void const* env;
};

struct IntStringUnitFun2IntTuple2 {
    struct IntStringUnitFun2 t0;
    int t1;
};

struct StringUnitFun1 {
    char(*fun)(void const*, struct String);
    void const* env;
};

struct StringTuple1 {
    struct String t0;
};

char fun_(void const* env_, struct String arg_) {
    struct IntStringUnitFun2 arg_1 = (*(((struct IntStringUnitFun2IntTuple2 const*)env_))).t0;
    int arg_2 = (*(((struct IntStringUnitFun2IntTuple2 const*)env_))).t1;
    char app_ = arg_1.fun(arg_1.env, arg_2, arg_);
    return 0;
}

struct StringUnitFun1 fun_with_fun_arg_Program_bindInt(struct IntStringUnitFun2 f_, int x_) {
    struct IntStringUnitFun2 callee_ = f_;
    struct IntStringUnitFun2IntTuple2 tuple_ = (struct IntStringUnitFun2IntTuple2){.t0 = callee_, .t1 = x_};
    void const* box_ = milone_mem_alloc(1, sizeof(struct IntStringUnitFun2IntTuple2));
    (*(((struct IntStringUnitFun2IntTuple2*)box_))) = tuple_;
    struct StringUnitFun1 fun_3 = (struct StringUnitFun1){.fun = fun_, .env = box_};
    return fun_3;
}

char fun_with_fun_arg_Program_printInt(int value_, struct String label_) {
    printf("%d: %s\n", value_, str_to_c_str(label_));
    return 0;
}

char fun_1(void const* env_1, int arg_3, struct String arg_4) {
    char call_ = fun_with_fun_arg_Program_printInt(arg_3, arg_4);
    return 0;
}

char der_(struct String d_, int n_, struct String f_1) {
tailrec_1:;
    char if_;
    if ((n_ == 0)) {
        goto then_3;
    } else {
        goto else_4;
    }
then_3:;
    printf("%s\n", str_to_c_str(f_1));
    if_ = 0;
    goto if_next_2;
else_4:;
    struct String arg_8 = d_;
    int arg_9 = (n_ - 1);
    struct String arg_10 = str_add(f_1, d_);
    d_ = arg_8;
    n_ = arg_9;
    f_1 = arg_10;
    goto tailrec_1;
if_next_2:;
    return 0;
}

char fun_2(void const* env_2, int arg_5, struct String arg_6) {
    struct String arg_7 = (*(((struct StringTuple1 const*)env_2))).t0;
    char call_1 = der_(arg_7, arg_5, arg_6);
    return 0;
}

int milone_main() {
    struct IntStringUnitFun2 fun_4 = (struct IntStringUnitFun2){.fun = fun_1, .env = NULL};
    struct StringUnitFun1 call_2 = fun_with_fun_arg_Program_bindInt(fun_4, 42);
    struct StringUnitFun1 print42_ = call_2;
    char app_1 = print42_.fun(print42_.env, (struct String){.str = "The answer", .len = 10});
    struct String d_ = (struct String){.str = "\'", .len = 1};
    struct StringTuple1 tuple_1 = (struct StringTuple1){.t0 = d_};
    void const* box_1 = milone_mem_alloc(1, sizeof(struct StringTuple1));
    (*(((struct StringTuple1*)box_1))) = tuple_1;
    struct IntStringUnitFun2 fun_5 = (struct IntStringUnitFun2){.fun = fun_2, .env = box_1};
    struct StringUnitFun1 call_3 = fun_with_fun_arg_Program_bindInt(fun_5, 2);
    struct StringUnitFun1 der2_ = call_3;
    char app_2 = der2_.fun(der2_.env, (struct String){.str = "f", .len = 1});
    return 0;
}
