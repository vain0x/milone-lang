#include "milone.h"

int inc_(int x_);

int twice_(int x_1);

int sub_(int x_2, int y_);

int between_(int l_, int r_, int x_3);

struct IntList;

int len_(struct IntList* xs_);

int main();

int inc_(int x_) {
    return (x_ + 1);
}

int twice_(int x_1) {
    return (x_1 * x_1);
}

int sub_(int x_2, int y_) {
    return (x_2 - y_);
}

int between_(int l_, int r_, int x_3) {
    int match_;
    if ((x_3 < l_)) goto next_2;
    match_ = (x_3 < r_);
    goto end_match_1;
next_2:;
    if ((x_3 >= l_)) goto next_3;
    match_ = 0;
    goto end_match_1;
next_3:;
    exit(1);
end_match_1:;
    return match_;
}

struct IntList {
    int head;
    struct IntList* tail;
};

int len_(struct IntList* xs_) {
    int match_1;
    if ((!((!(xs_))))) goto next_5;
    match_1 = 0;
    goto end_match_4;
next_5:;
    struct IntList* __1 = xs_;
    match_1 = 1;
    goto end_match_4;
next_6:;
end_match_4:;
    return match_1;
}

int main() {
    int call_ = inc_(1);
    int call_1 = twice_(call_);
    int call_2 = twice_(call_1);
    int n_ = call_2;
    milone_assert((n_ == 16), 7, 2);
    int call_3 = 0;
    int call_4 = sub_(100, 98);
    int call_5 = between_(2, 3, call_4);
    milone_assert(call_5, 9, 2);
    int call_6 = 0;
    struct IntList* list_ = (struct IntList*)malloc(sizeof(struct IntList));
    list_->head = 1;
    list_->tail = NULL;
    int call_7 = len_(list_);
    milone_assert((call_7 != 0), 17, 2);
    int call_8 = 0;
    return 0;
}
