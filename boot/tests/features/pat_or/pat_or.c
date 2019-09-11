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
    if (!((x_ == 0))) goto next_3;
    goto match_body_2;
next_3:;
    if (!((x_ == 1))) goto next_4;
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
    int match_2;
    int call_ = isZeroOrOne_(0);
    if (!((call_ == 1))) goto next_8;
    int call_1 = isZeroOrOne_(1);
    match_2 = call_1;
    goto end_match_7;
next_8:;
    if (!((call_ == 0))) goto next_9;
    match_2 = 0;
    goto end_match_7;
next_9:;
    exit(1);
end_match_7:;
    if (!(((!(match_2)) == 1))) goto next_10;
    exit(1);
    match_1 = 0;
    goto end_match_6;
next_10:;
    if (!(((!(match_2)) == 0))) goto next_11;
    match_1 = 0;
    goto end_match_6;
next_11:;
    exit(1);
end_match_6:;
    int match_3;
    int call_2 = isZeroOrOne_(2);
    if (!((call_2 == 1))) goto next_13;
    exit(1);
    match_3 = 0;
    goto end_match_12;
next_13:;
    if (!((call_2 == 0))) goto next_14;
    match_3 = 0;
    goto end_match_12;
next_14:;
    exit(1);
end_match_12:;
    return 0;
}

struct IntList {
    int head;
    struct IntList* tail;
};

int startsWithDoubleBits_(struct IntList* xs_) {
    int match_4;
    if (!((!((!(xs_)))))) goto next_17;
    if (!((xs_->head == 0))) goto next_17;
    if (!((!((!(xs_->tail)))))) goto next_17;
    if (!((xs_->tail->head == 0))) goto next_17;
    goto match_body_16;
next_17:;
    if (!((!((!(xs_)))))) goto next_18;
    if (!((xs_->head == 0))) goto next_18;
    if (!((!((!(xs_->tail)))))) goto next_18;
    if (!((xs_->tail->head == 1))) goto next_18;
    goto match_body_16;
next_18:;
    if (!((!((!(xs_)))))) goto next_19;
    if (!((xs_->head == 1))) goto next_19;
    if (!((!((!(xs_->tail)))))) goto next_19;
    if (!((xs_->tail->head == 0))) goto next_19;
    goto match_body_16;
next_19:;
    if (!((!((!(xs_)))))) goto next_20;
    if (!((xs_->head == 1))) goto next_20;
    if (!((!((!(xs_->tail)))))) goto next_20;
    if (!((xs_->tail->head == 1))) goto next_20;
    goto match_body_16;
match_body_16:;
    match_4 = 1;
    goto end_match_15;
next_20:;
    match_4 = 0;
    goto end_match_15;
next_21:;
end_match_15:;
    return match_4;
}

int nestedCase_(int arg_1) {
    int match_5;
    struct IntList* list_2 = (struct IntList*)malloc(sizeof(struct IntList));
    list_2->head = 2;
    list_2->tail = NULL;
    struct IntList* list_1 = (struct IntList*)malloc(sizeof(struct IntList));
    list_1->head = 1;
    list_1->tail = list_2;
    struct IntList* list_ = (struct IntList*)malloc(sizeof(struct IntList));
    list_->head = 0;
    list_->tail = list_1;
    int call_3 = startsWithDoubleBits_(list_);
    if (!(((!(call_3)) == 1))) goto next_23;
    exit(1);
    match_5 = 0;
    goto end_match_22;
next_23:;
    if (!(((!(call_3)) == 0))) goto next_24;
    match_5 = 0;
    goto end_match_22;
next_24:;
    exit(1);
end_match_22:;
    int match_6;
    struct IntList* list_4 = (struct IntList*)malloc(sizeof(struct IntList));
    list_4->head = 2;
    list_4->tail = NULL;
    struct IntList* list_3 = (struct IntList*)malloc(sizeof(struct IntList));
    list_3->head = 1;
    list_3->tail = list_4;
    int call_4 = startsWithDoubleBits_(list_3);
    if (!((call_4 == 1))) goto next_26;
    exit(1);
    match_6 = 0;
    goto end_match_25;
next_26:;
    if (!((call_4 == 0))) goto next_27;
    match_6 = 0;
    goto end_match_25;
next_27:;
    exit(1);
end_match_25:;
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
    int match_7;
    if (!(((*(expr_.Add_)).t0 == 0))) goto next_30;
    if (!(((*(expr_.Add_)).t1 == 0))) goto next_30;
    goto match_body_29;
next_30:;
    if (!(((*(expr_.Add_)).t0 == 0))) goto next_31;
    if (!(((*(expr_.Add_)).t1 == 1))) goto next_31;
    goto match_body_29;
match_body_29:;
    match_7 = 1;
    goto end_match_28;
next_31:;
    match_7 = 0;
    goto end_match_28;
next_32:;
end_match_28:;
    return match_7;
}

int complexCase_(int arg_2) {
    int match_8;
    struct IntIntTuple2 tuple_;
    tuple_.t0 = 0;
    tuple_.t1 = 1;
    struct IntIntTuple2* payload_ = (struct IntIntTuple2*)malloc(sizeof(struct IntIntTuple2));
    (*(((struct IntIntTuple2*)payload_))) = tuple_;
    struct Expr_ variant_ = (struct Expr_){.tag = Add_, .Add_ = payload_};
    int call_5 = performComplexMatching_(variant_);
    if (!(((!(call_5)) == 1))) goto next_34;
    exit(1);
    match_8 = 0;
    goto end_match_33;
next_34:;
    if (!(((!(call_5)) == 0))) goto next_35;
    match_8 = 0;
    goto end_match_33;
next_35:;
    exit(1);
end_match_33:;
    int match_9;
    struct IntIntTuple2 tuple_1;
    tuple_1.t0 = 1;
    tuple_1.t1 = 2;
    struct IntIntTuple2* payload_1 = (struct IntIntTuple2*)malloc(sizeof(struct IntIntTuple2));
    (*(((struct IntIntTuple2*)payload_1))) = tuple_1;
    struct Expr_ variant_1 = (struct Expr_){.tag = Add_, .Add_ = payload_1};
    int call_6 = performComplexMatching_(variant_1);
    if (!((call_6 == 1))) goto next_37;
    exit(1);
    match_9 = 0;
    goto end_match_36;
next_37:;
    if (!((call_6 == 0))) goto next_38;
    match_9 = 0;
    goto end_match_36;
next_38:;
    exit(1);
end_match_36:;
    return 0;
}

int main() {
    int call_7 = simpleCase_(0);
    int call_8 = nestedCase_(0);
    int call_9 = complexCase_(0);
    return 0;
}
