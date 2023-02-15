#include <stdio.h>
#include <stdlib.h>
#include <milone.h>

struct Int32Cons;

struct Int32Cons;

void obj_box_unbox_obj_box_unbox_main_printIntOrStr(bool isInt_, void const *value_);

int main(int argc, char **argv);

struct Int32Cons {
    int32_t head;
    struct Int32Cons const *tail;
};

void obj_box_unbox_obj_box_unbox_main_printIntOrStr(bool isInt_, void const *value_) {
    char if_;
    if (isInt_) {
        goto then_2;
    } else {
        goto else_3;
    }
then_2:;
    printf("%d\n", ((int32_t)((intptr_t)value_)));
    if_ = 0;
    goto if_next_1;
else_3:;
    printf("%s\n", string_to_c_str((*(((struct String const *)value_)))));
    if_ = 0;
    goto if_next_1;
if_next_1:;
    return;
}

int main(int argc, char **argv) {
    milone_start(argc, argv);
    void const *n_;
    void const *xs_;
    int32_t a_;
    int32_t b_;
    void const *box_;
    struct Int32Cons const *list_;
    struct Int32Cons const *list_1;
    char match_;
    obj_box_unbox_obj_box_unbox_main_printIntOrStr(true, ((void const *)((intptr_t)2)));
    box_ = ((void const *)milone_region_alloc(1, sizeof(struct String)));
    (*(((struct String *)box_))) = (struct String){.ptr = "Fizz", .len = 4};
    obj_box_unbox_obj_box_unbox_main_printIntOrStr(false, box_);
    n_ = ((void const *)((intptr_t)42));
    if ((((int32_t)((intptr_t)n_)) != 42)) milone_assert_error("obj_box_unbox/obj_box_unbox.milone", 19, 2);
    list_1 = ((struct Int32Cons const *)milone_region_alloc(1, sizeof(struct Int32Cons)));
    (*(((struct Int32Cons *)list_1))) = (struct Int32Cons){.head = 2, .tail = NULL};
    list_ = ((struct Int32Cons const *)milone_region_alloc(1, sizeof(struct Int32Cons)));
    (*(((struct Int32Cons *)list_))) = (struct Int32Cons){.head = 4, .tail = list_1};
    xs_ = ((void const *)((intptr_t)list_));
    if ((!(((struct Int32Cons const *)((intptr_t)xs_))))) goto next_2;
    a_ = ((struct Int32Cons const *)((intptr_t)xs_))->head;
    if ((!(((struct Int32Cons const *)((intptr_t)xs_))->tail))) goto next_2;
    b_ = ((struct Int32Cons const *)((intptr_t)xs_))->tail->head;
    if ((!((!(((struct Int32Cons const *)((intptr_t)xs_))->tail->tail))))) goto next_2;
    if ((((a_ * 10) + b_) != 42)) milone_assert_error("obj_box_unbox/obj_box_unbox.milone", 24, 16);
    match_ = 0;
    goto end_match_1;
next_2:;
    if (true) milone_assert_error("obj_box_unbox/obj_box_unbox.milone", 25, 9);
    match_ = 0;
    goto end_match_1;
next_3:;
end_match_1:;
    return 0;
}
