#include "milone.h"

struct IntIntTuple2_;

struct IntIntTuple2IntIntTuple2Tuple2_;

struct IntIntTuple2IntIntTuple2Tuple2_ module_along_with_type_Program_Range_pair(struct IntIntTuple2_ s_, struct IntIntTuple2_ t_);

struct String module_along_with_type_Program_Range_toString(struct IntIntTuple2IntIntTuple2Tuple2_ arg_1);

struct IntIntTuple2_ module_along_with_type_sub_Pos_add(struct IntIntTuple2_, struct IntIntTuple2_);

struct String module_along_with_type_sub_Pos_toString(struct IntIntTuple2_);

int milone_main();

struct IntIntTuple2_ {
    int t0;
    int t1;
};

struct IntIntTuple2IntIntTuple2Tuple2_ {
    struct IntIntTuple2_ t0;
    struct IntIntTuple2_ t1;
};

struct IntIntTuple2_ module_along_with_type_sub_Pos_eol;

extern struct IntIntTuple2_ module_along_with_type_sub_Pos_eol;

struct IntIntTuple2IntIntTuple2Tuple2_ module_along_with_type_Program_Range_pair(struct IntIntTuple2_ s_, struct IntIntTuple2_ t_) {
    struct IntIntTuple2IntIntTuple2Tuple2_ IntIntTuple2IntIntTuple2Tuple2_ = (struct IntIntTuple2IntIntTuple2Tuple2_){.t0 = s_, .t1 = t_};
    return IntIntTuple2IntIntTuple2Tuple2_;
}

struct String module_along_with_type_Program_Range_toString(struct IntIntTuple2IntIntTuple2Tuple2_ arg_1) {
    struct IntIntTuple2_ s_1 = arg_1.t0;
    struct IntIntTuple2_ t_1 = arg_1.t1;
    int sy_ = s_1.t0;
    int sx_ = s_1.t1;
    int ty_ = t_1.t0;
    int tx_ = t_1.t1;
    struct String call_2 = str_of_int64((sy_ + 1));
    struct String call_3 = str_of_int64((sx_ + 1));
    struct String call_4 = str_of_int64((ty_ + 1));
    struct String call_5 = str_of_int64((tx_ + 1));
    return str_add(str_add(str_add(str_add(str_add(str_add(call_2, (struct String){.str = ".", .len = 1}), call_3), (struct String){.str = "-", .len = 1}), call_4), (struct String){.str = ".", .len = 1}), call_5);
}

int milone_main() {
    struct IntIntTuple2_ IntIntTuple2_1 = (struct IntIntTuple2_){.t0 = 1, .t1 = 0};
    module_along_with_type_sub_Pos_eol = IntIntTuple2_1;
    struct IntIntTuple2_ p_ = module_along_with_type_sub_Pos_eol;
    struct IntIntTuple2_ call_6 = module_along_with_type_sub_Pos_add(p_, p_);
    struct IntIntTuple2IntIntTuple2Tuple2_ IntIntTuple2IntIntTuple2Tuple2_1 = (struct IntIntTuple2IntIntTuple2Tuple2_){.t0 = p_, .t1 = call_6};
    struct IntIntTuple2IntIntTuple2Tuple2_ r_1 = IntIntTuple2IntIntTuple2Tuple2_1;
    struct String call_7 = module_along_with_type_sub_Pos_toString(p_);
    milone_assert((str_compare(call_7, (struct String){.str = "2:1", .len = 3}) == 0), 29, 2);
    struct IntIntTuple2_ call_8 = module_along_with_type_sub_Pos_add(p_, p_);
    struct String call_9 = module_along_with_type_sub_Pos_toString(call_8);
    milone_assert((str_compare(call_9, (struct String){.str = "3:1", .len = 3}) == 0), 30, 2);
    struct String call_10 = module_along_with_type_Program_Range_toString(r_1);
    milone_assert((str_compare(call_10, (struct String){.str = "2.1-3.1", .len = 7}) == 0), 32, 2);
    return 0;
}
