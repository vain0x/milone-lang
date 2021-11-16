#include "milone.h"

struct StringList;

struct StringStringListTuple2_;

struct StringStringTuple2_;

struct IntIntTuple2_;

struct StringList;

struct StringStringListTuple2_ ty_var_ty_var_StringStringStringListTuple2Fun1_useTyVarInBody(struct String x_1);

char ty_var_ty_var_StringCharFun1_useStringIndexWithoutAscription(struct String x_);

int ty_var_ty_var_StringStringTuple2IntFun1_pair(struct StringStringTuple2_ arg_);

int ty_var_ty_var_IntIntTuple2IntFun1_pair(struct IntIntTuple2_ arg_1);

int milone_main(void);

struct StringStringListTuple2_ {
    struct String t0;
    struct StringList const* t1;
};

struct StringStringTuple2_ {
    struct String t0;
    struct String t1;
};

struct IntIntTuple2_ {
    int t0;
    int t1;
};

struct StringList {
    struct String head;
    struct StringList const* tail;
};

struct StringStringListTuple2_ ty_var_ty_var_StringStringStringListTuple2Fun1_useTyVarInBody(struct String x_1) {
    struct StringList const* xs_ = NULL;
    struct StringStringListTuple2_ StringStringListTuple2_ = (struct StringStringListTuple2_){.t0 = x_1, .t1 = xs_};
    return StringStringListTuple2_;
}

char ty_var_ty_var_StringCharFun1_useStringIndexWithoutAscription(struct String x_) {
    struct StringStringTuple2_ StringStringTuple2_ = (struct StringStringTuple2_){.t0 = x_, .t1 = (struct String){.str = "", .len = 0}};
    int call_ = ty_var_ty_var_StringStringTuple2IntFun1_pair(StringStringTuple2_);
    return x_.str[0];
}

int ty_var_ty_var_StringStringTuple2IntFun1_pair(struct StringStringTuple2_ arg_) {
    return 2;
}

int ty_var_ty_var_IntIntTuple2IntFun1_pair(struct IntIntTuple2_ arg_1) {
    return 2;
}

int milone_main(void) {
    struct String s_;
    struct IntIntTuple2_ IntIntTuple2_ = (struct IntIntTuple2_){.t0 = 0, .t1 = 0};
    int call_1 = ty_var_ty_var_IntIntTuple2IntFun1_pair(IntIntTuple2_);
    milone_assert((call_1 == 2), 18, 2);
    struct StringStringTuple2_ StringStringTuple2_1 = (struct StringStringTuple2_){.t0 = (struct String){.str = "", .len = 0}, .t1 = (struct String){.str = "", .len = 0}};
    int call_2 = ty_var_ty_var_StringStringTuple2IntFun1_pair(StringStringTuple2_1);
    milone_assert((call_2 == 2), 19, 2);
    char call_3 = ty_var_ty_var_StringCharFun1_useStringIndexWithoutAscription((struct String){.str = "a", .len = 1});
    milone_assert((call_3 == 'a'), 21, 2);
    char match_;
    struct StringStringListTuple2_ call_4 = ty_var_ty_var_StringStringStringListTuple2Fun1_useTyVarInBody((struct String){.str = "b", .len = 1});
    if ((!(call_4.t1))) goto next_2;
    s_ = call_4.t1->head;
    milone_assert((s_.str[0] == 'b'), 24, 17);
    match_ = 0;
    goto end_match_1;
next_2:;
    match_ = 0;
    goto end_match_1;
next_3:;
end_match_1:;
    return 0;
}
