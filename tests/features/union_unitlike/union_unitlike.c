#include "milone.h"

enum MyUnit_Tag;

struct MyUnit_;

int basicCase_(int arg_);

enum MyBool_Tag;

struct MyBool_;

bool toBool_(struct MyBool_ myBool_1);

int usedInOtherSumTypeCase_(int arg_1);

struct MyUnit_List;

struct RecordUsingMyUnit_;

int usedInRecordTypeCase_(int arg_2);

int main();

enum MyUnit_Tag {
    MyUnit_,
};

struct MyUnit_ {
    enum MyUnit_Tag tag;
};

int basicCase_(int arg_) {
    struct MyUnit_ myUnit_ = (struct MyUnit_){.tag = MyUnit_};
    int switch_;
    switch (myUnit_.tag) {
        case MyUnit_:
            goto clause_2;

        default:
            exit(1);
    }
clause_2:;
    switch_ = 0;
    goto switch_next_1;
switch_next_1:;
    return 0;
}

enum MyBool_Tag {
    MyFalse_,
    MyTrue_,
};

struct MyBool_ {
    enum MyBool_Tag tag;
    union {
        struct MyUnit_ MyFalse_;
        struct MyUnit_ MyTrue_;
    };
};

bool toBool_(struct MyBool_ myBool_1) {
    bool switch_1;
    switch (myBool_1.tag) {
        case MyFalse_:
            goto clause_4;

        case MyTrue_:
            goto clause_5;

        default:
            exit(1);
    }
clause_4:;
    switch_1 = false;
    goto switch_next_3;
clause_5:;
    switch_1 = true;
    goto switch_next_3;
switch_next_3:;
    return switch_1;
}

int usedInOtherSumTypeCase_(int arg_1) {
    struct MyBool_ variant_ = (struct MyBool_){.tag = MyTrue_, .MyTrue_ = (struct MyUnit_){.tag = MyUnit_}};
    struct MyBool_ myBool_ = variant_;
    bool call_ = toBool_(myBool_);
    milone_assert(call_, 27, 2);
    return 0;
}

struct MyUnit_List {
    struct MyUnit_ head;
    struct MyUnit_List* tail;
};

struct RecordUsingMyUnit_ {
    struct MyUnit_ First;
    struct MyUnit_List* Second;
};

int usedInRecordTypeCase_(int arg_2) {
    struct MyUnit_List* list_ = milone_mem_alloc(1, sizeof(struct MyUnit_List));
    list_->head = (struct MyUnit_){.tag = MyUnit_};
    list_->tail = NULL;
    struct RecordUsingMyUnit_ RecordUsingMyUnit_;
    RecordUsingMyUnit_.First = (struct MyUnit_){.tag = MyUnit_};
    RecordUsingMyUnit_.Second = list_;
    struct RecordUsingMyUnit_ record_ = RecordUsingMyUnit_;
    int match_;
    if ((!(record_.Second))) goto next_7;
    if ((record_.Second->head.tag != MyUnit_)) goto next_7;
    if ((!((!(record_.Second->tail))))) goto next_7;
    match_ = 0;
    goto end_match_6;
next_7:;
    milone_assert(false, 37, 9);
    match_ = 0;
    goto end_match_6;
next_8:;
end_match_6:;
    return 0;
}

int main() {
    int call_1 = basicCase_(0);
    int call_2 = usedInOtherSumTypeCase_(0);
    int call_3 = usedInRecordTypeCase_(0);
    return 0;
}