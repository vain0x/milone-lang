#include <stdio.h>
#include <stdlib.h>
#include <milone.h>

struct Int32Int32Tuple2_;

void pat_as_pat_as_simpleCase(void);

void pat_as_pat_as_shadowingCase(void);

int main(int argc, char **argv);

struct Int32Int32Tuple2_ {
    int32_t t0;
    int32_t t1;
};

void pat_as_pat_as_simpleCase(void) {
    int32_t x_;
    char match_;
    x_ = 1;
    if ((x_ != 1)) goto next_2;
    if ((x_ != 1)) milone_assert_error("pat_as/pat_as.milone", 6, 14);
    match_ = 0;
    goto end_match_1;
next_2:;
    if (true) milone_assert_error("pat_as/pat_as.milone", 7, 9);
    match_ = 0;
    goto end_match_1;
next_3:;
end_match_1:;
    return;
}

void pat_as_pat_as_shadowingCase(void) {
    int32_t x_1;
    int32_t x_2;
    struct Int32Int32Tuple2_ y_;
    int32_t y1_;
    int32_t y2_;
    char match_1;
    struct Int32Int32Tuple2_ Int32Int32Tuple2_;
    bool if_;
    bool if_1;
    x_1 = 1;
    Int32Int32Tuple2_ = (struct Int32Int32Tuple2_){.t0 = x_1, .t1 = 2};
    y_ = Int32Int32Tuple2_;
    x_2 = y_.t1;
    y1_ = y_.t0;
    y2_ = y_.t1;
    if ((x_2 == 2)) {
        goto then_4;
    } else {
        goto else_5;
    }
then_4:;
    if_ = (y1_ == 1);
    goto if_next_3;
else_5:;
    if_ = false;
    goto if_next_3;
if_next_3:;
    if (if_) {
        goto then_7;
    } else {
        goto else_8;
    }
then_7:;
    if_1 = (y2_ == 2);
    goto if_next_6;
else_8:;
    if_1 = false;
    goto if_next_6;
if_next_6:;
    if ((!(if_1))) milone_assert_error("pat_as/pat_as.milone", 15, 4);
    match_1 = 0;
    goto end_match_1;
next_2:;
end_match_1:;
    return;
}

int main(int argc, char **argv) {
    milone_start(argc, argv);
    pat_as_pat_as_simpleCase();
    pat_as_pat_as_shadowingCase();
    return 0;
}
