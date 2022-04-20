#include <stdio.h>
#include <stdlib.h>
#include <milone.h>

struct Int32StringTuple2_;

struct Int32StringTuple2option1_;

int32_t fun_generic_ty_degeneration_fun_generic_ty_degeneration_ObjectInt32StringTuple2option1Int32Fun2_fstUnbox(void const *boxedPair_, struct Int32StringTuple2option1_ phantom_);

int32_t fun_generic_ty_degeneration_fun_generic_ty_degeneration_fstUnbox_ObjectUnitInt32Fun2_f(void const *boxedPair_);

int32_t fun_generic_ty_degeneration_fun_generic_ty_degeneration_Int32StringTuple2Int32Fun1_myFst(struct Int32StringTuple2_ arg_);

void fun_generic_ty_degeneration_fun_generic_ty_degeneration_testCase(struct Int32StringTuple2_ kv_);

int main(int argc, char **argv);

struct Int32StringTuple2_ {
    int32_t t0;
    struct String t1;
};

enum Int32StringTuple2option1_Discriminant {
    None_,
    Some_,
};

struct Int32StringTuple2option1_ {
    enum Int32StringTuple2option1_Discriminant discriminant;
    union {
        struct Int32StringTuple2_ Some_;
    };
};

int32_t fun_generic_ty_degeneration_fun_generic_ty_degeneration_ObjectInt32StringTuple2option1Int32Fun2_fstUnbox(void const *boxedPair_, struct Int32StringTuple2option1_ phantom_) {
    int32_t call_;
    call_ = fun_generic_ty_degeneration_fun_generic_ty_degeneration_fstUnbox_ObjectUnitInt32Fun2_f(boxedPair_);
    return call_;
}

int32_t fun_generic_ty_degeneration_fun_generic_ty_degeneration_fstUnbox_ObjectUnitInt32Fun2_f(void const *boxedPair_) {
    int32_t call_1;
    call_1 = fun_generic_ty_degeneration_fun_generic_ty_degeneration_Int32StringTuple2Int32Fun1_myFst((*(((struct Int32StringTuple2_ const *)boxedPair_))));
    return call_1;
}

int32_t fun_generic_ty_degeneration_fun_generic_ty_degeneration_Int32StringTuple2Int32Fun1_myFst(struct Int32StringTuple2_ arg_) {
    int32_t x_;
    x_ = arg_.t0;
    return x_;
}

void fun_generic_ty_degeneration_fun_generic_ty_degeneration_testCase(struct Int32StringTuple2_ kv_) {
    void const *box_;
    int32_t call_2;
    box_ = ((void const *)milone_region_alloc(1, sizeof(struct Int32StringTuple2_)));
    (*(((struct Int32StringTuple2_ *)box_))) = kv_;
    call_2 = fun_generic_ty_degeneration_fun_generic_ty_degeneration_ObjectInt32StringTuple2option1Int32Fun2_fstUnbox(box_, (struct Int32StringTuple2option1_){.discriminant = None_});
    if ((call_2 != 0)) milone_assert_error("fun_generic_ty_degeneration/fun_generic_ty_degeneration.milone", 20, 2);
    return;
}

int main(int argc, char **argv) {
    milone_start(argc, argv);
    struct Int32StringTuple2_ Int32StringTuple2_;
    Int32StringTuple2_ = (struct Int32StringTuple2_){.t0 = 0, .t1 = (struct String){.ptr = "right", .len = 5}};
    fun_generic_ty_degeneration_fun_generic_ty_degeneration_testCase(Int32StringTuple2_);
    return 0;
}
