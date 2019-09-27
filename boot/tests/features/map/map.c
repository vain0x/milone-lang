#include "milone.h"

int strCmp_(struct String x_, struct String y_);

struct StringStringIntFun2;

struct StringIntTuple2;

struct StringIntTuple2List;

struct StringIntTuple2ListStringStringIntFun2Tuple2;

struct StringIntTuple2ListStringStringIntFun2Tuple2 mapNewSingleton_1(struct String key_, int value_, struct StringStringIntFun2 cmp_);

int fun_(void* env_, struct String arg_, struct String arg_1);

int main();

int strCmp_(struct String x_, struct String y_) {
    int match_;
    if ((str_cmp(y_, x_) >= 0)) goto next_2;
    match_ = 1;
    goto end_match_1;
next_2:;
    if ((str_cmp(y_, x_) < 0)) goto next_3;
    int match_1;
    if ((str_cmp(y_, x_) != 0)) goto next_5;
    match_1 = 0;
    goto end_match_4;
next_5:;
    if ((str_cmp(y_, x_) == 0)) goto next_6;
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

struct StringStringIntFun2 {
    int(*fun)(void*, struct String, struct String);
    void* env;
};

struct StringIntTuple2 {
    struct String t0;
    int t1;
};

struct StringIntTuple2List {
    struct StringIntTuple2 head;
    struct StringIntTuple2List* tail;
};

struct StringIntTuple2ListStringStringIntFun2Tuple2 {
    struct StringIntTuple2List* t0;
    struct StringStringIntFun2 t1;
};

struct StringIntTuple2ListStringStringIntFun2Tuple2 mapNewSingleton_1(struct String key_, int value_, struct StringStringIntFun2 cmp_) {
    int app_ = cmp_.fun(cmp_.env, key_, key_);
    milone_assert((app_ == 0), 9, 2);
    int call_ = 0;
    struct StringIntTuple2 tuple_1;
    tuple_1.t0 = key_;
    tuple_1.t1 = value_;
    struct StringIntTuple2List* list_ = (struct StringIntTuple2List*)malloc(sizeof(struct StringIntTuple2List));
    list_->head = tuple_1;
    list_->tail = NULL;
    struct StringIntTuple2ListStringStringIntFun2Tuple2 tuple_;
    tuple_.t0 = list_;
    tuple_.t1 = cmp_;
    return tuple_;
}

int fun_(void* env_, struct String arg_, struct String arg_1) {
    int call_1 = strCmp_(arg_, arg_1);
    return call_1;
}

int main() {
    void* box_ = (void*)malloc(sizeof(int));
    (*(((int*)box_))) = 0;
    void* env_1 = box_;
    struct StringStringIntFun2 fun_1 = (struct StringStringIntFun2){.fun = fun_, .env = env_1};
    struct StringIntTuple2ListStringStringIntFun2Tuple2 call_2 = mapNewSingleton_1((struct String){.str = "a", .len = 1}, 1, fun_1);
    struct StringIntTuple2ListStringStringIntFun2Tuple2 map_ = call_2;
    return 0;
}
