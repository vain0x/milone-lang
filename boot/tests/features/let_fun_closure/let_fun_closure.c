#include "milone.h"

int sub_(int y_, int x_);

int main();

int sub_(int y_, int x_) {
    return (x_ - y_);
}

int main() {
    int y_ = 3;
    int call_ = sub_(y_, 8);
    return (call_ - 5);
}
