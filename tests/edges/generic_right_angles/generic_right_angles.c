#include <stdio.h>
#include <stdlib.h>
#include <milone.h>

struct Int32ListListList;

int main(int argc, char** argv);

int main(int argc, char** argv) {
    milone_start(argc, argv);
    struct Int32ListListList const* n_;
    bool ok_;
    bool if_;
    n_ = NULL;
    if ((!(n_))) {
        goto nil_cl_2;
    } else {
        goto cons_cl_3;
    }
nil_cl_2:;
    if_ = true;
    goto if_next_1;
cons_cl_3:;
    if_ = false;
    goto if_next_1;
if_next_1:;
    ok_ = if_;
    milone_assert(ok_, (struct String){.ptr = "generic_right_angles/generic_right_angles.milone", .len = 48}, 16, 2);
    milone_assert((3 >= 2), (struct String){.ptr = "generic_right_angles/generic_right_angles.milone", .len = 48}, 19, 2);
    milone_assert(((2 << 3) == 16), (struct String){.ptr = "generic_right_angles/generic_right_angles.milone", .len = 48}, 22, 2);
    return 0;
}
