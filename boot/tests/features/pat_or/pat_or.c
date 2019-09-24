#include "milone.h"

int isZeroOrOne_(int x_);

int simpleCase_(int arg_);

struct IntList;

int startsWithDoubleBits_(struct IntList* xs_);

int nestedCase_(int arg_1);

enum Expr_Tag;

struct Expr_;

struct IntIntTuple2;

int performComplexMatching_(struct Expr_ expr_);

int complexCase_(int arg_2);

int main();

int isZeroOrOne_(int x_) {
    int match_;
    if ((x_ != 0)) goto next_3;
    goto match_body_2;
next_3:;
    if ((x_ != 1)) goto next_4;
    goto match_body_2;
match_body_2:;
    match_ = 1;
    goto end_match_1;
next_4:;
    match_ = 0;
    goto end_match_1;
next_5:;
end_match_1:;
    return match_;
}

int simpleCase_(int arg_) {
    int match_1;
    int call_ = isZeroOrOne_(0);
    if ((!(call_))) goto next_7;
    int call_1 = isZeroOrOne_(1);
    match_1 = call_1;
    goto end_match_6;
next_7:;
    if (call_) goto next_8;
    match_1 = 0;
    goto end_match_6;
next_8:;
    exit(1);
end_match_6:;
    milone_assert(match_1, 8, 2);
    int call_2 = 0;
    int call_3 = isZeroOrOne_(2);
    milone_assert((!(call_3)), 9, 2);
    int call_4 = 0;
    return 0;
}

struct IntList {
    int head;
    struct IntList* tail;
};

int startsWithDoubleBits_(struct IntList* xs_) {
    int match_2;
    if ((!(xs_))) goto next_11;
    if ((xs_->head != 0)) goto next_11;
    if ((!(xs_->tail))) goto next_11;
    if ((xs_->tail->head != 0)) goto next_11;
    goto match_body_10;
next_11:;
    if ((!(xs_))) goto next_12;
    if ((xs_->head != 0)) goto next_12;
    if ((!(xs_->tail))) goto next_12;
    if ((xs_->tail->head != 1)) goto next_12;
    goto match_body_10;
next_12:;
    if ((!(xs_))) goto next_13;
    if ((xs_->head != 1)) goto next_13;
    if ((!(xs_->tail))) goto next_13;
    if ((xs_->tail->head != 0)) goto next_13;
    goto match_body_10;
next_13:;
    if ((!(xs_))) goto next_14;
    if ((xs_->head != 1)) goto next_14;
    if ((!(xs_->tail))) goto next_14;
    if ((xs_->tail->head != 1)) goto next_14;
    goto match_body_10;
match_body_10:;
    match_2 = 1;
    goto end_match_9;
next_14:;
    match_2 = 0;
    goto end_match_9;
next_15:;
end_match_9:;
    return match_2;
}

int nestedCase_(int arg_1) {
    struct IntList* list_2 = (struct IntList*)malloc(sizeof(struct IntList));
    list_2->head = 2;
    list_2->tail = NULL;
    struct IntList* list_1 = (struct IntList*)malloc(sizeof(struct IntList));
    list_1->head = 1;
    list_1->tail = list_2;
    struct IntList* list_ = (struct IntList*)malloc(sizeof(struct IntList));
    list_->head = 0;
    list_->tail = list_1;
    int call_5 = startsWithDoubleBits_(list_);
    milone_assert(call_5, 20, 2);
    int call_6 = 0;
    struct IntList* list_4 = (struct IntList*)malloc(sizeof(struct IntList));
    list_4->head = 2;
    list_4->tail = NULL;
    struct IntList* list_3 = (struct IntList*)malloc(sizeof(struct IntList));
    list_3->head = 1;
    list_3->tail = list_4;
    int call_7 = startsWithDoubleBits_(list_3);
    milone_assert((!(call_7)), 21, 2);
    int call_8 = 0;
    return 0;
}

enum Expr_Tag {
    Add_,
};

struct Expr_ {
    enum Expr_Tag tag;
    union {
        struct IntIntTuple2* Add_;
    };
};

struct IntIntTuple2 {
    int t0;
    int t1;
};

int performComplexMatching_(struct Expr_ expr_) {
    int match_3;
    if (((*(expr_.Add_)).t0 != 0)) goto next_18;
    if (((*(expr_.Add_)).t1 != 0)) goto next_18;
    goto match_body_17;
next_18:;
    if (((*(expr_.Add_)).t0 != 0)) goto next_19;
    if (((*(expr_.Add_)).t1 != 1)) goto next_19;
    goto match_body_17;
match_body_17:;
    match_3 = 1;
    goto end_match_16;
next_19:;
    match_3 = 0;
    goto end_match_16;
next_20:;
end_match_16:;
    return match_3;
}

int complexCase_(int arg_2) {
    struct IntIntTuple2 tuple_;
    tuple_.t0 = 0;
    tuple_.t1 = 1;
    struct IntIntTuple2* payload_ = (struct IntIntTuple2*)malloc(sizeof(struct IntIntTuple2));
    (*(((struct IntIntTuple2*)payload_))) = tuple_;
    struct Expr_ variant_ = (struct Expr_){.tag = Add_, .Add_ = payload_};
    int call_9 = performComplexMatching_(variant_);
    milone_assert(call_9, 35, 2);
    int call_10 = 0;
    struct IntIntTuple2 tuple_1;
    tuple_1.t0 = 1;
    tuple_1.t1 = 2;
    struct IntIntTuple2* payload_1 = (struct IntIntTuple2*)malloc(sizeof(struct IntIntTuple2));
    (*(((struct IntIntTuple2*)payload_1))) = tuple_1;
    struct Expr_ variant_1 = (struct Expr_){.tag = Add_, .Add_ = payload_1};
    int call_11 = performComplexMatching_(variant_1);
    milone_assert((!(call_11)), 36, 2);
    int call_12 = 0;
    return 0;
}

int main() {
    int call_13 = simpleCase_(0);
    int call_14 = nestedCase_(0);
    int call_15 = complexCase_(0);
    return 0;
}
