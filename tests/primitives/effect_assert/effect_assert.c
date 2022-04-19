#include <stdio.h>
#include <stdlib.h>
#include <milone.h>

int main(int argc, char** argv);

int main(int argc, char** argv) {
    milone_start(argc, argv);
    milone_assert(true, (struct String){.ptr = "effect_assert/effect_assert.milone", .len = 34}, 3, 2);
    printf("pass\n");
    printf("Notice: test \'effect_assert\' intentionally prints an assertion error:\n");
    milone_assert(false, (struct String){.ptr = "effect_assert/effect_assert.milone", .len = 34}, 7, 2);
    printf("not pass\n");
    return 0;
}
