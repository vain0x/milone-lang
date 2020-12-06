#include "milone.h"

struct IntList;

struct IntList const* go_(struct IntList const* acc_, struct IntList const* xs_1);

struct IntList const* rev_(struct IntList const* xs_);

int printList_(struct IntList const* xs_3);

int main();

struct IntList {
    int head;
    struct IntList const* tail;
};

struct IntList const* go_(struct IntList const* acc_, struct IntList const* xs_1) {
tailrec_1:;
    struct IntList const* match_;
    if ((!((!(xs_1))))) goto next_3;
    match_ = acc_;
    goto end_match_2;
next_3:;
    if ((!(xs_1))) goto next_4;
    int x_ = xs_1->head;
    struct IntList const* xs_2 = xs_1->tail;
    struct IntList const* list_ = milone_mem_alloc(1, sizeof(struct IntList));
    (*(((struct IntList*)list_))) = (struct IntList){.head = x_, .tail = acc_};
    struct IntList const* arg_ = list_;
    struct IntList const* arg_1 = xs_2;
    acc_ = arg_;
    xs_1 = arg_1;
    goto tailrec_1;
    match_ = NULL;
    goto end_match_2;
next_4:;
    exit(1);
end_match_2:;
    return match_;
}

struct IntList const* rev_(struct IntList const* xs_) {
    struct IntList const* call_ = go_(NULL, xs_);
    return call_;
}

int printList_(struct IntList const* xs_3) {
tailrec_5:;
    int match_1;
    if ((!((!(xs_3))))) goto next_7;
    match_1 = 0;
    goto end_match_6;
next_7:;
    if ((!(xs_3))) goto next_8;
    int x_1 = xs_3->head;
    struct IntList const* xs_4 = xs_3->tail;
    printf("%d\n", x_1);
    struct IntList const* arg_2 = xs_4;
    xs_3 = arg_2;
    goto tailrec_5;
    match_1 = 0;
    goto end_match_6;
next_8:;
    exit(1);
end_match_6:;
    return 0;
}

int main() {
    struct IntList const* list_3 = milone_mem_alloc(1, sizeof(struct IntList));
    (*(((struct IntList*)list_3))) = (struct IntList){.head = 2, .tail = NULL};
    struct IntList const* list_2 = milone_mem_alloc(1, sizeof(struct IntList));
    (*(((struct IntList*)list_2))) = (struct IntList){.head = 1, .tail = list_3};
    struct IntList const* list_1 = milone_mem_alloc(1, sizeof(struct IntList));
    (*(((struct IntList*)list_1))) = (struct IntList){.head = 0, .tail = list_2};
    struct IntList const* xs_5 = list_1;
    printf("xs:\n");
    int call_1 = printList_(xs_5);
    printf("rev xs:\n");
    struct IntList const* call_2 = rev_(xs_5);
    int call_3 = printList_(call_2);
    return 0;
}
