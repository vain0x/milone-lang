#include "milone.h"

int main();

int main() {
    struct String str_ = (struct String){.str = "Hello, John!", .len = 12};
    struct String slice_ = str_get_slice(0, 4, str_);
    milone_assert((str_cmp(slice_, (struct String){.str = "Hello", .len = 5}) == 0), 2, 2);
    struct String slice_1 = str_get_slice(7, 10, str_);
    milone_assert((str_cmp(slice_1, (struct String){.str = "John", .len = 4}) == 0), 3, 2);
    struct String slice_2 = str_get_slice(11, 11, str_);
    milone_assert((str_cmp(slice_2, (struct String){.str = "!", .len = 1}) == 0), 4, 2);
    return 0;
}
