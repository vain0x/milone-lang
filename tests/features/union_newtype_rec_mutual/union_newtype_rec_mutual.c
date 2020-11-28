#include "milone.h"

enum Odd_Tag;

struct Odd_;

struct Odd_List;

struct StringOdd_ListTuple2;

enum Even_Tag;

struct Even_;

struct Even_List;

struct IntEven_ListTuple2;

int main();

enum Odd_Tag {
    Odd_,
};

struct Odd_ {
    enum Odd_Tag tag;
    union {
        void* Odd_;
    };
};

struct Odd_List {
    struct Odd_ head;
    struct Odd_List* tail;
};

struct StringOdd_ListTuple2 {
    struct String t0;
    struct Odd_List* t1;
};

enum Even_Tag {
    Even_,
};

struct Even_ {
    enum Even_Tag tag;
    union {
        struct StringOdd_ListTuple2 Even_;
    };
};

struct Even_List {
    struct Even_ head;
    struct Even_List* tail;
};

struct IntEven_ListTuple2 {
    int t0;
    struct Even_List* t1;
};

int main() {
    struct IntEven_ListTuple2 tuple_;
    tuple_.t0 = 1;
    tuple_.t1 = NULL;
    void* box_ = (void*)milone_mem_alloc(1, sizeof(struct IntEven_ListTuple2));
    (*(((struct IntEven_ListTuple2*)box_))) = tuple_;
    struct Odd_ variant_ = (struct Odd_){.tag = Odd_, .Odd_ = box_};
    struct Odd_ one_ = variant_;
    struct Odd_List* some_ = (struct Odd_List*)milone_mem_alloc(1, sizeof(struct Odd_List));
    some_->head = one_;
    some_->tail = NULL;
    struct StringOdd_ListTuple2 tuple_1;
    tuple_1.t0 = (struct String){.str = "two", .len = 3};
    tuple_1.t1 = some_;
    struct Even_ variant_1 = (struct Even_){.tag = Even_, .Even_ = tuple_1};
    struct Even_ two_ = variant_1;
    struct Even_List* some_1 = (struct Even_List*)milone_mem_alloc(1, sizeof(struct Even_List));
    some_1->head = two_;
    some_1->tail = NULL;
    struct IntEven_ListTuple2 tuple_2;
    tuple_2.t0 = 3;
    tuple_2.t1 = some_1;
    void* box_1 = (void*)milone_mem_alloc(1, sizeof(struct IntEven_ListTuple2));
    (*(((struct IntEven_ListTuple2*)box_1))) = tuple_2;
    struct Odd_ variant_2 = (struct Odd_){.tag = Odd_, .Odd_ = box_1};
    struct Odd_ three_ = variant_2;
    struct Odd_List* some_2 = (struct Odd_List*)milone_mem_alloc(1, sizeof(struct Odd_List));
    some_2->head = three_;
    some_2->tail = NULL;
    struct StringOdd_ListTuple2 tuple_3;
    tuple_3.t0 = (struct String){.str = "four", .len = 4};
    tuple_3.t1 = some_2;
    struct Even_ variant_3 = (struct Even_){.tag = Even_, .Even_ = tuple_3};
    struct Even_ four_ = variant_3;
    int match_;
    struct String s4_ = four_.Even_.t0;
    if ((!(four_.Even_.t1))) goto next_2;
    int n3_ = (*(((struct IntEven_ListTuple2*)four_.Even_.t1->head.Odd_))).t0;
    if ((!((*(((struct IntEven_ListTuple2*)four_.Even_.t1->head.Odd_))).t1))) goto next_2;
    struct String s2_ = (*(((struct IntEven_ListTuple2*)four_.Even_.t1->head.Odd_))).t1->head.Even_.t0;
    if ((!((*(((struct IntEven_ListTuple2*)four_.Even_.t1->head.Odd_))).t1->head.Even_.t1))) goto next_2;
    int n1_ = (*(((struct IntEven_ListTuple2*)(*(((struct IntEven_ListTuple2*)four_.Even_.t1->head.Odd_))).t1->head.Even_.t1->head.Odd_))).t0;
    if ((!((!((*(((struct IntEven_ListTuple2*)(*(((struct IntEven_ListTuple2*)four_.Even_.t1->head.Odd_))).t1->head.Even_.t1->head.Odd_))).t1))))) goto next_2;
    if ((!((!((*(((struct IntEven_ListTuple2*)four_.Even_.t1->head.Odd_))).t1->head.Even_.t1->tail))))) goto next_2;
    if ((!((!((*(((struct IntEven_ListTuple2*)four_.Even_.t1->head.Odd_))).t1->tail))))) goto next_2;
    if ((!((!(four_.Even_.t1->tail))))) goto next_2;
    milone_assert((n1_ == 1), 15, 6);
    milone_assert((str_cmp(s2_, (struct String){.str = "two", .len = 3}) == 0), 16, 6);
    milone_assert((n3_ == 3), 17, 6);
    milone_assert((str_cmp(s4_, (struct String){.str = "four", .len = 4}) == 0), 18, 6);
    match_ = 0;
    goto end_match_1;
next_2:;
    milone_assert(false, 20, 9);
    match_ = 0;
    goto end_match_1;
next_3:;
end_match_1:;
    return 0;
}
