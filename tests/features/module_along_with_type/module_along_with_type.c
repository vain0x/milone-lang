#include "milone.h"

struct IntIntTuple2;

enum Pos_Discriminant;

struct Pos_;

struct Pos_ add_(struct Pos_ l_, struct Pos_ r_1);

struct String toString_1(struct Pos_ arg_);

struct Pos_Pos_Tuple2;

enum Range_Discriminant;

struct Range_;

struct Range_ pair_(struct Pos_ s_, struct Pos_ t_);

struct String toString_(struct Range_ arg_1);

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

struct Pos_ add_(struct Pos_ l_, struct Pos_ r_1) {
    int ly_ = l_.Pos_.t0;
    int lx_ = l_.Pos_.t1;
    int ry_ = r_1.Pos_.t0;
    int rx_ = r_1.Pos_.t1;
    struct IntIntTuple2 tuple_ = (struct IntIntTuple2){.t0 = (ly_ + ry_), .t1 = (lx_ + rx_)};
    struct Pos_ variant_ = (struct Pos_){.discriminant = Pos_, .Pos_ = tuple_};
    return variant_;
}

struct String toString_1(struct Pos_ arg_) {
    int row_ = arg_.Pos_.t0;
    int column_ = arg_.Pos_.t1;
    struct String call_ = str_of_int64((row_ + 1));
    struct String call_1 = str_of_int64((column_ + 1));
    return str_add(str_add(call_, (struct String){.str = ":", .len = 1}), call_1);
}

struct Pos_Pos_Tuple2 {
    struct Pos_ t0;
    struct Pos_ t1;
};

enum Range_Discriminant {
    Range_,
};

struct Range_ {
    enum Range_Discriminant discriminant;
    union {
        struct Pos_Pos_Tuple2 Range_;
    };
};

struct Range_ pair_(struct Pos_ s_, struct Pos_ t_) {
    struct Pos_Pos_Tuple2 tuple_1 = (struct Pos_Pos_Tuple2){.t0 = s_, .t1 = t_};
    struct Range_ variant_1 = (struct Range_){.discriminant = Range_, .Range_ = tuple_1};
    return variant_1;
}

struct String toString_(struct Range_ arg_1) {
    struct Pos_ s_1 = arg_1.Range_.t0;
    struct Pos_ t_1 = arg_1.Range_.t1;
    int sy_ = s_1.Pos_.t0;
    int sx_ = s_1.Pos_.t1;
    int ty_ = t_1.Pos_.t0;
    int tx_ = t_1.Pos_.t1;
    struct String call_2 = str_of_int64((sy_ + 1));
    struct String call_3 = str_of_int64((sx_ + 1));
    struct String call_4 = str_of_int64((ty_ + 1));
    struct String call_5 = str_of_int64((tx_ + 1));
    return str_add(str_add(str_add(str_add(str_add(str_add(call_2, (struct String){.str = ".", .len = 1}), call_3), (struct String){.str = "-", .len = 1}), call_4), (struct String){.str = ".", .len = 1}), call_5);
}

int milone_main() {
    struct IntIntTuple2 tuple_2 = (struct IntIntTuple2){.t0 = 1, .t1 = 0};
    struct Pos_ variant_2 = (struct Pos_){.discriminant = Pos_, .Pos_ = tuple_2};
    eol_ = variant_2;
    struct Pos_ p_ = eol_;
    struct Pos_ call_6 = add_(p_, p_);
    struct Pos_Pos_Tuple2 tuple_3 = (struct Pos_Pos_Tuple2){.t0 = p_, .t1 = call_6};
    struct Range_ variant_3 = (struct Range_){.discriminant = Range_, .Range_ = tuple_3};
    struct Range_ r_ = variant_3;
    struct String call_7 = toString_1(p_);
    milone_assert((str_cmp(call_7, (struct String){.str = "2:1", .len = 3}) == 0), 29, 2);
    struct Pos_ call_8 = add_(p_, p_);
    struct String call_9 = toString_1(call_8);
    milone_assert((str_cmp(call_9, (struct String){.str = "3:1", .len = 3}) == 0), 30, 2);
    struct String call_10 = toString_(r_);
    milone_assert((str_cmp(call_10, (struct String){.str = "2.1-3.1", .len = 7}) == 0), 32, 2);
    return 0;
}
