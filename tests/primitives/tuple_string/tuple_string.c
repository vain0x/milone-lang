#include <stdio.h>
#include <stdlib.h>
#include <milone.h>

struct Int32Int32Tuple2_;

struct Int32Int32Int32Tuple3_;

struct Int32Int32Int32Int32Tuple2Tuple3_;

struct String MiloneDerive_TupleString_tuple2String(struct Int32Int32Tuple2_ arg_);

struct String MiloneDerive_TupleString_tuple3String(struct Int32Int32Int32Tuple3_ arg_1);

struct String MiloneDerive_TupleString_tuple2String(struct Int32Int32Tuple2_);

struct String MiloneDerive_TupleString_tuple3String_1(struct Int32Int32Int32Int32Tuple2Tuple3_ arg_2);

struct String MiloneDerive_TupleString_tuple3String(struct Int32Int32Int32Tuple3_);

struct String MiloneDerive_TupleString_tuple3String_1(struct Int32Int32Int32Int32Tuple2Tuple3_);

int main(int argc, char **argv);

struct Int32Int32Tuple2_ {
    int32_t t0;
    int32_t t1;
};

struct Int32Int32Int32Tuple3_ {
    int32_t t0;
    int32_t t1;
    int32_t t2;
};

struct Int32Int32Int32Int32Tuple2Tuple3_ {
    int32_t t0;
    int32_t t1;
    struct Int32Int32Tuple2_ t2;
};

struct String MiloneDerive_TupleString_tuple2String(struct Int32Int32Tuple2_ arg_) {
    int32_t x0_2;
    int32_t x1_2;
    struct String call_;
    struct String call_1;
    x0_2 = arg_.t0;
    x1_2 = arg_.t1;
    call_ = string_of_int64(x0_2);
    call_1 = string_of_int64(x1_2);
    return string_add(string_add(string_add(string_add((struct String){.ptr = "(", .len = 1}, call_), (struct String){.ptr = ", ", .len = 2}), call_1), (struct String){.ptr = ")", .len = 1});
}

struct String MiloneDerive_TupleString_tuple3String(struct Int32Int32Int32Tuple3_ arg_1) {
    int32_t x0_;
    int32_t x1_;
    int32_t x2_;
    struct String call_2;
    struct String call_3;
    struct String call_4;
    x0_ = arg_1.t0;
    x1_ = arg_1.t1;
    x2_ = arg_1.t2;
    call_2 = string_of_int64(x0_);
    call_3 = string_of_int64(x1_);
    call_4 = string_of_int64(x2_);
    return string_add(string_add(string_add(string_add(string_add(string_add((struct String){.ptr = "(", .len = 1}, call_2), (struct String){.ptr = ", ", .len = 2}), call_3), (struct String){.ptr = ", ", .len = 2}), call_4), (struct String){.ptr = ")", .len = 1});
}

struct String MiloneDerive_TupleString_tuple3String_1(struct Int32Int32Int32Int32Tuple2Tuple3_ arg_2) {
    int32_t x0_1;
    int32_t x1_1;
    struct Int32Int32Tuple2_ x2_1;
    struct String call_5;
    struct String call_6;
    struct String call_7;
    x0_1 = arg_2.t0;
    x1_1 = arg_2.t1;
    x2_1 = arg_2.t2;
    call_5 = string_of_int64(x0_1);
    call_6 = string_of_int64(x1_1);
    call_7 = MiloneDerive_TupleString_tuple2String(x2_1);
    return string_add(string_add(string_add(string_add(string_add(string_add((struct String){.ptr = "(", .len = 1}, call_5), (struct String){.ptr = ", ", .len = 2}), call_6), (struct String){.ptr = ", ", .len = 2}), call_7), (struct String){.ptr = ")", .len = 1});
}

int main(int argc, char **argv) {
    milone_start(argc, argv);
    struct Int32Int32Int32Tuple3_ Int32Int32Int32Tuple3_;
    struct String call_8;
    struct Int32Int32Int32Int32Tuple2Tuple3_ Int32Int32Int32Int32Tuple2Tuple3_;
    struct Int32Int32Tuple2_ Int32Int32Tuple2_;
    struct String call_9;
    if ((string_compare((struct String){.ptr = "()", .len = 2}, (struct String){.ptr = "()", .len = 2}) != 0)) milone_assert_error("tuple_string/tuple_string.milone", 3, 2);
    Int32Int32Int32Tuple3_ = (struct Int32Int32Int32Tuple3_){.t0 = 1, .t1 = 2, .t2 = 3};
    call_8 = MiloneDerive_TupleString_tuple3String(Int32Int32Int32Tuple3_);
    if ((string_compare(call_8, (struct String){.ptr = "(1, 2, 3)", .len = 9}) != 0)) milone_assert_error("tuple_string/tuple_string.milone", 4, 2);
    Int32Int32Tuple2_ = (struct Int32Int32Tuple2_){.t0 = 3, .t1 = 4};
    Int32Int32Int32Int32Tuple2Tuple3_ = (struct Int32Int32Int32Int32Tuple2Tuple3_){.t0 = 1, .t1 = 2, .t2 = Int32Int32Tuple2_};
    call_9 = MiloneDerive_TupleString_tuple3String_1(Int32Int32Int32Int32Tuple2Tuple3_);
    if ((string_compare(call_9, (struct String){.ptr = "(1, 2, (3, 4))", .len = 14}) != 0)) milone_assert_error("tuple_string/tuple_string.milone", 5, 2);
    return 0;
}
