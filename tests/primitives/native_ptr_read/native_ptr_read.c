#include <milone.h>

char const* str_as_ptr(struct String );

int main(int argc, char** argv);

int main(int argc, char** argv) {
    milone_start(argc, argv);
    void const* box_ = milone_mem_alloc(1, sizeof(struct String));
    (*(((struct String*)box_))) = (struct String){.str = "hey", .len = 3};
    struct String const* p_ = ((struct String const*)box_);
    struct String read_ = (*(p_));
    milone_assert((str_compare(read_, (struct String){.str = "hey", .len = 3}) == 0), (struct String){.str = "native_ptr_read/native_ptr_read.milone", .len = 38}, 6, 2);
    char const* str_as_ptr_result = str_as_ptr((struct String){.str = "Hello!", .len = 6});
    char const* s_ = str_as_ptr_result;
    char read_1 = s_[4];
    milone_assert((read_1 == 'o'), (struct String){.str = "native_ptr_read/native_ptr_read.milone", .len = 38}, 9, 2);
    return 0;
}
