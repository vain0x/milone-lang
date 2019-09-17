#include "milone.h"

enum First_Tag;

struct First_;

struct First_Second_Tuple2ListFirst_ListSecond_ListTuple2Fun1;

struct First_List;

enum Second_Tag;

struct Second_;

struct Second_List;

struct First_ListSecond_ListTuple2;

struct First_Second_Tuple2;

struct First_Second_Tuple2List;

struct First_ListSecond_ListTuple2 f_(struct First_Second_Tuple2List* __2);

struct First_ListSecond_ListTuple2 fun_(void* env_, struct First_Second_Tuple2List* arg_);

struct First_ListSecond_ListTuple2 fun_1(void* env_1, struct First_Second_Tuple2List* arg_1);

enum Node_Tag;

struct Node_;

struct Node_List;

int main();

enum First_Tag {
    First_,
};

struct First_ {
    enum First_Tag tag;
    union {
        struct First_Second_Tuple2ListFirst_ListSecond_ListTuple2Fun1* First_;
    };
};

struct First_Second_Tuple2ListFirst_ListSecond_ListTuple2Fun1 {
    struct First_ListSecond_ListTuple2(*fun)(void*, struct First_Second_Tuple2List*);
    void* env;
};

struct First_List {
    struct First_ head;
    struct First_List* tail;
};

enum Second_Tag {
    Second_,
};

struct Second_ {
    enum Second_Tag tag;
    union {
        struct First_Second_Tuple2ListFirst_ListSecond_ListTuple2Fun1* Second_;
    };
};

struct Second_List {
    struct Second_ head;
    struct Second_List* tail;
};

struct First_ListSecond_ListTuple2 {
    struct First_List* t0;
    struct Second_List* t1;
};

struct First_Second_Tuple2 {
    struct First_ t0;
    struct Second_ t1;
};

struct First_Second_Tuple2List {
    struct First_Second_Tuple2 head;
    struct First_Second_Tuple2List* tail;
};

struct First_ListSecond_ListTuple2 f_(struct First_Second_Tuple2List* __2) {
    struct First_ListSecond_ListTuple2 tuple_;
    tuple_.t0 = NULL;
    tuple_.t1 = NULL;
    return tuple_;
}

struct First_ListSecond_ListTuple2 fun_(void* env_, struct First_Second_Tuple2List* arg_) {
    struct First_ListSecond_ListTuple2 call_ = f_(arg_);
    return call_;
}

struct First_ListSecond_ListTuple2 fun_1(void* env_1, struct First_Second_Tuple2List* arg_1) {
    struct First_ListSecond_ListTuple2 call_1 = f_(arg_1);
    return call_1;
}

enum Node_Tag {
    Leaf_,
    Node_,
};

struct Node_ {
    enum Node_Tag tag;
    union {
        int* Leaf_;
        struct Node_List** Node_;
    };
};

struct Node_List {
    struct Node_ head;
    struct Node_List* tail;
};

int main() {
    int match_;
    int* payload_ = (int*)malloc(sizeof(int));
    (*(((int*)payload_))) = 1;
    struct Node_ variant_ = (struct Node_){.tag = Leaf_, .Leaf_ = payload_};
    int* payload_1 = (int*)malloc(sizeof(int));
    (*(((int*)payload_1))) = 2;
    struct Node_ variant_1 = (struct Node_){.tag = Leaf_, .Leaf_ = payload_1};
    struct Node_List* list_2 = (struct Node_List*)malloc(sizeof(struct Node_List));
    list_2->head = variant_1;
    list_2->tail = NULL;
    struct Node_List* list_1 = (struct Node_List*)malloc(sizeof(struct Node_List));
    list_1->head = variant_;
    list_1->tail = list_2;
    struct Node_List** payload_2 = (struct Node_List**)malloc(sizeof(struct Node_List*));
    (*(((struct Node_List**)payload_2))) = list_1;
    struct Node_ variant_2 = (struct Node_){.tag = Node_, .Node_ = payload_2};
    struct Node_List** payload_3 = (struct Node_List**)malloc(sizeof(struct Node_List*));
    (*(((struct Node_List**)payload_3))) = NULL;
    struct Node_ variant_3 = (struct Node_){.tag = Node_, .Node_ = payload_3};
    int* payload_4 = (int*)malloc(sizeof(int));
    (*(((int*)payload_4))) = 3;
    struct Node_ variant_4 = (struct Node_){.tag = Leaf_, .Leaf_ = payload_4};
    struct Node_List* list_5 = (struct Node_List*)malloc(sizeof(struct Node_List));
    list_5->head = variant_4;
    list_5->tail = NULL;
    struct Node_List** payload_5 = (struct Node_List**)malloc(sizeof(struct Node_List*));
    (*(((struct Node_List**)payload_5))) = list_5;
    struct Node_ variant_5 = (struct Node_){.tag = Node_, .Node_ = payload_5};
    struct Node_List* list_4 = (struct Node_List*)malloc(sizeof(struct Node_List));
    list_4->head = variant_5;
    list_4->tail = NULL;
    struct Node_List* list_3 = (struct Node_List*)malloc(sizeof(struct Node_List));
    list_3->head = variant_3;
    list_3->tail = list_4;
    struct Node_List* list_ = (struct Node_List*)malloc(sizeof(struct Node_List));
    list_->head = variant_2;
    list_->tail = list_3;
    struct Node_List** payload_6 = (struct Node_List**)malloc(sizeof(struct Node_List*));
    (*(((struct Node_List**)payload_6))) = list_;
    struct Node_ variant_6 = (struct Node_){.tag = Node_, .Node_ = payload_6};
    if (!((variant_6.tag == Node_))) goto next_2;
    if (!((!((!((*(variant_6.Node_)))))))) goto next_2;
    if (!(((*(variant_6.Node_))->head.tag == Node_))) goto next_2;
    if (!((!((!((*((*(variant_6.Node_))->head.Node_)))))))) goto next_2;
    if (!(((*((*(variant_6.Node_))->head.Node_))->head.tag == Leaf_))) goto next_2;
    int x_ = (*((*((*(variant_6.Node_))->head.Node_))->head.Leaf_));
    if (!((!((!((*((*(variant_6.Node_))->head.Node_))->tail)))))) goto next_2;
    if (!(((*((*(variant_6.Node_))->head.Node_))->tail->head.tag == Leaf_))) goto next_2;
    int y_ = (*((*((*(variant_6.Node_))->head.Node_))->tail->head.Leaf_));
    if (!((!((*((*(variant_6.Node_))->head.Node_))->tail->tail)))) goto next_2;
    if (!((!((!((*(variant_6.Node_))->tail)))))) goto next_2;
    if (!(((*(variant_6.Node_))->tail->head.tag == Node_))) goto next_2;
    if (!((!((*((*(variant_6.Node_))->tail->head.Node_)))))) goto next_2;
    if (!((!((!((*(variant_6.Node_))->tail->tail)))))) goto next_2;
    if (!(((*(variant_6.Node_))->tail->tail->head.tag == Node_))) goto next_2;
    if (!((!((!((*((*(variant_6.Node_))->tail->tail->head.Node_)))))))) goto next_2;
    if (!(((*((*(variant_6.Node_))->tail->tail->head.Node_))->head.tag == Leaf_))) goto next_2;
    int z_ = (*((*((*(variant_6.Node_))->tail->tail->head.Node_))->head.Leaf_));
    if (!((!((*((*(variant_6.Node_))->tail->tail->head.Node_))->tail)))) goto next_2;
    if (!((!((*(variant_6.Node_))->tail->tail->tail)))) goto next_2;
    int match_1;
    int match_2;
    if (!(((x_ == 1) == 1))) goto next_6;
    match_2 = (y_ == 2);
    goto end_match_5;
next_6:;
    if (!(((x_ == 1) == 0))) goto next_7;
    match_2 = 0;
    goto end_match_5;
next_7:;
    exit(1);
end_match_5:;
    if (!((match_2 == 1))) goto next_8;
    match_1 = (z_ == 3);
    goto end_match_4;
next_8:;
    if (!((match_2 == 0))) goto next_9;
    match_1 = 0;
    goto end_match_4;
next_9:;
    exit(1);
end_match_4:;
    milone_assert(match_1, 22, 4);
    int call_2 = 0;
    match_ = 0;
    goto end_match_1;
next_2:;
    milone_assert(0, 24, 4);
    int call_3 = 0;
    match_ = 0;
    goto end_match_1;
next_3:;
end_match_1:;
    void* box_ = (void*)malloc(sizeof(int));
    (*(((int*)box_))) = 0;
    void* env_2 = box_;
    struct First_Second_Tuple2ListFirst_ListSecond_ListTuple2Fun1 fun_2 = (struct First_Second_Tuple2ListFirst_ListSecond_ListTuple2Fun1){.fun = fun_, .env = env_2};
    struct First_Second_Tuple2ListFirst_ListSecond_ListTuple2Fun1* payload_7 = (struct First_Second_Tuple2ListFirst_ListSecond_ListTuple2Fun1*)malloc(sizeof(struct First_Second_Tuple2ListFirst_ListSecond_ListTuple2Fun1));
    (*(((struct First_Second_Tuple2ListFirst_ListSecond_ListTuple2Fun1*)payload_7))) = fun_2;
    struct First_ variant_7 = (struct First_){.tag = First_, .First_ = payload_7};
    void* box_1 = (void*)malloc(sizeof(int));
    (*(((int*)box_1))) = 0;
    void* env_3 = box_1;
    struct First_Second_Tuple2ListFirst_ListSecond_ListTuple2Fun1 fun_3 = (struct First_Second_Tuple2ListFirst_ListSecond_ListTuple2Fun1){.fun = fun_1, .env = env_3};
    struct First_Second_Tuple2ListFirst_ListSecond_ListTuple2Fun1* payload_8 = (struct First_Second_Tuple2ListFirst_ListSecond_ListTuple2Fun1*)malloc(sizeof(struct First_Second_Tuple2ListFirst_ListSecond_ListTuple2Fun1));
    (*(((struct First_Second_Tuple2ListFirst_ListSecond_ListTuple2Fun1*)payload_8))) = fun_3;
    struct Second_ variant_8 = (struct Second_){.tag = Second_, .Second_ = payload_8};
    struct First_Second_Tuple2 tuple_1;
    tuple_1.t0 = variant_7;
    tuple_1.t1 = variant_8;
    struct First_ first_ = tuple_1.t0;
    struct Second_ second_ = tuple_1.t1;
    return 0;
}
