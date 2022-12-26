#include <stdio.h>
#include <stdlib.h>
#include <milone.h>

struct Int32Cons;

struct Int32Cons;

struct Int32Int32Tuple2_;

bool pat_or_pat_or_isZeroOrOne(int32_t x_);

void pat_or_pat_or_simpleCase(void);

bool pat_or_pat_or_startsWithDoubleBits(struct Int32Cons const *xs_);

void pat_or_pat_or_nestedCase(void);

bool pat_or_pat_or_performComplexMatching(struct Int32Int32Tuple2_ expr_);

void pat_or_pat_or_complexCase(void);

int main(int argc, char **argv);

struct Int32Cons {
    int32_t head;
    struct Int32Cons const *tail;
};

struct Int32Int32Tuple2_ {
    int32_t t0;
    int32_t t1;
};

bool pat_or_pat_or_isZeroOrOne(int32_t x_) {
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
        goto then_2;
    } else {
        goto else_3;
    }
then_2:;
    call_1 = pat_or_pat_or_isZeroOrOne(1);
    if_ = call_1;
    goto if_next_1;
else_3:;
    if_ = false;
    goto if_next_1;
if_next_1:;
    if ((!(if_))) milone_assert_error("pat_or/pat_or.milone", 12, 2);
    call_2 = pat_or_pat_or_isZeroOrOne(2);
    if (call_2) milone_assert_error("pat_or/pat_or.milone", 13, 2);
    return;
}

bool pat_or_pat_or_startsWithDoubleBits(struct Int32Cons const *xs_) {
    bool match_;
    if ((!(xs_))) goto next_3;
    if ((xs_->head != 0)) goto next_3;
    if ((!(xs_->tail))) goto next_3;
    if ((xs_->tail->head != 0)) goto next_3;
    goto match_body_2;
next_3:;
    if ((!(xs_))) goto next_4;
    if ((xs_->head != 1)) goto next_4;
    if ((!(xs_->tail))) goto next_4;
    if ((xs_->tail->head != 0)) goto next_4;
    goto match_body_2;
next_4:;
    if ((!(xs_))) goto next_5;
    if ((xs_->head != 0)) goto next_5;
    if ((!(xs_->tail))) goto next_5;
    if ((xs_->tail->head != 1)) goto next_5;
    goto match_body_2;
next_5:;
    if ((!(xs_))) goto next_6;
    if ((xs_->head != 1)) goto next_6;
    if ((!(xs_->tail))) goto next_6;
    if ((xs_->tail->head != 1)) goto next_6;
    goto match_body_2;
match_body_2:;
    match_ = true;
    goto end_match_1;
next_6:;
    match_ = false;
    goto end_match_1;
next_7:;
end_match_1:;
    return match_;
}

void pat_or_pat_or_nestedCase(void) {
    struct Int32Cons const *list_;
    struct Int32Cons const *list_1;
    struct Int32Cons const *list_2;
    bool call_3;
    struct Int32Cons const *list_3;
    struct Int32Cons const *list_4;
    bool call_4;
    list_2 = ((struct Int32Cons const *)milone_region_alloc(1, sizeof(struct Int32Cons)));
    (*(((struct Int32Cons *)list_2))) = (struct Int32Cons){.head = 2, .tail = NULL};
    list_1 = ((struct Int32Cons const *)milone_region_alloc(1, sizeof(struct Int32Cons)));
    (*(((struct Int32Cons *)list_1))) = (struct Int32Cons){.head = 1, .tail = list_2};
    list_ = ((struct Int32Cons const *)milone_region_alloc(1, sizeof(struct Int32Cons)));
    (*(((struct Int32Cons *)list_))) = (struct Int32Cons){.head = 0, .tail = list_1};
    call_3 = pat_or_pat_or_startsWithDoubleBits(list_);
    if ((!(call_3))) milone_assert_error("pat_or/pat_or.milone", 24, 2);
    list_4 = ((struct Int32Cons const *)milone_region_alloc(1, sizeof(struct Int32Cons)));
    (*(((struct Int32Cons *)list_4))) = (struct Int32Cons){.head = 2, .tail = NULL};
    list_3 = ((struct Int32Cons const *)milone_region_alloc(1, sizeof(struct Int32Cons)));
    (*(((struct Int32Cons *)list_3))) = (struct Int32Cons){.head = 1, .tail = list_4};
    call_4 = pat_or_pat_or_startsWithDoubleBits(list_3);
    if (call_4) milone_assert_error("pat_or/pat_or.milone", 25, 2);
    return;
}

bool pat_or_pat_or_performComplexMatching(struct Int32Int32Tuple2_ expr_) {
    bool match_1;
    if ((expr_.t0 != 0)) goto next_3;
    if ((expr_.t1 != 0)) goto next_3;
    goto match_body_2;
next_3:;
    if ((expr_.t0 != 0)) goto next_4;
    if ((expr_.t1 != 1)) goto next_4;
    goto match_body_2;
match_body_2:;
    match_1 = true;
    goto end_match_1;
next_4:;
    match_1 = false;
    goto end_match_1;
next_5:;
end_match_1:;
    return match_1;
}

void pat_or_pat_or_complexCase(void) {
    struct Int32Int32Tuple2_ Int32Int32Tuple2_;
    bool call_5;
    struct Int32Int32Tuple2_ Int32Int32Tuple2_1;
    bool call_6;
    Int32Int32Tuple2_ = (struct Int32Int32Tuple2_){.t0 = 0, .t1 = 1};
    call_5 = pat_or_pat_or_performComplexMatching(Int32Int32Tuple2_);
    if ((!(call_5))) milone_assert_error("pat_or/pat_or.milone", 38, 2);
    Int32Int32Tuple2_1 = (struct Int32Int32Tuple2_){.t0 = 1, .t1 = 2};
    call_6 = pat_or_pat_or_performComplexMatching(Int32Int32Tuple2_1);
    if (call_6) milone_assert_error("pat_or/pat_or.milone", 39, 2);
    return;
}

int main(int argc, char **argv) {
    milone_start(argc, argv);
    pat_or_pat_or_simpleCase();
    pat_or_pat_or_nestedCase();
    pat_or_pat_or_complexCase();
    return 0;
}
