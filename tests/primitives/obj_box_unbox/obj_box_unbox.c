#include <milone.h>

struct IntList;

struct IntList;

void obj_box_unbox_obj_box_unbox_main_printIntOrStr(bool isInt_, void const* value_);

int main(int argc, char** argv);

struct IntList {
    int head;
    struct IntList const* tail;
};

void obj_box_unbox_obj_box_unbox_main_printIntOrStr(bool isInt_, void const* value_) {
    char if_;
    if (isInt_) {
        goto then_2;
    } else {
        goto else_3;
    }
then_2:;
    printf("%d\n", ((int)((intptr_t)value_)));
    if_ = 0;
    goto if_next_1;
else_3:;
    printf("%s\n", str_to_c_str((*(((struct String const*)value_)))));
    if_ = 0;
    goto if_next_1;
if_next_1:;
    return;
}

int main(int argc, char** argv) {
    milone_start(argc, argv);
    void const* n_;
    void const* xs_;
    int a_;
    int b_;
    void const* box_;
    struct IntList const* list_;
    struct IntList const* list_1;
    char match_;
    obj_box_unbox_obj_box_unbox_main_printIntOrStr(true, ((void const*)((intptr_t)2)));
    box_ = ((void const*)milone_mem_alloc(1, sizeof(struct String)));
    (*(((struct String*)box_))) = (struct String){.str = "Fizz", .len = 4};
    obj_box_unbox_obj_box_unbox_main_printIntOrStr(false, box_);
    n_ = ((void const*)((intptr_t)42));
    milone_assert((((int)((intptr_t)n_)) == 42), (struct String){.str = "obj_box_unbox/obj_box_unbox.milone", .len = 34}, 19, 2);
    list_1 = ((struct IntList const*)milone_mem_alloc(1, sizeof(struct IntList)));
    (*(((struct IntList*)list_1))) = (struct IntList){.head = 2, .tail = NULL};
    list_ = ((struct IntList const*)milone_mem_alloc(1, sizeof(struct IntList)));
    (*(((struct IntList*)list_))) = (struct IntList){.head = 4, .tail = list_1};
    xs_ = ((void const*)((intptr_t)list_));
    if ((!(((struct IntList const*)((intptr_t)xs_))))) goto next_5;
    a_ = ((struct IntList const*)((intptr_t)xs_))->head;
    if ((!(((struct IntList const*)((intptr_t)xs_))->tail))) goto next_5;
    b_ = ((struct IntList const*)((intptr_t)xs_))->tail->head;
    if ((!((!(((struct IntList const*)((intptr_t)xs_))->tail->tail))))) goto next_5;
    milone_assert((((a_ * 10) + b_) == 42), (struct String){.str = "obj_box_unbox/obj_box_unbox.milone", .len = 34}, 24, 16);
    match_ = 0;
    goto end_match_4;
next_5:;
    milone_assert(false, (struct String){.str = "obj_box_unbox/obj_box_unbox.milone", .len = 34}, 25, 9);
    match_ = 0;
    goto end_match_4;
next_6:;
end_match_4:;
    return 0;
}
