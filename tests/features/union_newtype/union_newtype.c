#include <stdio.h>
#include <stdlib.h>
#include <milone.h>

int main(int argc, char** argv);

int main(int argc, char** argv) {
    milone_start(argc, argv);
    int inner_;
    inner_ = 1;
    milone_assert((inner_ == 1), (struct String){.ptr = "union_newtype/union_newtype.milone", .len = 34}, 8, 2);
    return 0;
}
