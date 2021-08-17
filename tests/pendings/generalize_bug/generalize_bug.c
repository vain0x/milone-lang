#include "milone.h"

struct UnitList;

struct UnitList;

void anotherFun_(void);

struct UnitList const* go_(struct UnitList const* acc_, struct UnitList const* pats_1);

struct UnitList const* doInferPats_(struct UnitList const* pats_);

void generalize_bug_Program_inferPat(void);

int milone_main(void);

struct UnitList {
    char head;
    struct UnitList const* tail;
};

void anotherFun_(void) {
    generalize_bug_Program_inferPat();
    return;
}

struct UnitList const* go_(struct UnitList const* acc_, struct UnitList const* pats_1) {
    struct UnitList const* pats_2;
    char pat_1;
tailrec_1:;
    struct UnitList const* match_;
    if ((!((!(pats_1))))) goto next_3;
    match_ = acc_;
    goto end_match_2;
next_3:;
    if ((!(pats_1))) goto next_4;
    pat_1 = pats_1->head;
    pats_2 = pats_1->tail;
    generalize_bug_Program_inferPat();
    char pat_2 = 0;
    struct UnitList const* list_ = milone_mem_alloc(1, sizeof(struct UnitList));
    (*(((struct UnitList*)list_))) = (struct UnitList){.head = 0, .tail = acc_};
    struct UnitList const* arg_ = list_;
    struct UnitList const* arg_1 = pats_2;
    acc_ = arg_;
    pats_1 = arg_1;
    goto tailrec_1;
next_4:;
    exit(1);
end_match_2:;
    return match_;
}

struct UnitList const* doInferPats_(struct UnitList const* pats_) {
    struct UnitList const* call_ = go_(NULL, pats_);
    return call_;
}

void generalize_bug_Program_inferPat(void) {
    return;
}

int milone_main(void) {
    struct UnitList const* call_1 = doInferPats_(NULL);
    return 0;
}
