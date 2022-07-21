#include <stdio.h>
#include <stdlib.h>
#include <milone.h>

struct Int32ListListCons;

int main(int argc, char **argv);

int main(int argc, char **argv) {
    milone_start(argc, argv);
    struct Int32ListListCons const *n_;
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
    if ((!(ok_))) milone_assert_error("generic_right_angles/generic_right_angles.milone", 16, 2);
    if ((3 < 2)) milone_assert_error("generic_right_angles/generic_right_angles.milone", 19, 2);
    if (((2 << 3) != 16)) milone_assert_error("generic_right_angles/generic_right_angles.milone", 22, 2);
    return 0;
}
