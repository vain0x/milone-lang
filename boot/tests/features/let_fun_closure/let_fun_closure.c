#include "milone.h"

struct IntTuple1;

int sub_(struct IntTuple1 arg_, int x_);

int main();

struct IntTuple1 {
    int t0;
};

int sub_(struct IntTuple1 arg_, int x_) {
    int y_ = arg_.t0;
    return (x_ - y_);
}

int main() {
    int y_ = 3;
    struct IntTuple1 tuple_;
    tuple_.t0 = y_;
    int call_ = sub_(tuple_, 8);
    return (call_ - 5);
}
