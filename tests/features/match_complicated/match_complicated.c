#include "milone.h"

struct IntList;

struct IntList;

struct IntIntTuple2_;

char match_complicated_Program_testTrivialCase(char arg_);

char match_complicated_Program_testListMatching(char arg_1);

char match_complicated_Program_testMatchArmsMakeScope(char arg_2);

char match_complicated_Program_testNestedMatchesParseCorrectly(char arg_3);

int milone_main();

struct IntList {
    int head;
    struct IntList const* tail;
};

struct IntIntTuple2_ {
    int t0;
    int t1;
};

char match_complicated_Program_testTrivialCase(char arg_) {
    char match_;
    match_ = 0;
    goto end_match_1;
next_2:;
end_match_1:;
    return 0;
}

char match_complicated_Program_testListMatching(char arg_1) {
    char match_1;
    struct IntList const* list_ = milone_mem_alloc(1, sizeof(struct IntList));
    (*(((struct IntList*)list_))) = (struct IntList){.head = 0, .tail = NULL};
    if ((!(list_))) goto next_4;
    if ((!(list_->tail))) goto next_4;
    milone_assert(false, 10, 19);
    match_1 = 0;
    goto end_match_3;
next_4:;
    if ((!(list_))) goto next_5;
    if ((!((!(list_->tail))))) goto next_5;
    match_1 = 0;
    goto end_match_3;
next_5:;
    if ((!((!(list_))))) goto next_6;
    milone_assert(false, 12, 10);
    match_1 = 0;
    goto end_match_3;
next_6:;
    exit(1);
end_match_3:;
    return 0;
}

char match_complicated_Program_testMatchArmsMakeScope(char arg_2) {
    int x_1;
    int x_ = 2;
    char match_2;
    struct IntIntTuple2_ IntIntTuple2_ = (struct IntIntTuple2_){.t0 = x_, .t1 = 1};
    if ((IntIntTuple2_.t0 != 1)) goto next_8;
    x_1 = IntIntTuple2_.t1;
    milone_assert(false, 18, 12);
    match_2 = 0;
    goto end_match_7;
next_8:;
    if ((IntIntTuple2_.t0 != 2)) goto next_9;
    char if_;
    if ((x_ != 2)) {
        goto then_12;
    } else {
        goto else_13;
    }
then_12:;
    milone_assert(false, 19, 27);
    if_ = 0;
    goto if_next_11;
else_13:;
    if_ = 0;
    goto if_next_11;
if_next_11:;
    match_2 = 0;
    goto end_match_7;
next_9:;
    milone_assert(false, 20, 9);
    match_2 = 0;
    goto end_match_7;
next_10:;
end_match_7:;
    return 0;
}

char match_complicated_Program_testNestedMatchesParseCorrectly(char arg_3) {
    char match_3;
    if (true) goto next_15;
    char switch_;
    switch (1) {
        default:
            goto clause_18;
    }
clause_18:;
    milone_assert(false, 26, 11);
    switch_ = 0;
    goto switch_next_17;
switch_next_17:;
    match_3 = 0;
    goto end_match_14;
next_15:;
    match_3 = 0;
    goto end_match_14;
next_16:;
end_match_14:;
    return 0;
}

int milone_main() {
    char call_ = match_complicated_Program_testTrivialCase(0);
    char call_1 = match_complicated_Program_testListMatching(0);
    char call_2 = match_complicated_Program_testMatchArmsMakeScope(0);
    char call_3 = match_complicated_Program_testNestedMatchesParseCorrectly(0);
    return 0;
}
