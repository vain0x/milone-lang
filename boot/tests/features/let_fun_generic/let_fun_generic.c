int fun_1(void* env_1, int arg_1);

int fun_(void* env_, int arg_);

int f_1(int x_2);

struct IntIntFun1;

struct IntList;

struct IntList* listMap_1(struct IntIntFun1 f_, struct IntList* xs_);

struct StringList;

struct StringList* id_1(struct StringList* x_);

int id_2(int x_);

int main();

int fun_1(void* env_1, int arg_1) {
    int call_6 = f_1(arg_1);
    return call_6;
}

int fun_(void* env_, int arg_) {
    int call_5 = f_1(arg_);
    return call_5;
}

int f_1(int x_2) {
    printf("%d\n", x_2);
    int call_4 = 0;
    return (x_2 * x_2);
}

struct IntIntFun1 {
    int(*fun)(void*, int);
    void* env;
};

struct IntList {
    int head;
    struct IntList* tail;
};

struct IntList* listMap_1(struct IntIntFun1 f_, struct IntList* xs_) {
    struct IntList* match_;
    if (!((!(xs_)))) goto next_2;
    match_ = NULL;
    goto end_match_1;
next_2:;
    if (!((!((!(xs_)))))) goto next_3;
    int x_1 = xs_->head;
    struct IntList* xs_1 = xs_->tail;
    int app_ = f_.fun(f_.env, x_1);
    struct IntList* call_3 = listMap_1(f_, xs_1);
    struct IntList* list_1 = (struct IntList*)malloc(sizeof(struct IntList));
    list_1->head = app_;
    list_1->tail = call_3;
    match_ = list_1;
    goto end_match_1;
next_3:;
    exit(1);
end_match_1:;
    return match_;
}

struct StringList {
    struct String head;
    struct StringList* tail;
};

struct StringList* id_1(struct StringList* x_) {
    return x_;
}

int id_2(int x_) {
    return x_;
}

int main() {
    int call_ = id_2(42);
    int call_1 = id_2(1);
    struct StringList* list_ = (struct StringList*)malloc(sizeof(struct StringList));
    list_->head = (struct String){.str = "A", .len = 1};
    list_->tail = NULL;
    struct StringList* call_2 = id_1(list_);
    void* box_ = (void*)malloc(sizeof(int));
    (*(((int*)box_))) = 0;
    void* env_2 = box_;
    struct IntIntFun1 fun_2 = (struct IntIntFun1){.fun = fun_, .env = env_2};
    void* box_1 = (void*)malloc(sizeof(int));
    (*(((int*)box_1))) = 0;
    void* env_3 = box_1;
    struct IntIntFun1 fun_3 = (struct IntIntFun1){.fun = fun_1, .env = env_3};
    struct IntList* list_4 = (struct IntList*)malloc(sizeof(struct IntList));
    list_4->head = 3;
    list_4->tail = NULL;
    struct IntList* list_3 = (struct IntList*)malloc(sizeof(struct IntList));
    list_3->head = 2;
    list_3->tail = list_4;
    struct IntList* list_2 = (struct IntList*)malloc(sizeof(struct IntList));
    list_2->head = 1;
    list_2->tail = list_3;
    struct IntList* call_7 = listMap_1(fun_3, list_2);
    struct IntList* call_8 = listMap_1(fun_2, call_7);
    return 0;
}
