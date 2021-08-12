#include "milone.h"

int milone_main(void);

int milone_main(void) {
    milone_assert(true, 3, 2);
    printf("pass\n");
    printf("Notice: test \'effect_assert\' intentionally prints an assertion error:\n");
    milone_assert(false, 7, 2);
    printf("not pass\n");
    return 0;
}
