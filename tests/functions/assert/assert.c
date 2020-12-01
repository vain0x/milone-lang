#include "milone.h"

int main();

int main() {
    milone_assert(true, 1, 2);
    printf("pass\n");
    milone_assert(false, 4, 2);
    printf("not pass\n");
    return 0;
}
