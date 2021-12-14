#include <milone.h>

int main(int argc, char** argv);

int main(int argc, char** argv) {
    milone_start(argc, argv);
    milone_assert((0 == 0), (struct String){.str = "union_runtime/union_runtime.milone", .len = 34}, 8, 2);
    milone_assert((1 == 1), (struct String){.str = "union_runtime/union_runtime.milone", .len = 34}, 9, 2);
    milone_assert((2 == 2), (struct String){.str = "union_runtime/union_runtime.milone", .len = 34}, 10, 2);
    return 0;
}
