#include <stdio.h>
#include <stdlib.h>
#include <milone.h>

struct Int32Cons;

struct Int32Cons;

struct String ty_synonym_ty_synonym_BoolStringStringStringFun3_proj(bool cond_, struct String body_, struct String alt_);

int32_t ty_synonym_ty_synonym_BoolInt32Int32Int32Fun3_proj(bool cond_, int32_t body_, int32_t alt_);

void ty_synonym_ty_synonym_baseCase(void);

void ty_synonym_ty_synonym_yodaCase(int32_t exitCode_);

void ty_synonym_ty_synonym_polymorphicFunCase(void);

int main(int argc, char **argv);

struct Int32Cons {
    int32_t head;
    struct Int32Cons const *tail;
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

int32_t ty_synonym_ty_synonym_BoolInt32Int32Int32Fun3_proj(bool cond_, int32_t body_, int32_t alt_) {
    int32_t if_1;
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
    int32_t success_;
    int32_t failure_;
    struct Int32Cons const *codes_;
    struct Int32Cons const *list_;
    struct Int32Cons const *list_1;
    success_ = 0;
    failure_ = 1;
    list_1 = ((struct Int32Cons const *)milone_region_alloc(1, sizeof(struct Int32Cons)));
    (*(((struct Int32Cons *)list_1))) = (struct Int32Cons){.head = failure_, .tail = NULL};
    list_ = ((struct Int32Cons const *)milone_region_alloc(1, sizeof(struct Int32Cons)));
    (*(((struct Int32Cons *)list_))) = (struct Int32Cons){.head = success_, .tail = list_1};
    codes_ = list_;
    if ((success_ != 0)) milone_assert_error("ty_synonym/ty_synonym.milone", 13, 2);
    return;
}

void ty_synonym_ty_synonym_yodaCase(int32_t exitCode_) {
    if ((0 != exitCode_)) milone_assert_error("ty_synonym/ty_synonym.milone", 16, 36);
    return;
}

void ty_synonym_ty_synonym_polymorphicFunCase(void) {
    int32_t call_;
    struct String call_1;
    call_ = ty_synonym_ty_synonym_BoolInt32Int32Int32Fun3_proj(true, 1, 0);
    if ((call_ != 1)) milone_assert_error("ty_synonym/ty_synonym.milone", 21, 2);
    call_1 = ty_synonym_ty_synonym_BoolStringStringStringFun3_proj(false, (struct String){.ptr = "T", .len = 1}, (struct String){.ptr = "F", .len = 1});
    if ((string_compare(call_1, (struct String){.ptr = "F", .len = 1}) != 0)) milone_assert_error("ty_synonym/ty_synonym.milone", 22, 2);
    return;
}

int main(int argc, char **argv) {
    milone_start(argc, argv);
    ty_synonym_ty_synonym_baseCase();
    ty_synonym_ty_synonym_yodaCase(0);
    ty_synonym_ty_synonym_polymorphicFunCase();
    return 0;
}
