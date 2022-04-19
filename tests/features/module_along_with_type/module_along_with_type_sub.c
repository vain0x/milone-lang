#include <stdio.h>
#include <stdlib.h>
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
    int ly_;
    int lx_;
    int ry_;
    int rx_;
    struct IntIntTuple2_ IntIntTuple2_;
    ly_ = l_.t0;
    lx_ = l_.t1;
    ry_ = r_.t0;
    rx_ = r_.t1;
    IntIntTuple2_ = (struct IntIntTuple2_){.t0 = (ly_ + ry_), .t1 = (lx_ + rx_)};
    return IntIntTuple2_;
}

struct String module_along_with_type_sub_Pos_toString(struct IntIntTuple2_ arg_) {
    int row_;
    int column_;
    struct String call_;
    struct String call_1;
    row_ = arg_.t0;
    column_ = arg_.t1;
    call_ = string_of_int64((row_ + 1));
    call_1 = string_of_int64((column_ + 1));
    return string_add(string_add(call_, (struct String){.ptr = ":", .len = 1}), call_1);
}

void module_along_with_type_sub_start(void) {
    struct IntIntTuple2_ IntIntTuple2_1;
    IntIntTuple2_1 = (struct IntIntTuple2_){.t0 = 1, .t1 = 0};
    module_along_with_type_sub_Pos_eol = IntIntTuple2_1;
    return;
}
