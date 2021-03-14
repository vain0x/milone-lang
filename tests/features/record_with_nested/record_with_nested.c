#include "milone.h"

struct Date_;

struct Person_;

struct Person_ newPerson_(char arg_);

int milone_main();

struct Date_ {
    int t0;
    int t1;
    int t2;
};

struct Person_ {
    struct String t0;
    int t1;
    struct Date_ t2;
};

struct Person_ newPerson_(char arg_) {
    struct Date_ Date_ = (struct Date_){.t0 = 2007, .t1 = 8, .t2 = 31};
    struct Person_ Person_ = (struct Person_){.t0 = (struct String){.str = "Jane Doe", .len = 8}, .t1 = 16, .t2 = Date_};
    return Person_;
}

int milone_main() {
    struct Person_ call_ = newPerson_(0);
    struct Person_ base_ = call_;
    struct Person_ Person_1 = (struct Person_){.t0 = (struct String){.str = "John Doe", .len = 8}, .t1 = base_.t1, .t2 = base_.t2};
    struct Person_ john_ = Person_1;
    struct String name_ = john_.t0;
    milone_assert((name_.len == 8), 20, 2);
    return 0;
}
