#include "milone.h"

struct IntList;

int basicSomeCase_(int arg_);

struct StringList;

int basicNoneCase_(int arg_1);

int main();

struct IntList {
    int head;
    struct IntList* tail;
};

int basicSomeCase_(int arg_) {
    int match_;
    struct IntList* some_ = (struct IntList*)milone_mem_alloc(1, sizeof(struct IntList));
    some_->head = 1;
    some_->tail = NULL;
    if ((!((!(some_))))) goto next_2;
    milone_assert(0, 5, 4);
    int call_ = 0;
    match_ = 0;
    goto end_match_1;
next_2:;
    if ((!(some_))) goto next_3;
    if ((some_->head != 1)) goto next_3;
    if ((!((!(some_->tail))))) goto next_3;
    match_ = 0;
    goto end_match_1;
next_3:;
    milone_assert(0, 11, 4);
    int call_1 = 0;
    match_ = 0;
    goto end_match_1;
next_4:;
end_match_1:;
    return 0;
}

struct StringList {
    struct String head;
    struct StringList* tail;
};

int basicNoneCase_(int arg_1) {
    struct StringList* none_ = NULL;
    int match_1;
    if ((!(none_))) goto next_6;
    if ((str_cmp(none_->head, (struct String){.str = "a", .len = 1}) != 0)) goto next_6;
    if ((!((!(none_->tail))))) goto next_6;
    milone_assert(0, 19, 4);
    int call_2 = 0;
    match_1 = 0;
    goto end_match_5;
next_6:;
    if ((!((!(none_))))) goto next_7;
    match_1 = 0;
    goto end_match_5;
next_7:;
    milone_assert(0, 25, 4);
    int call_3 = 0;
    match_1 = 0;
    goto end_match_5;
next_8:;
end_match_5:;
    return 0;
}

int main() {
    int call_4 = basicSomeCase_(0);
    int call_5 = basicNoneCase_(0);
    return 0;
}
