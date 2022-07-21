#include <stdio.h>
#include <stdlib.h>
#include <milone.h>

struct Int32Int32Tuple2_;

struct Int32Int32Tuple2Int32Int32Tuple2Tuple2_;

struct Int32Int32Tuple2Int32Int32Tuple2Tuple2_ module_along_with_type_module_along_with_type_Range_pair(struct Int32Int32Tuple2_ s_, struct Int32Int32Tuple2_ t_);

struct String module_along_with_type_module_along_with_type_Range_toString(struct Int32Int32Tuple2Int32Int32Tuple2Tuple2_ arg_);

void module_along_with_type_sub_start(void);

struct Int32Int32Tuple2_ module_along_with_type_sub_Pos_add(struct Int32Int32Tuple2_, struct Int32Int32Tuple2_);

struct String module_along_with_type_sub_Pos_toString(struct Int32Int32Tuple2_);

int main(int argc, char **argv);

struct Int32Int32Tuple2_ {
    int32_t t0;
    int32_t t1;
};

struct Int32Int32Tuple2Int32Int32Tuple2Tuple2_ {
    struct Int32Int32Tuple2_ t0;
    struct Int32Int32Tuple2_ t1;
};

extern struct Int32Int32Tuple2_ module_along_with_type_sub_Pos_eol;

struct Int32Int32Tuple2Int32Int32Tuple2Tuple2_ module_along_with_type_module_along_with_type_Range_pair(struct Int32Int32Tuple2_ s_, struct Int32Int32Tuple2_ t_) {
    struct Int32Int32Tuple2Int32Int32Tuple2Tuple2_ Int32Int32Tuple2Int32Int32Tuple2Tuple2_;
    Int32Int32Tuple2Int32Int32Tuple2Tuple2_ = (struct Int32Int32Tuple2Int32Int32Tuple2Tuple2_){.t0 = s_, .t1 = t_};
    return Int32Int32Tuple2Int32Int32Tuple2Tuple2_;
}

struct String module_along_with_type_module_along_with_type_Range_toString(struct Int32Int32Tuple2Int32Int32Tuple2Tuple2_ arg_) {
    struct Int32Int32Tuple2_ s_1;
    struct Int32Int32Tuple2_ t_1;
    int32_t sy_;
    int32_t sx_;
    int32_t ty_;
    int32_t tx_;
    struct String call_;
    struct String call_1;
    struct String call_2;
    struct String call_3;
    s_1 = arg_.t0;
    t_1 = arg_.t1;
    sy_ = s_1.t0;
    sx_ = s_1.t1;
    ty_ = t_1.t0;
    tx_ = t_1.t1;
    call_ = string_of_int64((sy_ + 1));
    call_1 = string_of_int64((sx_ + 1));
    call_2 = string_of_int64((ty_ + 1));
    call_3 = string_of_int64((tx_ + 1));
    return string_add(string_add(string_add(string_add(string_add(string_add(call_, (struct String){.ptr = ".", .len = 1}), call_1), (struct String){.ptr = "-", .len = 1}), call_2), (struct String){.ptr = ".", .len = 1}), call_3);
}

int main(int argc, char **argv) {
    milone_start(argc, argv);
    struct Int32Int32Tuple2_ p_;
    struct Int32Int32Tuple2Int32Int32Tuple2Tuple2_ r_;
    struct Int32Int32Tuple2Int32Int32Tuple2Tuple2_ Int32Int32Tuple2Int32Int32Tuple2Tuple2_1;
    struct Int32Int32Tuple2_ call_4;
    struct String call_5;
    struct Int32Int32Tuple2_ call_6;
    struct String call_7;
    struct String call_8;
    module_along_with_type_sub_start();
    p_ = module_along_with_type_sub_Pos_eol;
    call_4 = module_along_with_type_sub_Pos_add(p_, p_);
    Int32Int32Tuple2Int32Int32Tuple2Tuple2_1 = (struct Int32Int32Tuple2Int32Int32Tuple2Tuple2_){.t0 = p_, .t1 = call_4};
    r_ = Int32Int32Tuple2Int32Int32Tuple2Tuple2_1;
    call_5 = module_along_with_type_sub_Pos_toString(p_);
    if ((string_compare(call_5, (struct String){.ptr = "2:1", .len = 3}) != 0)) milone_assert_error("module_along_with_type/module_along_with_type.milone", 29, 2);
    call_6 = module_along_with_type_sub_Pos_add(p_, p_);
    call_7 = module_along_with_type_sub_Pos_toString(call_6);
    if ((string_compare(call_7, (struct String){.ptr = "3:1", .len = 3}) != 0)) milone_assert_error("module_along_with_type/module_along_with_type.milone", 30, 2);
    call_8 = module_along_with_type_module_along_with_type_Range_toString(r_);
    if ((string_compare(call_8, (struct String){.ptr = "2.1-3.1", .len = 7}) != 0)) milone_assert_error("module_along_with_type/module_along_with_type.milone", 32, 2);
    return 0;
}
