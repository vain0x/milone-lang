#include "milone.h"

char str_literal_raw_Program_testEol(char arg_);

char str_literal_raw_Program_testNoEscape(char arg_1);

int milone_main();

char str_literal_raw_Program_testEol(char arg_) {
    struct String eol_ = (struct String){.str = "\n", .len = 1};
    bool if_;
    if ((str_compare(eol_, (struct String){.str = "\n", .len = 1}) == 0)) {
        goto then_2;
    } else {
        goto else_3;
    }
then_2:;
    if_ = true;
    goto if_next_1;
else_3:;
    if_ = (str_compare(eol_, (struct String){.str = "\r\n", .len = 2}) == 0);
    goto if_next_1;
if_next_1:;
    milone_assert(if_, 6, 2);
    return 0;
}

char str_literal_raw_Program_testNoEscape(char arg_1) {
    milone_assert((str_compare((struct String){.str = " \\\"\" ", .len = 5}, (struct String){.str = " \\\"\" ", .len = 5}) == 0), 8, 22);
    return 0;
}

int milone_main() {
    char call_ = str_literal_raw_Program_testEol(0);
    char call_1 = str_literal_raw_Program_testNoEscape(0);
    return 0;
}
