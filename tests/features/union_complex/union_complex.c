#include "milone.h"

struct ObjectObjectTuple2;

struct ObjectObjectTuple2List;

struct ObjectList;

struct ObjectListObjectListTuple2;

struct ObjectListObjectListTuple2 f_(struct ObjectObjectTuple2List* arg_2);

struct ObjectListObjectListTuple2 fun_(void* env_, struct ObjectObjectTuple2List* arg_);

struct ObjectListObjectListTuple2 fun_1(void* env_1, struct ObjectObjectTuple2List* arg_1);

enum Node_Tag;

struct Node_;

struct Node_List;

struct ObjectObjectTuple2ListObjectListObjectListTuple2Fun1;

enum Third_Tag;

struct Third_;

struct IntThird_Tuple2;

struct IntThird_Tuple2List;

int main();

struct ObjectObjectTuple2 {
    void* t0;
    void* t1;
};

struct ObjectObjectTuple2List {
    struct ObjectObjectTuple2 head;
    struct ObjectObjectTuple2List* tail;
};

struct ObjectList {
    void* head;
    struct ObjectList* tail;
};

struct ObjectListObjectListTuple2 {
    struct ObjectList* t0;
    struct ObjectList* t1;
};

struct ObjectListObjectListTuple2 f_(struct ObjectObjectTuple2List* arg_2) {
    struct ObjectListObjectListTuple2 tuple_;
    tuple_.t0 = NULL;
    tuple_.t1 = NULL;
    return tuple_;
}

struct ObjectListObjectListTuple2 fun_(void* env_, struct ObjectObjectTuple2List* arg_) {
    struct ObjectListObjectListTuple2 call_ = f_(arg_);
    return call_;
}

struct ObjectListObjectListTuple2 fun_1(void* env_1, struct ObjectObjectTuple2List* arg_1) {
    struct ObjectListObjectListTuple2 call_1 = f_(arg_1);
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

struct ObjectObjectTuple2ListObjectListObjectListTuple2Fun1 {
    struct ObjectListObjectListTuple2(*fun)(void*, struct ObjectObjectTuple2List*);
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
    int if_;
    int if_1;
    if ((x_ == 1)) {
        goto then_6;
    } else {
        goto else_7;
    }
then_6:;
    if_1 = (y_ == 2);
    goto if_next_5;
else_7:;
    if_1 = 0;
    goto if_next_5;
if_next_5:;
    if (if_1) {
        goto then_8;
    } else {
        goto else_9;
    }
then_8:;
    if_ = (z_ == 3);
    goto if_next_4;
else_9:;
    if_ = 0;
    goto if_next_4;
if_next_4:;
    milone_assert(if_, 27, 4);
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
    struct ObjectObjectTuple2ListObjectListObjectListTuple2Fun1 fun_2 = (struct ObjectObjectTuple2ListObjectListObjectListTuple2Fun1){.fun = fun_, .env = env_2};
    void* box_8 = (void*)milone_mem_alloc(1, sizeof(struct ObjectObjectTuple2ListObjectListObjectListTuple2Fun1));
    (*(((struct ObjectObjectTuple2ListObjectListObjectListTuple2Fun1*)box_8))) = fun_2;
    void* box_9 = (void*)milone_mem_alloc(1, sizeof(int));
    (*(((int*)box_9))) = 0;
    void* env_3 = box_9;
    struct ObjectObjectTuple2ListObjectListObjectListTuple2Fun1 fun_3 = (struct ObjectObjectTuple2ListObjectListObjectListTuple2Fun1){.fun = fun_1, .env = env_3};
    void* box_10 = (void*)milone_mem_alloc(1, sizeof(struct ObjectObjectTuple2ListObjectListObjectListTuple2Fun1));
    (*(((struct ObjectObjectTuple2ListObjectListObjectListTuple2Fun1*)box_10))) = fun_3;
    struct ObjectObjectTuple2 tuple_1;
    tuple_1.t0 = box_8;
    tuple_1.t1 = box_10;
    void* first_ = tuple_1.t0;
    void* second_ = tuple_1.t1;
    int match_1;
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
    match_1 = 0;
    goto end_match_10;
next_11:;
    milone_assert(0, 37, 9);
    int call_4 = 0;
    match_1 = 0;
    goto end_match_10;
next_12:;
end_match_10:;
    return 0;
}
