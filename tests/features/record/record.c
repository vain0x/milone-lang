#include "milone.h"

struct Point_;

int main();

struct Point_ {
    int X;
    int Y;
};

int main() {
    struct Point_ Point_;
    Point_.X = 40;
    Point_.Y = 2;
    struct Point_ point_ = Point_;
    milone_assert((point_.X == 40), 9, 2);
    milone_assert((point_.Y == 2), 10, 2);
    return 0;
}
