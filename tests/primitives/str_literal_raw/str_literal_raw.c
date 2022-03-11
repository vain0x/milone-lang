#include <milone.h>

void str_literal_raw_str_literal_raw_testEol(void);

void str_literal_raw_str_literal_raw_testNoEscape(void);

int main(int argc, char** argv);

void str_literal_raw_str_literal_raw_testEol(void) {
    struct String eol_;
    bool if_;
    eol_ = (struct String){.str = "\n", .len = 1};
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
    milone_assert(if_, (struct String){.str = "str_literal_raw/str_literal_raw.milone", .len = 38}, 7, 2);
    return;
}

void str_literal_raw_str_literal_raw_testNoEscape(void) {
    milone_assert((str_compare((struct String){.str = " \\\"\" ", .len = 5}, (struct String){.str = " \\\"\" ", .len = 5}) == 0), (struct String){.str = "str_literal_raw/str_literal_raw.milone", .len = 38}, 9, 22);
    return;
}

int main(int argc, char** argv) {
    milone_start(argc, argv);
    str_literal_raw_str_literal_raw_testEol();
    str_literal_raw_str_literal_raw_testNoEscape();
    return 0;
}
