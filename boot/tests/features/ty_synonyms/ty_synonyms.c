#include "milone.h"

int proj_2(int cond_, int body_, int alt_);

struct String proj_1(int cond_, struct String body_, struct String alt_);

int polymorphicFunTest_(int arg_);

struct IntList;

int main();

int proj_2(int cond_, int body_, int alt_) {
    int match_;
    if ((!(cond_))) goto next_2;
    match_ = body_;
    goto end_match_1;
next_2:;
    if (cond_) goto next_3;
    match_ = alt_;
    goto end_match_1;
next_3:;
    exit(1);
end_match_1:;
    return match_;
}

struct String proj_1(int cond_, struct String body_, struct String alt_) {
    struct String match_1;
    if ((!(cond_))) goto next_5;
    match_1 = body_;
    goto end_match_4;
next_5:;
    if (cond_) goto next_6;
    match_1 = alt_;
    goto end_match_4;
next_6:;
    exit(1);
end_match_4:;
    return match_1;
}

int polymorphicFunTest_(int arg_) {
    int call_ = proj_2(1, 1, 0);
    milone_assert((call_ == 1), 9, 2);
    int call_1 = 0;
    struct String call_2 = proj_1(0, (struct String){.str = "T", .len = 1}, (struct String){.str = "F", .len = 1});
    milone_assert((str_cmp(call_2, (struct String){.str = "F", .len = 1}) == 0), 10, 2);
    int call_3 = 0;
    return 0;
}

struct IntList {
    int head;
    struct IntList* tail;
};

int main() {
    int success_ = 0;
    int failure_ = 1;
    struct IntList* list_1 = (struct IntList*)malloc(sizeof(struct IntList));
    list_1->head = failure_;
    list_1->tail = NULL;
    struct IntList* list_ = (struct IntList*)malloc(sizeof(struct IntList));
    list_->head = success_;
    list_->tail = list_1;
    struct IntList* codes_ = list_;
    milone_assert((success_ == 0), 16, 2);
    int call_4 = 0;
    int call_5 = polymorphicFunTest_(0);
    return 0;
}
