#include "milone.h"

int intCmp_(int x_, int y_);

int strCmp_(struct String x_1, struct String y_1);

struct StringStringIntFun2;

struct StringIntTuple2;

struct StringIntTuple2List;

struct StringIntTuple2ListStringStringIntFun2Tuple2;

struct StringIntTuple2ListStringStringIntFun2Tuple2 mapNewSingleton_1(struct String key_, int value_, struct StringStringIntFun2 cmp_);

struct IntIntIntFun2;

struct IntStringTuple2;

struct IntStringTuple2List;

struct IntStringTuple2ListIntIntIntFun2Tuple2;

struct IntStringTuple2ListIntIntIntFun2Tuple2 mapEmpty_1(struct IntIntIntFun2 cmp_1);

struct IntStringTuple2ListIntIntIntFun2Tuple2 mapAdd_1(int key_1, struct String value_1, struct IntStringTuple2ListIntIntIntFun2Tuple2 arg_4);

struct String go_1(struct IntIntIntFun2 cmp_3, struct String alt_, int key_2, struct IntStringTuple2List* map_2);

struct String mapFind_1(int key_2, struct String alt_, struct IntStringTuple2ListIntIntIntFun2Tuple2 arg_5);

int fun_(void* env_, struct String arg_, struct String arg_1);

int typeTest_(int arg_6);

int fun_1(void* env_1, int arg_2, int arg_3);

int basicCaseTest_(int arg_7);

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

int strCmp_(struct String x_1, struct String y_1) {
    int match_2;
    if ((str_cmp(y_1, x_1) >= 0)) goto next_8;
    match_2 = 1;
    goto end_match_7;
next_8:;
    if ((str_cmp(y_1, x_1) < 0)) goto next_9;
    int match_3;
    if ((str_cmp(y_1, x_1) != 0)) goto next_11;
    match_3 = 0;
    goto end_match_10;
next_11:;
    if ((str_cmp(y_1, x_1) == 0)) goto next_12;
    match_3 = (0 - 1);
    goto end_match_10;
next_12:;
    exit(1);
end_match_10:;
    match_2 = match_3;
    goto end_match_7;
next_9:;
    exit(1);
end_match_7:;
    return match_2;
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
    milone_assert((app_ == 0), 17, 2);
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

struct IntStringTuple2ListIntIntIntFun2Tuple2 {
    struct IntStringTuple2List* t0;
    struct IntIntIntFun2 t1;
};

struct IntStringTuple2ListIntIntIntFun2Tuple2 mapEmpty_1(struct IntIntIntFun2 cmp_1) {
    struct IntStringTuple2ListIntIntIntFun2Tuple2 tuple_2;
    tuple_2.t0 = NULL;
    tuple_2.t1 = cmp_1;
    return tuple_2;
}

struct IntStringTuple2ListIntIntIntFun2Tuple2 mapAdd_1(int key_1, struct String value_1, struct IntStringTuple2ListIntIntIntFun2Tuple2 arg_4) {
    struct IntStringTuple2List* map_ = arg_4.t0;
    struct IntIntIntFun2 cmp_2 = arg_4.t1;
    struct IntStringTuple2 tuple_4;
    tuple_4.t0 = key_1;
    tuple_4.t1 = value_1;
    struct IntStringTuple2List* list_1 = (struct IntStringTuple2List*)malloc(sizeof(struct IntStringTuple2List));
    list_1->head = tuple_4;
    list_1->tail = map_;
    struct IntStringTuple2ListIntIntIntFun2Tuple2 tuple_3;
    tuple_3.t0 = list_1;
    tuple_3.t1 = cmp_2;
    return tuple_3;
}

struct String go_1(struct IntIntIntFun2 cmp_3, struct String alt_, int key_2, struct IntStringTuple2List* map_2) {
    struct String match_4;
    if ((!((!(map_2))))) goto next_14;
    match_4 = alt_;
    goto end_match_13;
next_14:;
    if ((!(map_2))) goto next_15;
    int k_ = map_2->head.t0;
    struct String v_ = map_2->head.t1;
    int app_1 = cmp_3.fun(cmp_3.env, key_2, k_);
    if ((app_1 != 0)) goto next_15;
    match_4 = v_;
    goto end_match_13;
next_15:;
    if ((!(map_2))) goto next_16;
    struct IntStringTuple2List* map_3 = map_2->tail;
    struct String call_1 = go_1(cmp_3, alt_, key_2, map_3);
    match_4 = call_1;
    goto end_match_13;
next_16:;
    exit(1);
end_match_13:;
    return match_4;
}

struct String mapFind_1(int key_2, struct String alt_, struct IntStringTuple2ListIntIntIntFun2Tuple2 arg_5) {
    struct IntStringTuple2List* map_1 = arg_5.t0;
    struct IntIntIntFun2 cmp_3 = arg_5.t1;
    struct String call_2 = go_1(cmp_3, alt_, key_2, map_1);
    return call_2;
}

int fun_(void* env_, struct String arg_, struct String arg_1) {
    int call_3 = strCmp_(arg_, arg_1);
    return call_3;
}

int typeTest_(int arg_6) {
    void* box_ = (void*)malloc(sizeof(int));
    (*(((int*)box_))) = 0;
    void* env_2 = box_;
    struct StringStringIntFun2 fun_2 = (struct StringStringIntFun2){.fun = fun_, .env = env_2};
    struct StringIntTuple2ListStringStringIntFun2Tuple2 call_4 = mapNewSingleton_1((struct String){.str = "a", .len = 1}, 1, fun_2);
    struct StringIntTuple2ListStringStringIntFun2Tuple2 map_4 = call_4;
    return 0;
}

int fun_1(void* env_1, int arg_2, int arg_3) {
    int call_5 = intCmp_(arg_2, arg_3);
    return call_5;
}

int basicCaseTest_(int arg_7) {
    void* box_1 = (void*)malloc(sizeof(int));
    (*(((int*)box_1))) = 0;
    void* env_3 = box_1;
    struct IntIntIntFun2 fun_3 = (struct IntIntIntFun2){.fun = fun_1, .env = env_3};
    struct IntStringTuple2ListIntIntIntFun2Tuple2 call_6 = mapEmpty_1(fun_3);
    struct IntStringTuple2ListIntIntIntFun2Tuple2 call_7 = mapAdd_1(1, (struct String){.str = "a", .len = 1}, call_6);
    struct IntStringTuple2ListIntIntIntFun2Tuple2 call_8 = mapAdd_1(2, (struct String){.str = "b", .len = 1}, call_7);
    struct IntStringTuple2ListIntIntIntFun2Tuple2 call_9 = mapAdd_1(3, (struct String){.str = "c", .len = 1}, call_8);
    struct IntStringTuple2ListIntIntIntFun2Tuple2 m_ = call_9;
    struct String call_10 = mapFind_1(2, (struct String){.str = "", .len = 0}, m_);
    milone_assert((str_cmp(call_10, (struct String){.str = "b", .len = 1}) == 0), 48, 2);
    int call_11 = 0;
    struct String call_12 = mapFind_1(4, (struct String){.str = "", .len = 0}, m_);
    milone_assert((str_cmp(call_12, (struct String){.str = "", .len = 0}) == 0), 49, 2);
    int call_13 = 0;
    struct IntStringTuple2ListIntIntIntFun2Tuple2 call_14 = mapAdd_1(2, (struct String){.str = "B", .len = 1}, m_);
    struct IntStringTuple2ListIntIntIntFun2Tuple2 n_ = call_14;
    struct String call_15 = mapFind_1(2, (struct String){.str = "", .len = 0}, n_);
    milone_assert((str_cmp(call_15, (struct String){.str = "B", .len = 1}) == 0), 53, 2);
    int call_16 = 0;
    struct String call_17 = mapFind_1(2, (struct String){.str = "", .len = 0}, m_);
    milone_assert((str_cmp(call_17, (struct String){.str = "b", .len = 1}) == 0), 54, 2);
    int call_18 = 0;
    return 0;
}

int main() {
    int call_19 = typeTest_(0);
    int call_20 = basicCaseTest_(0);
    return 0;
}
