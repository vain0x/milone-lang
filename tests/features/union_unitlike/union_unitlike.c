#include "milone.h"

int basicCase_(int arg_);

enum MyBool_Discriminant;

struct MyBool_;

bool toBool_(struct MyBool_ myBool_1);

int usedInOtherSumTypeCase_(int arg_1);

struct UnitList;

struct UnitList;

struct RecordUsingMyUnit_;

int usedInRecordTypeCase_(int arg_2);

int milone_main();

int basicCase_(int arg_) {
    int myUnit_ = 0;
    int match_;
    match_ = 0;
    goto end_match_1;
next_2:;
end_match_1:;
    return 0;
}

enum MyBool_Discriminant {
    MyFalse_,
    MyTrue_,
};

struct MyBool_ {
    enum MyBool_Discriminant discriminant;
    union {
        int MyFalse_;
        int MyTrue_;
    };
};

bool toBool_(struct MyBool_ myBool_1) {
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

int usedInOtherSumTypeCase_(int arg_1) {
    struct MyBool_ variant_ = (struct MyBool_){.discriminant = MyTrue_, .MyTrue_ = 0};
    struct MyBool_ myBool_ = variant_;
    bool call_ = toBool_(myBool_);
    milone_assert(call_, 27, 2);
    return 0;
}


struct UnitList {
    int head;
    struct UnitList const* tail;
};

struct RecordUsingMyUnit_ {
    int t0;
    struct UnitList const* t1;
};

int usedInRecordTypeCase_(int arg_2) {
    struct UnitList const* list_ = milone_mem_alloc(1, sizeof(struct UnitList));
    (*(((struct UnitList*)list_))) = (struct UnitList){.head = 0, .tail = NULL};
    struct RecordUsingMyUnit_ RecordUsingMyUnit_ = (struct RecordUsingMyUnit_){.t0 = 0, .t1 = list_};
    struct RecordUsingMyUnit_ record_ = RecordUsingMyUnit_;
    int match_2;
    if ((!(record_.t1))) goto next_7;
    if ((!((!(record_.t1->tail))))) goto next_7;
    match_2 = 0;
    goto end_match_6;
next_7:;
    milone_assert(false, 37, 9);
    match_2 = 0;
    goto end_match_6;
next_8:;
end_match_6:;
    return 0;
}

int milone_main() {
    int call_1 = basicCase_(0);
    int call_2 = usedInOtherSumTypeCase_(0);
    int call_3 = usedInRecordTypeCase_(0);
    return 0;
}
