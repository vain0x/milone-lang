#include "milone.h"

struct IntList;

struct IntList;

void ty_synonym_Program_baseCase(void);

void ty_synonym_Program_yodaCase(int exitCode_);

int proj_1(bool cond_, int body_, int alt_);

struct String proj_(bool cond_, struct String body_, struct String alt_);

void ty_synonym_Program_polymorphicFunCase(void);

int milone_main(void);

struct IntList {
    int head;
    struct IntList const* tail;
};

void ty_synonym_Program_baseCase(void) {
    int success_ = 0;
    int failure_ = 1;
    struct IntList const* list_1 = milone_mem_alloc(1, sizeof(struct IntList));
    (*(((struct IntList*)list_1))) = (struct IntList){.head = failure_, .tail = NULL};
    struct IntList const* list_ = milone_mem_alloc(1, sizeof(struct IntList));
    (*(((struct IntList*)list_))) = (struct IntList){.head = success_, .tail = list_1};
    struct IntList const* codes_ = list_;
    milone_assert((success_ == 0), 13, 2);
    return;
}

void ty_synonym_Program_yodaCase(int exitCode_) {
    milone_assert((0 == exitCode_), 16, 36);
    return;
}

int proj_1(bool cond_, int body_, int alt_) {
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

struct String proj_(bool cond_, struct String body_, struct String alt_) {
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

void ty_synonym_Program_polymorphicFunCase(void) {
    int call_ = proj_1(true, 1, 0);
    milone_assert((call_ == 1), 21, 2);
    struct String call_1 = proj_(false, (struct String){.str = "T", .len = 1}, (struct String){.str = "F", .len = 1});
    milone_assert((str_compare(call_1, (struct String){.str = "F", .len = 1}) == 0), 22, 2);
    return;
}

int milone_main(void) {
    ty_synonym_Program_baseCase();
    ty_synonym_Program_yodaCase(0);
    ty_synonym_Program_polymorphicFunCase();
    return 0;
}
