#include <stdio.h>
#include <stdlib.h>
#include <milone.h>

struct IntStringTuple2_;

struct StringIntTuple2_;

struct StringStringTuple2_;

struct StringStringTuple2StringTuple2_;

int main(int argc, char** argv);

struct IntStringTuple2_ {
    int t0;
    struct String t1;
};

struct StringIntTuple2_ {
    struct String t0;
    int t1;
};

struct StringStringTuple2_ {
    struct String t0;
    struct String t1;
};

struct StringStringTuple2StringTuple2_ {
    struct StringStringTuple2_ t0;
    struct String t1;
};

int main(int argc, char** argv) {
    milone_start(argc, argv);
    struct IntStringTuple2_ a_;
    int x_;
    struct String _x;
    struct StringIntTuple2_ b_;
    struct String y_;
    int _y;
    struct String z_;
    struct String w_;
    struct String p_;
    struct String q_;
    struct String r_;
    struct IntStringTuple2_ IntStringTuple2_;
    struct StringIntTuple2_ StringIntTuple2_;
    struct StringStringTuple2_ StringStringTuple2_;
    struct StringStringTuple2StringTuple2_ StringStringTuple2StringTuple2_;
    struct StringStringTuple2_ StringStringTuple2_1;
    IntStringTuple2_ = (struct IntStringTuple2_){.t0 = 1, .t1 = (struct String){.ptr = "snd", .len = 3}};
    a_ = IntStringTuple2_;
    x_ = a_.t0;
    _x = a_.t1;
    printf("%d\n", x_);
    StringIntTuple2_ = (struct StringIntTuple2_){.t0 = (struct String){.ptr = "fst", .len = 3}, .t1 = 2};
    b_ = StringIntTuple2_;
    y_ = b_.t0;
    _y = b_.t1;
    printf("%s\n", string_to_c_str(y_));
    StringStringTuple2_ = (struct StringStringTuple2_){.t0 = (struct String){.ptr = "z", .len = 1}, .t1 = (struct String){.ptr = "w", .len = 1}};
    z_ = StringStringTuple2_.t0;
    w_ = StringStringTuple2_.t1;
    printf("z=%s\n", string_to_c_str(z_));
    printf("w=%s\n", string_to_c_str(w_));
    StringStringTuple2_1 = (struct StringStringTuple2_){.t0 = (struct String){.ptr = "p", .len = 1}, .t1 = (struct String){.ptr = "q", .len = 1}};
    StringStringTuple2StringTuple2_ = (struct StringStringTuple2StringTuple2_){.t0 = StringStringTuple2_1, .t1 = (struct String){.ptr = "r", .len = 1}};
    p_ = StringStringTuple2StringTuple2_.t0.t0;
    q_ = StringStringTuple2StringTuple2_.t0.t1;
    r_ = StringStringTuple2StringTuple2_.t1;
    printf("p=%s\n", string_to_c_str(p_));
    return 0;
}
