#include "milone.h"

struct Person_;

int main();

struct Person_ {
    struct String Name;
    int Age;
};

int main() {
    struct Person_ Person_;
    Person_.Name = (struct String){.str = "John Doe", .len = 8};
    Person_.Age = 16;
    struct Person_ john_ = Person_;
    struct Person_ base_ = john_;
    struct Person_ Person_1;
    Person_1.Name = (struct String){.str = "Jane Doe", .len = 8};
    Person_1.Age = base_.Age;
    struct Person_ jane_ = Person_1;
    milone_assert((str_cmp(john_.Name, (struct String){.str = "John Doe", .len = 8}) == 0), 8, 2);
    milone_assert((str_cmp(jane_.Name, (struct String){.str = "Jane Doe", .len = 8}) == 0), 9, 2);
    milone_assert((jane_.Age == 16), 10, 2);
    struct Person_ base_1 = john_;
    struct Person_ Person_2;
    Person_2.Name = base_1.Name;
    Person_2.Age = (john_.Age + 1);
    struct Person_ john_1 = Person_2;
    milone_assert((john_1.Age == 17), 13, 2);
    return 0;
}
