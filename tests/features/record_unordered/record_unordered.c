#include <stdio.h>
#include <stdlib.h>
#include <milone.h>

struct Person_;

int main(int argc, char** argv);

struct Person_ {
    struct String t0;
    int32_t t1;
};

int main(int argc, char** argv) {
    milone_start(argc, argv);
    struct Person_ _john;
    struct Person_ _jane;
    struct Person_ Person_;
    struct Person_ Person_1;
    Person_ = (struct Person_){.t0 = (struct String){.ptr = "John Doe", .len = 8}, .t1 = 16};
    _john = Person_;
    Person_1 = (struct Person_){.t0 = (struct String){.ptr = "Jane Doe", .len = 8}, .t1 = 18};
    _jane = Person_1;
    return 0;
}
