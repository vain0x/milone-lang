#include <stdio.h>
#include <stdlib.h>
#include <milone.h>

int main(int argc, char **argv);

int main(int argc, char **argv) {
    milone_start(argc, argv);
    if ((0 != 0)) milone_assert_error("union_runtime/union_runtime.milone", 8, 2);
    if ((1 != 1)) milone_assert_error("union_runtime/union_runtime.milone", 9, 2);
    if ((2 != 2)) milone_assert_error("union_runtime/union_runtime.milone", 10, 2);
    return 0;
}
