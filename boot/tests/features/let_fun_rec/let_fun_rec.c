#include "milone.h"

int go_(int len_, struct String source_, int i_);

int main();

int go_(int len_, struct String source_, int i_) {
    int match_;
    if ((i_ >= len_)) goto next_2;
    int match_1;
    if ((source_.str[i_] != 'o')) goto next_5;
    printf("%d\n", i_);
    int call_ = 0;
    match_1 = 0;
    goto end_match_4;
next_5:;
    if ((source_.str[i_] == 'o')) goto next_6;
    match_1 = 0;
    goto end_match_4;
next_6:;
    exit(1);
end_match_4:;
    int call_1 = go_(len_, source_, (i_ + 1));
    match_ = 0;
    goto end_match_1;
next_2:;
    if ((i_ < len_)) goto next_3;
    match_ = 0;
    goto end_match_1;
next_3:;
    exit(1);
end_match_1:;
    return 0;
}

int main() {
    struct String source_ = (struct String){.str = "hello world", .len = 11};
    int len_ = source_.len;
    int call_2 = go_(len_, source_, 0);
    return 0;
}
