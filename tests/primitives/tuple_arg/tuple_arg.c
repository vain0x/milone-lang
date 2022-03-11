#include <milone.h>

struct IntIntTuple2_;

int tuple_arg_tuple_arg_main_sub(struct IntIntTuple2_ arg_);

int main(int argc, char** argv);

struct IntIntTuple2_ {
    int t0;
    int t1;
};

int tuple_arg_tuple_arg_main_sub(struct IntIntTuple2_ arg_) {
    int x_;
    int y_;
    x_ = arg_.t0;
    y_ = arg_.t1;
    return (x_ - y_);
}

int main(int argc, char** argv) {
    milone_start(argc, argv);
    struct IntIntTuple2_ IntIntTuple2_;
    int call_;
    IntIntTuple2_ = (struct IntIntTuple2_){.t0 = 8, .t1 = 3};
    call_ = tuple_arg_tuple_arg_main_sub(IntIntTuple2_);
    return (call_ - 5);
}
