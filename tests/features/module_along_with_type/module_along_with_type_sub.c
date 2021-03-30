#include "milone.h"

struct IntIntTuple2;

struct IntIntTuple2 module_along_with_type_sub_Pos_add(struct IntIntTuple2 l_, struct IntIntTuple2 r_);

struct String module_along_with_type_sub_Pos_toString(struct IntIntTuple2 arg_);

struct IntIntTuple2 {
    int t0;
    int t1;
};

struct IntIntTuple2 module_along_with_type_sub_Pos_add(struct IntIntTuple2 l_, struct IntIntTuple2 r_) {
    int ly_ = l_.t0;
    int lx_ = l_.t1;
    int ry_ = r_.t0;
    int rx_ = r_.t1;
    struct IntIntTuple2 tuple_ = (struct IntIntTuple2){.t0 = (ly_ + ry_), .t1 = (lx_ + rx_)};
    return tuple_;
}

struct String module_along_with_type_sub_Pos_toString(struct IntIntTuple2 arg_) {
    int row_ = arg_.t0;
    int column_ = arg_.t1;
    struct String call_ = str_of_int64((row_ + 1));
    struct String call_1 = str_of_int64((column_ + 1));
    return str_add(str_add(call_, (struct String){.str = ":", .len = 1}), call_1);
}
