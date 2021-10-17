#include "milone.h"

struct StringList;

struct StringList;

struct IntList;

struct IntList;

int listToArraySize_(struct StringList const* xs_);

int listToArraySize_1(struct IntList const* xs_);

int go_(int n_, struct IntList const* xs_1);

int go_1(int n_, struct StringList const* xs_1);

int milone_main(void);

struct StringList {
    struct String head;
    struct StringList const* tail;
};

struct IntList {
    int head;
    struct IntList const* tail;
};

int listToArraySize_(struct StringList const* xs_) {
    struct String x_;
    int match_;
    if ((!((!(xs_))))) goto next_2;
    match_ = 0;
    goto end_match_1;
next_2:;
    if ((!(xs_))) goto next_3;
    x_ = xs_->head;
    int itemSize_ = sizeof(struct String);
    int call_ = go_1(0, xs_);
    int n_1 = call_;
    match_ = (itemSize_ * n_1);
    goto end_match_1;
next_3:;
    exit(1);
end_match_1:;
    return match_;
}

int listToArraySize_1(struct IntList const* xs_) {
    int x_;
    int match_1;
    if ((!((!(xs_))))) goto next_5;
    match_1 = 0;
    goto end_match_4;
next_5:;
    if ((!(xs_))) goto next_6;
    x_ = xs_->head;
    int itemSize_ = sizeof(int);
    int call_1 = go_(0, xs_);
    int n_1 = call_1;
    match_1 = (itemSize_ * n_1);
    goto end_match_4;
next_6:;
    exit(1);
end_match_4:;
    return match_1;
}

int go_(int n_, struct IntList const* xs_1) {
    struct IntList const* xs_2;
tailrec_7:;
    int match_2;
    if ((!((!(xs_1))))) goto next_9;
    match_2 = n_;
    goto end_match_8;
next_9:;
    if ((!(xs_1))) goto next_10;
    xs_2 = xs_1->tail;
    int arg_ = (n_ + 1);
    struct IntList const* arg_1 = xs_2;
    n_ = arg_;
    xs_1 = arg_1;
    goto tailrec_7;
next_10:;
    exit(1);
end_match_8:;
    return match_2;
}

int go_1(int n_, struct StringList const* xs_1) {
    struct StringList const* xs_2;
tailrec_11:;
    int match_3;
    if ((!((!(xs_1))))) goto next_13;
    match_3 = n_;
    goto end_match_12;
next_13:;
    if ((!(xs_1))) goto next_14;
    xs_2 = xs_1->tail;
    int arg_2 = (n_ + 1);
    struct StringList const* arg_3 = xs_2;
    n_ = arg_2;
    xs_1 = arg_3;
    goto tailrec_11;
next_14:;
    exit(1);
end_match_12:;
    return match_3;
}

int milone_main(void) {
    struct IntList const* list_2 = milone_mem_alloc(1, sizeof(struct IntList));
    (*(((struct IntList*)list_2))) = (struct IntList){.head = 5, .tail = NULL};
    struct IntList const* list_1 = milone_mem_alloc(1, sizeof(struct IntList));
    (*(((struct IntList*)list_1))) = (struct IntList){.head = 3, .tail = list_2};
    struct IntList const* list_ = milone_mem_alloc(1, sizeof(struct IntList));
    (*(((struct IntList*)list_))) = (struct IntList){.head = 2, .tail = list_1};
    int call_2 = listToArraySize_1(list_);
    milone_assert((call_2 == (3 * 4)), 21, 2);
    struct StringList const* list_4 = milone_mem_alloc(1, sizeof(struct StringList));
    (*(((struct StringList*)list_4))) = (struct StringList){.head = (struct String){.str = "y", .len = 1}, .tail = NULL};
    struct StringList const* list_3 = milone_mem_alloc(1, sizeof(struct StringList));
    (*(((struct StringList*)list_3))) = (struct StringList){.head = (struct String){.str = "x", .len = 1}, .tail = list_4};
    int call_3 = listToArraySize_(list_3);
    milone_assert((call_3 == (2 * 16)), 22, 2);
    return 0;
}
