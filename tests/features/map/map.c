#include "milone.h"

uint32_t intHash_(int x_);

struct IntUIntFun1;

struct IntIntIntFun2;

struct IntStringTuple2;

struct IntStringTuple2List;

struct UIntIntStringTuple2ListTuple2;

struct UIntIntStringTuple2ListTuple2List;

struct UIntIntStringTuple2ListTuple2ListIntUIntFun1IntIntIntFun2Tuple3;

struct UIntIntStringTuple2ListTuple2ListIntUIntFun1IntIntIntFun2Tuple3 mapNewSingleton_2(int key_, struct String value_, struct IntUIntFun1 hash_, struct IntIntIntFun2 cmp_);

struct IntUnitTuple2;

struct IntUnitTuple2List;

struct UIntIntUnitTuple2ListTuple2;

struct UIntIntUnitTuple2ListTuple2List;

struct UIntIntUnitTuple2ListTuple2ListIntUIntFun1IntIntIntFun2Tuple3;

struct UIntIntUnitTuple2ListTuple2ListIntUIntFun1IntIntIntFun2Tuple3 mapNewSingleton_1(int key_, int value_, struct IntUIntFun1 hash_, struct IntIntIntFun2 cmp_);

uint32_t fun_(void const* env_, int arg_);

int fun_1(void const* env_1, int arg_1, int arg_2);

uint32_t fun_2(void const* env_2, int arg_3);

int fun_3(void const* env_3, int arg_4, int arg_5);

int typeTest_(int arg_6);

int main();

uint32_t intHash_(int x_) {
    return (((uint32_t)x_) % ((uint32_t)128));
}

struct IntUIntFun1 {
    uint32_t(*fun)(void const*, int);
    void const* env;
};

struct IntIntIntFun2 {
    int(*fun)(void const*, int, int);
    void const* env;
};

struct IntStringTuple2 {
    int t0;
    struct String t1;
};

struct IntStringTuple2List {
    struct IntStringTuple2 head;
    struct IntStringTuple2List const* tail;
};

struct UIntIntStringTuple2ListTuple2 {
    uint32_t t0;
    struct IntStringTuple2List const* t1;
};

struct UIntIntStringTuple2ListTuple2List {
    struct UIntIntStringTuple2ListTuple2 head;
    struct UIntIntStringTuple2ListTuple2List const* tail;
};

struct UIntIntStringTuple2ListTuple2ListIntUIntFun1IntIntIntFun2Tuple3 {
    struct UIntIntStringTuple2ListTuple2List const* t0;
    struct IntUIntFun1 t1;
    struct IntIntIntFun2 t2;
};

struct UIntIntStringTuple2ListTuple2ListIntUIntFun1IntIntIntFun2Tuple3 mapNewSingleton_2(int key_, struct String value_, struct IntUIntFun1 hash_, struct IntIntIntFun2 cmp_) {
    int app_ = cmp_.fun(cmp_.env, key_, key_);
    milone_assert((app_ == 0), 13, 2);
    uint32_t app_1 = hash_.fun(hash_.env, key_);
    struct IntStringTuple2 tuple_2;
    tuple_2.t0 = key_;
    tuple_2.t1 = value_;
    struct IntStringTuple2List const* list_1 = milone_mem_alloc(1, sizeof(struct IntStringTuple2List));
    (*(((struct IntStringTuple2List*)list_1))) = (struct IntStringTuple2List){.head = tuple_2, .tail = NULL};
    struct UIntIntStringTuple2ListTuple2 tuple_1;
    tuple_1.t0 = app_1;
    tuple_1.t1 = list_1;
    struct UIntIntStringTuple2ListTuple2List const* list_ = milone_mem_alloc(1, sizeof(struct UIntIntStringTuple2ListTuple2List));
    (*(((struct UIntIntStringTuple2ListTuple2List*)list_))) = (struct UIntIntStringTuple2ListTuple2List){.head = tuple_1, .tail = NULL};
    struct UIntIntStringTuple2ListTuple2ListIntUIntFun1IntIntIntFun2Tuple3 tuple_;
    tuple_.t0 = list_;
    tuple_.t1 = hash_;
    tuple_.t2 = cmp_;
    return tuple_;
}

struct IntUnitTuple2 {
    int t0;
    int t1;
};

struct IntUnitTuple2List {
    struct IntUnitTuple2 head;
    struct IntUnitTuple2List const* tail;
};

struct UIntIntUnitTuple2ListTuple2 {
    uint32_t t0;
    struct IntUnitTuple2List const* t1;
};

struct UIntIntUnitTuple2ListTuple2List {
    struct UIntIntUnitTuple2ListTuple2 head;
    struct UIntIntUnitTuple2ListTuple2List const* tail;
};

struct UIntIntUnitTuple2ListTuple2ListIntUIntFun1IntIntIntFun2Tuple3 {
    struct UIntIntUnitTuple2ListTuple2List const* t0;
    struct IntUIntFun1 t1;
    struct IntIntIntFun2 t2;
};

struct UIntIntUnitTuple2ListTuple2ListIntUIntFun1IntIntIntFun2Tuple3 mapNewSingleton_1(int key_, int value_, struct IntUIntFun1 hash_, struct IntIntIntFun2 cmp_) {
    int app_2 = cmp_.fun(cmp_.env, key_, key_);
    milone_assert((app_2 == 0), 13, 2);
    uint32_t app_3 = hash_.fun(hash_.env, key_);
    struct IntUnitTuple2 tuple_5;
    tuple_5.t0 = key_;
    tuple_5.t1 = 0;
    struct IntUnitTuple2List const* list_3 = milone_mem_alloc(1, sizeof(struct IntUnitTuple2List));
    (*(((struct IntUnitTuple2List*)list_3))) = (struct IntUnitTuple2List){.head = tuple_5, .tail = NULL};
    struct UIntIntUnitTuple2ListTuple2 tuple_4;
    tuple_4.t0 = app_3;
    tuple_4.t1 = list_3;
    struct UIntIntUnitTuple2ListTuple2List const* list_2 = milone_mem_alloc(1, sizeof(struct UIntIntUnitTuple2ListTuple2List));
    (*(((struct UIntIntUnitTuple2ListTuple2List*)list_2))) = (struct UIntIntUnitTuple2ListTuple2List){.head = tuple_4, .tail = NULL};
    struct UIntIntUnitTuple2ListTuple2ListIntUIntFun1IntIntIntFun2Tuple3 tuple_3;
    tuple_3.t0 = list_2;
    tuple_3.t1 = hash_;
    tuple_3.t2 = cmp_;
    return tuple_3;
}

uint32_t fun_(void const* env_, int arg_) {
    uint32_t call_ = intHash_(arg_);
    return call_;
}

int fun_1(void const* env_1, int arg_1, int arg_2) {
    return int_compare(arg_1, arg_2);
}

uint32_t fun_2(void const* env_2, int arg_3) {
    uint32_t call_1 = intHash_(arg_3);
    return call_1;
}

int fun_3(void const* env_3, int arg_4, int arg_5) {
    return int_compare(arg_4, arg_5);
}

int typeTest_(int arg_6) {
    void const* box_ = milone_mem_alloc(1, sizeof(int));
    (*(((int*)box_))) = 0;
    void const* env_4 = box_;
    struct IntUIntFun1 fun_4 = (struct IntUIntFun1){.fun = fun_, .env = env_4};
    void const* box_1 = milone_mem_alloc(1, sizeof(int));
    (*(((int*)box_1))) = 0;
    void const* env_5 = box_1;
    struct IntIntIntFun2 fun_5 = (struct IntIntIntFun2){.fun = fun_1, .env = env_5};
    struct UIntIntStringTuple2ListTuple2ListIntUIntFun1IntIntIntFun2Tuple3 call_2 = mapNewSingleton_2(1, (struct String){.str = "a", .len = 1}, fun_4, fun_5);
    struct UIntIntStringTuple2ListTuple2ListIntUIntFun1IntIntIntFun2Tuple3 map_ = call_2;
    void const* box_2 = milone_mem_alloc(1, sizeof(int));
    (*(((int*)box_2))) = 0;
    void const* env_6 = box_2;
    struct IntUIntFun1 fun_6 = (struct IntUIntFun1){.fun = fun_2, .env = env_6};
    void const* box_3 = milone_mem_alloc(1, sizeof(int));
    (*(((int*)box_3))) = 0;
    void const* env_7 = box_3;
    struct IntIntIntFun2 fun_7 = (struct IntIntIntFun2){.fun = fun_3, .env = env_7};
    struct UIntIntUnitTuple2ListTuple2ListIntUIntFun1IntIntIntFun2Tuple3 call_3 = mapNewSingleton_1(2, 0, fun_6, fun_7);
    struct UIntIntUnitTuple2ListTuple2ListIntUIntFun1IntIntIntFun2Tuple3 set_ = call_3;
    return 0;
}

int main() {
    int call_4 = typeTest_(0);
    return 0;
}
