#include "milone.h"

enum Node_Tag;

struct Node_;

struct Node_ leaf_(int n_);

struct Node_Node_Tuple2;

struct Node_ node_(struct Node_ l_, struct Node_ r_);

int main();

enum Node_Tag {
    Leaf_,
    Node_,
};

struct Node_ {
    enum Node_Tag tag;
    union {
        int* Leaf_;
        struct Node_Node_Tuple2* Node_;
    };
};

struct Node_ leaf_(int n_) {
    int* payload_ = (int*)milone_mem_alloc(1, sizeof(int));
    (*(((int*)payload_))) = n_;
    struct Node_ variant_ = (struct Node_){.tag = Leaf_, .Leaf_ = payload_};
    return variant_;
}

struct Node_Node_Tuple2 {
    struct Node_ t0;
    struct Node_ t1;
};

struct Node_ node_(struct Node_ l_, struct Node_ r_) {
    struct Node_Node_Tuple2 tuple_;
    tuple_.t0 = l_;
    tuple_.t1 = r_;
    struct Node_Node_Tuple2* payload_1 = (struct Node_Node_Tuple2*)milone_mem_alloc(1, sizeof(struct Node_Node_Tuple2));
    (*(((struct Node_Node_Tuple2*)payload_1))) = tuple_;
    struct Node_ variant_1 = (struct Node_){.tag = Node_, .Node_ = payload_1};
    return variant_1;
}

int main() {
    struct Node_ call_ = leaf_(2);
    struct Node_ call_1 = leaf_(3);
    struct Node_ call_2 = leaf_(5);
    struct Node_ call_3 = node_(call_1, call_2);
    struct Node_ call_4 = node_(call_, call_3);
    struct Node_ t_ = call_4;
    int match_;
    if ((t_.tag != Node_)) goto next_2;
    if (((*(t_.Node_)).t0.tag != Leaf_)) goto next_2;
    int x_ = (*((*(t_.Node_)).t0.Leaf_));
    milone_assert((x_ == 2), 26, 24);
    int call_5 = 0;
    match_ = 0;
    goto end_match_1;
next_2:;
    milone_assert(0, 27, 9);
    int call_6 = 0;
    match_ = 0;
    goto end_match_1;
next_3:;
end_match_1:;
    return 0;
}
