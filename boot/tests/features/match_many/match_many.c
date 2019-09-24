#include "milone.h"

int testTrivialCase_(int arg_);

struct IntList;

int testListMatching_(int arg_1);

struct IntIntTuple2;

int testMatchArmsMakeScope_(int arg_2);

int testNestedMatchesParseCorrectly_(int arg_3);

int main();

int testTrivialCase_(int arg_) {
    int match_;
    match_ = 0;
    goto end_match_1;
next_2:;
end_match_1:;
    return 0;
}

struct IntList {
    int head;
    struct IntList* tail;
};

int testListMatching_(int arg_1) {
    int match_1;
    struct IntList* list_ = (struct IntList*)malloc(sizeof(struct IntList));
    list_->head = 0;
    list_->tail = NULL;
    if ((!(list_))) goto next_4;
    if ((!(list_->tail))) goto next_4;
    milone_assert(0, 6, 19);
    int call_ = 0;
    match_1 = 0;
    goto end_match_3;
next_4:;
    if ((!(list_))) goto next_5;
    if ((!((!(list_->tail))))) goto next_5;
    match_1 = 0;
    goto end_match_3;
next_5:;
    if ((!((!(list_))))) goto next_6;
    milone_assert(0, 8, 10);
    int call_1 = 0;
    match_1 = 0;
    goto end_match_3;
next_6:;
    exit(1);
end_match_3:;
    return 0;
}

struct IntIntTuple2 {
    int t0;
    int t1;
};

int testMatchArmsMakeScope_(int arg_2) {
    int x_ = 2;
    int match_2;
    struct IntIntTuple2 tuple_;
    tuple_.t0 = x_;
    tuple_.t1 = 1;
    if ((tuple_.t0 != 1)) goto next_8;
    int x_1 = tuple_.t1;
    milone_assert(0, 14, 4);
    int call_2 = 0;
    match_2 = 0;
    goto end_match_7;
next_8:;
    if ((tuple_.t0 != 2)) goto next_9;
    int match_3;
    if ((x_ == 2)) goto next_12;
    milone_assert(0, 16, 19);
    int call_3 = 0;
    match_3 = 0;
    goto end_match_11;
next_12:;
    if ((x_ != 2)) goto next_13;
    match_3 = 0;
    goto end_match_11;
next_13:;
    exit(1);
end_match_11:;
    match_2 = 0;
    goto end_match_7;
next_9:;
    milone_assert(0, 18, 4);
    int call_4 = 0;
    match_2 = 0;
    goto end_match_7;
next_10:;
end_match_7:;
    return 0;
}

int testNestedMatchesParseCorrectly_(int arg_3) {
    int match_4;
    if (1) goto next_15;
    int match_5;
    milone_assert(0, 25, 6);
    int call_5 = 0;
    match_5 = 0;
    goto end_match_17;
next_18:;
end_match_17:;
    match_4 = 0;
    goto end_match_14;
next_15:;
    match_4 = 0;
    goto end_match_14;
next_16:;
end_match_14:;
    return 0;
}

int main() {
    int call_6 = testTrivialCase_(0);
    int call_7 = testListMatching_(0);
    int call_8 = testMatchArmsMakeScope_(0);
    int call_9 = testNestedMatchesParseCorrectly_(0);
    return 0;
}
