#include "milone.h"

int basicCase_(int arg_);

enum MyBool_Tag;

struct MyBool_;

int toBool_(struct MyBool_ myBool_1);

int usedInOtherSumTypeCase_(int arg_1);

struct ObjectList;

struct RecordUsingMyUnit_;

int usedInRecordTypeCase_(int arg_2);

int main();

int basicCase_(int arg_) {
    void* myUnit_ = 0;
    int match_;
    match_ = 0;
    goto end_match_1;
next_2:;
end_match_1:;
    return 0;
}

enum MyBool_Tag {
    MyFalse_,
    MyTrue_,
};

struct MyBool_ {
    enum MyBool_Tag tag;
    union {
        void* MyFalse_;
        void* MyTrue_;
    };
};

int toBool_(struct MyBool_ myBool_1) {
    int match_1;
    if ((myBool_1.tag != MyFalse_)) goto next_4;
    match_1 = 0;
    goto end_match_3;
next_4:;
    if ((myBool_1.tag != MyTrue_)) goto next_5;
    match_1 = 1;
    goto end_match_3;
next_5:;
    exit(1);
end_match_3:;
    return match_1;
}

int usedInOtherSumTypeCase_(int arg_1) {
    void* box_ = (void*)milone_mem_alloc(1, sizeof(int));
    (*(((int*)box_))) = 0;
    struct MyBool_ variant_ = (struct MyBool_){.tag = MyTrue_, .MyTrue_ = box_};
    struct MyBool_ myBool_ = variant_;
    int call_ = toBool_(myBool_);
    milone_assert(call_, 27, 2);
    int call_1 = 0;
    return 0;
}

struct ObjectList {
    void* head;
    struct ObjectList* tail;
};

struct RecordUsingMyUnit_ {
    void* First;
    struct ObjectList* Second;
};

int usedInRecordTypeCase_(int arg_2) {
    struct ObjectList* list_ = (struct ObjectList*)milone_mem_alloc(1, sizeof(struct ObjectList));
    list_->head = 0;
    list_->tail = NULL;
    struct RecordUsingMyUnit_ RecordUsingMyUnit_;
    RecordUsingMyUnit_.First = 0;
    RecordUsingMyUnit_.Second = list_;
    void* box_1 = (void*)milone_mem_alloc(1, sizeof(struct RecordUsingMyUnit_));
    (*(((struct RecordUsingMyUnit_*)box_1))) = RecordUsingMyUnit_;
    void* record_ = box_1;
    int match_2;
    if ((!((*(((struct RecordUsingMyUnit_*)record_))).Second))) goto next_7;
    if ((!((!((*(((struct RecordUsingMyUnit_*)record_))).Second->tail))))) goto next_7;
    match_2 = 0;
    goto end_match_6;
next_7:;
    milone_assert(0, 37, 9);
    int call_2 = 0;
    match_2 = 0;
    goto end_match_6;
next_8:;
end_match_6:;
    return 0;
}

int main() {
    int call_3 = basicCase_(0);
    int call_4 = usedInOtherSumTypeCase_(0);
    int call_5 = usedInRecordTypeCase_(0);
    return 0;
}
