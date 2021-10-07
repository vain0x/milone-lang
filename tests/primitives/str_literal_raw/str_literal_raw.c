#include "milone.h"

void str_literal_raw_Program_testEol(void);

void str_literal_raw_Program_testNoEscape(void);

int milone_main(void);

void str_literal_raw_Program_testEol(void) {
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
    milone_assert(if_, 7, 2);
    return;
}

void str_literal_raw_Program_testNoEscape(void) {
    milone_assert((str_compare((struct String){.str = " \\\"\" ", .len = 5}, (struct String){.str = " \\\"\" ", .len = 5}) == 0), 9, 22);
    return;
}

int milone_main(void) {
    str_literal_raw_Program_testEol();
    str_literal_raw_Program_testNoEscape();
    return 0;
}
