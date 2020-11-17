#include "milone.h"

int testBinarySafe_(int arg_);

int main();

int testBinarySafe_(int arg_) {
    milone_assert((str_cmp((struct String){.str = "\0x", .len = 2}, (struct String){.str = "\0y", .len = 2}) < 0), 1, 2);
    int call_ = 0;
    return 0;
}

int main() {
    int le_ = (str_cmp((struct String){.str = "a", .len = 1}, (struct String){.str = "b", .len = 1}) < 0);
    int eq_ = (str_cmp((struct String){.str = "o", .len = 1}, (struct String){.str = "o", .len = 1}) == 0);
    int if_;
    if ((!(le_))) goto else_1;
    if_ = eq_;
    goto end_if_2;
else_1:;
    if_ = 0;
end_if_2:;
    milone_assert(if_, 6, 2);
    int call_1 = 0;
    int call_2 = testBinarySafe_(0);
    return 0;
}
