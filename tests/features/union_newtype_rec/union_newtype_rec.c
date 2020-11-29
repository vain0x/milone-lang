#include "milone.h"

enum MyList_Tag;

struct MyList_;

struct MyList_List;

struct IntMyList_ListTuple2;

struct MyList_ myCons_(int head_, struct MyList_ tail_);

int main();

enum MyList_Tag {
    MyList_,
};

struct MyList_ {
    enum MyList_Tag tag;
    union {
        void* MyList_;
    };
};

struct MyList_List {
    struct MyList_ head;
    struct MyList_List* tail;
};

struct IntMyList_ListTuple2 {
    int t0;
    struct MyList_List* t1;
};

struct MyList_ myCons_(int head_, struct MyList_ tail_) {
    struct MyList_List* some_ = milone_mem_alloc(1, sizeof(struct MyList_List));
    some_->head = tail_;
    some_->tail = NULL;
    struct IntMyList_ListTuple2 tuple_;
    tuple_.t0 = head_;
    tuple_.t1 = some_;
    void* box_ = milone_mem_alloc(1, sizeof(struct IntMyList_ListTuple2));
    (*(((struct IntMyList_ListTuple2*)box_))) = tuple_;
    struct MyList_ variant_ = (struct MyList_){.tag = MyList_, .MyList_ = box_};
    return variant_;
}

int main() {
    struct IntMyList_ListTuple2 tuple_1;
    tuple_1.t0 = 0;
    tuple_1.t1 = NULL;
    void* box_1 = milone_mem_alloc(1, sizeof(struct IntMyList_ListTuple2));
    (*(((struct IntMyList_ListTuple2*)box_1))) = tuple_1;
    struct MyList_ variant_1 = (struct MyList_){.tag = MyList_, .MyList_ = box_1};
    struct MyList_ first_ = variant_1;
    struct MyList_ call_ = myCons_(1, first_);
    struct MyList_ second_ = call_;
    int match_;
    if (((*(((struct IntMyList_ListTuple2*)first_.MyList_))).t0 != 0)) goto next_2;
    if ((!((!((*(((struct IntMyList_ListTuple2*)first_.MyList_))).t1))))) goto next_2;
    match_ = 0;
    goto end_match_1;
next_2:;
    milone_assert(false, 14, 9);
    match_ = 0;
    goto end_match_1;
next_3:;
end_match_1:;
    int match_1;
    if ((!((*(((struct IntMyList_ListTuple2*)second_.MyList_))).t1))) goto next_5;
    int value_ = (*(((struct IntMyList_ListTuple2*)(*(((struct IntMyList_ListTuple2*)second_.MyList_))).t1->head.MyList_))).t0;
    if ((!((!((*(((struct IntMyList_ListTuple2*)second_.MyList_))).t1->tail))))) goto next_5;
    milone_assert((value_ == 0), 17, 44);
    match_1 = 0;
    goto end_match_4;
next_5:;
    milone_assert(false, 18, 9);
    match_1 = 0;
    goto end_match_4;
next_6:;
end_match_4:;
    return 0;
}
