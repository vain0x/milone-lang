#include "milone.h"

enum Expr_Tag;

struct Expr_;

struct Expr_Expr_Tuple2;

int eval_(struct Expr_ expr_);

int main();

enum Expr_Tag {
    Int_,
    Add_,
};

struct Expr_ {
    enum Expr_Tag tag;
    union {
        void* Int_;
        void* Add_;
    };
};

struct Expr_Expr_Tuple2 {
    struct Expr_ t0;
    struct Expr_ t1;
};

int eval_(struct Expr_ expr_) {
    int match_;
    if ((expr_.tag != Int_)) goto next_2;
    int value_ = (*(((int*)expr_.Int_)));
    match_ = value_;
    goto end_match_1;
next_2:;
    if ((expr_.tag != Add_)) goto next_3;
    struct Expr_ l_ = (*(((struct Expr_Expr_Tuple2*)expr_.Add_))).t0;
    struct Expr_ r_ = (*(((struct Expr_Expr_Tuple2*)expr_.Add_))).t1;
    int call_ = eval_(l_);
    int call_1 = eval_(r_);
    match_ = (call_ + call_1);
    goto end_match_1;
next_3:;
    exit(1);
end_match_1:;
    return match_;
}

int main() {
    void* box_ = (void*)milone_mem_alloc(1, sizeof(int));
    (*(((int*)box_))) = 11;
    struct Expr_ variant_ = (struct Expr_){.tag = Int_, .Int_ = box_};
    void* box_1 = (void*)milone_mem_alloc(1, sizeof(int));
    (*(((int*)box_1))) = 22;
    struct Expr_ variant_1 = (struct Expr_){.tag = Int_, .Int_ = box_1};
    void* box_2 = (void*)milone_mem_alloc(1, sizeof(int));
    (*(((int*)box_2))) = 9;
    struct Expr_ variant_2 = (struct Expr_){.tag = Int_, .Int_ = box_2};
    struct Expr_Expr_Tuple2 tuple_1;
    tuple_1.t0 = variant_1;
    tuple_1.t1 = variant_2;
    void* box_3 = (void*)milone_mem_alloc(1, sizeof(struct Expr_Expr_Tuple2));
    (*(((struct Expr_Expr_Tuple2*)box_3))) = tuple_1;
    struct Expr_ variant_3 = (struct Expr_){.tag = Add_, .Add_ = box_3};
    struct Expr_Expr_Tuple2 tuple_;
    tuple_.t0 = variant_;
    tuple_.t1 = variant_3;
    void* box_4 = (void*)milone_mem_alloc(1, sizeof(struct Expr_Expr_Tuple2));
    (*(((struct Expr_Expr_Tuple2*)box_4))) = tuple_;
    struct Expr_ variant_4 = (struct Expr_){.tag = Add_, .Add_ = box_4};
    struct Expr_ expr_1 = variant_4;
    int call_2 = eval_(expr_1);
    milone_assert((call_2 == 42), 18, 2);
    int call_3 = 0;
    return 0;
}
