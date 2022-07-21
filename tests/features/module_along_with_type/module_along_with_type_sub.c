#include <stdio.h>
#include <stdlib.h>
#include <milone.h>

struct Int32Int32Tuple2_;

struct Int32Int32Tuple2_ module_along_with_type_sub_Pos_add(struct Int32Int32Tuple2_ l_, struct Int32Int32Tuple2_ r_);

struct String module_along_with_type_sub_Pos_toString(struct Int32Int32Tuple2_ arg_);

void module_along_with_type_sub_start(void);

struct Int32Int32Tuple2_ {
    int32_t t0;
    int32_t t1;
};

struct Int32Int32Tuple2_ module_along_with_type_sub_Pos_eol;

struct Int32Int32Tuple2_ module_along_with_type_sub_Pos_add(struct Int32Int32Tuple2_ l_, struct Int32Int32Tuple2_ r_) {
    int32_t ly_;
    int32_t lx_;
    int32_t ry_;
    int32_t rx_;
    struct Int32Int32Tuple2_ Int32Int32Tuple2_;
    ly_ = l_.t0;
    lx_ = l_.t1;
    ry_ = r_.t0;
    rx_ = r_.t1;
    Int32Int32Tuple2_ = (struct Int32Int32Tuple2_){.t0 = (ly_ + ry_), .t1 = (lx_ + rx_)};
    return Int32Int32Tuple2_;
}

struct String module_along_with_type_sub_Pos_toString(struct Int32Int32Tuple2_ arg_) {
    int32_t row_;
    int32_t column_;
    struct String call_;
    struct String call_1;
    row_ = arg_.t0;
    column_ = arg_.t1;
    call_ = string_of_int64((row_ + 1));
    call_1 = string_of_int64((column_ + 1));
    return string_add(string_add(call_, (struct String){.ptr = ":", .len = 1}), call_1);
}

void module_along_with_type_sub_start(void) {
    struct Int32Int32Tuple2_ Int32Int32Tuple2_1;
    Int32Int32Tuple2_1 = (struct Int32Int32Tuple2_){.t0 = 1, .t1 = 0};
    module_along_with_type_sub_Pos_eol = Int32Int32Tuple2_1;
    return;
}
