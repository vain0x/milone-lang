#include "milone.h"

int not_(int arg_);

int main();

int not_(int arg_) {
    printf("shadowing not\n");
    return 0;
}

int main() {
    int if_;
    if (true) {
        goto then_2;
    } else {
        goto else_3;
    }
then_2:;
    printf("not false\n");
    if_ = 0;
    goto if_next_1;
else_3:;
    if_ = 0;
    goto if_next_1;
if_next_1:;
    int call_ = not_(0);
    return 0;
}
