#include "milone.h"

int main();

int main() {
    milone_assert(1, 1, 2);
    printf("pass\n");
    milone_assert(0, 4, 2);
    printf("not pass\n");
    return 0;
}
