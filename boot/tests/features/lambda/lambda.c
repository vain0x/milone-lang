struct IntIntFun1;

int twice_1(struct IntIntFun1 f_, int x_);

int fun_(int x_2);

int fun_2(void* env_, int arg_);

int fun_1(int x_3, int y_1);

int fun_3(void* env_1, int arg_1, int arg_2);

struct IntIntIntFun2;

int main();

struct IntIntFun1 {
    int(*fun)(void*, int);
    void* env;
};

int twice_1(struct IntIntFun1 f_, int x_) {
    int app_ = f_.fun(f_.env, x_);
    int app_1 = f_.fun(f_.env, app_);
    return app_1;
}

int fun_(int x_2) {
    int y_ = (x_2 + 1);
    return y_;
}

int fun_2(void* env_, int arg_) {
    int call_ = fun_(arg_);
    return call_;
}

int fun_1(int x_3, int y_1) {
    return (x_3 / y_1);
}

int fun_3(void* env_1, int arg_1, int arg_2) {
    int call_2 = fun_1(arg_1, arg_2);
    return call_2;
}

struct IntIntIntFun2 {
    int(*fun)(void*, int, int);
    void* env;
};

int main() {
    void* box_ = (void*)malloc(sizeof(int));
    (*(((int*)box_))) = 0;
    void* env_2 = box_;
    struct IntIntFun1 fun_4 = (struct IntIntFun1){.fun = fun_2, .env = env_2};
    int call_1 = twice_1(fun_4, 40);
    int x_1 = call_1;
    int match_;
    if (!(((x_1 != 42) == 1))) goto next_2;
    exit(1);
    match_ = 0;
    goto end_match_1;
next_2:;
    if (!(((x_1 != 42) == 0))) goto next_3;
    match_ = 0;
    goto end_match_1;
next_3:;
    exit(1);
end_match_1:;
    int match_1;
    void* box_1 = (void*)malloc(sizeof(int));
    (*(((int*)box_1))) = 0;
    void* env_3 = box_1;
    struct IntIntIntFun2 fun_5 = (struct IntIntIntFun2){.fun = fun_3, .env = env_3};
    int app_2 = fun_5.fun(fun_5.env, 84, 2);
    if (!(((app_2 != 42) == 1))) goto next_5;
    exit(1);
    match_1 = 0;
    goto end_match_4;
next_5:;
    if (!(((app_2 != 42) == 0))) goto next_6;
    match_1 = 0;
    goto end_match_4;
next_6:;
    exit(1);
end_match_4:;
    return 0;
}
