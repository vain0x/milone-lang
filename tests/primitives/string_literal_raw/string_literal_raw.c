#include <stdio.h>
#include <stdlib.h>
#include <milone.h>

void string_literal_raw_string_literal_raw_testEol(void);

void string_literal_raw_string_literal_raw_testNoEscape(void);

int main(int argc, char **argv);

void string_literal_raw_string_literal_raw_testEol(void) {
    struct String eol_;
    bool if_;
    eol_ = (struct String){.ptr = "\n", .len = 1};
    if ((string_compare(eol_, (struct String){.ptr = "\n", .len = 1}) == 0)) {
        goto then_2;
    } else {
        goto else_3;
    }
then_2:;
    if_ = true;
    goto if_next_1;
else_3:;
    if_ = (string_compare(eol_, (struct String){.ptr = "\r\n", .len = 2}) == 0);
    goto if_next_1;
if_next_1:;
    if ((!(if_))) milone_assert_error("string_literal_raw/string_literal_raw.milone", 7, 2);
    return;
}

void string_literal_raw_string_literal_raw_testNoEscape(void) {
    if ((string_compare((struct String){.ptr = " \\\"\" ", .len = 5}, (struct String){.ptr = " \\\"\" ", .len = 5}) != 0)) milone_assert_error("string_literal_raw/string_literal_raw.milone", 9, 22);
    return;
}

int main(int argc, char **argv) {
    milone_start(argc, argv);
    string_literal_raw_string_literal_raw_testEol();
    string_literal_raw_string_literal_raw_testNoEscape();
    return 0;
}
