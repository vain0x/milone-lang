#include <stdio.h>
#include <stdlib.h>
#include <milone.h>

int main(int argc, char** argv);

int main(int argc, char** argv) {
    milone_start(argc, argv);
    struct String hello_;
    struct String world_;
    struct String message_;
    hello_ = (struct String){.ptr = "hello", .len = 5};
    world_ = (struct String){.ptr = "world", .len = 5};
    milone_assert((hello_.len == 5), (struct String){.ptr = "string_length/string_length.milone", .len = 34}, 8, 2);
    message_ = string_add(hello_, world_);
    milone_assert((message_.len == 10), (struct String){.ptr = "string_length/string_length.milone", .len = 34}, 11, 2);
    milone_assert((hello_.len == 5), (struct String){.ptr = "string_length/string_length.milone", .len = 34}, 13, 2);
    milone_assert((5 == 5), (struct String){.ptr = "string_length/string_length.milone", .len = 34}, 15, 2);
    milone_assert((3 == 3), (struct String){.ptr = "string_length/string_length.milone", .len = 34}, 18, 2);
    return 0;
}
