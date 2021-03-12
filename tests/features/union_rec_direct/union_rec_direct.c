#include "milone.h"

struct Expr_;

struct Expr_Expr_Tuple2;

int eval_(struct Expr_ expr_);

int milone_main();

enum Expr_Discriminant {
    Int_,
    Add_,
};

struct Expr_ {
    enum Expr_Discriminant discriminant;
    union {
        int Int_;
        void const* Add_;
    } payload;
};

struct Expr_Expr_Tuple2 {
    struct Expr_ t0;
    struct Expr_ t1;
};

int eval_(struct Expr_ expr_) {
    int match_;
    if ((expr_.discriminant != Int_)) goto next_2;
    int value_ = expr_.payload.Int_;
    match_ = value_;
    goto end_match_1;
next_2:;
    if ((expr_.discriminant != Add_)) goto next_3;
    struct Expr_ l_ = (*(((struct Expr_Expr_Tuple2 const*)expr_.payload.Add_))).t0;
    struct Expr_ r_ = (*(((struct Expr_Expr_Tuple2 const*)expr_.payload.Add_))).t1;
    int call_ = eval_(l_);
    int call_1 = eval_(r_);
    match_ = (call_ + call_1);
    goto end_match_1;
next_3:;
    exit(1);
end_match_1:;
    return match_;
}

int milone_main() {
    struct Expr_ variant_ = ((struct Expr_){.discriminant = Int_, .payload = {.Int_ = 11}});
    struct Expr_ variant_1 = ((struct Expr_){.discriminant = Int_, .payload = {.Int_ = 22}});
    struct Expr_ variant_2 = ((struct Expr_){.discriminant = Int_, .payload = {.Int_ = 9}});
    struct Expr_Expr_Tuple2 tuple_1 = ((struct Expr_Expr_Tuple2){.t0 = variant_1, .t1 = variant_2});
    void const* box_ = milone_mem_alloc(1, sizeof(struct Expr_Expr_Tuple2));
    (*(((struct Expr_Expr_Tuple2*)box_))) = tuple_1;
    struct Expr_ variant_3 = ((struct Expr_){.discriminant = Add_, .payload = {.Add_ = box_}});
    struct Expr_Expr_Tuple2 tuple_ = ((struct Expr_Expr_Tuple2){.t0 = variant_, .t1 = variant_3});
    void const* box_1 = milone_mem_alloc(1, sizeof(struct Expr_Expr_Tuple2));
    (*(((struct Expr_Expr_Tuple2*)box_1))) = tuple_;
    struct Expr_ variant_4 = ((struct Expr_){.discriminant = Add_, .payload = {.Add_ = box_1}});
    struct Expr_ expr_1 = variant_4;
    int call_2 = eval_(expr_1);
    milone_assert((call_2 == 42), 17, 2);
    return 0;
}
