#include "milone.h"

enum Odd_Discriminant;

struct Odd_;

struct Odd_List;

struct StringOdd_ListTuple2;

enum Even_Discriminant;

struct Even_;

struct Even_List;

struct IntEven_ListTuple2;

int main();

enum Odd_Discriminant {
    Odd_,
};

struct Odd_ {
    enum Odd_Discriminant discriminant;
    union {
        void const* Odd_;
    };
};

struct Odd_List {
    struct Odd_ head;
    struct Odd_List const* tail;
};

struct StringOdd_ListTuple2 {
    struct String t0;
    struct Odd_List const* t1;
};

enum Even_Discriminant {
    Even_,
};

struct Even_ {
    enum Even_Discriminant discriminant;
    union {
        struct StringOdd_ListTuple2 Even_;
    };
};

struct Even_List {
    struct Even_ head;
    struct Even_List const* tail;
};

struct IntEven_ListTuple2 {
    int t0;
    struct Even_List const* t1;
};

int main() {
    struct IntEven_ListTuple2 tuple_ = (struct IntEven_ListTuple2){.t0 = 1, .t1 = NULL};
    void const* box_ = milone_mem_alloc(1, sizeof(struct IntEven_ListTuple2));
    (*(((struct IntEven_ListTuple2*)box_))) = tuple_;
    struct Odd_ variant_ = (struct Odd_){.discriminant = Odd_, .Odd_ = box_};
    struct Odd_ one_ = variant_;
    struct Odd_List const* some_ = milone_mem_alloc(1, sizeof(struct Odd_List));
    (*(((struct Odd_List*)some_))) = (struct Odd_List){.head = one_, .tail = NULL};
    struct StringOdd_ListTuple2 tuple_1 = (struct StringOdd_ListTuple2){.t0 = (struct String){.str = "two", .len = 3}, .t1 = some_};
    struct Even_ variant_1 = (struct Even_){.discriminant = Even_, .Even_ = tuple_1};
    struct Even_ two_ = variant_1;
    struct Even_List const* some_1 = milone_mem_alloc(1, sizeof(struct Even_List));
    (*(((struct Even_List*)some_1))) = (struct Even_List){.head = two_, .tail = NULL};
    struct IntEven_ListTuple2 tuple_2 = (struct IntEven_ListTuple2){.t0 = 3, .t1 = some_1};
    void const* box_1 = milone_mem_alloc(1, sizeof(struct IntEven_ListTuple2));
    (*(((struct IntEven_ListTuple2*)box_1))) = tuple_2;
    struct Odd_ variant_2 = (struct Odd_){.discriminant = Odd_, .Odd_ = box_1};
    struct Odd_ three_ = variant_2;
    struct Odd_List const* some_2 = milone_mem_alloc(1, sizeof(struct Odd_List));
    (*(((struct Odd_List*)some_2))) = (struct Odd_List){.head = three_, .tail = NULL};
    struct StringOdd_ListTuple2 tuple_3 = (struct StringOdd_ListTuple2){.t0 = (struct String){.str = "four", .len = 4}, .t1 = some_2};
    struct Even_ variant_3 = (struct Even_){.discriminant = Even_, .Even_ = tuple_3};
    struct Even_ four_ = variant_3;
    int match_;
    struct String s4_ = four_.Even_.t0;
    if ((!(four_.Even_.t1))) goto next_2;
    int n3_ = (*(((struct IntEven_ListTuple2 const*)four_.Even_.t1->head.Odd_))).t0;
    if ((!((*(((struct IntEven_ListTuple2 const*)four_.Even_.t1->head.Odd_))).t1))) goto next_2;
    struct String s2_ = (*(((struct IntEven_ListTuple2 const*)four_.Even_.t1->head.Odd_))).t1->head.Even_.t0;
    if ((!((*(((struct IntEven_ListTuple2 const*)four_.Even_.t1->head.Odd_))).t1->head.Even_.t1))) goto next_2;
    int n1_ = (*(((struct IntEven_ListTuple2 const*)(*(((struct IntEven_ListTuple2 const*)four_.Even_.t1->head.Odd_))).t1->head.Even_.t1->head.Odd_))).t0;
    if ((!((!((*(((struct IntEven_ListTuple2 const*)(*(((struct IntEven_ListTuple2 const*)four_.Even_.t1->head.Odd_))).t1->head.Even_.t1->head.Odd_))).t1))))) goto next_2;
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
