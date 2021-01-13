#include "milone.h"

struct IntIntTuple2;

enum Pos_Discriminant;

struct Pos_;

struct Pos_ add_(struct Pos_ l_, struct Pos_ r_);

struct String toString_(struct Pos_ arg_);

static struct Pos_ eol_;

int milone_main();

struct IntIntTuple2 {
    int t0;
    int t1;
};

enum Pos_Discriminant {
    Pos_,
};

struct Pos_ {
    enum Pos_Discriminant discriminant;
    union {
        struct IntIntTuple2 Pos_;
    };
};

struct Pos_ add_(struct Pos_ l_, struct Pos_ r_) {
    int ly_ = l_.Pos_.t0;
    int lx_ = l_.Pos_.t1;
    int ry_ = r_.Pos_.t0;
    int rx_ = r_.Pos_.t1;
    struct IntIntTuple2 tuple_ = (struct IntIntTuple2){.t0 = (ly_ + ry_), .t1 = (lx_ + rx_)};
    struct Pos_ variant_ = (struct Pos_){.discriminant = Pos_, .Pos_ = tuple_};
    return variant_;
}

struct String toString_(struct Pos_ arg_) {
    int row_ = arg_.Pos_.t0;
    int column_ = arg_.Pos_.t1;
    struct String call_ = str_of_int64((row_ + 1));
    struct String call_1 = str_of_int64((column_ + 1));
    return str_add(str_add(call_, (struct String){.str = ":", .len = 1}), call_1);
}

int milone_main() {
    struct IntIntTuple2 tuple_1 = (struct IntIntTuple2){.t0 = 1, .t1 = 0};
    struct Pos_ variant_1 = (struct Pos_){.discriminant = Pos_, .Pos_ = tuple_1};
    eol_ = variant_1;
    struct String call_2 = toString_(eol_);
    milone_assert((str_cmp(call_2, (struct String){.str = "2:1", .len = 3}) == 0), 19, 2);
    struct Pos_ call_3 = add_(eol_, eol_);
    struct String call_4 = toString_(call_3);
    milone_assert((str_cmp(call_4, (struct String){.str = "3:1", .len = 3}) == 0), 20, 2);
    return 0;
}
