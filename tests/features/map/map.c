#include "milone.h"

int intCmp_(int x_, int y_);

uint32_t intHash_(int x_1);

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

uint32_t fun_(void* env_, int arg_);

int fun_1(void* env_1, int arg_1, int arg_2);

uint32_t fun_2(void* env_2, int arg_3);

int fun_3(void* env_3, int arg_4, int arg_5);

int typeTest_(int arg_6);

int main();

int intCmp_(int x_, int y_) {
    int if_;
    if ((y_ < x_)) {
        goto then_2;
    } else {
        goto else_3;
    }
then_2:;
    if_ = 1;
    goto if_next_1;
else_3:;
    int if_1;
    if ((y_ == x_)) {
        goto then_5;
    } else {
        goto else_6;
    }
then_5:;
    if_1 = 0;
    goto if_next_4;
else_6:;
    if_1 = (0 - 1);
    goto if_next_4;
if_next_4:;
    if_ = if_1;
    goto if_next_1;
if_next_1:;
    return if_;
}

uint32_t intHash_(int x_1) {
    return (((uint32_t)x_1) % ((uint32_t)128));
}

struct IntUIntFun1 {
    uint32_t(*fun)(void*, int);
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

struct UIntIntStringTuple2ListTuple2 {
    uint32_t t0;
    struct IntStringTuple2List* t1;
};

struct UIntIntStringTuple2ListTuple2List {
    struct UIntIntStringTuple2ListTuple2 head;
    struct UIntIntStringTuple2ListTuple2List* tail;
};

struct UIntIntStringTuple2ListTuple2ListIntUIntFun1IntIntIntFun2Tuple3 {
    struct UIntIntStringTuple2ListTuple2List* t0;
    struct IntUIntFun1 t1;
    struct IntIntIntFun2 t2;
};

struct UIntIntStringTuple2ListTuple2ListIntUIntFun1IntIntIntFun2Tuple3 mapNewSingleton_2(int key_, struct String value_, struct IntUIntFun1 hash_, struct IntIntIntFun2 cmp_) {
    int app_ = cmp_.fun(cmp_.env, key_, key_);
    milone_assert((app_ == 0), 18, 2);
    int call_ = 0;
    uint32_t app_1 = hash_.fun(hash_.env, key_);
    struct IntStringTuple2 tuple_2;
    tuple_2.t0 = key_;
    tuple_2.t1 = value_;
    struct IntStringTuple2List* list_1 = (struct IntStringTuple2List*)milone_mem_alloc(1, sizeof(struct IntStringTuple2List));
    list_1->head = tuple_2;
    list_1->tail = NULL;
    struct UIntIntStringTuple2ListTuple2 tuple_1;
    tuple_1.t0 = app_1;
    tuple_1.t1 = list_1;
    struct UIntIntStringTuple2ListTuple2List* list_ = (struct UIntIntStringTuple2ListTuple2List*)milone_mem_alloc(1, sizeof(struct UIntIntStringTuple2ListTuple2List));
    list_->head = tuple_1;
    list_->tail = NULL;
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
    struct IntUnitTuple2List* tail;
};

struct UIntIntUnitTuple2ListTuple2 {
    uint32_t t0;
    struct IntUnitTuple2List* t1;
};

struct UIntIntUnitTuple2ListTuple2List {
    struct UIntIntUnitTuple2ListTuple2 head;
    struct UIntIntUnitTuple2ListTuple2List* tail;
};

struct UIntIntUnitTuple2ListTuple2ListIntUIntFun1IntIntIntFun2Tuple3 {
    struct UIntIntUnitTuple2ListTuple2List* t0;
    struct IntUIntFun1 t1;
    struct IntIntIntFun2 t2;
};

struct UIntIntUnitTuple2ListTuple2ListIntUIntFun1IntIntIntFun2Tuple3 mapNewSingleton_1(int key_, int value_, struct IntUIntFun1 hash_, struct IntIntIntFun2 cmp_) {
    int app_2 = cmp_.fun(cmp_.env, key_, key_);
    milone_assert((app_2 == 0), 18, 2);
    int call_1 = 0;
    uint32_t app_3 = hash_.fun(hash_.env, key_);
    struct IntUnitTuple2 tuple_5;
    tuple_5.t0 = key_;
    tuple_5.t1 = 0;
    struct IntUnitTuple2List* list_3 = (struct IntUnitTuple2List*)milone_mem_alloc(1, sizeof(struct IntUnitTuple2List));
    list_3->head = tuple_5;
    list_3->tail = NULL;
    struct UIntIntUnitTuple2ListTuple2 tuple_4;
    tuple_4.t0 = app_3;
    tuple_4.t1 = list_3;
    struct UIntIntUnitTuple2ListTuple2List* list_2 = (struct UIntIntUnitTuple2ListTuple2List*)milone_mem_alloc(1, sizeof(struct UIntIntUnitTuple2ListTuple2List));
    list_2->head = tuple_4;
    list_2->tail = NULL;
    struct UIntIntUnitTuple2ListTuple2ListIntUIntFun1IntIntIntFun2Tuple3 tuple_3;
    tuple_3.t0 = list_2;
    tuple_3.t1 = hash_;
    tuple_3.t2 = cmp_;
    return tuple_3;
}

uint32_t fun_(void* env_, int arg_) {
    uint32_t call_2 = intHash_(arg_);
    return call_2;
}

int fun_1(void* env_1, int arg_1, int arg_2) {
    int call_3 = intCmp_(arg_1, arg_2);
    return call_3;
}

uint32_t fun_2(void* env_2, int arg_3) {
    uint32_t call_4 = intHash_(arg_3);
    return call_4;
}

int fun_3(void* env_3, int arg_4, int arg_5) {
    int call_5 = intCmp_(arg_4, arg_5);
    return call_5;
}

int typeTest_(int arg_6) {
    void* box_ = (void*)milone_mem_alloc(1, sizeof(int));
    (*(((int*)box_))) = 0;
    void* env_4 = box_;
    struct IntUIntFun1 fun_4 = (struct IntUIntFun1){.fun = fun_, .env = env_4};
    void* box_1 = (void*)milone_mem_alloc(1, sizeof(int));
    (*(((int*)box_1))) = 0;
    void* env_5 = box_1;
    struct IntIntIntFun2 fun_5 = (struct IntIntIntFun2){.fun = fun_1, .env = env_5};
    struct UIntIntStringTuple2ListTuple2ListIntUIntFun1IntIntIntFun2Tuple3 call_6 = mapNewSingleton_2(1, (struct String){.str = "a", .len = 1}, fun_4, fun_5);
    struct UIntIntStringTuple2ListTuple2ListIntUIntFun1IntIntIntFun2Tuple3 map_ = call_6;
    void* box_2 = (void*)milone_mem_alloc(1, sizeof(int));
    (*(((int*)box_2))) = 0;
    void* env_6 = box_2;
    struct IntUIntFun1 fun_6 = (struct IntUIntFun1){.fun = fun_2, .env = env_6};
    void* box_3 = (void*)milone_mem_alloc(1, sizeof(int));
    (*(((int*)box_3))) = 0;
    void* env_7 = box_3;
    struct IntIntIntFun2 fun_7 = (struct IntIntIntFun2){.fun = fun_3, .env = env_7};
    struct UIntIntUnitTuple2ListTuple2ListIntUIntFun1IntIntIntFun2Tuple3 call_7 = mapNewSingleton_1(2, 0, fun_6, fun_7);
    struct UIntIntUnitTuple2ListTuple2ListIntUIntFun1IntIntIntFun2Tuple3 set_ = call_7;
    return 0;
}

int main() {
    int call_8 = typeTest_(0);
    return 0;
}
