#include "milone.h"

struct Node_;

struct Node_Node_Tuple2;

static struct Node_ leaf_(int n_);

static struct Node_ node_(struct Node_ l_, struct Node_ r_);

int milone_main();

enum Node_Discriminant {
    Leaf_,
    Node_,
};

struct Node_ {
    enum Node_Discriminant discriminant;
    union {
        int Leaf_;
        void const* Node_;
    };
};

struct Node_Node_Tuple2 {
    struct Node_ t0;
    struct Node_ t1;
};

static struct Node_ leaf_(int n_) {
    struct Node_ variant_ = (struct Node_){.discriminant = Leaf_, .Leaf_ = n_};
    return variant_;
}

static struct Node_ node_(struct Node_ l_, struct Node_ r_) {
    struct Node_Node_Tuple2 tuple_ = (struct Node_Node_Tuple2){.t0 = l_, .t1 = r_};
    void const* box_ = milone_mem_alloc(1, sizeof(struct Node_Node_Tuple2));
    (*(((struct Node_Node_Tuple2*)box_))) = tuple_;
    struct Node_ variant_1 = (struct Node_){.discriminant = Node_, .Node_ = box_};
    return variant_1;
}

int milone_main() {
    struct Node_ call_ = leaf_(2);
    struct Node_ call_1 = leaf_(3);
    struct Node_ call_2 = leaf_(5);
    struct Node_ call_3 = node_(call_1, call_2);
    struct Node_ call_4 = node_(call_, call_3);
    struct Node_ t_ = call_4;
    char match_;
    if ((t_.discriminant != Node_)) goto next_2;
    if (((*(((struct Node_Node_Tuple2 const*)t_.Node_))).t0.discriminant != Leaf_)) goto next_2;
    int x_ = (*(((struct Node_Node_Tuple2 const*)t_.Node_))).t0.Leaf_;
    milone_assert((x_ == 2), 22, 24);
    match_ = 0;
    goto end_match_1;
next_2:;
    milone_assert(false, 23, 9);
    match_ = 0;
    goto end_match_1;
next_3:;
end_match_1:;
    return 0;
}
