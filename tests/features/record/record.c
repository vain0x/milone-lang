#include "milone.h"

struct Point_;

int milone_main(void);

struct Point_ {
    int t0;
    int t1;
};

int milone_main(void) {
    struct Point_ Point_ = (struct Point_){.t0 = 40, .t1 = 2};
    struct Point_ point_ = Point_;
    milone_assert((point_.t0 == 40), 9, 2);
    milone_assert((point_.t1 == 2), 10, 2);
    return 0;
}
