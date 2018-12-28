int isZeroOrOne_(int x_);

int simpleCase_(int arg_);

struct IntList;

int startsWithDoubleBits_(struct IntList* xs_);

int nestedCase_(int arg_1);

struct IntIntTuple2;

enum Expr_Tag;

struct Expr_;

int performComplexMatching_(struct Expr_ expr_);

int complexCase_(int arg_2);

int main();

int isZeroOrOne_(int x_) {
    int match_;
    if (!((x_ == 0))) goto next_2;
    match_ = 1;
    goto end_match_1;
next_2:;
    if (!((x_ == 1))) goto next_3;
    match_ = 1;
    goto end_match_1;
next_3:;
    match_ = 0;
    goto end_match_1;
next_4:;
end_match_1:;
    return match_;
}

int simpleCase_(int arg_) {
    int match_1;
    int match_2;
    int call_ = isZeroOrOne_(0);
    if (!((call_ == 1))) goto next_7;
    int call_1 = isZeroOrOne_(1);
    match_2 = call_1;
    goto end_match_6;
next_7:;
    if (!((call_ == 0))) goto next_8;
    match_2 = 0;
    goto end_match_6;
next_8:;
    exit(1);
end_match_6:;
    if (!(((!(match_2)) == 1))) goto next_9;
    exit(1);
    match_1 = 0;
    goto end_match_5;
next_9:;
    if (!(((!(match_2)) == 0))) goto next_10;
    match_1 = 0;
    goto end_match_5;
next_10:;
    exit(1);
end_match_5:;
    int match_3;
    int call_2 = isZeroOrOne_(2);
    if (!((call_2 == 1))) goto next_12;
    exit(1);
    match_3 = 0;
    goto end_match_11;
next_12:;
    if (!((call_2 == 0))) goto next_13;
    match_3 = 0;
    goto end_match_11;
next_13:;
    exit(1);
end_match_11:;
    return 0;
}

struct IntList {
    int head;
    struct IntList* tail;
};

int startsWithDoubleBits_(struct IntList* xs_) {
    int match_4;
    if (!((!((!(xs_)))))) goto next_15;
    if (!((xs_->head == 0))) goto next_15;
    if (!((!((!(xs_->tail)))))) goto next_15;
    if (!((xs_->tail->head == 0))) goto next_15;
    match_4 = 1;
    goto end_match_14;
next_15:;
    if (!((!((!(xs_)))))) goto next_16;
    if (!((xs_->head == 0))) goto next_16;
    if (!((!((!(xs_->tail)))))) goto next_16;
    if (!((xs_->tail->head == 1))) goto next_16;
    match_4 = 1;
    goto end_match_14;
next_16:;
    if (!((!((!(xs_)))))) goto next_17;
    if (!((xs_->head == 1))) goto next_17;
    if (!((!((!(xs_->tail)))))) goto next_17;
    if (!((xs_->tail->head == 0))) goto next_17;
    match_4 = 1;
    goto end_match_14;
next_17:;
    if (!((!((!(xs_)))))) goto next_18;
    if (!((xs_->head == 1))) goto next_18;
    if (!((!((!(xs_->tail)))))) goto next_18;
    if (!((xs_->tail->head == 1))) goto next_18;
    match_4 = 1;
    goto end_match_14;
next_18:;
    match_4 = 0;
    goto end_match_14;
next_19:;
end_match_14:;
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
    if (!(((!(call_3)) == 1))) goto next_21;
    exit(1);
    match_5 = 0;
    goto end_match_20;
next_21:;
    if (!(((!(call_3)) == 0))) goto next_22;
    match_5 = 0;
    goto end_match_20;
next_22:;
    exit(1);
end_match_20:;
    int match_6;
    struct IntList* list_4 = (struct IntList*)malloc(sizeof(struct IntList));
    list_4->head = 2;
    list_4->tail = NULL;
    struct IntList* list_3 = (struct IntList*)malloc(sizeof(struct IntList));
    list_3->head = 1;
    list_3->tail = list_4;
    int call_4 = startsWithDoubleBits_(list_3);
    if (!((call_4 == 1))) goto next_24;
    exit(1);
    match_6 = 0;
    goto end_match_23;
next_24:;
    if (!((call_4 == 0))) goto next_25;
    match_6 = 0;
    goto end_match_23;
next_25:;
    exit(1);
end_match_23:;
    return 0;
}

struct IntIntTuple2 {
    int t0;
    int t1;
};

enum Expr_Tag {
    Add_,
};

struct Expr_ {
    enum Expr_Tag tag;
    union {
        struct IntIntTuple2 Add_;
    };
};

int performComplexMatching_(struct Expr_ expr_) {
    int match_7;
    if (!((expr_.tag == Add_))) goto next_27;
    if (!((expr_.Add_.t0 == 0))) goto next_27;
    if (!((expr_.Add_.t1 == 0))) goto next_27;
    match_7 = 1;
    goto end_match_26;
next_27:;
    if (!((expr_.tag == Add_))) goto next_28;
    if (!((expr_.Add_.t0 == 0))) goto next_28;
    if (!((expr_.Add_.t1 == 1))) goto next_28;
    match_7 = 1;
    goto end_match_26;
next_28:;
    match_7 = 0;
    goto end_match_26;
next_29:;
end_match_26:;
    return match_7;
}

int complexCase_(int arg_2) {
    int match_8;
    struct IntIntTuple2 tuple_;
    tuple_.t0 = 0;
    tuple_.t1 = 1;
    struct Expr_ variant_ = (struct Expr_){.tag = Add_, .Add_ = tuple_};
    int call_5 = performComplexMatching_(variant_);
    if (!(((!(call_5)) == 1))) goto next_31;
    exit(1);
    match_8 = 0;
    goto end_match_30;
next_31:;
    if (!(((!(call_5)) == 0))) goto next_32;
    match_8 = 0;
    goto end_match_30;
next_32:;
    exit(1);
end_match_30:;
    int match_9;
    struct IntIntTuple2 tuple_1;
    tuple_1.t0 = 1;
    tuple_1.t1 = 2;
    struct Expr_ variant_1 = (struct Expr_){.tag = Add_, .Add_ = tuple_1};
    int call_6 = performComplexMatching_(variant_1);
    if (!((call_6 == 1))) goto next_34;
    exit(1);
    match_9 = 0;
    goto end_match_33;
next_34:;
    if (!((call_6 == 0))) goto next_35;
    match_9 = 0;
    goto end_match_33;
next_35:;
    exit(1);
end_match_33:;
    return 0;
}

int main() {
    int call_7 = simpleCase_(0);
    int call_8 = nestedCase_(0);
    int call_9 = complexCase_(0);
    return 0;
}
