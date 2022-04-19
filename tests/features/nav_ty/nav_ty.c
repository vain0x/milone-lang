#include <stdio.h>
#include <stdlib.h>
#include <milone.h>

struct Node_;

struct NodeNodeTuple2_;

struct Node_ nav_ty_nav_ty_main_leaf(int32_t n_);

struct Node_ nav_ty_nav_ty_main_node(struct Node_ l_, struct Node_ r_);

int main(int argc, char** argv);

enum Node_Discriminant {
    Leaf_,
    Node_,
};

struct Node_ {
    enum Node_Discriminant discriminant;
    union {
        int32_t Leaf_;
        void const* Node_;
    };
};

struct NodeNodeTuple2_ {
    struct Node_ t0;
    struct Node_ t1;
};

struct Node_ nav_ty_nav_ty_main_leaf(int32_t n_) {
    struct Node_ variant_;
    variant_ = (struct Node_){.discriminant = Leaf_, .Leaf_ = n_};
    return variant_;
}

struct Node_ nav_ty_nav_ty_main_node(struct Node_ l_, struct Node_ r_) {
    struct NodeNodeTuple2_ NodeNodeTuple2_;
    void const* box_;
    struct Node_ variant_1;
    NodeNodeTuple2_ = (struct NodeNodeTuple2_){.t0 = l_, .t1 = r_};
    box_ = ((void const*)milone_region_alloc(1, sizeof(struct NodeNodeTuple2_)));
    (*(((struct NodeNodeTuple2_*)box_))) = NodeNodeTuple2_;
    variant_1 = (struct Node_){.discriminant = Node_, .Node_ = box_};
    return variant_1;
}

int main(int argc, char** argv) {
    milone_start(argc, argv);
    struct Node_ t_;
    int32_t x_;
    struct Node_ call_;
    struct Node_ call_1;
    struct Node_ call_2;
    struct Node_ call_3;
    struct Node_ call_4;
    char match_;
    call_ = nav_ty_nav_ty_main_leaf(2);
    call_1 = nav_ty_nav_ty_main_leaf(3);
    call_2 = nav_ty_nav_ty_main_leaf(5);
    call_3 = nav_ty_nav_ty_main_node(call_1, call_2);
    call_4 = nav_ty_nav_ty_main_node(call_, call_3);
    t_ = call_4;
    if ((t_.discriminant != Node_)) goto next_2;
    if (((*(((struct NodeNodeTuple2_ const*)t_.Node_))).t0.discriminant != Leaf_)) goto next_2;
    x_ = (*(((struct NodeNodeTuple2_ const*)t_.Node_))).t0.Leaf_;
    milone_assert((x_ == 2), (struct String){.ptr = "nav_ty/nav_ty.milone", .len = 20}, 22, 24);
    match_ = 0;
    goto end_match_1;
next_2:;
    milone_assert(false, (struct String){.ptr = "nav_ty/nav_ty.milone", .len = 20}, 23, 9);
    match_ = 0;
    goto end_match_1;
next_3:;
end_match_1:;
    return 0;
}
