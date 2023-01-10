#include <stdio.h>
#include <stdlib.h>
#include <milone.h>

struct Int32Cons;

struct Int32Cons;

int32_t resolved_issues_generalization_issue_3_anotherFun(int32_t pat_);

struct Int32Cons const *resolved_issues_generalization_issue_3_doInferPats_go(struct Int32Cons const *acc_, struct Int32Cons const *pats_1);

struct Int32Cons const *resolved_issues_generalization_issue_3_doInferPats(struct Int32Cons const *pats_);

int32_t resolved_issues_generalization_issue_3_inferPat(int32_t pat_3);

void resolved_issues_generalization_issue_3_test(void);

void resolved_issues_generalization_issue_3_start(void);

struct Int32Cons {
    int32_t head;
    struct Int32Cons const *tail;
};

int32_t resolved_issues_generalization_issue_3_anotherFun(int32_t pat_) {
    int32_t call_;
    call_ = resolved_issues_generalization_issue_3_inferPat(pat_);
    return call_;
}

struct Int32Cons const *resolved_issues_generalization_issue_3_doInferPats_go(struct Int32Cons const *acc_, struct Int32Cons const *pats_1) {
    int32_t pat_1;
    struct Int32Cons const *pats_2;
    int32_t pat_2;
    struct Int32Cons const *match_;
    int32_t call_1;
    struct Int32Cons const *list_;
    struct Int32Cons const *arg_;
    struct Int32Cons const *arg_1;
tailrec_1:;
    if ((!((!(pats_1))))) goto next_3;
    match_ = acc_;
    goto end_match_2;
next_3:;
    if ((!(pats_1))) goto next_4;
    pat_1 = pats_1->head;
    pats_2 = pats_1->tail;
    call_1 = resolved_issues_generalization_issue_3_inferPat(pat_1);
    pat_2 = call_1;
    list_ = ((struct Int32Cons const *)milone_region_alloc(1, sizeof(struct Int32Cons)));
    (*(((struct Int32Cons *)list_))) = (struct Int32Cons){.head = pat_2, .tail = acc_};
    arg_ = list_;
    arg_1 = pats_2;
    acc_ = arg_;
    pats_1 = arg_1;
    goto tailrec_1;
next_4:;
    milone_exhaust_error("resolved_issues/generalization_issue_3.milone", 13, 4);
end_match_2:;
    return match_;
}

struct Int32Cons const *resolved_issues_generalization_issue_3_doInferPats(struct Int32Cons const *pats_) {
    struct Int32Cons const *call_2;
    call_2 = resolved_issues_generalization_issue_3_doInferPats_go(NULL, pats_);
    return call_2;
}

int32_t resolved_issues_generalization_issue_3_inferPat(int32_t pat_3) {
    return pat_3;
}

void resolved_issues_generalization_issue_3_test(void) {
    struct Int32Cons const *list_1;
    struct Int32Cons const *call_3;
    list_1 = ((struct Int32Cons const *)milone_region_alloc(1, sizeof(struct Int32Cons)));
    (*(((struct Int32Cons *)list_1))) = (struct Int32Cons){.head = 0, .tail = NULL};
    call_3 = resolved_issues_generalization_issue_3_doInferPats(list_1);
    return;
}

void resolved_issues_generalization_issue_3_start(void) {
    resolved_issues_generalization_issue_3_test();
    return;
}
