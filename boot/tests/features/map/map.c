#include "milone.h"

int intCmp_(int x_, int y_);

int intHash_(int x_1);

struct IntIntFun1;

struct IntIntIntFun2;

struct IntStringTuple2;

struct IntStringTuple2List;

struct IntIntStringTuple2ListTuple2;

struct IntIntStringTuple2ListTuple2List;

struct IntIntStringTuple2ListTuple2ListIntIntFun1IntIntIntFun2Tuple3;

struct IntIntStringTuple2ListTuple2ListIntIntFun1IntIntIntFun2Tuple3 mapNewSingleton_1(int key_, struct String value_, struct IntIntFun1 hash_, struct IntIntIntFun2 cmp_);

int fun_(void* env_, int arg_);

int fun_1(void* env_1, int arg_1, int arg_2);

int typeTest_(int arg_3);

int main();

int intCmp_(int x_, int y_) {
    int match_;
    if ((y_ >= x_)) goto next_2;
    match_ = 1;
    goto end_match_1;
next_2:;
    if ((y_ < x_)) goto next_3;
    int match_1;
    if ((y_ != x_)) goto next_5;
    match_1 = 0;
    goto end_match_4;
next_5:;
    if ((y_ == x_)) goto next_6;
    match_1 = (0 - 1);
    goto end_match_4;
next_6:;
    exit(1);
end_match_4:;
    match_ = match_1;
    goto end_match_1;
next_3:;
    exit(1);
end_match_1:;
    return match_;
}

int intHash_(int x_1) {
    return (x_1 % 128);
}

struct IntIntFun1 {
    int(*fun)(void*, int);
    void* env;
};

struct IntIntIntFun2 {
    int(*fun)(void*, int, int);
    void* env;
};

struct IntStringTuple2 {
    int t0;
    struct String t1;
};

struct IntStringTuple2List {
    struct IntStringTuple2 head;
    struct IntStringTuple2List* tail;
};

struct IntIntStringTuple2ListTuple2 {
    int t0;
    struct IntStringTuple2List* t1;
};

struct IntIntStringTuple2ListTuple2List {
    struct IntIntStringTuple2ListTuple2 head;
    struct IntIntStringTuple2ListTuple2List* tail;
};

struct IntIntStringTuple2ListTuple2ListIntIntFun1IntIntIntFun2Tuple3 {
    struct IntIntStringTuple2ListTuple2List* t0;
    struct IntIntFun1 t1;
    struct IntIntIntFun2 t2;
};

struct IntIntStringTuple2ListTuple2ListIntIntFun1IntIntIntFun2Tuple3 mapNewSingleton_1(int key_, struct String value_, struct IntIntFun1 hash_, struct IntIntIntFun2 cmp_) {
    int app_ = cmp_.fun(cmp_.env, key_, key_);
    milone_assert((app_ == 0), 12, 2);
    int call_ = 0;
    int app_1 = hash_.fun(hash_.env, key_);
    struct IntStringTuple2 tuple_2;
    tuple_2.t0 = key_;
    tuple_2.t1 = value_;
    struct IntStringTuple2List* list_1 = (struct IntStringTuple2List*)malloc(sizeof(struct IntStringTuple2List));
    list_1->head = tuple_2;
    list_1->tail = NULL;
    struct IntIntStringTuple2ListTuple2 tuple_1;
    tuple_1.t0 = app_1;
    tuple_1.t1 = list_1;
    struct IntIntStringTuple2ListTuple2List* list_ = (struct IntIntStringTuple2ListTuple2List*)malloc(sizeof(struct IntIntStringTuple2ListTuple2List));
    list_->head = tuple_1;
    list_->tail = NULL;
    struct IntIntStringTuple2ListTuple2ListIntIntFun1IntIntIntFun2Tuple3 tuple_;
    tuple_.t0 = list_;
    tuple_.t1 = hash_;
    tuple_.t2 = cmp_;
    return tuple_;
}

int fun_(void* env_, int arg_) {
    int call_1 = intHash_(arg_);
    return call_1;
}

int fun_1(void* env_1, int arg_1, int arg_2) {
    int call_2 = intCmp_(arg_1, arg_2);
    return call_2;
}

int typeTest_(int arg_3) {
    void* box_ = (void*)malloc(sizeof(int));
    (*(((int*)box_))) = 0;
    void* env_2 = box_;
    struct IntIntFun1 fun_2 = (struct IntIntFun1){.fun = fun_, .env = env_2};
    void* box_1 = (void*)malloc(sizeof(int));
    (*(((int*)box_1))) = 0;
    void* env_3 = box_1;
    struct IntIntIntFun2 fun_3 = (struct IntIntIntFun2){.fun = fun_1, .env = env_3};
    struct IntIntStringTuple2ListTuple2ListIntIntFun1IntIntIntFun2Tuple3 call_3 = mapNewSingleton_1(1, (struct String){.str = "a", .len = 1}, fun_2, fun_3);
    struct IntIntStringTuple2ListTuple2ListIntIntFun1IntIntIntFun2Tuple3 map_ = call_3;
    return 0;
}

int main() {
    int call_4 = typeTest_(0);
    return 0;
}
