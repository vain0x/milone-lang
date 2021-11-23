#include <milone.h>

int main(int argc, char** argv);

int main(int argc, char** argv) {
    milone_start(argc, argv);
    struct String hello_ = (struct String){.str = "hello", .len = 5};
    struct String world_ = (struct String){.str = "world", .len = 5};
    milone_assert((hello_.len == 5), (struct String){.str = "str_length/str_length.milone", .len = 28}, 8, 2);
    struct String message_ = str_add(hello_, world_);
    milone_assert((message_.len == 10), (struct String){.str = "str_length/str_length.milone", .len = 28}, 11, 2);
    milone_assert((hello_.len == 5), (struct String){.str = "str_length/str_length.milone", .len = 28}, 13, 2);
    milone_assert((5 == 5), (struct String){.str = "str_length/str_length.milone", .len = 28}, 15, 2);
    milone_assert((3 == 3), (struct String){.str = "str_length/str_length.milone", .len = 28}, 18, 2);
    return 0;
}
