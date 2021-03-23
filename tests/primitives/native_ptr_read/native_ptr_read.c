#include "milone.h"

char const* str_as_ptr(struct String);

int milone_main();

int milone_main() {
    void const* box_ = milone_mem_alloc(1, sizeof(int));
    (*(((int*)box_))) = 42;
    int const* p_ = ((int const*)box_);
    int read_ = (*(p_));
    milone_assert((read_ == 42), 6, 2);
    char const* str_as_ptr_result = str_as_ptr((struct String){.str = "Hello!", .len = 6});
    char const* s_ = str_as_ptr_result;
    char read_1 = s_[4];
    milone_assert((read_1 == 'o'), 9, 2);
    return 0;
}
