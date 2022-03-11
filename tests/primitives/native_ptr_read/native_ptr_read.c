#include <milone.h>

char const* str_as_ptr(struct String );

int main(int argc, char** argv);

int main(int argc, char** argv) {
    milone_start(argc, argv);
    struct String const* p_;
    char const* s_;
    void const* box_;
    struct String read_;
    char const* str_as_ptr_result;
    char read_1;
    box_ = ((void const*)milone_mem_alloc(1, sizeof(struct String)));
    (*(((struct String*)box_))) = (struct String){.str = "hey", .len = 3};
    p_ = ((struct String const*)box_);
    read_ = (*(p_));
    milone_assert((str_compare(read_, (struct String){.str = "hey", .len = 3}) == 0), (struct String){.str = "native_ptr_read/native_ptr_read.milone", .len = 38}, 6, 2);
    str_as_ptr_result = str_as_ptr((struct String){.str = "Hello!", .len = 6});
    s_ = str_as_ptr_result;
    read_1 = s_[4];
    milone_assert((read_1 == 'o'), (struct String){.str = "native_ptr_read/native_ptr_read.milone", .len = 38}, 9, 2);
    return 0;
}
