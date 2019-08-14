struct IntList;

struct IntList* go_1(struct IntList* acc_, struct IntList* xs_1);

struct IntList* listRev_2(struct IntList* xs_);

struct StringList;

struct StringList* go_2(struct StringList* acc_, struct StringList* xs_1);

struct StringList* listRev_1(struct StringList* xs_);

int id_2(int x_1);

struct StringList* id_1(struct StringList* x_1);

struct IntIntFun1;

struct IntList* listMap_1(struct IntIntFun1 f_, struct IntList* xs_3);

int f_1(int x_3);

int fun_(void* env_, int arg_);

int fun_1(void* env_1, int arg_1);

struct StringIntTuple2;

struct IntStringTuple2;

struct IntStringTuple2 flip_2(struct StringIntTuple2 arg_2);

struct StringIntTuple2 flip_1(struct IntStringTuple2 arg_3);

struct IntListStringListTuple2;

int main();

struct IntList {
    int head;
    struct IntList* tail;
};

struct IntList* go_1(struct IntList* acc_, struct IntList* xs_1) {
    struct IntList* match_;
    if (!((!(xs_1)))) goto next_2;
    match_ = acc_;
    goto end_match_1;
next_2:;
    if (!((!((!(xs_1)))))) goto next_3;
    int x_ = xs_1->head;
    struct IntList* xs_2 = xs_1->tail;
    struct IntList* list_ = (struct IntList*)malloc(sizeof(struct IntList));
    list_->head = x_;
    list_->tail = acc_;
    struct IntList* call_ = go_1(list_, xs_2);
    match_ = call_;
    goto end_match_1;
next_3:;
    exit(1);
end_match_1:;
    return match_;
}

struct IntList* listRev_2(struct IntList* xs_) {
    struct IntList* call_1 = go_1(NULL, xs_);
    return call_1;
}

struct StringList {
    struct String head;
    struct StringList* tail;
};

struct StringList* go_2(struct StringList* acc_, struct StringList* xs_1) {
    struct StringList* match_1;
    if (!((!(xs_1)))) goto next_5;
    match_1 = acc_;
    goto end_match_4;
next_5:;
    if (!((!((!(xs_1)))))) goto next_6;
    struct String x_ = xs_1->head;
    struct StringList* xs_2 = xs_1->tail;
    struct StringList* list_1 = (struct StringList*)malloc(sizeof(struct StringList));
    list_1->head = x_;
    list_1->tail = acc_;
    struct StringList* call_2 = go_2(list_1, xs_2);
    match_1 = call_2;
    goto end_match_4;
next_6:;
    exit(1);
end_match_4:;
    return match_1;
}

struct StringList* listRev_1(struct StringList* xs_) {
    struct StringList* call_3 = go_2(NULL, xs_);
    return call_3;
}

int id_2(int x_1) {
    return x_1;
}

struct StringList* id_1(struct StringList* x_1) {
    return x_1;
}

struct IntIntFun1 {
    int(*fun)(void*, int);
    void* env;
};

struct IntList* listMap_1(struct IntIntFun1 f_, struct IntList* xs_3) {
    struct IntList* match_2;
    if (!((!(xs_3)))) goto next_8;
    match_2 = NULL;
    goto end_match_7;
next_8:;
    if (!((!((!(xs_3)))))) goto next_9;
    int x_2 = xs_3->head;
    struct IntList* xs_4 = xs_3->tail;
    int app_ = f_.fun(f_.env, x_2);
    struct IntList* call_7 = listMap_1(f_, xs_4);
    struct IntList* list_3 = (struct IntList*)malloc(sizeof(struct IntList));
    list_3->head = app_;
    list_3->tail = call_7;
    match_2 = list_3;
    goto end_match_7;
next_9:;
    exit(1);
end_match_7:;
    return match_2;
}

int f_1(int x_3) {
    printf("%d\n", x_3);
    int call_8 = 0;
    return (x_3 * x_3);
}

int fun_(void* env_, int arg_) {
    int call_9 = f_1(arg_);
    return call_9;
}

int fun_1(void* env_1, int arg_1) {
    int call_10 = f_1(arg_1);
    return call_10;
}

struct StringIntTuple2 {
    struct String t0;
    int t1;
};

struct IntStringTuple2 {
    int t0;
    struct String t1;
};

struct IntStringTuple2 flip_2(struct StringIntTuple2 arg_2) {
    struct String x_4 = arg_2.t0;
    int y_ = arg_2.t1;
    struct IntStringTuple2 tuple_;
    tuple_.t0 = y_;
    tuple_.t1 = x_4;
    return tuple_;
}

struct StringIntTuple2 flip_1(struct IntStringTuple2 arg_3) {
    int x_4 = arg_3.t0;
    struct String y_ = arg_3.t1;
    struct StringIntTuple2 tuple_1;
    tuple_1.t0 = y_;
    tuple_1.t1 = x_4;
    return tuple_1;
}

struct IntListStringListTuple2 {
    struct IntList* t0;
    struct StringList* t1;
};

int main() {
    int call_4 = id_2(42);
    int call_5 = id_2(1);
    struct StringList* list_2 = (struct StringList*)malloc(sizeof(struct StringList));
    list_2->head = (struct String){.str = "A", .len = 1};
    list_2->tail = NULL;
    struct StringList* call_6 = id_1(list_2);
    void* box_ = (void*)malloc(sizeof(int));
    (*(((int*)box_))) = 0;
    void* env_2 = box_;
    struct IntIntFun1 fun_2 = (struct IntIntFun1){.fun = fun_, .env = env_2};
    void* box_1 = (void*)malloc(sizeof(int));
    (*(((int*)box_1))) = 0;
    void* env_3 = box_1;
    struct IntIntFun1 fun_3 = (struct IntIntFun1){.fun = fun_1, .env = env_3};
    struct IntList* list_6 = (struct IntList*)malloc(sizeof(struct IntList));
    list_6->head = 3;
    list_6->tail = NULL;
    struct IntList* list_5 = (struct IntList*)malloc(sizeof(struct IntList));
    list_5->head = 2;
    list_5->tail = list_6;
    struct IntList* list_4 = (struct IntList*)malloc(sizeof(struct IntList));
    list_4->head = 1;
    list_4->tail = list_5;
    struct IntList* call_11 = listMap_1(fun_3, list_4);
    struct IntList* call_12 = listMap_1(fun_2, call_11);
    int match_3;
    struct IntStringTuple2 tuple_2;
    tuple_2.t0 = 1;
    tuple_2.t1 = (struct String){.str = "a", .len = 1};
    struct StringIntTuple2 call_13 = flip_1(tuple_2);
    struct IntStringTuple2 call_14 = flip_2(call_13);
    if (!((call_14.t0 == 1))) goto next_11;
    if (!((str_cmp(call_14.t1, (struct String){.str = "a", .len = 1}) == 0))) goto next_11;
    match_3 = 0;
    goto end_match_10;
next_11:;
    exit(1);
    match_3 = 0;
    goto end_match_10;
next_12:;
end_match_10:;
    int match_4;
    struct IntList* list_8 = (struct IntList*)malloc(sizeof(struct IntList));
    list_8->head = 2;
    list_8->tail = NULL;
    struct IntList* list_7 = (struct IntList*)malloc(sizeof(struct IntList));
    list_7->head = 1;
    list_7->tail = list_8;
    struct IntList* call_15 = listRev_2(list_7);
    struct StringList* list_10 = (struct StringList*)malloc(sizeof(struct StringList));
    list_10->head = (struct String){.str = "b", .len = 1};
    list_10->tail = NULL;
    struct StringList* list_9 = (struct StringList*)malloc(sizeof(struct StringList));
    list_9->head = (struct String){.str = "a", .len = 1};
    list_9->tail = list_10;
    struct StringList* call_16 = listRev_1(list_9);
    struct IntListStringListTuple2 tuple_3;
    tuple_3.t0 = call_15;
    tuple_3.t1 = call_16;
    if (!((!((!(tuple_3.t0)))))) goto next_14;
    if (!((tuple_3.t0->head == 2))) goto next_14;
    if (!((!((!(tuple_3.t0->tail)))))) goto next_14;
    if (!((tuple_3.t0->tail->head == 1))) goto next_14;
    if (!((!(tuple_3.t0->tail->tail)))) goto next_14;
    if (!((!((!(tuple_3.t1)))))) goto next_14;
    if (!((str_cmp(tuple_3.t1->head, (struct String){.str = "b", .len = 1}) == 0))) goto next_14;
    if (!((!((!(tuple_3.t1->tail)))))) goto next_14;
    if (!((str_cmp(tuple_3.t1->tail->head, (struct String){.str = "a", .len = 1}) == 0))) goto next_14;
    if (!((!(tuple_3.t1->tail->tail)))) goto next_14;
    match_4 = 0;
    goto end_match_13;
next_14:;
    milone_assert(0);
    int call_17 = 0;
    match_4 = 0;
    goto end_match_13;
next_15:;
end_match_13:;
    return 0;
}
