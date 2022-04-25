#include <stdio.h>
#include <stdlib.h>
#include <milone.h>

int main(int argc, char **argv);

int main(int argc, char **argv) {
    milone_start(argc, argv);
    struct String hello_;
    struct String world_;
    struct String message_;
    hello_ = (struct String){.ptr = "hello", .len = 5};
    world_ = (struct String){.ptr = "world", .len = 5};
    if ((((int32_t)hello_.len) != 5)) milone_assert_error("string_length/string_length.milone", 8, 2);
    message_ = string_add(hello_, world_);
    if ((((int32_t)message_.len) != 10)) milone_assert_error("string_length/string_length.milone", 11, 2);
    if ((((int32_t)hello_.len) != 5)) milone_assert_error("string_length/string_length.milone", 13, 2);
    if ((((int32_t)5) != 5)) milone_assert_error("string_length/string_length.milone", 15, 2);
    if ((((int32_t)3) != 3)) milone_assert_error("string_length/string_length.milone", 18, 2);
    return 0;
}
