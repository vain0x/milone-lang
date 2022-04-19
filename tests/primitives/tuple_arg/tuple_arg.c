#include <stdio.h>
#include <stdlib.h>
#include <milone.h>

struct Int32Int32Tuple2_;

int32_t tuple_arg_tuple_arg_main_sub(struct Int32Int32Tuple2_ arg_);

int main(int argc, char** argv);

struct Int32Int32Tuple2_ {
    int32_t t0;
    int32_t t1;
};

int32_t tuple_arg_tuple_arg_main_sub(struct Int32Int32Tuple2_ arg_) {
    int32_t x_;
    int32_t y_;
    x_ = arg_.t0;
    y_ = arg_.t1;
    return (x_ - y_);
}

int main(int argc, char** argv) {
    milone_start(argc, argv);
    struct Int32Int32Tuple2_ Int32Int32Tuple2_;
    int32_t call_;
    Int32Int32Tuple2_ = (struct Int32Int32Tuple2_){.t0 = 8, .t1 = 3};
    call_ = tuple_arg_tuple_arg_main_sub(Int32Int32Tuple2_);
    return (call_ - 5);
}
