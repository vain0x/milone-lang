#include "milone.h"

struct Person_;

int milone_main();

struct Person_ {
    struct String t0;
    int t1;
};

int milone_main() {
    struct Person_ Person_ = (struct Person_){.t0 = (struct String){.str = "John Doe", .len = 8}, .t1 = 16};
    struct Person_ john_ = Person_;
    struct Person_ base_ = john_;
    struct Person_ Person_1 = (struct Person_){.t0 = (struct String){.str = "Jane Doe", .len = 8}, .t1 = base_.t1};
    struct Person_ jane_ = Person_1;
    milone_assert((str_cmp(john_.t0, (struct String){.str = "John Doe", .len = 8}) == 0), 10, 2);
    milone_assert((str_cmp(jane_.t0, (struct String){.str = "Jane Doe", .len = 8}) == 0), 11, 2);
    milone_assert((jane_.t1 == 16), 12, 2);
    struct Person_ base_1 = john_;
    struct Person_ Person_2 = (struct Person_){.t0 = base_1.t0, .t1 = (john_.t1 + 1)};
    struct Person_ john_1 = Person_2;
    milone_assert((john_1.t1 == 17), 15, 2);
    return 0;
}
