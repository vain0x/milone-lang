#include "milone.h"

int argCount_(int arg_);

struct String argGet_(int i_);

int go_(int i_1);

int main();

int argCount_(int arg_) {
    int call_ = arg_count(0);
    return call_;
}

struct String argGet_(int i_) {
    struct String call_1 = arg_get(i_);
    return call_1;
}

int go_(int i_1) {
tailrec_1:;
    int match_;
    int call_2 = argCount_(0);
    if ((i_1 >= call_2)) goto next_3;
    struct String call_3 = argGet_(i_1);
    struct String call_4 = str_of_int(i_1);
    milone_assert((str_cmp(call_3, str_add((struct String){.str = "#", .len = 1}, call_4)) != 0), 10, 4);
    int call_5 = 0;
    int arg_1 = (i_1 + 1);
    i_1 = arg_1;
    goto tailrec_1;
    match_ = 0;
    goto end_match_2;
next_3:;
    if ((i_1 < call_2)) goto next_4;
    match_ = 0;
    goto end_match_2;
next_4:;
    exit(1);
end_match_2:;
    return 0;
}

int main() {
    int call_6 = go_(0);
    return 0;
}