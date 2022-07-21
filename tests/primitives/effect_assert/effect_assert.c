#include <stdio.h>
#include <stdlib.h>
#include <milone.h>

int main(int argc, char **argv);

int main(int argc, char **argv) {
    milone_start(argc, argv);
    if (false) milone_assert_error("effect_assert/effect_assert.milone", 3, 2);
    printf("pass\n");
    printf("Notice: test \'effect_assert\' intentionally prints an assertion error:\n");
    if (true) milone_assert_error("effect_assert/effect_assert.milone", 7, 2);
    printf("not pass\n");
    return 0;
}
