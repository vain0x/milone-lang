#include <stdio.h>
#include <stdlib.h>
#include <milone.h>

struct Int32Cons;

struct Int32Cons;

void list_operators_list_operators_nilTest(void);

void list_operators_list_operators_cons1Test(void);

void list_operators_list_operators_cons2Test(void);

void list_operators_list_operators_literalTest(void);

int main(int argc, char **argv);

struct Int32Cons {
    int32_t head;
    struct Int32Cons const *tail;
};

void list_operators_list_operators_nilTest(void) {
    struct Int32Cons const *nil_;
    char if_;
    nil_ = NULL;
    if ((!(nil_))) {
        goto nil_cl_2;
    } else {
        goto cons_cl_3;
    }
nil_cl_2:;
    if_ = 0;
    goto if_next_1;
cons_cl_3:;
    if (true) milone_assert_error("list_operators/list_operators.milone", 9, 9);
    if_ = 0;
    goto if_next_1;
if_next_1:;
    return;
}

void list_operators_list_operators_cons1Test(void) {
    struct Int32Cons const *xs_;
    int32_t x_;
    struct Int32Cons const *list_;
    char match_;
    list_ = ((struct Int32Cons const *)milone_region_alloc(1, sizeof(struct Int32Cons)));
    (*(((struct Int32Cons *)list_))) = (struct Int32Cons){.head = 1, .tail = NULL};
    xs_ = list_;
    if ((!(xs_))) goto next_2;
    x_ = xs_->head;
    if ((!((!(xs_->tail))))) goto next_2;
    if ((x_ != 1)) milone_assert_error("list_operators/list_operators.milone", 15, 15);
    match_ = 0;
    goto end_match_1;
next_2:;
    if (true) milone_assert_error("list_operators/list_operators.milone", 16, 9);
    match_ = 0;
    goto end_match_1;
next_3:;
end_match_1:;
    return;
}

void list_operators_list_operators_cons2Test(void) {
    struct Int32Cons const *ys_;
    int32_t y2_;
    int32_t y3_;
    struct Int32Cons const *list_1;
    struct Int32Cons const *list_2;
    char match_1;
    bool if_1;
    list_2 = ((struct Int32Cons const *)milone_region_alloc(1, sizeof(struct Int32Cons)));
    (*(((struct Int32Cons *)list_2))) = (struct Int32Cons){.head = 3, .tail = NULL};
    list_1 = ((struct Int32Cons const *)milone_region_alloc(1, sizeof(struct Int32Cons)));
    (*(((struct Int32Cons *)list_1))) = (struct Int32Cons){.head = 2, .tail = list_2};
    ys_ = list_1;
    if ((!(ys_))) goto next_2;
    y2_ = ys_->head;
    if ((!(ys_->tail))) goto next_2;
    y3_ = ys_->tail->head;
    if ((!((!(ys_->tail->tail))))) goto next_2;
    if ((y2_ == 2)) {
        goto then_5;
    } else {
        goto else_6;
    }
then_5:;
    if_1 = (y3_ == 3);
    goto if_next_4;
else_6:;
    if_1 = false;
    goto if_next_4;
if_next_4:;
    if ((!(if_1))) milone_assert_error("list_operators/list_operators.milone", 22, 22);
    match_1 = 0;
    goto end_match_1;
next_2:;
    if (true) milone_assert_error("list_operators/list_operators.milone", 23, 9);
    match_1 = 0;
    goto end_match_1;
next_3:;
end_match_1:;
    return;
}

void list_operators_list_operators_literalTest(void) {
    struct Int32Cons const *zs_;
    int32_t z2_;
    int32_t z3_;
    int32_t z5_;
    int32_t z7_;
    struct Int32Cons const *list_3;
    struct Int32Cons const *list_4;
    struct Int32Cons const *list_5;
    struct Int32Cons const *list_6;
    char match_2;
    list_6 = ((struct Int32Cons const *)milone_region_alloc(1, sizeof(struct Int32Cons)));
    (*(((struct Int32Cons *)list_6))) = (struct Int32Cons){.head = 7, .tail = NULL};
    list_5 = ((struct Int32Cons const *)milone_region_alloc(1, sizeof(struct Int32Cons)));
    (*(((struct Int32Cons *)list_5))) = (struct Int32Cons){.head = 5, .tail = list_6};
    list_4 = ((struct Int32Cons const *)milone_region_alloc(1, sizeof(struct Int32Cons)));
    (*(((struct Int32Cons *)list_4))) = (struct Int32Cons){.head = 3, .tail = list_5};
    list_3 = ((struct Int32Cons const *)milone_region_alloc(1, sizeof(struct Int32Cons)));
    (*(((struct Int32Cons *)list_3))) = (struct Int32Cons){.head = 2, .tail = list_4};
    zs_ = list_3;
    if ((!(zs_))) goto next_2;
    z2_ = zs_->head;
    if ((!(zs_->tail))) goto next_2;
    z3_ = zs_->tail->head;
    if ((!(zs_->tail->tail))) goto next_2;
    z5_ = zs_->tail->tail->head;
    if ((!(zs_->tail->tail->tail))) goto next_2;
    z7_ = zs_->tail->tail->tail->head;
    if ((!((!(zs_->tail->tail->tail->tail))))) goto next_2;
    if ((z2_ != 2)) milone_assert_error("list_operators/list_operators.milone", 30, 4);
    if ((z3_ != 3)) milone_assert_error("list_operators/list_operators.milone", 31, 4);
    if ((z5_ != 5)) milone_assert_error("list_operators/list_operators.milone", 32, 4);
    if ((z7_ != 7)) milone_assert_error("list_operators/list_operators.milone", 33, 4);
    match_2 = 0;
    goto end_match_1;
next_2:;
    if (true) milone_assert_error("list_operators/list_operators.milone", 35, 9);
    match_2 = 0;
    goto end_match_1;
next_3:;
end_match_1:;
    return;
}

int main(int argc, char **argv) {
    milone_start(argc, argv);
    list_operators_list_operators_nilTest();
    list_operators_list_operators_cons1Test();
    list_operators_list_operators_cons2Test();
    list_operators_list_operators_literalTest();
    return 0;
}
