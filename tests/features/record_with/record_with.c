#include <stdio.h>
#include <stdlib.h>
#include <milone.h>

struct Person_;

int main(int argc, char **argv);

struct Person_ {
    struct String t0;
    int32_t t1;
};

int main(int argc, char **argv) {
    milone_start(argc, argv);
    struct Person_ john_;
    struct Person_ jane_;
    struct Person_ john_1;
    struct Person_ Person_;
    struct Person_ Person_1;
    struct Person_ Person_2;
    Person_ = (struct Person_){.t0 = (struct String){.ptr = "John Doe", .len = 8}, .t1 = 16};
    john_ = Person_;
    Person_1 = (struct Person_){.t0 = (struct String){.ptr = "Jane Doe", .len = 8}, .t1 = john_.t1};
    jane_ = Person_1;
    if ((string_compare(john_.t0, (struct String){.ptr = "John Doe", .len = 8}) != 0)) milone_assert_error("record_with/record_with.milone", 10, 2);
    if ((string_compare(jane_.t0, (struct String){.ptr = "Jane Doe", .len = 8}) != 0)) milone_assert_error("record_with/record_with.milone", 11, 2);
    if ((jane_.t1 != 16)) milone_assert_error("record_with/record_with.milone", 12, 2);
    Person_2 = (struct Person_){.t0 = john_.t0, .t1 = (john_.t1 + 1)};
    john_1 = Person_2;
    if ((john_1.t1 != 17)) milone_assert_error("record_with/record_with.milone", 15, 2);
    return 0;
}
