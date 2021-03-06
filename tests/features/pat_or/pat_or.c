#include "milone.h"

struct IntList;

struct IntList;

struct IntIntTuple2;

bool isZeroOrOne_(int x_);

char simpleCase_(char arg_);

bool startsWithDoubleBits_(struct IntList const* xs_);

char nestedCase_(char arg_1);

bool performComplexMatching_(struct IntIntTuple2 expr_);

char complexCase_(char arg_2);

int milone_main();

struct IntList {
    int head;
    struct IntList const* tail;
};

struct IntIntTuple2 {
    int t0;
    int t1;
};

bool isZeroOrOne_(int x_) {
    bool switch_;
    switch (x_) {
        case 0:
        case 1:
            goto clause_2;

        default:
            goto clause_3;
    }
clause_2:;
    switch_ = true;
    goto switch_next_1;
clause_3:;
    switch_ = false;
    goto switch_next_1;
switch_next_1:;
    return switch_;
}

char simpleCase_(char arg_) {
    bool call_ = isZeroOrOne_(0);
    bool if_;
    if (call_) {
        goto then_5;
    } else {
        goto else_6;
    }
then_5:;
    bool call_1 = isZeroOrOne_(1);
    if_ = call_1;
    goto if_next_4;
else_6:;
    if_ = false;
    goto if_next_4;
if_next_4:;
    milone_assert(if_, 12, 2);
    bool call_2 = isZeroOrOne_(2);
    milone_assert((!(call_2)), 13, 2);
    return 0;
}

bool startsWithDoubleBits_(struct IntList const* xs_) {
    bool match_;
    if ((!(xs_))) goto next_9;
    if ((xs_->head != 0)) goto next_9;
    if ((!(xs_->tail))) goto next_9;
    if ((xs_->tail->head != 0)) goto next_9;
    goto match_body_8;
next_9:;
    if ((!(xs_))) goto next_10;
    if ((xs_->head != 1)) goto next_10;
    if ((!(xs_->tail))) goto next_10;
    if ((xs_->tail->head != 0)) goto next_10;
    goto match_body_8;
next_10:;
    if ((!(xs_))) goto next_11;
    if ((xs_->head != 0)) goto next_11;
    if ((!(xs_->tail))) goto next_11;
    if ((xs_->tail->head != 1)) goto next_11;
    goto match_body_8;
next_11:;
    if ((!(xs_))) goto next_12;
    if ((xs_->head != 1)) goto next_12;
    if ((!(xs_->tail))) goto next_12;
    if ((xs_->tail->head != 1)) goto next_12;
    goto match_body_8;
match_body_8:;
    match_ = true;
    goto end_match_7;
next_12:;
    match_ = false;
    goto end_match_7;
next_13:;
end_match_7:;
    return match_;
}

char nestedCase_(char arg_1) {
    struct IntList const* list_2 = milone_mem_alloc(1, sizeof(struct IntList));
    (*(((struct IntList*)list_2))) = (struct IntList){.head = 2, .tail = NULL};
    struct IntList const* list_1 = milone_mem_alloc(1, sizeof(struct IntList));
    (*(((struct IntList*)list_1))) = (struct IntList){.head = 1, .tail = list_2};
    struct IntList const* list_ = milone_mem_alloc(1, sizeof(struct IntList));
    (*(((struct IntList*)list_))) = (struct IntList){.head = 0, .tail = list_1};
    bool call_3 = startsWithDoubleBits_(list_);
    milone_assert(call_3, 24, 2);
    struct IntList const* list_4 = milone_mem_alloc(1, sizeof(struct IntList));
    (*(((struct IntList*)list_4))) = (struct IntList){.head = 2, .tail = NULL};
    struct IntList const* list_3 = milone_mem_alloc(1, sizeof(struct IntList));
    (*(((struct IntList*)list_3))) = (struct IntList){.head = 1, .tail = list_4};
    bool call_4 = startsWithDoubleBits_(list_3);
    milone_assert((!(call_4)), 25, 2);
    return 0;
}

bool performComplexMatching_(struct IntIntTuple2 expr_) {
    bool match_1;
    if ((expr_.t0 != 0)) goto next_16;
    if ((expr_.t1 != 0)) goto next_16;
    goto match_body_15;
next_16:;
    if ((expr_.t0 != 0)) goto next_17;
    if ((expr_.t1 != 1)) goto next_17;
    goto match_body_15;
match_body_15:;
    match_1 = true;
    goto end_match_14;
next_17:;
    match_1 = false;
    goto end_match_14;
next_18:;
end_match_14:;
    return match_1;
}

char complexCase_(char arg_2) {
    struct IntIntTuple2 tuple_ = (struct IntIntTuple2){.t0 = 0, .t1 = 1};
    bool call_5 = performComplexMatching_(tuple_);
    milone_assert(call_5, 38, 2);
    struct IntIntTuple2 tuple_1 = (struct IntIntTuple2){.t0 = 1, .t1 = 2};
    bool call_6 = performComplexMatching_(tuple_1);
    milone_assert((!(call_6)), 39, 2);
    return 0;
}

int milone_main() {
    char call_7 = simpleCase_(0);
    char call_8 = nestedCase_(0);
    char call_9 = complexCase_(0);
    return 0;
}
