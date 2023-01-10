#include <stdio.h>
#include <stdlib.h>
#include <milone.h>

typedef struct String(*VoidConstPtrStringStringStringFunPtr3)(void const *, struct String, struct String);

struct StringStringStringFun2;

struct StringCons;

struct StringCons;

struct String resolved_issues_generalization_issue_1_test_fun(struct String x_, struct String y_);

struct String resolved_issues_generalization_issue_1_eta3_test_fun(void const *env_, struct String arg_, struct String arg_1);

struct String MiloneCore_List_StringStringStringFun2StringStringListStringFun3_fold(struct StringStringStringFun2, struct String, struct StringCons const *);

void resolved_issues_generalization_issue_1_test(void);

void resolved_issues_generalization_issue_1_start(void);

struct StringStringStringFun2 {
    VoidConstPtrStringStringStringFunPtr3 fun;
    void const *env;
};

struct StringCons {
    struct String head;
    struct StringCons const *tail;
};

struct String resolved_issues_generalization_issue_1_test_fun(struct String x_, struct String y_) {
    return string_add(x_, y_);
}

struct String resolved_issues_generalization_issue_1_eta3_test_fun(void const *env_, struct String arg_, struct String arg_1) {
    struct String call_;
    call_ = resolved_issues_generalization_issue_1_test_fun(arg_, arg_1);
    return call_;
}

void resolved_issues_generalization_issue_1_test(void) {
    struct StringStringStringFun2 fun_;
    struct StringCons const *list_;
    struct StringCons const *list_1;
    struct StringCons const *list_2;
    struct String call_1;
    fun_ = (struct StringStringStringFun2){.fun = resolved_issues_generalization_issue_1_eta3_test_fun, .env = NULL};
    list_2 = ((struct StringCons const *)milone_region_alloc(1, sizeof(struct StringCons)));
    (*(((struct StringCons *)list_2))) = (struct StringCons){.head = (struct String){.ptr = "z", .len = 1}, .tail = NULL};
    list_1 = ((struct StringCons const *)milone_region_alloc(1, sizeof(struct StringCons)));
    (*(((struct StringCons *)list_1))) = (struct StringCons){.head = (struct String){.ptr = "y", .len = 1}, .tail = list_2};
    list_ = ((struct StringCons const *)milone_region_alloc(1, sizeof(struct StringCons)));
    (*(((struct StringCons *)list_))) = (struct StringCons){.head = (struct String){.ptr = "x", .len = 1}, .tail = list_1};
    call_1 = MiloneCore_List_StringStringStringFun2StringStringListStringFun3_fold(fun_, (struct String){.ptr = "", .len = 0}, list_);
    if ((string_compare(call_1, (struct String){.ptr = "xyz", .len = 3}) != 0)) milone_assert_error("resolved_issues/generalization_issue_1.milone", 11, 2);
    return;
}

void resolved_issues_generalization_issue_1_start(void) {
    resolved_issues_generalization_issue_1_test();
    return;
}
