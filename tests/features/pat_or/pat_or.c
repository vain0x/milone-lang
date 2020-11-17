#include "milone.h"

int isZeroOrOne_(int x_);

int simpleCase_(int arg_);

struct IntList;

int startsWithDoubleBits_(struct IntList* xs_);

int nestedCase_(int arg_1);

struct IntIntTuple2;

int performComplexMatching_(void* expr_);

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
    int if_;
    int call_ = isZeroOrOne_(0);
    if ((!(call_))) goto else_6;
    int call_1 = isZeroOrOne_(1);
    if_ = call_1;
    goto end_if_7;
else_6:;
    if_ = 0;
end_if_7:;
    milone_assert(if_, 8, 2);
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
    int match_1;
    if ((!(xs_))) goto next_10;
    if ((xs_->head != 0)) goto next_10;
    if ((!(xs_->tail))) goto next_10;
    if ((xs_->tail->head != 0)) goto next_10;
    goto match_body_9;
next_10:;
    if ((!(xs_))) goto next_11;
    if ((xs_->head != 0)) goto next_11;
    if ((!(xs_->tail))) goto next_11;
    if ((xs_->tail->head != 1)) goto next_11;
    goto match_body_9;
next_11:;
    if ((!(xs_))) goto next_12;
    if ((xs_->head != 1)) goto next_12;
    if ((!(xs_->tail))) goto next_12;
    if ((xs_->tail->head != 0)) goto next_12;
    goto match_body_9;
next_12:;
    if ((!(xs_))) goto next_13;
    if ((xs_->head != 1)) goto next_13;
    if ((!(xs_->tail))) goto next_13;
    if ((xs_->tail->head != 1)) goto next_13;
    goto match_body_9;
match_body_9:;
    match_1 = 1;
    goto end_match_8;
next_13:;
    match_1 = 0;
    goto end_match_8;
next_14:;
end_match_8:;
    return match_1;
}

int nestedCase_(int arg_1) {
    struct IntList* list_2 = (struct IntList*)milone_mem_alloc(1, sizeof(struct IntList));
    list_2->head = 2;
    list_2->tail = NULL;
    struct IntList* list_1 = (struct IntList*)milone_mem_alloc(1, sizeof(struct IntList));
    list_1->head = 1;
    list_1->tail = list_2;
    struct IntList* list_ = (struct IntList*)milone_mem_alloc(1, sizeof(struct IntList));
    list_->head = 0;
    list_->tail = list_1;
    int call_5 = startsWithDoubleBits_(list_);
    milone_assert(call_5, 20, 2);
    int call_6 = 0;
    struct IntList* list_4 = (struct IntList*)milone_mem_alloc(1, sizeof(struct IntList));
    list_4->head = 2;
    list_4->tail = NULL;
    struct IntList* list_3 = (struct IntList*)milone_mem_alloc(1, sizeof(struct IntList));
    list_3->head = 1;
    list_3->tail = list_4;
    int call_7 = startsWithDoubleBits_(list_3);
    milone_assert((!(call_7)), 21, 2);
    int call_8 = 0;
    return 0;
}

struct IntIntTuple2 {
    int t0;
    int t1;
};

int performComplexMatching_(void* expr_) {
    int match_2;
    if (((*(((struct IntIntTuple2*)expr_))).t0 != 0)) goto next_17;
    if (((*(((struct IntIntTuple2*)expr_))).t1 != 0)) goto next_17;
    goto match_body_16;
next_17:;
    if (((*(((struct IntIntTuple2*)expr_))).t0 != 0)) goto next_18;
    if (((*(((struct IntIntTuple2*)expr_))).t1 != 1)) goto next_18;
    goto match_body_16;
match_body_16:;
    match_2 = 1;
    goto end_match_15;
next_18:;
    match_2 = 0;
    goto end_match_15;
next_19:;
end_match_15:;
    return match_2;
}

int complexCase_(int arg_2) {
    struct IntIntTuple2 tuple_;
    tuple_.t0 = 0;
    tuple_.t1 = 1;
    void* box_ = (void*)milone_mem_alloc(1, sizeof(struct IntIntTuple2));
    (*(((struct IntIntTuple2*)box_))) = tuple_;
    int call_9 = performComplexMatching_(box_);
    milone_assert(call_9, 35, 2);
    int call_10 = 0;
    struct IntIntTuple2 tuple_1;
    tuple_1.t0 = 1;
    tuple_1.t1 = 2;
    void* box_1 = (void*)milone_mem_alloc(1, sizeof(struct IntIntTuple2));
    (*(((struct IntIntTuple2*)box_1))) = tuple_1;
    int call_11 = performComplexMatching_(box_1);
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
