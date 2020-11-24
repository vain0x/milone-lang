#include "milone.h"

int main();

int main() {
    milone_assert(1, 1, 2);
    printf("pass\n");
    int call_ = 0;
    milone_assert(0, 4, 2);
    printf("not pass\n");
    int call_1 = 0;
    return 0;
}
