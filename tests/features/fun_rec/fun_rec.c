#include "milone.h"

void go_(struct String source_, int len_, int i_);

int milone_main(void);

void go_(struct String source_, int len_, int i_) {
tailrec_1:;
    char if_;
    if ((i_ < len_)) {
        goto then_3;
    } else {
        goto else_7;
    }
then_3:;
    char if_1;
    if ((source_.str[i_] == 'o')) {
        goto then_5;
    } else {
        goto else_6;
    }
then_5:;
    printf("%d\n", i_);
    if_1 = 0;
    goto if_next_4;
else_6:;
    if_1 = 0;
    goto if_next_4;
if_next_4:;
    struct String arg_ = source_;
    int arg_1 = len_;
    int arg_2 = (i_ + 1);
    source_ = arg_;
    len_ = arg_1;
    i_ = arg_2;
    goto tailrec_1;
else_7:;
    if_ = 0;
    goto if_next_2;
if_next_2:;
    return;
}

int milone_main(void) {
    struct String source_ = (struct String){.str = "hello world", .len = 11};
    int len_ = source_.len;
    go_(source_, len_, 0);
    return 0;
}
