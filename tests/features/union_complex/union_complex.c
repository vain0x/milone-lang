#include "milone.h"

enum First_Tag;

struct First_;

enum Second_Tag;

struct Second_;

struct First_Second_Tuple2;

struct First_Second_Tuple2List;

struct First_List;

struct Second_List;

struct First_ListSecond_ListTuple2;

struct First_ListSecond_ListTuple2 f_(struct First_Second_Tuple2List* arg_2);

struct First_ListSecond_ListTuple2 fun_(void* env_, struct First_Second_Tuple2List* arg_);

struct First_ListSecond_ListTuple2 fun_1(void* env_1, struct First_Second_Tuple2List* arg_1);

enum Node_Tag;

struct Node_;

struct Node_List;

struct First_Second_Tuple2ListFirst_ListSecond_ListTuple2Fun1;

enum Third_Tag;

struct Third_;

struct IntThird_Tuple2;

struct IntThird_Tuple2List;

int main();

enum First_Tag {
    First_,
};

struct First_ {
    enum First_Tag tag;
    union {
        void* First_;
    };
};

enum Second_Tag {
    Second_,
};

struct Second_ {
    enum Second_Tag tag;
    union {
        void* Second_;
    };
};

struct First_Second_Tuple2 {
    struct First_ t0;
    struct Second_ t1;
};

struct First_Second_Tuple2List {
    struct First_Second_Tuple2 head;
    struct First_Second_Tuple2List* tail;
};

struct First_List {
    struct First_ head;
    struct First_List* tail;
};

struct Second_List {
    struct Second_ head;
    struct Second_List* tail;
};

struct First_ListSecond_ListTuple2 {
    struct First_List* t0;
    struct Second_List* t1;
};

struct First_ListSecond_ListTuple2 f_(struct First_Second_Tuple2List* arg_2) {
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
        void* Leaf_;
        void* Node_;
    };
};

struct Node_List {
    struct Node_ head;
    struct Node_List* tail;
};

struct First_Second_Tuple2ListFirst_ListSecond_ListTuple2Fun1 {
    struct First_ListSecond_ListTuple2(*fun)(void*, struct First_Second_Tuple2List*);
    void* env;
};

enum Third_Tag {
    Leaf3_,
    Node3_,
};

struct Third_ {
    enum Third_Tag tag;
    union {
        void* Node3_;
    };
};

struct IntThird_Tuple2 {
    int t0;
    struct Third_ t1;
};

struct IntThird_Tuple2List {
    struct IntThird_Tuple2 head;
    struct IntThird_Tuple2List* tail;
};

int main() {
    int match_;
    void* box_ = (void*)milone_mem_alloc(1, sizeof(int));
    (*(((int*)box_))) = 1;
    struct Node_ variant_ = (struct Node_){.tag = Leaf_, .Leaf_ = box_};
    void* box_1 = (void*)milone_mem_alloc(1, sizeof(int));
    (*(((int*)box_1))) = 2;
    struct Node_ variant_1 = (struct Node_){.tag = Leaf_, .Leaf_ = box_1};
    struct Node_List* list_2 = (struct Node_List*)milone_mem_alloc(1, sizeof(struct Node_List));
    list_2->head = variant_1;
    list_2->tail = NULL;
    struct Node_List* list_1 = (struct Node_List*)milone_mem_alloc(1, sizeof(struct Node_List));
    list_1->head = variant_;
    list_1->tail = list_2;
    void* box_2 = (void*)milone_mem_alloc(1, sizeof(struct Node_List*));
    (*(((struct Node_List**)box_2))) = list_1;
    struct Node_ variant_2 = (struct Node_){.tag = Node_, .Node_ = box_2};
    void* box_3 = (void*)milone_mem_alloc(1, sizeof(struct Node_List*));
    (*(((struct Node_List**)box_3))) = NULL;
    struct Node_ variant_3 = (struct Node_){.tag = Node_, .Node_ = box_3};
    void* box_4 = (void*)milone_mem_alloc(1, sizeof(int));
    (*(((int*)box_4))) = 3;
    struct Node_ variant_4 = (struct Node_){.tag = Leaf_, .Leaf_ = box_4};
    struct Node_List* list_5 = (struct Node_List*)milone_mem_alloc(1, sizeof(struct Node_List));
    list_5->head = variant_4;
    list_5->tail = NULL;
    void* box_5 = (void*)milone_mem_alloc(1, sizeof(struct Node_List*));
    (*(((struct Node_List**)box_5))) = list_5;
    struct Node_ variant_5 = (struct Node_){.tag = Node_, .Node_ = box_5};
    struct Node_List* list_4 = (struct Node_List*)milone_mem_alloc(1, sizeof(struct Node_List));
    list_4->head = variant_5;
    list_4->tail = NULL;
    struct Node_List* list_3 = (struct Node_List*)milone_mem_alloc(1, sizeof(struct Node_List));
    list_3->head = variant_3;
    list_3->tail = list_4;
    struct Node_List* list_ = (struct Node_List*)milone_mem_alloc(1, sizeof(struct Node_List));
    list_->head = variant_2;
    list_->tail = list_3;
    void* box_6 = (void*)milone_mem_alloc(1, sizeof(struct Node_List*));
    (*(((struct Node_List**)box_6))) = list_;
    struct Node_ variant_6 = (struct Node_){.tag = Node_, .Node_ = box_6};
    if ((variant_6.tag != Node_)) goto next_2;
    if ((!((*(((struct Node_List**)variant_6.Node_)))))) goto next_2;
    if (((*(((struct Node_List**)variant_6.Node_)))->head.tag != Node_)) goto next_2;
    if ((!((*(((struct Node_List**)(*(((struct Node_List**)variant_6.Node_)))->head.Node_)))))) goto next_2;
    if (((*(((struct Node_List**)(*(((struct Node_List**)variant_6.Node_)))->head.Node_)))->head.tag != Leaf_)) goto next_2;
    int x_ = (*(((int*)(*(((struct Node_List**)(*(((struct Node_List**)variant_6.Node_)))->head.Node_)))->head.Leaf_)));
    if ((!((*(((struct Node_List**)(*(((struct Node_List**)variant_6.Node_)))->head.Node_)))->tail))) goto next_2;
    if (((*(((struct Node_List**)(*(((struct Node_List**)variant_6.Node_)))->head.Node_)))->tail->head.tag != Leaf_)) goto next_2;
    int y_ = (*(((int*)(*(((struct Node_List**)(*(((struct Node_List**)variant_6.Node_)))->head.Node_)))->tail->head.Leaf_)));
    if ((!((!((*(((struct Node_List**)(*(((struct Node_List**)variant_6.Node_)))->head.Node_)))->tail->tail))))) goto next_2;
    if ((!((*(((struct Node_List**)variant_6.Node_)))->tail))) goto next_2;
    if (((*(((struct Node_List**)variant_6.Node_)))->tail->head.tag != Node_)) goto next_2;
    if ((!((!((*(((struct Node_List**)(*(((struct Node_List**)variant_6.Node_)))->tail->head.Node_)))))))) goto next_2;
    if ((!((*(((struct Node_List**)variant_6.Node_)))->tail->tail))) goto next_2;
    if (((*(((struct Node_List**)variant_6.Node_)))->tail->tail->head.tag != Node_)) goto next_2;
    if ((!((*(((struct Node_List**)(*(((struct Node_List**)variant_6.Node_)))->tail->tail->head.Node_)))))) goto next_2;
    if (((*(((struct Node_List**)(*(((struct Node_List**)variant_6.Node_)))->tail->tail->head.Node_)))->head.tag != Leaf_)) goto next_2;
    int z_ = (*(((int*)(*(((struct Node_List**)(*(((struct Node_List**)variant_6.Node_)))->tail->tail->head.Node_)))->head.Leaf_)));
    if ((!((!((*(((struct Node_List**)(*(((struct Node_List**)variant_6.Node_)))->tail->tail->head.Node_)))->tail))))) goto next_2;
    if ((!((!((*(((struct Node_List**)variant_6.Node_)))->tail->tail->tail))))) goto next_2;
    int match_1;
    int match_2;
    if ((x_ != 1)) goto next_6;
    match_2 = (y_ == 2);
    goto end_match_5;
next_6:;
    if ((x_ == 1)) goto next_7;
    match_2 = 0;
    goto end_match_5;
next_7:;
    exit(1);
end_match_5:;
    if ((!(match_2))) goto next_8;
    match_1 = (z_ == 3);
    goto end_match_4;
next_8:;
    if (match_2) goto next_9;
    match_1 = 0;
    goto end_match_4;
next_9:;
    exit(1);
end_match_4:;
    milone_assert(match_1, 27, 4);
    int call_2 = 0;
    match_ = 0;
    goto end_match_1;
next_2:;
    milone_assert(0, 29, 4);
    int call_3 = 0;
    match_ = 0;
    goto end_match_1;
next_3:;
end_match_1:;
    void* box_7 = (void*)milone_mem_alloc(1, sizeof(int));
    (*(((int*)box_7))) = 0;
    void* env_2 = box_7;
    struct First_Second_Tuple2ListFirst_ListSecond_ListTuple2Fun1 fun_2 = (struct First_Second_Tuple2ListFirst_ListSecond_ListTuple2Fun1){.fun = fun_, .env = env_2};
    void* box_8 = (void*)milone_mem_alloc(1, sizeof(struct First_Second_Tuple2ListFirst_ListSecond_ListTuple2Fun1));
    (*(((struct First_Second_Tuple2ListFirst_ListSecond_ListTuple2Fun1*)box_8))) = fun_2;
    struct First_ variant_7 = (struct First_){.tag = First_, .First_ = box_8};
    void* box_9 = (void*)milone_mem_alloc(1, sizeof(int));
    (*(((int*)box_9))) = 0;
    void* env_3 = box_9;
    struct First_Second_Tuple2ListFirst_ListSecond_ListTuple2Fun1 fun_3 = (struct First_Second_Tuple2ListFirst_ListSecond_ListTuple2Fun1){.fun = fun_1, .env = env_3};
    void* box_10 = (void*)milone_mem_alloc(1, sizeof(struct First_Second_Tuple2ListFirst_ListSecond_ListTuple2Fun1));
    (*(((struct First_Second_Tuple2ListFirst_ListSecond_ListTuple2Fun1*)box_10))) = fun_3;
    struct Second_ variant_8 = (struct Second_){.tag = Second_, .Second_ = box_10};
    struct First_Second_Tuple2 tuple_1;
    tuple_1.t0 = variant_7;
    tuple_1.t1 = variant_8;
    struct First_ first_ = tuple_1.t0;
    struct Second_ second_ = tuple_1.t1;
    int match_3;
    struct IntThird_Tuple2 tuple_2;
    tuple_2.t0 = 0;
    tuple_2.t1 = (struct Third_){.tag = Leaf3_};
    struct IntThird_Tuple2List* list_6 = (struct IntThird_Tuple2List*)milone_mem_alloc(1, sizeof(struct IntThird_Tuple2List));
    list_6->head = tuple_2;
    list_6->tail = NULL;
    if ((!(list_6))) goto next_11;
    if ((list_6->head.t0 != 0)) goto next_11;
    if ((list_6->head.t1.tag != Leaf3_)) goto next_11;
    if ((!((!(list_6->tail))))) goto next_11;
    match_3 = 0;
    goto end_match_10;
next_11:;
    milone_assert(0, 37, 9);
    int call_4 = 0;
    match_3 = 0;
    goto end_match_10;
next_12:;
end_match_10:;
    return 0;
}