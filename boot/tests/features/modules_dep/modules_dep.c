#include "milone.h"

int root_(int arg_);

int second_(int arg_1);

int third_(int arg_2);

int main();

int root_(int arg_) {
    return 0;
}

int second_(int arg_1) {
    int call_ = root_(0);
    return call_;
}

int third_(int arg_2) {
    int call_1 = root_(0);
    return call_1;
}

int main() {
    int call_2 = second_(0);
    int call_3 = third_(0);
    return (call_2 + call_3);
}
