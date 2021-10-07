#include "milone.h"

char const* str_as_ptr(struct String );

int milone_main(void);

int milone_main(void) {
    void const* box_ = milone_mem_alloc(1, sizeof(struct String));
    (*(((struct String*)box_))) = (struct String){.str = "hey", .len = 3};
    struct String const* p_ = ((struct String const*)box_);
    struct String read_ = (*(p_));
    milone_assert((str_compare(read_, (struct String){.str = "hey", .len = 3}) == 0), 6, 2);
    char const* str_as_ptr_result = str_as_ptr((struct String){.str = "Hello!", .len = 6});
    char const* s_ = str_as_ptr_result;
    char read_1 = s_[4];
    milone_assert((read_1 == 'o'), 9, 2);
    return 0;
}
