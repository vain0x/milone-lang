#include <stdio.h>
#include <stdlib.h>
#include <milone.h>

struct Point_;

int main(int argc, char **argv);

struct Point_ {
    int32_t t0;
    int32_t t1;
};

int main(int argc, char **argv) {
    milone_start(argc, argv);
    struct Point_ point_;
    struct Point_ Point_;
    Point_ = (struct Point_){.t0 = 40, .t1 = 2};
    point_ = Point_;
    if ((point_.t0 != 40)) milone_assert_error("record/record.milone", 9, 2);
    if ((point_.t1 != 2)) milone_assert_error("record/record.milone", 10, 2);
    return 0;
}
