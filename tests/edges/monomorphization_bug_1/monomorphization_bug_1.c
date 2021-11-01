#include "milone.h"

struct StringStringTuple2_;

struct StringStringTuple2_ monomorphization_bug_1_monomorphization_bug_1_StringStringStringTuple2Fun1_dup(struct String x_);

struct StringStringTuple2_ monomorphization_bug_1_monomorphization_bug_1_bug(struct String b_);

int milone_main(void);

struct StringStringTuple2_ {
    struct String t0;
    struct String t1;
};

struct StringStringTuple2_ monomorphization_bug_1_monomorphization_bug_1_StringStringStringTuple2Fun1_dup(struct String x_) {
    struct StringStringTuple2_ StringStringTuple2_ = (struct StringStringTuple2_){.t0 = x_, .t1 = x_};
    return StringStringTuple2_;
}

struct StringStringTuple2_ monomorphization_bug_1_monomorphization_bug_1_bug(struct String b_) {
    struct StringStringTuple2_ call_ = monomorphization_bug_1_monomorphization_bug_1_StringStringStringTuple2Fun1_dup(b_);
    return call_;
}

int milone_main(void) {
    struct StringStringTuple2_ call_1 = monomorphization_bug_1_monomorphization_bug_1_bug((struct String){.str = "a", .len = 1});
    struct String x1_ = call_1.t0;
    struct String x2_ = call_1.t1;
    printf("x1 = \'%s\'\n", str_to_c_str(x1_));
    printf("x2 = \'%s\'\n", str_to_c_str(x2_));
    return 0;
}
