struct IntIntFun {
    int(*fun)(void*, int);
    void* env;
};

int twice_(struct IntIntFun f_, int x_) {
    int call_ = f_.fun(f_.env, x_);
    int call_1 = f_.fun(f_.env, call_);
    return call_1;
}

int dec_(int y_, int x_1) {
    return (x_1 - y_);
}

struct IntTuple1 {
    int t0;
};

int fun_(void* env_, int arg_) {
    int call_4 = dec_((*(((struct IntTuple1*)env_))).t0, arg_);
    return call_4;
}

int main() {
    struct IntTuple1 env_1;
    env_1.t0 = 3;
    void* box_ = (void*)malloc(sizeof(struct IntTuple1));
    (*(((struct IntTuple1*)box_))) = env_1;
    struct IntIntFun call_2 = (struct IntIntFun){.fun = fun_, .env = box_};
    struct IntIntFun dec3_ = call_2;
    int call_3 = twice_(dec3_, 8);
    return (call_3 - 2);
}
