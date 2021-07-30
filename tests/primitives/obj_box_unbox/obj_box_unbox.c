#include "milone.h"

struct IntList;

struct IntList;

char printIntOrStr_(bool isInt_, void const* value_);

int milone_main();

struct IntList {
    int head;
    struct IntList const* tail;
};

char printIntOrStr_(bool isInt_, void const* value_) {
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
    return 0;
}

int milone_main() {
    char call_ = printIntOrStr_(true, ((void const*)((intptr_t)2)));
    void const* box_ = milone_mem_alloc(1, sizeof(struct String));
    (*(((struct String*)box_))) = (struct String){.str = "Fizz", .len = 4};
    char call_1 = printIntOrStr_(false, box_);
    void const* n_ = ((void const*)((intptr_t)42));
    milone_assert((((int)((intptr_t)n_)) == 42), 19, 2);
    struct IntList const* list_1 = milone_mem_alloc(1, sizeof(struct IntList));
    (*(((struct IntList*)list_1))) = (struct IntList){.head = 2, .tail = NULL};
    struct IntList const* list_ = milone_mem_alloc(1, sizeof(struct IntList));
    (*(((struct IntList*)list_))) = (struct IntList){.head = 4, .tail = list_1};
    void const* xs_ = ((void const*)((intptr_t)list_));
    char match_;
    if ((!(((struct IntList const*)((intptr_t)xs_))))) goto next_5;
    int a_ = ((struct IntList const*)((intptr_t)xs_))->head;
    if ((!(((struct IntList const*)((intptr_t)xs_))->tail))) goto next_5;
    int b_ = ((struct IntList const*)((intptr_t)xs_))->tail->head;
    if ((!((!(((struct IntList const*)((intptr_t)xs_))->tail->tail))))) goto next_5;
    milone_assert((((a_ * 10) + b_) == 42), 24, 16);
    match_ = 0;
    goto end_match_4;
next_5:;
    milone_assert(false, 25, 9);
    match_ = 0;
    goto end_match_4;
next_6:;
end_match_4:;
    return 0;
}
