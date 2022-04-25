#include <stdio.h>
#include <stdlib.h>
#include <milone.h>

struct FirstSecondTuple2_Cons;

struct First_Cons;

struct Second_Cons;

struct FirstListSecondListTuple2_;

typedef struct FirstListSecondListTuple2_(*VoidConstPtrFirstSecondTuple2_ConsConstPtrFirstListSecondListTuple2_FunPtr2)(void const *, struct FirstSecondTuple2_Cons const *);

struct FirstSecondTuple2_ListFirstListSecondListTuple2_Fun1;

struct First_;

struct Second_;

struct Node_Cons;

struct Node_;

struct FirstSecondTuple2_;

struct Int32ThirdTuple2_Cons;

struct Third_;

struct Int32ThirdTuple2_;

struct Node_Cons;

struct Int32ThirdTuple2_Cons;

struct FirstListSecondListTuple2_ union_complicated_union_complicated_main_f(struct FirstSecondTuple2_Cons const *arg_2);

struct FirstListSecondListTuple2_ union_complicated_union_complicated_eta2_main_f(void const *env_, struct FirstSecondTuple2_Cons const *arg_);

struct FirstListSecondListTuple2_ union_complicated_union_complicated_eta2_main_f_1(void const *env_1, struct FirstSecondTuple2_Cons const *arg_1);

int main(int argc, char **argv);

struct FirstListSecondListTuple2_ {
    struct First_Cons const *t0;
    struct Second_Cons const *t1;
};

struct FirstSecondTuple2_ListFirstListSecondListTuple2_Fun1 {
    VoidConstPtrFirstSecondTuple2_ConsConstPtrFirstListSecondListTuple2_FunPtr2 fun;
    void const *env;
};

enum First_Discriminant {
    First_First,
};

struct First_ {
    enum First_Discriminant discriminant;
    union {
        struct FirstSecondTuple2_ListFirstListSecondListTuple2_Fun1 First_First;
    };
};

enum Second_Discriminant {
    Second_Second,
};

struct Second_ {
    enum Second_Discriminant discriminant;
    union {
        struct FirstSecondTuple2_ListFirstListSecondListTuple2_Fun1 Second_Second;
    };
};

enum Node_Discriminant {
    Node_Leaf,
    Node_Node,
};

struct Node_ {
    enum Node_Discriminant discriminant;
    union {
        int32_t Node_Leaf;
        struct Node_Cons const *Node_Node;
    };
};

struct FirstSecondTuple2_ {
    struct First_ t0;
    struct Second_ t1;
};

enum Third_Discriminant {
    Third_Leaf3,
    Third_Node3,
};

struct Third_ {
    enum Third_Discriminant discriminant;
    union {
        struct Int32ThirdTuple2_Cons const *Third_Node3;
    };
};

struct Int32ThirdTuple2_ {
    int32_t t0;
    struct Third_ t1;
};

struct Node_Cons {
    struct Node_ head;
    struct Node_Cons const *tail;
};

struct Int32ThirdTuple2_Cons {
    struct Int32ThirdTuple2_ head;
    struct Int32ThirdTuple2_Cons const *tail;
};

struct FirstListSecondListTuple2_ union_complicated_union_complicated_main_f(struct FirstSecondTuple2_Cons const *arg_2) {
    struct FirstListSecondListTuple2_ FirstListSecondListTuple2_;
    FirstListSecondListTuple2_ = (struct FirstListSecondListTuple2_){.t0 = NULL, .t1 = NULL};
    return FirstListSecondListTuple2_;
}

struct FirstListSecondListTuple2_ union_complicated_union_complicated_eta2_main_f(void const *env_, struct FirstSecondTuple2_Cons const *arg_) {
    struct FirstListSecondListTuple2_ call_;
    call_ = union_complicated_union_complicated_main_f(arg_);
    return call_;
}

struct FirstListSecondListTuple2_ union_complicated_union_complicated_eta2_main_f_1(void const *env_1, struct FirstSecondTuple2_Cons const *arg_1) {
    struct FirstListSecondListTuple2_ call_1;
    call_1 = union_complicated_union_complicated_main_f(arg_1);
    return call_1;
}

int main(int argc, char **argv) {
    milone_start(argc, argv);
    int32_t x_;
    int32_t y_;
    int32_t z_;
    struct First_ first_;
    struct Second_ second_;
    char match_;
    struct Node_Cons const *list_;
    struct Node_Cons const *list_1;
    struct Node_ variant_;
    struct Node_Cons const *list_2;
    struct Node_ variant_1;
    struct Node_ variant_2;
    struct Node_Cons const *list_3;
    struct Node_ variant_3;
    struct Node_Cons const *list_4;
    struct Node_Cons const *list_5;
    struct Node_ variant_4;
    struct Node_ variant_5;
    struct Node_ variant_6;
    bool if_;
    bool if_1;
    struct FirstSecondTuple2_ FirstSecondTuple2_;
    struct FirstSecondTuple2_ListFirstListSecondListTuple2_Fun1 fun_;
    struct First_ variant_7;
    struct FirstSecondTuple2_ListFirstListSecondListTuple2_Fun1 fun_1;
    struct Second_ variant_8;
    char match_1;
    struct Int32ThirdTuple2_Cons const *list_6;
    struct Int32ThirdTuple2_ Int32ThirdTuple2_;
    variant_ = (struct Node_){.discriminant = Node_Leaf, .Node_Leaf = 1};
    variant_1 = (struct Node_){.discriminant = Node_Leaf, .Node_Leaf = 2};
    list_2 = ((struct Node_Cons const *)milone_region_alloc(1, sizeof(struct Node_Cons)));
    (*(((struct Node_Cons *)list_2))) = (struct Node_Cons){.head = variant_1, .tail = NULL};
    list_1 = ((struct Node_Cons const *)milone_region_alloc(1, sizeof(struct Node_Cons)));
    (*(((struct Node_Cons *)list_1))) = (struct Node_Cons){.head = variant_, .tail = list_2};
    variant_2 = (struct Node_){.discriminant = Node_Node, .Node_Node = list_1};
    variant_3 = (struct Node_){.discriminant = Node_Node, .Node_Node = NULL};
    variant_4 = (struct Node_){.discriminant = Node_Leaf, .Node_Leaf = 3};
    list_5 = ((struct Node_Cons const *)milone_region_alloc(1, sizeof(struct Node_Cons)));
    (*(((struct Node_Cons *)list_5))) = (struct Node_Cons){.head = variant_4, .tail = NULL};
    variant_5 = (struct Node_){.discriminant = Node_Node, .Node_Node = list_5};
    list_4 = ((struct Node_Cons const *)milone_region_alloc(1, sizeof(struct Node_Cons)));
    (*(((struct Node_Cons *)list_4))) = (struct Node_Cons){.head = variant_5, .tail = NULL};
    list_3 = ((struct Node_Cons const *)milone_region_alloc(1, sizeof(struct Node_Cons)));
    (*(((struct Node_Cons *)list_3))) = (struct Node_Cons){.head = variant_3, .tail = list_4};
    list_ = ((struct Node_Cons const *)milone_region_alloc(1, sizeof(struct Node_Cons)));
    (*(((struct Node_Cons *)list_))) = (struct Node_Cons){.head = variant_2, .tail = list_3};
    variant_6 = (struct Node_){.discriminant = Node_Node, .Node_Node = list_};
    if ((variant_6.discriminant != Node_Node)) goto next_2;
    if ((!(variant_6.Node_Node))) goto next_2;
    if ((variant_6.Node_Node->head.discriminant != Node_Node)) goto next_2;
    if ((!(variant_6.Node_Node->head.Node_Node))) goto next_2;
    if ((variant_6.Node_Node->head.Node_Node->head.discriminant != Node_Leaf)) goto next_2;
    x_ = variant_6.Node_Node->head.Node_Node->head.Node_Leaf;
    if ((!(variant_6.Node_Node->head.Node_Node->tail))) goto next_2;
    if ((variant_6.Node_Node->head.Node_Node->tail->head.discriminant != Node_Leaf)) goto next_2;
    y_ = variant_6.Node_Node->head.Node_Node->tail->head.Node_Leaf;
    if ((!((!(variant_6.Node_Node->head.Node_Node->tail->tail))))) goto next_2;
    if ((!(variant_6.Node_Node->tail))) goto next_2;
    if ((variant_6.Node_Node->tail->head.discriminant != Node_Node)) goto next_2;
    if ((!((!(variant_6.Node_Node->tail->head.Node_Node))))) goto next_2;
    if ((!(variant_6.Node_Node->tail->tail))) goto next_2;
    if ((variant_6.Node_Node->tail->tail->head.discriminant != Node_Node)) goto next_2;
    if ((!(variant_6.Node_Node->tail->tail->head.Node_Node))) goto next_2;
    if ((variant_6.Node_Node->tail->tail->head.Node_Node->head.discriminant != Node_Leaf)) goto next_2;
    z_ = variant_6.Node_Node->tail->tail->head.Node_Node->head.Node_Leaf;
    if ((!((!(variant_6.Node_Node->tail->tail->head.Node_Node->tail))))) goto next_2;
    if ((!((!(variant_6.Node_Node->tail->tail->tail))))) goto next_2;
    if ((x_ == 1)) {
        goto then_5;
    } else {
        goto else_6;
    }
then_5:;
    if_ = (y_ == 2);
    goto if_next_4;
else_6:;
    if_ = false;
    goto if_next_4;
if_next_4:;
    if (if_) {
        goto then_8;
    } else {
        goto else_9;
    }
then_8:;
    if_1 = (z_ == 3);
    goto if_next_7;
else_9:;
    if_1 = false;
    goto if_next_7;
if_next_7:;
    if ((!(if_1))) milone_assert_error("union_complicated/union_complicated.milone", 23, 84);
    match_ = 0;
    goto end_match_1;
next_2:;
    if (true) milone_assert_error("union_complicated/union_complicated.milone", 24, 9);
    match_ = 0;
    goto end_match_1;
next_3:;
end_match_1:;
    fun_ = (struct FirstSecondTuple2_ListFirstListSecondListTuple2_Fun1){.fun = union_complicated_union_complicated_eta2_main_f, .env = NULL};
    variant_7 = (struct First_){.discriminant = First_First, .First_First = fun_};
    fun_1 = (struct FirstSecondTuple2_ListFirstListSecondListTuple2_Fun1){.fun = union_complicated_union_complicated_eta2_main_f_1, .env = NULL};
    variant_8 = (struct Second_){.discriminant = Second_Second, .Second_Second = fun_1};
    FirstSecondTuple2_ = (struct FirstSecondTuple2_){.t0 = variant_7, .t1 = variant_8};
    first_ = FirstSecondTuple2_.t0;
    second_ = FirstSecondTuple2_.t1;
    Int32ThirdTuple2_ = (struct Int32ThirdTuple2_){.t0 = 0, .t1 = (struct Third_){.discriminant = Third_Leaf3}};
    list_6 = ((struct Int32ThirdTuple2_Cons const *)milone_region_alloc(1, sizeof(struct Int32ThirdTuple2_Cons)));
    (*(((struct Int32ThirdTuple2_Cons *)list_6))) = (struct Int32ThirdTuple2_Cons){.head = Int32ThirdTuple2_, .tail = NULL};
    if ((!(list_6))) goto next_11;
    if ((list_6->head.t0 != 0)) goto next_11;
    if ((list_6->head.t1.discriminant != Third_Leaf3)) goto next_11;
    if ((!((!(list_6->tail))))) goto next_11;
    match_1 = 0;
    goto end_match_10;
next_11:;
    if (true) milone_assert_error("union_complicated/union_complicated.milone", 32, 9);
    match_1 = 0;
    goto end_match_10;
next_12:;
end_match_10:;
    return 0;
}
