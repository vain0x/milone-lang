#include "milone.h"

int even_(int n_);

int odd_(int n_1);

int main();

int even_(int n_) {
    int if_;
    if ((n_ != 0)) goto else_1;
    if_ = 1;
    goto end_if_2;
else_1:;
    int call_ = odd_((n_ - 1));
    if_ = call_;
end_if_2:;
    return if_;
}

int odd_(int n_1) {
    int if_1;
    if ((n_1 == 0)) goto else_3;
    int call_1 = even_((n_1 - 1));
    if_1 = call_1;
    goto end_if_4;
else_3:;
    if_1 = 0;
end_if_4:;
    return if_1;
}

int main() {
    int call_2 = odd_(1);
    milone_assert(call_2, 9, 2);
    int call_3 = 0;
    int call_4 = even_(2);
    milone_assert(call_4, 10, 2);
    int call_5 = 0;
    int call_6 = even_(3);
    milone_assert((!(call_6)), 11, 2);
    int call_7 = 0;
    return 0;
}
