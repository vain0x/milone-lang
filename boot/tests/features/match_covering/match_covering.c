struct BoolBoolTuple2;

struct IntList;

enum Node_Tag;

struct Node_;

struct Node_Node_Tuple2;

int main();

struct BoolBoolTuple2 {
    int t0;
    int t1;
};

struct IntList {
    int head;
    struct IntList* tail;
};

enum Node_Tag {
    Leaf_,
    Node_,
};

struct Node_ {
    enum Node_Tag tag;
    union {
        struct Node_Node_Tuple2* Node_;
    };
};

struct Node_Node_Tuple2 {
    struct Node_ t0;
    struct Node_ t1;
};

int main() {
    int match_;
    if (!((0 == 0))) goto next_2;
    match_ = 0;
    goto end_match_1;
next_2:;
    if (!((0 == 1))) goto next_3;
    milone_assert(0);
    int call_ = 0;
    match_ = 0;
    goto end_match_1;
next_3:;
end_match_1:;
    int match_1;
    struct BoolBoolTuple2 tuple_;
    tuple_.t0 = 0;
    tuple_.t1 = 1;
    if (!((tuple_.t0 == 0))) goto next_5;
    if (!((tuple_.t1 == 0))) goto next_5;
    milone_assert(0);
    int call_1 = 0;
    match_1 = 0;
    goto end_match_4;
next_5:;
    if (!((tuple_.t0 == 0))) goto next_6;
    if (!((tuple_.t1 == 1))) goto next_6;
    match_1 = 0;
    goto end_match_4;
next_6:;
    if (!((tuple_.t0 == 1))) goto next_7;
    if (!((tuple_.t1 == 0))) goto next_7;
    milone_assert(0);
    int call_2 = 0;
    match_1 = 0;
    goto end_match_4;
next_7:;
    if (!((tuple_.t0 == 1))) goto next_8;
    if (!((tuple_.t1 == 1))) goto next_8;
    milone_assert(0);
    int call_3 = 0;
    match_1 = 0;
    goto end_match_4;
next_8:;
end_match_4:;
    int match_2;
    struct IntList* list_1 = (struct IntList*)malloc(sizeof(struct IntList));
    list_1->head = 2;
    list_1->tail = NULL;
    struct IntList* list_ = (struct IntList*)malloc(sizeof(struct IntList));
    list_->head = 1;
    list_->tail = list_1;
    if (!((!(list_)))) goto next_10;
    match_2 = 0;
    goto end_match_9;
next_10:;
    if (!((!((!(list_)))))) goto next_11;
    match_2 = 0;
    goto end_match_9;
next_11:;
end_match_9:;
    int match_3;
    if (!(((struct Node_){.tag = Leaf_}.tag == Leaf_))) goto next_13;
    match_3 = 0;
    goto end_match_12;
next_13:;
    if (!(((struct Node_){.tag = Leaf_}.tag == Node_))) goto next_14;
    if (!(((*((struct Node_){.tag = Leaf_}.Node_)).t0.tag == Leaf_))) goto next_14;
    if (!(((*((struct Node_){.tag = Leaf_}.Node_)).t1.tag == Leaf_))) goto next_14;
    milone_assert(0);
    int call_4 = 0;
    match_3 = 0;
    goto end_match_12;
next_14:;
    if (!(((struct Node_){.tag = Leaf_}.tag == Node_))) goto next_15;
    if (!(((*((struct Node_){.tag = Leaf_}.Node_)).t0.tag == Node_))) goto next_15;
    if (!(((*((struct Node_){.tag = Leaf_}.Node_)).t1.tag == Leaf_))) goto next_15;
    milone_assert(0);
    int call_5 = 0;
    match_3 = 0;
    goto end_match_12;
next_15:;
    if (!(((struct Node_){.tag = Leaf_}.tag == Node_))) goto next_16;
    if (!(((*((struct Node_){.tag = Leaf_}.Node_)).t0.tag == Leaf_))) goto next_16;
    if (!(((*((struct Node_){.tag = Leaf_}.Node_)).t1.tag == Node_))) goto next_16;
    milone_assert(0);
    int call_6 = 0;
    match_3 = 0;
    goto end_match_12;
next_16:;
    if (!(((struct Node_){.tag = Leaf_}.tag == Node_))) goto next_17;
    if (!(((*((struct Node_){.tag = Leaf_}.Node_)).t0.tag == Node_))) goto next_17;
    if (!(((*((struct Node_){.tag = Leaf_}.Node_)).t1.tag == Node_))) goto next_17;
    milone_assert(0);
    int call_7 = 0;
    match_3 = 0;
    goto end_match_12;
next_17:;
end_match_12:;
    return 0;
}
