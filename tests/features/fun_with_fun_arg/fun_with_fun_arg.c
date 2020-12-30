#include "milone.h"

struct IntStringUnitFun2;

struct IntStringUnitFun2IntTuple2;

int fun_(void const* env_, struct String arg_);

struct StringUnitFun1;

struct StringUnitFun1 bindInt_(struct IntStringUnitFun2 f_, int x_);

int printInt_(int value_, struct String label_);

int fun_1(void const* env_1, int arg_3, struct String arg_4);

int der_(struct String d_, int n_, struct String f_1);

struct StringTuple1;

int fun_2(void const* env_2, int arg_5, struct String arg_6);

int main();

struct IntStringUnitFun2 {
    int(*fun)(void const*, int, struct String);
    void const* env;
};

struct IntStringUnitFun2IntTuple2 {
    struct IntStringUnitFun2 t0;
    int t1;
};

int fun_(void const* env_, struct String arg_) {
    struct IntStringUnitFun2 arg_1 = (*(((struct IntStringUnitFun2IntTuple2 const*)env_))).t0;
    int arg_2 = (*(((struct IntStringUnitFun2IntTuple2 const*)env_))).t1;
    int app_ = arg_1.fun(arg_1.env, arg_2, arg_);
    return 0;
}

struct StringUnitFun1 {
    int(*fun)(void const*, struct String);
    void const* env;
};

struct StringUnitFun1 bindInt_(struct IntStringUnitFun2 f_, int x_) {
    struct IntStringUnitFun2 callee_ = f_;
    struct IntStringUnitFun2IntTuple2 tuple_ = (struct IntStringUnitFun2IntTuple2){.t0 = callee_, .t1 = x_};
    void const* box_ = milone_mem_alloc(1, sizeof(struct IntStringUnitFun2IntTuple2));
    (*(((struct IntStringUnitFun2IntTuple2*)box_))) = tuple_;
    struct StringUnitFun1 fun_3 = (struct StringUnitFun1){.fun = fun_, .env = box_};
    return fun_3;
}

int printInt_(int value_, struct String label_) {
    printf("%d: %s\n", value_, label_.str);
    return 0;
}

int fun_1(void const* env_1, int arg_3, struct String arg_4) {
    int call_ = printInt_(arg_3, arg_4);
    return 0;
}

int der_(struct String d_, int n_, struct String f_1) {
tailrec_1:;
    int if_;
    if ((n_ == 0)) {
        goto then_3;
    } else {
        goto else_4;
    }
then_3:;
    printf("%s\n", f_1.str);
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
    if_ = 0;
    goto if_next_2;
if_next_2:;
    return 0;
}

struct StringTuple1 {
    struct String t0;
};

int fun_2(void const* env_2, int arg_5, struct String arg_6) {
    struct String arg_7 = (*(((struct StringTuple1 const*)env_2))).t0;
    int call_1 = der_(arg_7, arg_5, arg_6);
    return 0;
}

int main() {
    void const* box_1 = milone_mem_alloc(1, sizeof(int));
    (*(((int*)box_1))) = 0;
    struct IntStringUnitFun2 fun_4 = (struct IntStringUnitFun2){.fun = fun_1, .env = box_1};
    struct StringUnitFun1 call_2 = bindInt_(fun_4, 42);
    struct StringUnitFun1 print42_ = call_2;
    int app_1 = print42_.fun(print42_.env, (struct String){.str = "The answer", .len = 10});
    struct String d_ = (struct String){.str = "\'", .len = 1};
    struct StringTuple1 tuple_1 = (struct StringTuple1){.t0 = d_};
    void const* box_2 = milone_mem_alloc(1, sizeof(struct StringTuple1));
    (*(((struct StringTuple1*)box_2))) = tuple_1;
    struct IntStringUnitFun2 fun_5 = (struct IntStringUnitFun2){.fun = fun_2, .env = box_2};
    struct StringUnitFun1 call_3 = bindInt_(fun_5, 2);
    struct StringUnitFun1 der2_ = call_3;
    int app_2 = der2_.fun(der2_.env, (struct String){.str = "f", .len = 1});
    return 0;
}
