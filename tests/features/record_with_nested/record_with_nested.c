#include <stdio.h>
#include <stdlib.h>
#include <milone.h>

struct Date_;

struct Person_;

struct Person_ record_with_nested_record_with_nested_newPerson(void);

int main(int argc, char** argv);

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

struct Person_ record_with_nested_record_with_nested_newPerson(void) {
    struct Person_ Person_;
    struct Date_ Date_;
    Date_ = (struct Date_){.t0 = 2007, .t1 = 8, .t2 = 31};
    Person_ = (struct Person_){.t0 = (struct String){.ptr = "Jane Doe", .len = 8}, .t1 = 16, .t2 = Date_};
    return Person_;
}

int main(int argc, char** argv) {
    milone_start(argc, argv);
    struct Person_ john_;
    struct String name_;
    struct Person_ base_;
    struct Person_ call_;
    struct Person_ Person_1;
    call_ = record_with_nested_record_with_nested_newPerson();
    base_ = call_;
    Person_1 = (struct Person_){.t0 = (struct String){.ptr = "John Doe", .len = 8}, .t1 = base_.t1, .t2 = base_.t2};
    john_ = Person_1;
    name_ = john_.t0;
    milone_assert((name_.len == 8), (struct String){.ptr = "record_with_nested/record_with_nested.milone", .len = 44}, 20, 2);
    return 0;
}
