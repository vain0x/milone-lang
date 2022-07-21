#include <stdio.h>
#include <stdlib.h>
#include <milone.h>

int main(int argc, char **argv);

int main(int argc, char **argv) {
    milone_start(argc, argv);
    int32_t inner_;
    inner_ = 1;
    if ((inner_ != 1)) milone_assert_error("union_newtype/union_newtype.milone", 8, 2);
    return 0;
}
