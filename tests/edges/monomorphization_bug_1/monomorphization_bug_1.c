#include <stdio.h>
#include <stdlib.h>
#include <milone.h>

struct StringStringTuple2_;

struct StringStringTuple2_ monomorphization_bug_1_monomorphization_bug_1_StringStringStringTuple2Fun1_dup(struct String x_);

struct StringStringTuple2_ monomorphization_bug_1_monomorphization_bug_1_bug(struct String b_);

int main(int argc, char **argv);

struct StringStringTuple2_ {
    struct String t0;
    struct String t1;
};

struct StringStringTuple2_ monomorphization_bug_1_monomorphization_bug_1_StringStringStringTuple2Fun1_dup(struct String x_) {
    struct StringStringTuple2_ StringStringTuple2_;
    StringStringTuple2_ = (struct StringStringTuple2_){.t0 = x_, .t1 = x_};
    return StringStringTuple2_;
}

struct StringStringTuple2_ monomorphization_bug_1_monomorphization_bug_1_bug(struct String b_) {
    struct StringStringTuple2_ call_;
    call_ = monomorphization_bug_1_monomorphization_bug_1_StringStringStringTuple2Fun1_dup(b_);
    return call_;
}

int main(int argc, char **argv) {
    milone_start(argc, argv);
    struct String x1_;
    struct String x2_;
    struct StringStringTuple2_ call_1;
    call_1 = monomorphization_bug_1_monomorphization_bug_1_bug((struct String){.ptr = "a", .len = 1});
    x1_ = call_1.t0;
    x2_ = call_1.t1;
    printf("x1 = \'%s\'\n", string_to_c_str(x1_));
    printf("x2 = \'%s\'\n", string_to_c_str(x2_));
    return 0;
}
