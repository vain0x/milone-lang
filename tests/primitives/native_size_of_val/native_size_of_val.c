#include "milone.h"

struct IntList;

struct IntList;

struct StringList;

struct StringList;

int go_1(int n_, struct IntList const* xs_1);

int go_(int n_, struct StringList const* xs_1);

int listToArraySize_1(struct IntList const* xs_);

int listToArraySize_(struct StringList const* xs_);

int milone_main();

struct IntList {
    int head;
    struct IntList const* tail;
};

struct StringList {
    struct String head;
    struct StringList const* tail;
};

int go_1(int n_, struct IntList const* xs_1) {
    struct IntList const* xs_2;
tailrec_1:;
    int match_;
    if ((!((!(xs_1))))) goto next_3;
    match_ = n_;
    goto end_match_2;
next_3:;
    if ((!(xs_1))) goto next_4;
    xs_2 = xs_1->tail;
    int arg_ = (n_ + 1);
    struct IntList const* arg_1 = xs_2;
    n_ = arg_;
    xs_1 = arg_1;
    goto tailrec_1;
next_4:;
    exit(1);
end_match_2:;
    return match_;
}

int go_(int n_, struct StringList const* xs_1) {
    struct StringList const* xs_2;
tailrec_5:;
    int match_1;
    if ((!((!(xs_1))))) goto next_7;
    match_1 = n_;
    goto end_match_6;
next_7:;
    if ((!(xs_1))) goto next_8;
    xs_2 = xs_1->tail;
    int arg_2 = (n_ + 1);
    struct StringList const* arg_3 = xs_2;
    n_ = arg_2;
    xs_1 = arg_3;
    goto tailrec_5;
next_8:;
    exit(1);
end_match_6:;
    return match_1;
}

int listToArraySize_1(struct IntList const* xs_) {
    int x_;
    int match_2;
    if ((!((!(xs_))))) goto next_10;
    match_2 = 0;
    goto end_match_9;
next_10:;
    if ((!(xs_))) goto next_11;
    x_ = xs_->head;
    int itemSize_ = sizeof(int);
    int call_ = go_1(0, xs_);
    int n_1 = call_;
    match_2 = (itemSize_ * n_1);
    goto end_match_9;
next_11:;
    exit(1);
end_match_9:;
    return match_2;
}

int listToArraySize_(struct StringList const* xs_) {
    struct String x_;
    int match_3;
    if ((!((!(xs_))))) goto next_13;
    match_3 = 0;
    goto end_match_12;
next_13:;
    if ((!(xs_))) goto next_14;
    x_ = xs_->head;
    int itemSize_ = sizeof(struct String);
    int call_1 = go_(0, xs_);
    int n_1 = call_1;
    match_3 = (itemSize_ * n_1);
    goto end_match_12;
next_14:;
    exit(1);
end_match_12:;
    return match_3;
}

int milone_main() {
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
