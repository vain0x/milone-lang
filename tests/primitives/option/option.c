#include "milone.h"

struct IntList;

int basicSomeCase_(int arg_);

struct StringList;

int basicNoneCase_(int arg_1);

struct UnitList;

int basicMatchCase_(int arg_2);

int milone_main();

struct IntList {
    int head;
    struct IntList const* tail;
};

int basicSomeCase_(int arg_) {
    int match_;
    struct IntList const* some_ = milone_mem_alloc(1, sizeof(struct IntList));
    (*(((struct IntList*)some_))) = (struct IntList){.head = 1, .tail = NULL};
    if ((!((!(some_))))) goto next_2;
    milone_assert(false, 6, 12);
    match_ = 0;
    goto end_match_1;
next_2:;
    if ((!(some_))) goto next_3;
    if ((some_->head != 1)) goto next_3;
    match_ = 0;
    goto end_match_1;
next_3:;
    milone_assert(false, 10, 9);
    match_ = 0;
    goto end_match_1;
next_4:;
end_match_1:;
    return 0;
}

struct StringList {
    struct String head;
    struct StringList const* tail;
};

int basicNoneCase_(int arg_1) {
    struct StringList const* none_ = NULL;
    int match_1;
    if ((!(none_))) goto next_6;
    if ((str_cmp(none_->head, (struct String){.str = "a", .len = 1}) != 0)) goto next_6;
    milone_assert(false, 17, 16);
    match_1 = 0;
    goto end_match_5;
next_6:;
    if ((!((!(none_))))) goto next_7;
    match_1 = 0;
    goto end_match_5;
next_7:;
    milone_assert(false, 21, 9);
    match_1 = 0;
    goto end_match_5;
next_8:;
end_match_5:;
    return 0;
}

struct UnitList {
    int head;
    struct UnitList const* tail;
};

int basicMatchCase_(int arg_2) {
    struct UnitList const* some_1 = milone_mem_alloc(1, sizeof(struct UnitList));
    (*(((struct UnitList*)some_1))) = (struct UnitList){.head = 0, .tail = NULL};
    int if_;
    if ((!(some_1))) {
        goto none_cl_10;
    } else {
        goto some_cl_11;
    }
none_cl_10:;
    milone_assert(false, 27, 12);
    if_ = 0;
    goto if_next_9;
some_cl_11:;
    if_ = 0;
    goto if_next_9;
if_next_9:;
    return 0;
}

int milone_main() {
    int call_ = basicSomeCase_(0);
    int call_1 = basicNoneCase_(0);
    int call_2 = basicMatchCase_(0);
    return 0;
}
