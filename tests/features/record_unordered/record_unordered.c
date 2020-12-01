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
    struct Person_ _john_ = Person_;
    struct Person_ Person_1;
    Person_1.Name = (struct String){.str = "Jane Doe", .len = 8};
    Person_1.Age = 18;
    struct Person_ _jane_ = Person_1;
    return 0;
}
