#include "milone.h"

int go_(int len_, struct String source_, int i_);

int main();

int go_(int len_, struct String source_, int i_) {
tailrec_1:;
    int if_;
    if ((i_ >= len_)) goto else_2;
    int if_1;
    if ((source_.str[i_] != 'o')) goto else_4;
    printf("%d\n", i_);
    int call_ = 0;
    if_1 = 0;
    goto end_if_5;
else_4:;
    if_1 = 0;
end_if_5:;
    int arg_ = len_;
    struct String arg_1 = source_;
    int arg_2 = (i_ + 1);
    len_ = arg_;
    source_ = arg_1;
    i_ = arg_2;
    goto tailrec_1;
    if_ = 0;
    goto end_if_3;
else_2:;
    if_ = 0;
end_if_3:;
    return 0;
}

int main() {
    struct String source_ = (struct String){.str = "hello world", .len = 11};
    int len_ = source_.len;
    int call_1 = go_(len_, source_, 0);
    return 0;
}
