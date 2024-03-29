#include <stdio.h>
#include <stdlib.h>
#include <milone.h>

struct Int32Cons;

struct Int32Cons;

struct Int32Int32Tuple2_;

void match_complicated_match_complicated_testTrivialCase(void);

void match_complicated_match_complicated_testListMatching(void);

void match_complicated_match_complicated_testMatchArmsMakeScope(void);

void match_complicated_match_complicated_testNestedMatchesParseCorrectly(void);

int main(int argc, char **argv);

struct Int32Cons {
    int32_t head;
    struct Int32Cons const *tail;
};

struct Int32Int32Tuple2_ {
    int32_t t0;
    int32_t t1;
};

void match_complicated_match_complicated_testTrivialCase(void) {
    char match_;
    match_ = 0;
    goto end_match_1;
next_2:;
end_match_1:;
    return;
}

void match_complicated_match_complicated_testListMatching(void) {
    char match_1;
    struct Int32Cons const *list_;
    list_ = ((struct Int32Cons const *)milone_region_alloc(1, sizeof(struct Int32Cons)));
    (*(((struct Int32Cons *)list_))) = (struct Int32Cons){.head = 0, .tail = NULL};
    if ((!(list_))) goto next_2;
    if ((!(list_->tail))) goto next_2;
    if (true) milone_assert_error("match_complicated/match_complicated.milone", 10, 19);
    match_1 = 0;
    goto end_match_1;
next_2:;
    if ((!(list_))) goto next_3;
    if ((!((!(list_->tail))))) goto next_3;
    match_1 = 0;
    goto end_match_1;
next_3:;
    if ((!((!(list_))))) goto next_4;
    if (true) milone_assert_error("match_complicated/match_complicated.milone", 12, 10);
    match_1 = 0;
    goto end_match_1;
next_4:;
    milone_exhaust_error("match_complicated/match_complicated.milone", 9, 2);
end_match_1:;
    return;
}

void match_complicated_match_complicated_testMatchArmsMakeScope(void) {
    int32_t x_;
    int32_t x_1;
    char match_2;
    struct Int32Int32Tuple2_ Int32Int32Tuple2_;
    char if_;
    x_ = 2;
    Int32Int32Tuple2_ = (struct Int32Int32Tuple2_){.t0 = x_, .t1 = 1};
    if ((Int32Int32Tuple2_.t0 != 1)) goto next_2;
    x_1 = Int32Int32Tuple2_.t1;
    if (true) milone_assert_error("match_complicated/match_complicated.milone", 18, 12);
    match_2 = 0;
    goto end_match_1;
next_2:;
    if ((Int32Int32Tuple2_.t0 != 2)) goto next_3;
    if ((x_ != 2)) {
        goto then_6;
    } else {
        goto else_7;
    }
then_6:;
    if (true) milone_assert_error("match_complicated/match_complicated.milone", 19, 27);
    if_ = 0;
    goto if_next_5;
else_7:;
    if_ = 0;
    goto if_next_5;
if_next_5:;
    match_2 = 0;
    goto end_match_1;
next_3:;
    if (true) milone_assert_error("match_complicated/match_complicated.milone", 20, 9);
    match_2 = 0;
    goto end_match_1;
next_4:;
end_match_1:;
    return;
}

void match_complicated_match_complicated_testNestedMatchesParseCorrectly(void) {
    char match_3;
    char switch_;
    if (true) goto next_2;
    switch (1) {
        default:
            goto clause_5;
    }
clause_5:;
    if (true) milone_assert_error("match_complicated/match_complicated.milone", 26, 11);
    switch_ = 0;
    goto switch_next_4;
switch_next_4:;
    match_3 = 0;
    goto end_match_1;
next_2:;
    match_3 = 0;
    goto end_match_1;
next_3:;
end_match_1:;
    return;
}

int main(int argc, char **argv) {
    milone_start(argc, argv);
    match_complicated_match_complicated_testTrivialCase();
    match_complicated_match_complicated_testListMatching();
    match_complicated_match_complicated_testMatchArmsMakeScope();
    match_complicated_match_complicated_testNestedMatchesParseCorrectly();
    return 0;
}
