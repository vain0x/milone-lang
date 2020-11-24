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
    void* box_ = (void*)milone_mem_alloc(1, sizeof(struct Point_));
    (*(((struct Point_*)box_))) = Point_;
    void* point_ = box_;
    milone_assert(((*(((struct Point_*)point_))).X == 40), 7, 2);
    milone_assert(((*(((struct Point_*)point_))).Y == 2), 8, 2);
    return 0;
}
