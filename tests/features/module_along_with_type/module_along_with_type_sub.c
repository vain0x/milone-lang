#include <milone.h>

struct IntIntTuple2_;

struct IntIntTuple2_ module_along_with_type_sub_Pos_add(struct IntIntTuple2_ l_, struct IntIntTuple2_ r_);

struct String module_along_with_type_sub_Pos_toString(struct IntIntTuple2_ arg_);

void module_along_with_type_sub_start(void);

struct IntIntTuple2_ {
    int t0;
    int t1;
};

struct IntIntTuple2_ module_along_with_type_sub_Pos_eol;

struct IntIntTuple2_ module_along_with_type_sub_Pos_add(struct IntIntTuple2_ l_, struct IntIntTuple2_ r_) {
    int ly_ = l_.t0;
    int lx_ = l_.t1;
    int ry_ = r_.t0;
    int rx_ = r_.t1;
    struct IntIntTuple2_ IntIntTuple2_ = (struct IntIntTuple2_){.t0 = (ly_ + ry_), .t1 = (lx_ + rx_)};
    return IntIntTuple2_;
}

struct String module_along_with_type_sub_Pos_toString(struct IntIntTuple2_ arg_) {
    int row_ = arg_.t0;
    int column_ = arg_.t1;
    struct String call_ = str_of_int64((row_ + 1));
    struct String call_1 = str_of_int64((column_ + 1));
    return str_add(str_add(call_, (struct String){.str = ":", .len = 1}), call_1);
}

void module_along_with_type_sub_start(void) {
    struct IntIntTuple2_ IntIntTuple2_1 = (struct IntIntTuple2_){.t0 = 1, .t1 = 0};
    module_along_with_type_sub_Pos_eol = IntIntTuple2_1;
    return;
}
