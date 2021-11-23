#include <milone.h>

char str_operators_str_operators_indexOperatorTest_IntStringCharFun2_at(int i_, struct String s_);

void str_operators_Program_addTest(void);

void str_operators_Program_compareTest(void);

void str_operators_Program_indexOperatorTest(void);

void str_operators_Program_subscriptOperatorTest(void);

int main(int argc, char** argv);

char str_operators_str_operators_indexOperatorTest_IntStringCharFun2_at(int i_, struct String s_) {
    return s_.str[i_];
}

void str_operators_Program_addTest(void) {
    struct String hello_ = (struct String){.str = "Hello", .len = 5};
    struct String world_ = (struct String){.str = ", world!", .len = 8};
    milone_assert((str_compare(str_add(hello_, world_), (struct String){.str = "Hello, world!", .len = 13}) == 0), (struct String){.str = "str_operators/str_operators.milone", .len = 34}, 5, 2);
    milone_assert((str_add((struct String){.str = "a", .len = 1}, (struct String){.str = "\0b", .len = 2}).str[2] == 'b'), (struct String){.str = "str_operators/str_operators.milone", .len = 34}, 8, 2);
    return;
}

void str_operators_Program_compareTest(void) {
    milone_assert((str_compare((struct String){.str = "", .len = 0}, (struct String){.str = "", .len = 0}) == 0), (struct String){.str = "str_operators/str_operators.milone", .len = 34}, 11, 2);
    milone_assert((str_compare((struct String){.str = "o", .len = 1}, (struct String){.str = "o", .len = 1}) == 0), (struct String){.str = "str_operators/str_operators.milone", .len = 34}, 12, 2);
    milone_assert((str_compare((struct String){.str = "alpha", .len = 5}, (struct String){.str = "alpha", .len = 5}) == 0), (struct String){.str = "str_operators/str_operators.milone", .len = 34}, 13, 2);
    milone_assert((str_compare((struct String){.str = "a", .len = 1}, (struct String){.str = "b", .len = 1}) < 0), (struct String){.str = "str_operators/str_operators.milone", .len = 34}, 15, 2);
    milone_assert((str_compare((struct String){.str = "alpha", .len = 5}, (struct String){.str = "beta", .len = 4}) < 0), (struct String){.str = "str_operators/str_operators.milone", .len = 34}, 16, 2);
    milone_assert((str_compare((struct String){.str = "a", .len = 1}, (struct String){.str = "z", .len = 1}) < 0), (struct String){.str = "str_operators/str_operators.milone", .len = 34}, 18, 2);
    milone_assert((str_compare((struct String){.str = "alpha", .len = 5}, (struct String){.str = "beta", .len = 4}) < 0), (struct String){.str = "str_operators/str_operators.milone", .len = 34}, 20, 2);
    milone_assert((str_compare((struct String){.str = "alpha", .len = 5}, (struct String){.str = "alpha", .len = 5}) == 0), (struct String){.str = "str_operators/str_operators.milone", .len = 34}, 21, 2);
    milone_assert((0 < str_compare((struct String){.str = "beta", .len = 4}, (struct String){.str = "alpha", .len = 5})), (struct String){.str = "str_operators/str_operators.milone", .len = 34}, 22, 2);
    milone_assert((str_compare((struct String){.str = "\0x", .len = 2}, (struct String){.str = "\0y", .len = 2}) < 0), (struct String){.str = "str_operators/str_operators.milone", .len = 34}, 25, 2);
    return;
}

void str_operators_Program_indexOperatorTest(void) {
    struct String hello_1 = (struct String){.str = "hello", .len = 5};
    bool if_;
    if ((hello_1.str[0] == 'h')) {
        goto then_2;
    } else {
        goto else_3;
    }
then_2:;
    if_ = (hello_1.str[4] == 'o');
    goto if_next_1;
else_3:;
    if_ = false;
    goto if_next_1;
if_next_1:;
    milone_assert(if_, (struct String){.str = "str_operators/str_operators.milone", .len = 34}, 33, 2);
    char call_ = str_operators_str_operators_indexOperatorTest_IntStringCharFun2_at(0, hello_1);
    milone_assert((call_ == 'h'), (struct String){.str = "str_operators/str_operators.milone", .len = 34}, 38, 2);
    return;
}

void str_operators_Program_subscriptOperatorTest(void) {
    struct String str_ = (struct String){.str = "Hello, John!", .len = 12};
    struct String slice_ = str_get_slice(0, 4, str_);
    milone_assert((str_compare(slice_, (struct String){.str = "Hello", .len = 5}) == 0), (struct String){.str = "str_operators/str_operators.milone", .len = 34}, 42, 2);
    struct String slice_1 = str_get_slice(7, 10, str_);
    milone_assert((str_compare(slice_1, (struct String){.str = "John", .len = 4}) == 0), (struct String){.str = "str_operators/str_operators.milone", .len = 34}, 43, 2);
    struct String slice_2 = str_get_slice(11, 11, str_);
    milone_assert((str_compare(slice_2, (struct String){.str = "!", .len = 1}) == 0), (struct String){.str = "str_operators/str_operators.milone", .len = 34}, 44, 2);
    return;
}

int main(int argc, char** argv) {
    milone_start(argc, argv);
    str_operators_Program_addTest();
    str_operators_Program_compareTest();
    str_operators_Program_indexOperatorTest();
    str_operators_Program_subscriptOperatorTest();
    return 0;
}
