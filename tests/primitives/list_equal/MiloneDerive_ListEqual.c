#include "milone.h"

struct IntList;

struct IntIntBoolFun2;

struct IntStringTuple2_;

struct IntStringTuple2_List;

struct IntStringTuple2_IntStringTuple2_BoolFun2;

bool fun_(void const* env_, int arg_, int arg_1);

bool genericListEqual_1(struct IntIntBoolFun2 , struct IntList const* , struct IntList const* );

bool listEqual_(struct IntList const* l_, struct IntList const* r_);

bool tuple2Equal_(struct IntStringTuple2_ , struct IntStringTuple2_ );

bool fun_1(void const* env_1, struct IntStringTuple2_ arg_2, struct IntStringTuple2_ arg_3);

bool genericListEqual_(struct IntStringTuple2_IntStringTuple2_BoolFun2 , struct IntStringTuple2_List const* , struct IntStringTuple2_List const* );

bool listEqual_1(struct IntStringTuple2_List const* l_1, struct IntStringTuple2_List const* r_1);

struct IntIntBoolFun2 {
    bool(*fun)(void const*, int, int);
    void const* env;
};

struct IntStringTuple2_ {
    int t0;
    struct String t1;
};

struct IntStringTuple2_IntStringTuple2_BoolFun2 {
    bool(*fun)(void const*, struct IntStringTuple2_, struct IntStringTuple2_);
    void const* env;
};

bool fun_(void const* env_, int arg_, int arg_1) {
    return (arg_ == arg_1);
}

bool listEqual_(struct IntList const* l_, struct IntList const* r_) {
    struct IntIntBoolFun2 fun_2 = (struct IntIntBoolFun2){.fun = fun_, .env = NULL};
    bool call_ = genericListEqual_1(fun_2, l_, r_);
    return call_;
}

bool fun_1(void const* env_1, struct IntStringTuple2_ arg_2, struct IntStringTuple2_ arg_3) {
    bool call_1 = tuple2Equal_(arg_2, arg_3);
    return call_1;
}

bool listEqual_1(struct IntStringTuple2_List const* l_1, struct IntStringTuple2_List const* r_1) {
    struct IntStringTuple2_IntStringTuple2_BoolFun2 fun_3 = (struct IntStringTuple2_IntStringTuple2_BoolFun2){.fun = fun_1, .env = NULL};
    bool call_2 = genericListEqual_(fun_3, l_1, r_1);
    return call_2;
}
