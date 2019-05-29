int fun_1(void* env_, int arg_);

int fun_(int x_1);

struct IntIntFun1;

int twice_1(struct IntIntFun1 f_, int x_);

int main();

int fun_1(void* env_, int arg_) {
    int call_ = fun_(arg_);
    return call_;
}

int fun_(int x_1) {
    int y_ = (x_1 + 1);
    return y_;
}

struct IntIntFun1 {
    int(*fun)(void*, int);
    void* env;
};

int twice_1(struct IntIntFun1 f_, int x_) {
    int app_ = f_.fun(f_.env, x_);
    int app_1 = f_.fun(f_.env, app_);
    return app_1;
}

int main() {
    void* box_ = (void*)malloc(sizeof(int));
    (*(((int*)box_))) = 0;
    void* env_1 = box_;
    struct IntIntFun1 fun_2 = (struct IntIntFun1){.fun = fun_1, .env = env_1};
    int call_1 = twice_1(fun_2, 40);
    int x_2 = call_1;
    int match_;
    if (!(((x_2 != 42) == 1))) goto next_2;
    exit(1);
    match_ = 0;
    goto end_match_1;
next_2:;
    if (!(((x_2 != 42) == 0))) goto next_3;
    match_ = 0;
    goto end_match_1;
next_3:;
    exit(1);
end_match_1:;
    return 0;
}
