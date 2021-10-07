#include "milone.h"

struct Person_;

int milone_main(void);

struct Person_ {
    struct String t0;
    int t1;
};

int milone_main(void) {
    struct Person_ Person_ = (struct Person_){.t0 = (struct String){.str = "John Doe", .len = 8}, .t1 = 16};
    struct Person_ _john = Person_;
    struct Person_ Person_1 = (struct Person_){.t0 = (struct String){.str = "Jane Doe", .len = 8}, .t1 = 18};
    struct Person_ _jane = Person_1;
    return 0;
}
