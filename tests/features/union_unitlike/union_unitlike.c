#include <stdio.h>
#include <stdlib.h>
#include <milone.h>

struct MyBool_;

struct Int32Cons;

struct RecordUsingMyUnit_;

struct Int32Cons;

void union_unitlike_union_unitlike_basicCase(void);

bool union_unitlike_union_unitlike_usedInOtherSumTypeCase_toBool(struct MyBool_ myBool_1);

void union_unitlike_union_unitlike_usedInOtherSumTypeCase(void);

void union_unitlike_union_unitlike_usedInRecordTypeCase(void);

int main(int argc, char **argv);

enum MyBool_Discriminant {
    MyBool_MyFalse,
    MyBool_MyTrue,
};

struct MyBool_ {
    enum MyBool_Discriminant discriminant;
    union {
        int32_t MyBool_MyFalse;
        int32_t MyBool_MyTrue;
    };
};

struct RecordUsingMyUnit_ {
    int32_t t0;
    struct Int32Cons const *t1;
};

struct Int32Cons {
    int32_t head;
    struct Int32Cons const *tail;
};

void union_unitlike_union_unitlike_basicCase(void) {
    int32_t myUnit_;
    char switch_;
    myUnit_ = 0;
    switch (myUnit_) {
        case 0:
            goto clause_2;

        default:
            milone_exhaust_error("union_unitlike/union_unitlike.milone", 11, 2);
    }
clause_2:;
    switch_ = 0;
    goto switch_next_1;
switch_next_1:;
    return;
}

bool union_unitlike_union_unitlike_usedInOtherSumTypeCase_toBool(struct MyBool_ myBool_1) {
    bool match_;
    if ((myBool_1.discriminant != MyBool_MyFalse)) goto next_4;
    if ((myBool_1.MyBool_MyFalse != 0)) goto next_4;
    match_ = false;
    goto end_match_3;
next_4:;
    if ((myBool_1.discriminant != MyBool_MyTrue)) goto next_5;
    if ((myBool_1.MyBool_MyTrue != 0)) goto next_5;
    match_ = true;
    goto end_match_3;
next_5:;
    milone_exhaust_error("union_unitlike/union_unitlike.milone", 23, 4);
end_match_3:;
    return match_;
}

void union_unitlike_union_unitlike_usedInOtherSumTypeCase(void) {
    struct MyBool_ myBool_;
    struct MyBool_ variant_;
    bool call_;
    variant_ = (struct MyBool_){.discriminant = MyBool_MyTrue, .MyBool_MyTrue = 0};
    myBool_ = variant_;
    call_ = union_unitlike_union_unitlike_usedInOtherSumTypeCase_toBool(myBool_);
    if ((!(call_))) milone_assert_error("union_unitlike/union_unitlike.milone", 27, 2);
    return;
}

void union_unitlike_union_unitlike_usedInRecordTypeCase(void) {
    struct RecordUsingMyUnit_ record_;
    struct RecordUsingMyUnit_ RecordUsingMyUnit_;
    struct Int32Cons const *list_;
    char match_1;
    list_ = ((struct Int32Cons const *)milone_region_alloc(1, sizeof(struct Int32Cons)));
    (*(((struct Int32Cons *)list_))) = (struct Int32Cons){.head = 0, .tail = NULL};
    RecordUsingMyUnit_ = (struct RecordUsingMyUnit_){.t0 = 0, .t1 = list_};
    record_ = RecordUsingMyUnit_;
    if ((!(record_.t1))) goto next_7;
    if ((record_.t1->head != 0)) goto next_7;
    if ((!((!(record_.t1->tail))))) goto next_7;
    match_1 = 0;
    goto end_match_6;
next_7:;
    if (true) milone_assert_error("union_unitlike/union_unitlike.milone", 37, 9);
    match_1 = 0;
    goto end_match_6;
next_8:;
end_match_6:;
    return;
}

int main(int argc, char **argv) {
    milone_start(argc, argv);
    union_unitlike_union_unitlike_basicCase();
    union_unitlike_union_unitlike_usedInOtherSumTypeCase();
    union_unitlike_union_unitlike_usedInRecordTypeCase();
    return 0;
}
