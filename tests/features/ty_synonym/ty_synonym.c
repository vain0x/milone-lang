#include <stdio.h>
#include <stdlib.h>
#include <milone.h>

struct IntList;

struct IntList;

struct String ty_synonym_ty_synonym_BoolStringStringStringFun3_proj(bool cond_, struct String body_, struct String alt_);

int ty_synonym_ty_synonym_BoolIntIntIntFun3_proj(bool cond_, int body_, int alt_);

void ty_synonym_ty_synonym_baseCase(void);

void ty_synonym_ty_synonym_yodaCase(int exitCode_);

void ty_synonym_ty_synonym_polymorphicFunCase(void);

int main(int argc, char** argv);

struct IntList {
    int head;
    struct IntList const* tail;
};

struct String ty_synonym_ty_synonym_BoolStringStringStringFun3_proj(bool cond_, struct String body_, struct String alt_) {
    struct String if_;
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

int ty_synonym_ty_synonym_BoolIntIntIntFun3_proj(bool cond_, int body_, int alt_) {
    int if_1;
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

void ty_synonym_ty_synonym_baseCase(void) {
    int success_;
    int failure_;
    struct IntList const* codes_;
    struct IntList const* list_;
    struct IntList const* list_1;
    success_ = 0;
    failure_ = 1;
    list_1 = ((struct IntList const*)milone_region_alloc(1, sizeof(struct IntList)));
    (*(((struct IntList*)list_1))) = (struct IntList){.head = failure_, .tail = NULL};
    list_ = ((struct IntList const*)milone_region_alloc(1, sizeof(struct IntList)));
    (*(((struct IntList*)list_))) = (struct IntList){.head = success_, .tail = list_1};
    codes_ = list_;
    milone_assert((success_ == 0), (struct String){.ptr = "ty_synonym/ty_synonym.milone", .len = 28}, 13, 2);
    return;
}

void ty_synonym_ty_synonym_yodaCase(int exitCode_) {
    milone_assert((0 == exitCode_), (struct String){.ptr = "ty_synonym/ty_synonym.milone", .len = 28}, 16, 36);
    return;
}

void ty_synonym_ty_synonym_polymorphicFunCase(void) {
    int call_;
    struct String call_1;
    call_ = ty_synonym_ty_synonym_BoolIntIntIntFun3_proj(true, 1, 0);
    milone_assert((call_ == 1), (struct String){.ptr = "ty_synonym/ty_synonym.milone", .len = 28}, 21, 2);
    call_1 = ty_synonym_ty_synonym_BoolStringStringStringFun3_proj(false, (struct String){.ptr = "T", .len = 1}, (struct String){.ptr = "F", .len = 1});
    milone_assert((string_compare(call_1, (struct String){.ptr = "F", .len = 1}) == 0), (struct String){.ptr = "ty_synonym/ty_synonym.milone", .len = 28}, 22, 2);
    return;
}

int main(int argc, char** argv) {
    milone_start(argc, argv);
    ty_synonym_ty_synonym_baseCase();
    ty_synonym_ty_synonym_yodaCase(0);
    ty_synonym_ty_synonym_polymorphicFunCase();
    return 0;
}
