#include <milone.h>

struct Person_;

int main(int argc, char** argv);

struct Person_ {
    struct String t0;
    int t1;
};

int main(int argc, char** argv) {
    milone_start(argc, argv);
    struct Person_ john_;
    struct Person_ jane_;
    struct Person_ john_1;
    struct Person_ base_;
    struct Person_ base_1;
    struct Person_ Person_;
    struct Person_ Person_1;
    struct Person_ Person_2;
    Person_ = (struct Person_){.t0 = (struct String){.str = "John Doe", .len = 8}, .t1 = 16};
    john_ = Person_;
    base_ = john_;
    Person_1 = (struct Person_){.t0 = (struct String){.str = "Jane Doe", .len = 8}, .t1 = base_.t1};
    jane_ = Person_1;
    milone_assert((str_compare(john_.t0, (struct String){.str = "John Doe", .len = 8}) == 0), (struct String){.str = "record_with/record_with.milone", .len = 30}, 10, 2);
    milone_assert((str_compare(jane_.t0, (struct String){.str = "Jane Doe", .len = 8}) == 0), (struct String){.str = "record_with/record_with.milone", .len = 30}, 11, 2);
    milone_assert((jane_.t1 == 16), (struct String){.str = "record_with/record_with.milone", .len = 30}, 12, 2);
    base_1 = john_;
    Person_2 = (struct Person_){.t0 = base_1.t0, .t1 = (john_.t1 + 1)};
    john_1 = Person_2;
    milone_assert((john_1.t1 == 17), (struct String){.str = "record_with/record_with.milone", .len = 30}, 15, 2);
    return 0;
}
