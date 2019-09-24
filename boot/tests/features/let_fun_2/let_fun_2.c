#include "milone.h"

int add_(int x_, int y_);

int main();

int add_(int x_, int y_) {
    return (x_ + y_);
}

int main() {
    int call_ = add_(3, 5);
    return (call_ - 8);
}
