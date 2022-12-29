#include <stdio.h>
#include <stdlib.h>
#include <milone.h>

struct StringInt32Tuple2_;

struct StringInt32Tuple2_ resolved_issues_generalization_issue_2_StringStringInt32Tuple2Fun1_tag1(struct String item_);

struct String resolved_issues_generalization_issue_2_StringInt32Tuple2StringFun1_untag(struct StringInt32Tuple2_ package_);

struct StringInt32Tuple2_ resolved_issues_generalization_issue_2_StringStringInt32Tuple2Fun1_tag2(struct String item_1);

void resolved_issues_generalization_issue_2_test(void);

void resolved_issues_generalization_issue_2_start(void);

struct StringInt32Tuple2_ {
    struct String t0;
    int32_t t1;
};

struct StringInt32Tuple2_ resolved_issues_generalization_issue_2_StringStringInt32Tuple2Fun1_tag1(struct String item_) {
    struct StringInt32Tuple2_ call_;
    call_ = resolved_issues_generalization_issue_2_StringStringInt32Tuple2Fun1_tag2(item_);
    return call_;
}

struct String resolved_issues_generalization_issue_2_StringInt32Tuple2StringFun1_untag(struct StringInt32Tuple2_ package_) {
    struct String item_2;
    item_2 = package_.t0;
    return item_2;
}

struct StringInt32Tuple2_ resolved_issues_generalization_issue_2_StringStringInt32Tuple2Fun1_tag2(struct String item_1) {
    struct StringInt32Tuple2_ StringInt32Tuple2_;
    StringInt32Tuple2_ = (struct StringInt32Tuple2_){.t0 = item_1, .t1 = 0};
    return StringInt32Tuple2_;
}

void resolved_issues_generalization_issue_2_test(void) {
    struct StringInt32Tuple2_ call_1;
    struct String call_2;
    call_1 = resolved_issues_generalization_issue_2_StringStringInt32Tuple2Fun1_tag1((struct String){.ptr = "anything", .len = 8});
    call_2 = resolved_issues_generalization_issue_2_StringInt32Tuple2StringFun1_untag(call_1);
    return;
}

void resolved_issues_generalization_issue_2_start(void) {
    resolved_issues_generalization_issue_2_test();
    return;
}
