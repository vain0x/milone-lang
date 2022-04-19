#include <stdio.h>
#include <stdlib.h>
#include <milone.h>

struct FirstSecondTuple2_List;

struct First_List;

struct Second_List;

struct FirstListSecondListTuple2_;

typedef struct FirstListSecondListTuple2_(*VoidConstPtrFirstSecondTuple2_ListConstPtrFirstListSecondListTuple2_FunPtr2)(void const*, struct FirstSecondTuple2_List const*);

struct FirstSecondTuple2_ListFirstListSecondListTuple2_Fun1;

struct First_;

struct Second_;

struct Node_List;

struct Node_;

struct FirstSecondTuple2_;

struct IntThirdTuple2_List;

struct Third_;

struct IntThirdTuple2_;

struct Node_List;

struct IntThirdTuple2_List;

struct FirstListSecondListTuple2_ union_complicated_union_complicated_main_f(struct FirstSecondTuple2_List const* arg_2);

struct FirstListSecondListTuple2_ union_complicated_union_complicated_eta2_main_f(void const* env_, struct FirstSecondTuple2_List const* arg_);

struct FirstListSecondListTuple2_ union_complicated_union_complicated_eta2_main_f_1(void const* env_1, struct FirstSecondTuple2_List const* arg_1);

int main(int argc, char** argv);

struct FirstListSecondListTuple2_ {
    struct First_List const* t0;
    struct Second_List const* t1;
};

struct FirstSecondTuple2_ListFirstListSecondListTuple2_Fun1 {
    VoidConstPtrFirstSecondTuple2_ListConstPtrFirstListSecondListTuple2_FunPtr2 fun;
    void const* env;
};

enum First_Discriminant {
    First_,
};

struct First_ {
    enum First_Discriminant discriminant;
    union {
        struct FirstSecondTuple2_ListFirstListSecondListTuple2_Fun1 First_;
    };
};

enum Second_Discriminant {
    Second_,
};

struct Second_ {
    enum Second_Discriminant discriminant;
    union {
        struct FirstSecondTuple2_ListFirstListSecondListTuple2_Fun1 Second_;
    };
};

enum Node_Discriminant {
    Leaf_,
    Node_,
};

struct Node_ {
    enum Node_Discriminant discriminant;
    union {
        int Leaf_;
        struct Node_List const* Node_;
    };
};

struct FirstSecondTuple2_ {
    struct First_ t0;
    struct Second_ t1;
};

enum Third_Discriminant {
    Leaf3_,
    Node3_,
};

struct Third_ {
    enum Third_Discriminant discriminant;
    union {
        struct IntThirdTuple2_List const* Node3_;
    };
};

struct IntThirdTuple2_ {
    int t0;
    struct Third_ t1;
};

struct Node_List {
    struct Node_ head;
    struct Node_List const* tail;
};

struct IntThirdTuple2_List {
    struct IntThirdTuple2_ head;
    struct IntThirdTuple2_List const* tail;
};

struct FirstListSecondListTuple2_ union_complicated_union_complicated_main_f(struct FirstSecondTuple2_List const* arg_2) {
    struct FirstListSecondListTuple2_ FirstListSecondListTuple2_;
    FirstListSecondListTuple2_ = (struct FirstListSecondListTuple2_){.t0 = NULL, .t1 = NULL};
    return FirstListSecondListTuple2_;
}

struct FirstListSecondListTuple2_ union_complicated_union_complicated_eta2_main_f(void const* env_, struct FirstSecondTuple2_List const* arg_) {
    struct FirstListSecondListTuple2_ call_;
    call_ = union_complicated_union_complicated_main_f(arg_);
    return call_;
}

struct FirstListSecondListTuple2_ union_complicated_union_complicated_eta2_main_f_1(void const* env_1, struct FirstSecondTuple2_List const* arg_1) {
    struct FirstListSecondListTuple2_ call_1;
    call_1 = union_complicated_union_complicated_main_f(arg_1);
    return call_1;
}

int main(int argc, char** argv) {
    milone_start(argc, argv);
    int x_;
    int y_;
    int z_;
    struct First_ first_;
    struct Second_ second_;
    char match_;
    struct Node_List const* list_;
    struct Node_List const* list_1;
    struct Node_ variant_;
    struct Node_List const* list_2;
    struct Node_ variant_1;
    struct Node_ variant_2;
    struct Node_List const* list_3;
    struct Node_ variant_3;
    struct Node_List const* list_4;
    struct Node_List const* list_5;
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
    struct IntThirdTuple2_List const* list_6;
    struct IntThirdTuple2_ IntThirdTuple2_;
    variant_ = (struct Node_){.discriminant = Leaf_, .Leaf_ = 1};
    variant_1 = (struct Node_){.discriminant = Leaf_, .Leaf_ = 2};
    list_2 = ((struct Node_List const*)milone_region_alloc(1, sizeof(struct Node_List)));
    (*(((struct Node_List*)list_2))) = (struct Node_List){.head = variant_1, .tail = NULL};
    list_1 = ((struct Node_List const*)milone_region_alloc(1, sizeof(struct Node_List)));
    (*(((struct Node_List*)list_1))) = (struct Node_List){.head = variant_, .tail = list_2};
    variant_2 = (struct Node_){.discriminant = Node_, .Node_ = list_1};
    variant_3 = (struct Node_){.discriminant = Node_, .Node_ = NULL};
    variant_4 = (struct Node_){.discriminant = Leaf_, .Leaf_ = 3};
    list_5 = ((struct Node_List const*)milone_region_alloc(1, sizeof(struct Node_List)));
    (*(((struct Node_List*)list_5))) = (struct Node_List){.head = variant_4, .tail = NULL};
    variant_5 = (struct Node_){.discriminant = Node_, .Node_ = list_5};
    list_4 = ((struct Node_List const*)milone_region_alloc(1, sizeof(struct Node_List)));
    (*(((struct Node_List*)list_4))) = (struct Node_List){.head = variant_5, .tail = NULL};
    list_3 = ((struct Node_List const*)milone_region_alloc(1, sizeof(struct Node_List)));
    (*(((struct Node_List*)list_3))) = (struct Node_List){.head = variant_3, .tail = list_4};
    list_ = ((struct Node_List const*)milone_region_alloc(1, sizeof(struct Node_List)));
    (*(((struct Node_List*)list_))) = (struct Node_List){.head = variant_2, .tail = list_3};
    variant_6 = (struct Node_){.discriminant = Node_, .Node_ = list_};
    if ((variant_6.discriminant != Node_)) goto next_2;
    if ((!(variant_6.Node_))) goto next_2;
    if ((variant_6.Node_->head.discriminant != Node_)) goto next_2;
    if ((!(variant_6.Node_->head.Node_))) goto next_2;
    if ((variant_6.Node_->head.Node_->head.discriminant != Leaf_)) goto next_2;
    x_ = variant_6.Node_->head.Node_->head.Leaf_;
    if ((!(variant_6.Node_->head.Node_->tail))) goto next_2;
    if ((variant_6.Node_->head.Node_->tail->head.discriminant != Leaf_)) goto next_2;
    y_ = variant_6.Node_->head.Node_->tail->head.Leaf_;
    if ((!((!(variant_6.Node_->head.Node_->tail->tail))))) goto next_2;
    if ((!(variant_6.Node_->tail))) goto next_2;
    if ((variant_6.Node_->tail->head.discriminant != Node_)) goto next_2;
    if ((!((!(variant_6.Node_->tail->head.Node_))))) goto next_2;
    if ((!(variant_6.Node_->tail->tail))) goto next_2;
    if ((variant_6.Node_->tail->tail->head.discriminant != Node_)) goto next_2;
    if ((!(variant_6.Node_->tail->tail->head.Node_))) goto next_2;
    if ((variant_6.Node_->tail->tail->head.Node_->head.discriminant != Leaf_)) goto next_2;
    z_ = variant_6.Node_->tail->tail->head.Node_->head.Leaf_;
    if ((!((!(variant_6.Node_->tail->tail->head.Node_->tail))))) goto next_2;
    if ((!((!(variant_6.Node_->tail->tail->tail))))) goto next_2;
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
    milone_assert(if_1, (struct String){.ptr = "union_complicated/union_complicated.milone", .len = 42}, 23, 84);
    match_ = 0;
    goto end_match_1;
next_2:;
    milone_assert(false, (struct String){.ptr = "union_complicated/union_complicated.milone", .len = 42}, 24, 9);
    match_ = 0;
    goto end_match_1;
next_3:;
end_match_1:;
    fun_ = (struct FirstSecondTuple2_ListFirstListSecondListTuple2_Fun1){.fun = union_complicated_union_complicated_eta2_main_f, .env = NULL};
    variant_7 = (struct First_){.discriminant = First_, .First_ = fun_};
    fun_1 = (struct FirstSecondTuple2_ListFirstListSecondListTuple2_Fun1){.fun = union_complicated_union_complicated_eta2_main_f_1, .env = NULL};
    variant_8 = (struct Second_){.discriminant = Second_, .Second_ = fun_1};
    FirstSecondTuple2_ = (struct FirstSecondTuple2_){.t0 = variant_7, .t1 = variant_8};
    first_ = FirstSecondTuple2_.t0;
    second_ = FirstSecondTuple2_.t1;
    IntThirdTuple2_ = (struct IntThirdTuple2_){.t0 = 0, .t1 = (struct Third_){.discriminant = Leaf3_}};
    list_6 = ((struct IntThirdTuple2_List const*)milone_region_alloc(1, sizeof(struct IntThirdTuple2_List)));
    (*(((struct IntThirdTuple2_List*)list_6))) = (struct IntThirdTuple2_List){.head = IntThirdTuple2_, .tail = NULL};
    if ((!(list_6))) goto next_11;
    if ((list_6->head.t0 != 0)) goto next_11;
    if ((list_6->head.t1.discriminant != Leaf3_)) goto next_11;
    if ((!((!(list_6->tail))))) goto next_11;
    match_1 = 0;
    goto end_match_10;
next_11:;
    milone_assert(false, (struct String){.ptr = "union_complicated/union_complicated.milone", .len = 42}, 32, 9);
    match_1 = 0;
    goto end_match_10;
next_12:;
end_match_10:;
    return 0;
}
