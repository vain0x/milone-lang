#include "milone.h"

int main();

int main() {
    int if_;
    if (1) {
        goto then_2;
    } else {
        goto else_3;
    }
then_2:;
    if_ = 0;
    goto if_next_1;
else_3:;
    if_ = 1;
    goto if_next_1;
if_next_1:;
    return if_;
}
