struct IntStringUnitFun2;

struct IntStringUnitFun2IntTuple2;

int fun_(void* env_, struct String arg_);

struct StringUnitFun1;

struct StringUnitFun1 bindInt_(struct IntStringUnitFun2 f_, int x_);

int printInt_(int value_, struct String label_);

struct StringTuple1;

struct StringTuple1Tuple1;

int fun_2(void* env_2, int arg_5, struct String arg_6);

int der_(struct StringTuple1 arg_8, int n_, struct String f_1);

int fun_1(void* env_1, int arg_3, struct String arg_4);

int main();

struct IntStringUnitFun2 {
    int(*fun)(void*, int, struct String);
    void* env;
};

struct IntStringUnitFun2IntTuple2 {
    struct IntStringUnitFun2 t0;
    int t1;
};

int fun_(void* env_, struct String arg_) {
    struct IntStringUnitFun2 arg_1 = (*(((struct IntStringUnitFun2IntTuple2*)env_))).t0;
    int arg_2 = (*(((struct IntStringUnitFun2IntTuple2*)env_))).t1;
    int app_ = arg_1.fun(arg_1.env, arg_2, arg_);
    return 0;
}

struct StringUnitFun1 {
    int(*fun)(void*, struct String);
    void* env;
};

struct StringUnitFun1 bindInt_(struct IntStringUnitFun2 f_, int x_) {
    struct IntStringUnitFun2 callee_ = f_;
    struct IntStringUnitFun2IntTuple2 tuple_;
    tuple_.t0 = callee_;
    tuple_.t1 = x_;
    void* box_ = (void*)malloc(sizeof(struct IntStringUnitFun2IntTuple2));
    (*(((struct IntStringUnitFun2IntTuple2*)box_))) = tuple_;
    void* env_3 = box_;
    struct StringUnitFun1 fun_3 = (struct StringUnitFun1){.fun = fun_, .env = env_3};
    return fun_3;
}

int printInt_(int value_, struct String label_) {
    printf("%d: %s\n", value_, label_.str);
    int call_ = 0;
    return 0;
}

struct StringTuple1 {
    struct String t0;
};

struct StringTuple1Tuple1 {
    struct StringTuple1 t0;
};

int fun_2(void* env_2, int arg_5, struct String arg_6) {
    struct StringTuple1 arg_7 = (*(((struct StringTuple1Tuple1*)env_2))).t0;
    int call_5 = der_(arg_7, arg_5, arg_6);
    return 0;
}

int der_(struct StringTuple1 arg_8, int n_, struct String f_1) {
    struct String d_ = arg_8.t0;
    int match_;
    if (!(((n_ == 0) == 1))) goto next_2;
    printf("%s\n", f_1.str);
    int call_3 = 0;
    match_ = 0;
    goto end_match_1;
next_2:;
    if (!(((n_ == 0) == 0))) goto next_3;
    struct StringTuple1 tuple_1;
    tuple_1.t0 = d_;
    int call_4 = der_(tuple_1, (n_ - 1), str_add(f_1, d_));
    match_ = 0;
    goto end_match_1;
next_3:;
    exit(1);
end_match_1:;
    return 0;
}

int fun_1(void* env_1, int arg_3, struct String arg_4) {
    int call_1 = printInt_(arg_3, arg_4);
    return 0;
}

int main() {
    void* box_1 = (void*)malloc(sizeof(int));
    (*(((int*)box_1))) = 0;
    void* env_4 = box_1;
    struct IntStringUnitFun2 fun_4 = (struct IntStringUnitFun2){.fun = fun_1, .env = env_4};
    struct StringUnitFun1 call_2 = bindInt_(fun_4, 42);
    struct StringUnitFun1 print42_ = call_2;
    int app_1 = print42_.fun(print42_.env, (struct String){.str = "The answer", .len = 10});
    struct String d_ = (struct String){.str = "'", .len = 1};
    struct StringTuple1 tuple_3;
    tuple_3.t0 = d_;
    struct StringTuple1Tuple1 tuple_2;
    tuple_2.t0 = tuple_3;
    void* box_2 = (void*)malloc(sizeof(struct StringTuple1Tuple1));
    (*(((struct StringTuple1Tuple1*)box_2))) = tuple_2;
    void* env_5 = box_2;
    struct IntStringUnitFun2 fun_5 = (struct IntStringUnitFun2){.fun = fun_2, .env = env_5};
    struct StringUnitFun1 call_6 = bindInt_(fun_5, 2);
    struct StringUnitFun1 der2_ = call_6;
    int app_2 = der2_.fun(der2_.env, (struct String){.str = "f", .len = 1});
    return 0;
}
