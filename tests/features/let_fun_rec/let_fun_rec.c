#include "milone.h"

int go_(int len_, struct String source_, int i_);

int main();

int go_(int len_, struct String source_, int i_) {
tailrec_1:;
    int match_;
    if ((i_ >= len_)) goto next_3;
    int match_1;
    if ((source_.str[i_] != 'o')) goto next_6;
    printf("%d\n", i_);
    int call_ = 0;
    match_1 = 0;
    goto end_match_5;
next_6:;
    if ((source_.str[i_] == 'o')) goto next_7;
    match_1 = 0;
    goto end_match_5;
next_7:;
    exit(1);
end_match_5:;
    int arg_ = len_;
    struct String arg_1 = source_;
    int arg_2 = (i_ + 1);
    len_ = arg_;
    source_ = arg_1;
    i_ = arg_2;
    goto tailrec_1;
    match_ = 0;
    goto end_match_2;
next_3:;
    if ((i_ < len_)) goto next_4;
    match_ = 0;
    goto end_match_2;
next_4:;
    exit(1);
end_match_2:;
    return 0;
}

int main() {
    struct String source_ = (struct String){.str = "hello world", .len = 11};
    int len_ = source_.len;
    int call_1 = go_(len_, source_, 0);
    return 0;
}
