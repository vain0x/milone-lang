#include "milone.h"

struct IntIntTuple2;

struct StringStringTuple2;

struct StringList;

struct StringStringListTuple2;

struct StringList;

int pair_2(struct IntIntTuple2 arg_);

int pair_1(struct StringStringTuple2 arg_1);

char useStringIndexWithoutAscription_(struct String x_);

struct StringStringListTuple2 useTyVarInBody_1(struct String x_1);

int milone_main();

struct IntIntTuple2 {
    int t0;
    int t1;
};

struct StringStringTuple2 {
    struct String t0;
    struct String t1;
};

struct StringStringListTuple2 {
    struct String t0;
    struct StringList const* t1;
};

struct StringList {
    struct String head;
    struct StringList const* tail;
};

int pair_2(struct IntIntTuple2 arg_) {
    return 2;
}

int pair_1(struct StringStringTuple2 arg_1) {
    return 2;
}

char useStringIndexWithoutAscription_(struct String x_) {
    struct StringStringTuple2 tuple_ = (struct StringStringTuple2){.t0 = x_, .t1 = (struct String){.str = "", .len = 0}};
    int call_ = pair_1(tuple_);
    return x_.str[0];
}

struct StringStringListTuple2 useTyVarInBody_1(struct String x_1) {
    struct StringList const* xs_ = NULL;
    struct StringStringListTuple2 tuple_1 = (struct StringStringListTuple2){.t0 = x_1, .t1 = xs_};
    return tuple_1;
}

int milone_main() {
    struct IntIntTuple2 tuple_2 = (struct IntIntTuple2){.t0 = 0, .t1 = 0};
    int call_1 = pair_2(tuple_2);
    milone_assert((call_1 == 2), 18, 2);
    struct StringStringTuple2 tuple_3 = (struct StringStringTuple2){.t0 = (struct String){.str = "", .len = 0}, .t1 = (struct String){.str = "", .len = 0}};
    int call_2 = pair_1(tuple_3);
    milone_assert((call_2 == 2), 19, 2);
    char call_3 = useStringIndexWithoutAscription_((struct String){.str = "a", .len = 1});
    milone_assert((call_3 == 'a'), 21, 2);
    char match_;
    struct StringStringListTuple2 call_4 = useTyVarInBody_1((struct String){.str = "b", .len = 1});
    if ((!(call_4.t1))) goto next_2;
    struct String s_ = call_4.t1->head;
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
