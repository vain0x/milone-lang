#include <stdio.h>
#include <stdlib.h>
#include <milone.h>

struct Expr_;

struct ExprExprTuple2_;

int32_t union_rec_direct_union_rec_direct_main_eval(struct Expr_ expr_);

int main(int argc, char** argv);

enum Expr_Discriminant {
    Int_,
    Add_,
};

struct Expr_ {
    enum Expr_Discriminant discriminant;
    union {
        int32_t Int_;
        void const* Add_;
    };
};

struct ExprExprTuple2_ {
    struct Expr_ t0;
    struct Expr_ t1;
};

int32_t union_rec_direct_union_rec_direct_main_eval(struct Expr_ expr_) {
    int32_t value_;
    struct Expr_ l_;
    struct Expr_ r_;
    int32_t match_;
    int32_t call_;
    int32_t call_1;
    if ((expr_.discriminant != Int_)) goto next_2;
    value_ = expr_.Int_;
    match_ = value_;
    goto end_match_1;
next_2:;
    if ((expr_.discriminant != Add_)) goto next_3;
    l_ = (*(((struct ExprExprTuple2_ const*)expr_.Add_))).t0;
    r_ = (*(((struct ExprExprTuple2_ const*)expr_.Add_))).t1;
    call_ = union_rec_direct_union_rec_direct_main_eval(l_);
    call_1 = union_rec_direct_union_rec_direct_main_eval(r_);
    match_ = (call_ + call_1);
    goto end_match_1;
next_3:;
    exit(1);
end_match_1:;
    return match_;
}

int main(int argc, char** argv) {
    milone_start(argc, argv);
    struct Expr_ expr_1;
    struct ExprExprTuple2_ ExprExprTuple2_;
    struct Expr_ variant_;
    struct ExprExprTuple2_ ExprExprTuple2_1;
    struct Expr_ variant_1;
    struct Expr_ variant_2;
    void const* box_;
    struct Expr_ variant_3;
    void const* box_1;
    struct Expr_ variant_4;
    int32_t call_2;
    variant_ = (struct Expr_){.discriminant = Int_, .Int_ = 11};
    variant_1 = (struct Expr_){.discriminant = Int_, .Int_ = 22};
    variant_2 = (struct Expr_){.discriminant = Int_, .Int_ = 9};
    ExprExprTuple2_1 = (struct ExprExprTuple2_){.t0 = variant_1, .t1 = variant_2};
    box_ = ((void const*)milone_region_alloc(1, sizeof(struct ExprExprTuple2_)));
    (*(((struct ExprExprTuple2_*)box_))) = ExprExprTuple2_1;
    variant_3 = (struct Expr_){.discriminant = Add_, .Add_ = box_};
    ExprExprTuple2_ = (struct ExprExprTuple2_){.t0 = variant_, .t1 = variant_3};
    box_1 = ((void const*)milone_region_alloc(1, sizeof(struct ExprExprTuple2_)));
    (*(((struct ExprExprTuple2_*)box_1))) = ExprExprTuple2_;
    variant_4 = (struct Expr_){.discriminant = Add_, .Add_ = box_1};
    expr_1 = variant_4;
    call_2 = union_rec_direct_union_rec_direct_main_eval(expr_1);
    milone_assert((call_2 == 42), (struct String){.ptr = "union_rec_direct/union_rec_direct.milone", .len = 40}, 17, 2);
    return 0;
}
