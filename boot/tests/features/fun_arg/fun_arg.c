struct IntStringUnitFun2;

struct IntStringUnitFun2IntTuple2;

int fun_(void* env_, struct String arg_);

struct StringUnitFun1;

struct StringUnitFun1 bindInt_(struct IntStringUnitFun2 f_, int x_);

int printInt_(int value_, struct String label_);

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
    void* env_2 = box_;
    struct StringUnitFun1 fun_2 = (struct StringUnitFun1){.fun = fun_, .env = env_2};
    return fun_2;
}

int printInt_(int value_, struct String label_) {
    printf("%d: %s\n", value_, label_.str);
    int call_ = 0;
    return 0;
}

int fun_1(void* env_1, int arg_3, struct String arg_4) {
    int call_1 = printInt_(arg_3, arg_4);
    return 0;
}

int main() {
    void* box_1 = (void*)malloc(sizeof(int));
    (*(((int*)box_1))) = 0;
    void* env_3 = box_1;
    struct IntStringUnitFun2 fun_3 = (struct IntStringUnitFun2){.fun = fun_1, .env = env_3};
    struct StringUnitFun1 call_2 = bindInt_(fun_3, 42);
    struct StringUnitFun1 print42_ = call_2;
    int app_1 = print42_.fun(print42_.env, (struct String){.str = "The answer", .len = 10});
    return 0;
}
