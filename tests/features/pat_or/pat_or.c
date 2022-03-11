#include <milone.h>

struct IntList;

struct IntList;

struct IntIntTuple2_;

bool pat_or_pat_or_isZeroOrOne(int x_);

void pat_or_pat_or_simpleCase(void);

bool pat_or_pat_or_startsWithDoubleBits(struct IntList const* xs_);

void pat_or_pat_or_nestedCase(void);

bool pat_or_pat_or_performComplexMatching(struct IntIntTuple2_ expr_);

void pat_or_pat_or_complexCase(void);

int main(int argc, char** argv);

struct IntList {
    int head;
    struct IntList const* tail;
};

struct IntIntTuple2_ {
    int t0;
    int t1;
};

bool pat_or_pat_or_isZeroOrOne(int x_) {
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

void pat_or_pat_or_simpleCase(void) {
    bool call_;
    bool if_;
    bool call_1;
    bool call_2;
    call_ = pat_or_pat_or_isZeroOrOne(0);
    if (call_) {
        goto then_5;
    } else {
        goto else_6;
    }
then_5:;
    call_1 = pat_or_pat_or_isZeroOrOne(1);
    if_ = call_1;
    goto if_next_4;
else_6:;
    if_ = false;
    goto if_next_4;
if_next_4:;
    milone_assert(if_, (struct String){.str = "pat_or/pat_or.milone", .len = 20}, 12, 2);
    call_2 = pat_or_pat_or_isZeroOrOne(2);
    milone_assert((!(call_2)), (struct String){.str = "pat_or/pat_or.milone", .len = 20}, 13, 2);
    return;
}

bool pat_or_pat_or_startsWithDoubleBits(struct IntList const* xs_) {
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

void pat_or_pat_or_nestedCase(void) {
    struct IntList const* list_;
    struct IntList const* list_1;
    struct IntList const* list_2;
    bool call_3;
    struct IntList const* list_3;
    struct IntList const* list_4;
    bool call_4;
    list_2 = ((struct IntList const*)milone_mem_alloc(1, sizeof(struct IntList)));
    (*(((struct IntList*)list_2))) = (struct IntList){.head = 2, .tail = NULL};
    list_1 = ((struct IntList const*)milone_mem_alloc(1, sizeof(struct IntList)));
    (*(((struct IntList*)list_1))) = (struct IntList){.head = 1, .tail = list_2};
    list_ = ((struct IntList const*)milone_mem_alloc(1, sizeof(struct IntList)));
    (*(((struct IntList*)list_))) = (struct IntList){.head = 0, .tail = list_1};
    call_3 = pat_or_pat_or_startsWithDoubleBits(list_);
    milone_assert(call_3, (struct String){.str = "pat_or/pat_or.milone", .len = 20}, 24, 2);
    list_4 = ((struct IntList const*)milone_mem_alloc(1, sizeof(struct IntList)));
    (*(((struct IntList*)list_4))) = (struct IntList){.head = 2, .tail = NULL};
    list_3 = ((struct IntList const*)milone_mem_alloc(1, sizeof(struct IntList)));
    (*(((struct IntList*)list_3))) = (struct IntList){.head = 1, .tail = list_4};
    call_4 = pat_or_pat_or_startsWithDoubleBits(list_3);
    milone_assert((!(call_4)), (struct String){.str = "pat_or/pat_or.milone", .len = 20}, 25, 2);
    return;
}

bool pat_or_pat_or_performComplexMatching(struct IntIntTuple2_ expr_) {
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

void pat_or_pat_or_complexCase(void) {
    struct IntIntTuple2_ IntIntTuple2_;
    bool call_5;
    struct IntIntTuple2_ IntIntTuple2_1;
    bool call_6;
    IntIntTuple2_ = (struct IntIntTuple2_){.t0 = 0, .t1 = 1};
    call_5 = pat_or_pat_or_performComplexMatching(IntIntTuple2_);
    milone_assert(call_5, (struct String){.str = "pat_or/pat_or.milone", .len = 20}, 38, 2);
    IntIntTuple2_1 = (struct IntIntTuple2_){.t0 = 1, .t1 = 2};
    call_6 = pat_or_pat_or_performComplexMatching(IntIntTuple2_1);
    milone_assert((!(call_6)), (struct String){.str = "pat_or/pat_or.milone", .len = 20}, 39, 2);
    return;
}

int main(int argc, char** argv) {
    milone_start(argc, argv);
    pat_or_pat_or_simpleCase();
    pat_or_pat_or_nestedCase();
    pat_or_pat_or_complexCase();
    return 0;
}
