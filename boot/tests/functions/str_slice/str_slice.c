#include "milone.h"

int main();

int main() {
    struct String str_ = (struct String){.str = "Hello, John!", .len = 12};
    struct String call_ = str_get_slice(0, 4, str_);
    milone_assert((str_cmp(call_, (struct String){.str = "Hello", .len = 5}) == 0));
    int call_1 = 0;
    struct String call_2 = str_get_slice(7, 10, str_);
    milone_assert((str_cmp(call_2, (struct String){.str = "John", .len = 4}) == 0));
    int call_3 = 0;
    struct String call_4 = str_get_slice(11, 11, str_);
    milone_assert((str_cmp(call_4, (struct String){.str = "!", .len = 1}) == 0));
    int call_5 = 0;
    return 0;
}
