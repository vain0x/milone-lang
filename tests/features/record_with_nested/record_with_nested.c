#include <milone.h>

struct Date_;

struct Person_;

struct Person_ record_with_nested_Program_newPerson(void);

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

struct Person_ record_with_nested_Program_newPerson(void) {
    struct Date_ Date_ = (struct Date_){.t0 = 2007, .t1 = 8, .t2 = 31};
    struct Person_ Person_ = (struct Person_){.t0 = (struct String){.str = "Jane Doe", .len = 8}, .t1 = 16, .t2 = Date_};
    return Person_;
}

int main(int argc, char** argv) {
    milone_start(argc, argv);
    struct Person_ call_ = record_with_nested_Program_newPerson();
    struct Person_ base_ = call_;
    struct Person_ Person_1 = (struct Person_){.t0 = (struct String){.str = "John Doe", .len = 8}, .t1 = base_.t1, .t2 = base_.t2};
    struct Person_ john_ = Person_1;
    struct String name_ = john_.t0;
    milone_assert((name_.len == 8), (struct String){.str = "record_with_nested/record_with_nested.milone", .len = 44}, 20, 2);
    return 0;
}
