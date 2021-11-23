#include <milone.h>

struct Point_;

int main(int argc, char** argv);

struct Point_ {
    int t0;
    int t1;
};

int main(int argc, char** argv) {
    milone_start(argc, argv);
    struct Point_ Point_ = (struct Point_){.t0 = 40, .t1 = 2};
    struct Point_ point_ = Point_;
    milone_assert((point_.t0 == 40), (struct String){.str = "record/record.milone", .len = 20}, 9, 2);
    milone_assert((point_.t1 == 2), (struct String){.str = "record/record.milone", .len = 20}, 10, 2);
    return 0;
}
