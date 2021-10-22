#include "milone.h"

struct StringStringTuple2_;

void const* monomorphization_bug_1_monomorphization_bug_1_ObjectObjectFun1_dup(void const* arg_);

void const* monomorphization_bug_1_monomorphization_bug_1_bug(void const* b_);

int milone_main(void);

struct StringStringTuple2_ {
    struct String t0;
    struct String t1;
};

void const* monomorphization_bug_1_monomorphization_bug_1_ObjectObjectFun1_dup(void const* arg_) {
    struct String x_ = (*(((struct String const*)arg_)));
    struct StringStringTuple2_ StringStringTuple2_ = (struct StringStringTuple2_){.t0 = x_, .t1 = x_};
    void const* box_ = milone_mem_alloc(1, sizeof(struct StringStringTuple2_));
    (*(((struct StringStringTuple2_*)box_))) = StringStringTuple2_;
    return box_;
}

void const* monomorphization_bug_1_monomorphization_bug_1_bug(void const* b_) {
    void const* call_ = monomorphization_bug_1_monomorphization_bug_1_ObjectObjectFun1_dup(b_);
    return call_;
}

int milone_main(void) {
    void const* box_1 = milone_mem_alloc(1, sizeof(struct String));
    (*(((struct String*)box_1))) = (struct String){.str = "a", .len = 1};
    void const* call_1 = monomorphization_bug_1_monomorphization_bug_1_bug(box_1);
    struct String x1_ = (*(((struct StringStringTuple2_ const*)call_1))).t0;
    struct String x2_ = (*(((struct StringStringTuple2_ const*)call_1))).t1;
    printf("x1 = \'%s\'\n", str_to_c_str(x1_));
    printf("x2 = \'%s\'\n", str_to_c_str(x2_));
    return 0;
}
