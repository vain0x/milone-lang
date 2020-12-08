#include "milone.h"

int f_(int x_);

int main();

int f_(int x_) {
    return (x_ - 2);
}

int main() {
    int m_ = -2;
    milone_assert(((m_ + 2) == 0), 2, 2);
    int u_ = 2;
    int v_ = (-(u_));
    milone_assert(((v_ + 2) == 0), 6, 2);
    int call_ = f_(4);
    int y_ = (-(call_));
    milone_assert(((y_ + 2) == 0), 10, 2);
    return 0;
}
