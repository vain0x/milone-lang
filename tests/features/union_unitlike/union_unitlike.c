#include <milone.h>

struct MyBool_;

struct UnitList;

struct RecordUsingMyUnit_;

struct UnitList;

void union_unitlike_union_unitlike_basicCase(void);

bool union_unitlike_union_unitlike_usedInOtherSumTypeCase_toBool(struct MyBool_ myBool_1);

void union_unitlike_union_unitlike_usedInOtherSumTypeCase(void);

void union_unitlike_union_unitlike_usedInRecordTypeCase(void);

int main(int argc, char** argv);

enum MyBool_Discriminant {
    MyFalse_,
    MyTrue_,
};

struct MyBool_ {
    enum MyBool_Discriminant discriminant;
    union {
        char MyFalse_;
        char MyTrue_;
    };
};

struct RecordUsingMyUnit_ {
    char t0;
    struct UnitList const* t1;
};

struct UnitList {
    char head;
    struct UnitList const* tail;
};

void union_unitlike_union_unitlike_basicCase(void) {
    char myUnit_;
    char match_;
    myUnit_ = 0;
    match_ = 0;
    goto end_match_1;
next_2:;
end_match_1:;
    return;
}

bool union_unitlike_union_unitlike_usedInOtherSumTypeCase_toBool(struct MyBool_ myBool_1) {
    bool match_1;
    if ((myBool_1.discriminant != MyFalse_)) goto next_4;
    match_1 = false;
    goto end_match_3;
next_4:;
    if ((myBool_1.discriminant != MyTrue_)) goto next_5;
    match_1 = true;
    goto end_match_3;
next_5:;
    exit(1);
end_match_3:;
    return match_1;
}

void union_unitlike_union_unitlike_usedInOtherSumTypeCase(void) {
    struct MyBool_ myBool_;
    struct MyBool_ variant_;
    bool call_;
    variant_ = (struct MyBool_){.discriminant = MyTrue_, .MyTrue_ = 0};
    myBool_ = variant_;
    call_ = union_unitlike_union_unitlike_usedInOtherSumTypeCase_toBool(myBool_);
    milone_assert(call_, (struct String){.str = "union_unitlike/union_unitlike.milone", .len = 36}, 27, 2);
    return;
}

void union_unitlike_union_unitlike_usedInRecordTypeCase(void) {
    struct RecordUsingMyUnit_ record_;
    struct RecordUsingMyUnit_ RecordUsingMyUnit_;
    struct UnitList const* list_;
    char match_2;
    list_ = ((struct UnitList const*)milone_mem_alloc(1, sizeof(struct UnitList)));
    (*(((struct UnitList*)list_))) = (struct UnitList){.head = 0, .tail = NULL};
    RecordUsingMyUnit_ = (struct RecordUsingMyUnit_){.t0 = 0, .t1 = list_};
    record_ = RecordUsingMyUnit_;
    if ((!(record_.t1))) goto next_7;
    if ((!((!(record_.t1->tail))))) goto next_7;
    match_2 = 0;
    goto end_match_6;
next_7:;
    milone_assert(false, (struct String){.str = "union_unitlike/union_unitlike.milone", .len = 36}, 37, 9);
    match_2 = 0;
    goto end_match_6;
next_8:;
end_match_6:;
    return;
}

int main(int argc, char** argv) {
    milone_start(argc, argv);
    union_unitlike_union_unitlike_basicCase();
    union_unitlike_union_unitlike_usedInOtherSumTypeCase();
    union_unitlike_union_unitlike_usedInRecordTypeCase();
    return 0;
}
