struct IntIntFun1;

int twice_(struct IntIntFun1 f_, int x_);

int dec_(int y_, int x_1);

int add4_(int x1_, int x2_, int x3_, int x4_);

struct IntTuple1;

int fun_(void* env_, int arg_);

struct IntIntTuple2;

int fun_1(void* env_2, int arg_1, int arg_2);

struct IntIntIntFun2;

int main();

struct IntIntFun1 {
    int(*fun)(void*, int);
    void* env;
};

int twice_(struct IntIntFun1 f_, int x_) {
    int call_ = f_.fun(f_.env, x_);
    int call_1 = f_.fun(f_.env, call_);
    return call_1;
}

int dec_(int y_, int x_1) {
    return (x_1 - y_);
}

int add4_(int x1_, int x2_, int x3_, int x4_) {
    return (((x1_ + x2_) + x3_) + x4_);
}

struct IntTuple1 {
    int t0;
};

int fun_(void* env_, int arg_) {
    int call_6 = dec_((*(((struct IntTuple1*)env_))).t0, arg_);
    return call_6;
}

struct IntIntTuple2 {
    int t0;
    int t1;
};

int fun_1(void* env_2, int arg_1, int arg_2) {
    int call_7 = add4_((*(((struct IntIntTuple2*)env_2))).t0, (*(((struct IntIntTuple2*)env_2))).t1, arg_1, arg_2);
    return call_7;
}

struct IntIntIntFun2 {
    int(*fun)(void*, int, int);
    void* env;
};

int main() {
    struct IntTuple1 env_1;
    env_1.t0 = 3;
    void* box_ = (void*)malloc(sizeof(struct IntTuple1));
    (*(((struct IntTuple1*)box_))) = env_1;
    struct IntIntFun1 call_2 = (struct IntIntFun1){.fun = fun_, .env = box_};
    struct IntIntFun1 dec3_ = call_2;
    int match_;
    int call_3 = twice_(dec3_, 8);
    if (!(((call_3 != 2) == 1))) goto next_2;
    exit(1);
    match_ = 0;
    goto end_match_1;
next_2:;
    if (!(((call_3 != 2) == 0))) goto next_3;
    match_ = 0;
    goto end_match_1;
next_3:;
    exit(1);
end_match_1:;
    struct IntIntTuple2 env_3;
    env_3.t0 = 2;
    env_3.t1 = 3;
    void* box_1 = (void*)malloc(sizeof(struct IntIntTuple2));
    (*(((struct IntIntTuple2*)box_1))) = env_3;
    struct IntIntIntFun2 call_4 = (struct IntIntIntFun2){.fun = fun_1, .env = box_1};
    struct IntIntIntFun2 add2_ = call_4;
    int match_1;
    int call_5 = add2_.fun(add2_.env, 5, 7);
    if (!(((call_5 != (((2 + 3) + 5) + 7)) == 1))) goto next_5;
    exit(1);
    match_1 = 0;
    goto end_match_4;
next_5:;
    if (!(((call_5 != (((2 + 3) + 5) + 7)) == 0))) goto next_6;
    match_1 = 0;
    goto end_match_4;
next_6:;
    exit(1);
end_match_4:;
    return 0;
}
