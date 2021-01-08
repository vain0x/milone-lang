#include "milone.h"

int arg_count();

int argCount_(int arg_);

struct String arg_get(int);

struct String argGet_(int i_);

int go_(int i_1);

int milone_main();

int argCount_(int arg_) {
    int arg_count_result_ = arg_count();
    return arg_count_result_;
}

struct String argGet_(int i_) {
    struct String arg_get_result_ = arg_get(i_);
    return arg_get_result_;
}

int go_(int i_1) {
tailrec_1:;
    int call_ = argCount_(0);
    int if_;
    if ((i_1 < call_)) {
        goto then_3;
    } else {
        goto else_4;
    }
then_3:;
    struct String call_1 = argGet_(i_1);
    struct String call_2 = str_of_int64(i_1);
    milone_assert((str_cmp(call_1, str_add((struct String){.str = "#", .len = 1}, call_2)) != 0), 10, 4);
    int arg_1 = (i_1 + 1);
    i_1 = arg_1;
    goto tailrec_1;
    if_ = 0;
    goto if_next_2;
else_4:;
    if_ = 0;
    goto if_next_2;
if_next_2:;
    return 0;
}

int milone_main() {
    int call_3 = go_(0);
    return 0;
}
