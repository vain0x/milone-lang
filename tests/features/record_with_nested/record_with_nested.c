#include "milone.h"

struct Date_;

struct Person_;

struct Person_ newPerson_(int arg_);

int main();

struct Date_ {
    int Year;
    int Month;
    int Date;
};

struct Person_ {
    struct String Name;
    int Age;
    struct Date_ Birthday;
};

struct Person_ newPerson_(int arg_) {
    struct Date_ Date_;
    Date_.Year = 2007;
    Date_.Month = 8;
    Date_.Date = 31;
    struct Person_ Person_;
    Person_.Name = (struct String){.str = "Jane Doe", .len = 8};
    Person_.Age = 16;
    Person_.Birthday = Date_;
    return Person_;
}

int main() {
    struct Person_ call_ = newPerson_(0);
    struct Person_ base_ = call_;
    struct Person_ Person_1;
    Person_1.Name = (struct String){.str = "John Doe", .len = 8};
    Person_1.Age = base_.Age;
    Person_1.Birthday = base_.Birthday;
    struct Person_ john_ = Person_1;
    struct String name_ = john_.Name;
    milone_assert((name_.len == 8), 18, 2);
    return 0;
}
