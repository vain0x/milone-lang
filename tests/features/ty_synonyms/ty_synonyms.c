#include "milone.h"

struct IntList;

int baseCase_(int arg_);

int yodaCase_(int exitCode_);

int proj_2(int cond_, int body_, int alt_);

struct String proj_1(int cond_, struct String body_, struct String alt_);

int polymorphicFunCase_(int arg_1);

int main();

struct IntList {
    int head;
    struct IntList* tail;
};

int baseCase_(int arg_) {
    int success_ = 0;
    int failure_ = 1;
    struct IntList* list_1 = (struct IntList*)milone_mem_alloc(1, sizeof(struct IntList));
    list_1->head = failure_;
    list_1->tail = NULL;
    struct IntList* list_ = (struct IntList*)milone_mem_alloc(1, sizeof(struct IntList));
    list_->head = success_;
    list_->tail = list_1;
    struct IntList* codes_ = list_;
    milone_assert((success_ == 0), 13, 2);
    return 0;
}

int yodaCase_(int exitCode_) {
    milone_assert((0 == exitCode_), 16, 36);
    return 0;
}

int proj_2(int cond_, int body_, int alt_) {
    int if_;
    if (cond_) {
        goto then_2;
    } else {
        goto else_3;
    }
then_2:;
    if_ = body_;
    goto if_next_1;
else_3:;
    if_ = alt_;
    goto if_next_1;
if_next_1:;
    return if_;
}

struct String proj_1(int cond_, struct String body_, struct String alt_) {
    struct String if_1;
    if (cond_) {
        goto then_5;
    } else {
        goto else_6;
    }
then_5:;
    if_1 = body_;
    goto if_next_4;
else_6:;
    if_1 = alt_;
    goto if_next_4;
if_next_4:;
    return if_1;
}

int polymorphicFunCase_(int arg_1) {
    int call_ = proj_2(1, 1, 0);
    milone_assert((call_ == 1), 21, 2);
    struct String call_1 = proj_1(0, (struct String){.str = "T", .len = 1}, (struct String){.str = "F", .len = 1});
    milone_assert((str_cmp(call_1, (struct String){.str = "F", .len = 1}) == 0), 22, 2);
    return 0;
}

int main() {
    int call_2 = baseCase_(0);
    int call_3 = yodaCase_(0);
    int call_4 = polymorphicFunCase_(0);
    return 0;
}
