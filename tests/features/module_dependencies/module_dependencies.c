#include "milone.h"

int root_(char arg_);

int third_(char arg_1);

int second_(char arg_2);

int milone_main();

int root_(char arg_) {
    return 0;
}

int third_(char arg_1) {
    int call_ = root_(0);
    return call_;
}

int second_(char arg_2) {
    int call_1 = root_(0);
    return call_1;
}

int milone_main() {
    int call_2 = second_(0);
    int call_3 = third_(0);
    return (call_2 + call_3);
}
