#include "milone.h"

int not_(int arg_);

int main();

int not_(int arg_) {
    printf("shadowing not\n");
    int call_ = 0;
    return 0;
}

int main() {
    int match_;
    if (!(((!(0)) == 1))) goto next_2;
    printf("not false\n");
    int call_1 = 0;
    match_ = 0;
    goto end_match_1;
next_2:;
    if (!(((!(0)) == 0))) goto next_3;
    match_ = 0;
    goto end_match_1;
next_3:;
    exit(1);
end_match_1:;
    int call_2 = not_(0);
    return 0;
}
