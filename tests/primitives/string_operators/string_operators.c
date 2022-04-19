#include <stdio.h>
#include <stdlib.h>
#include <milone.h>

void string_operators_string_operators_addTest(void);

void string_operators_string_operators_compareTest(void);

char string_operators_string_operators_indexOperatorTest_at(int i_, struct String s_);

void string_operators_string_operators_indexOperatorTest(void);

void string_operators_string_operators_subscriptOperatorTest(void);

int main(int argc, char** argv);

void string_operators_string_operators_addTest(void) {
    struct String hello_;
    struct String world_;
    hello_ = (struct String){.ptr = "Hello", .len = 5};
    world_ = (struct String){.ptr = ", world!", .len = 8};
    milone_assert((string_compare(string_add(hello_, world_), (struct String){.ptr = "Hello, world!", .len = 13}) == 0), (struct String){.ptr = "string_operators/string_operators.milone", .len = 40}, 5, 2);
    milone_assert((string_add((struct String){.ptr = "a", .len = 1}, (struct String){.ptr = "\0b", .len = 2}).ptr[2] == 'b'), (struct String){.ptr = "string_operators/string_operators.milone", .len = 40}, 8, 2);
    return;
}

void string_operators_string_operators_compareTest(void) {
    milone_assert((string_compare((struct String){.ptr = "", .len = 0}, (struct String){.ptr = "", .len = 0}) == 0), (struct String){.ptr = "string_operators/string_operators.milone", .len = 40}, 11, 2);
    milone_assert((string_compare((struct String){.ptr = "o", .len = 1}, (struct String){.ptr = "o", .len = 1}) == 0), (struct String){.ptr = "string_operators/string_operators.milone", .len = 40}, 12, 2);
    milone_assert((string_compare((struct String){.ptr = "alpha", .len = 5}, (struct String){.ptr = "alpha", .len = 5}) == 0), (struct String){.ptr = "string_operators/string_operators.milone", .len = 40}, 13, 2);
    milone_assert((string_compare((struct String){.ptr = "a", .len = 1}, (struct String){.ptr = "b", .len = 1}) < 0), (struct String){.ptr = "string_operators/string_operators.milone", .len = 40}, 15, 2);
    milone_assert((string_compare((struct String){.ptr = "alpha", .len = 5}, (struct String){.ptr = "beta", .len = 4}) < 0), (struct String){.ptr = "string_operators/string_operators.milone", .len = 40}, 16, 2);
    milone_assert((string_compare((struct String){.ptr = "a", .len = 1}, (struct String){.ptr = "z", .len = 1}) < 0), (struct String){.ptr = "string_operators/string_operators.milone", .len = 40}, 18, 2);
    milone_assert((string_compare((struct String){.ptr = "alpha", .len = 5}, (struct String){.ptr = "beta", .len = 4}) < 0), (struct String){.ptr = "string_operators/string_operators.milone", .len = 40}, 20, 2);
    milone_assert((string_compare((struct String){.ptr = "alpha", .len = 5}, (struct String){.ptr = "alpha", .len = 5}) == 0), (struct String){.ptr = "string_operators/string_operators.milone", .len = 40}, 21, 2);
    milone_assert((0 < string_compare((struct String){.ptr = "beta", .len = 4}, (struct String){.ptr = "alpha", .len = 5})), (struct String){.ptr = "string_operators/string_operators.milone", .len = 40}, 22, 2);
    milone_assert((string_compare((struct String){.ptr = "\0x", .len = 2}, (struct String){.ptr = "\0y", .len = 2}) < 0), (struct String){.ptr = "string_operators/string_operators.milone", .len = 40}, 25, 2);
    return;
}

char string_operators_string_operators_indexOperatorTest_at(int i_, struct String s_) {
    return s_.ptr[i_];
}

void string_operators_string_operators_indexOperatorTest(void) {
    struct String hello_1;
    bool if_;
    char call_;
    hello_1 = (struct String){.ptr = "hello", .len = 5};
    if ((hello_1.ptr[0] == 'h')) {
        goto then_2;
    } else {
        goto else_3;
    }
then_2:;
    if_ = (hello_1.ptr[4] == 'o');
    goto if_next_1;
else_3:;
    if_ = false;
    goto if_next_1;
if_next_1:;
    milone_assert(if_, (struct String){.ptr = "string_operators/string_operators.milone", .len = 40}, 33, 2);
    call_ = string_operators_string_operators_indexOperatorTest_at(0, hello_1);
    milone_assert((call_ == 'h'), (struct String){.ptr = "string_operators/string_operators.milone", .len = 40}, 38, 2);
    return;
}

void string_operators_string_operators_subscriptOperatorTest(void) {
    struct String text_;
    struct String slice_;
    struct String slice_1;
    struct String slice_2;
    text_ = (struct String){.ptr = "Hello, John!", .len = 12};
    slice_ = string_get_slice(0, 4, text_);
    milone_assert((string_compare(slice_, (struct String){.ptr = "Hello", .len = 5}) == 0), (struct String){.ptr = "string_operators/string_operators.milone", .len = 40}, 42, 2);
    slice_1 = string_get_slice(7, 10, text_);
    milone_assert((string_compare(slice_1, (struct String){.ptr = "John", .len = 4}) == 0), (struct String){.ptr = "string_operators/string_operators.milone", .len = 40}, 43, 2);
    slice_2 = string_get_slice(11, 11, text_);
    milone_assert((string_compare(slice_2, (struct String){.ptr = "!", .len = 1}) == 0), (struct String){.ptr = "string_operators/string_operators.milone", .len = 40}, 44, 2);
    return;
}

int main(int argc, char** argv) {
    milone_start(argc, argv);
    string_operators_string_operators_addTest();
    string_operators_string_operators_compareTest();
    string_operators_string_operators_indexOperatorTest();
    string_operators_string_operators_subscriptOperatorTest();
    return 0;
}
