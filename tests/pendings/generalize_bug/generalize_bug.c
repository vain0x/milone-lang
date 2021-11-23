#include <milone.h>

struct Pat_;

struct Pat_List;

struct Pat_List;

struct UnitList;

struct Pat_ generalize_bug_generalize_bug_anotherFun(struct Pat_ pat_);

struct Pat_List const* generalize_bug_generalize_bug_doInferPats_go(struct Pat_List const* acc_, struct Pat_List const* pats_1);

struct Pat_List const* generalize_bug_generalize_bug_doInferPats(struct Pat_List const* pats_);

struct Pat_ generalize_bug_Program_inferPat(struct Pat_ pat_3);

int main(int argc, char** argv);

enum Pat_Discriminant {
    Pat_,
    OtherPat_,
};

struct Pat_ {
    enum Pat_Discriminant discriminant;
};

struct Pat_List {
    struct Pat_ head;
    struct Pat_List const* tail;
};

struct Pat_ generalize_bug_generalize_bug_anotherFun(struct Pat_ pat_) {
    struct Pat_ call_ = generalize_bug_Program_inferPat(pat_);
    return call_;
}

struct Pat_List const* generalize_bug_generalize_bug_doInferPats_go(struct Pat_List const* acc_, struct Pat_List const* pats_1) {
    struct Pat_List const* pats_2;
    struct Pat_ pat_1;
tailrec_1:;
    struct Pat_List const* match_;
    if ((!((!(pats_1))))) goto next_3;
    match_ = acc_;
    goto end_match_2;
next_3:;
    if ((!(pats_1))) goto next_4;
    pat_1 = pats_1->head;
    pats_2 = pats_1->tail;
    struct Pat_ call_1 = generalize_bug_Program_inferPat(pat_1);
    struct Pat_ pat_2 = call_1;
    struct Pat_List const* list_ = milone_mem_alloc(1, sizeof(struct Pat_List));
    (*(((struct Pat_List*)list_))) = (struct Pat_List){.head = pat_2, .tail = acc_};
    struct Pat_List const* arg_ = list_;
    struct Pat_List const* arg_1 = pats_2;
    acc_ = arg_;
    pats_1 = arg_1;
    goto tailrec_1;
next_4:;
    exit(1);
end_match_2:;
    return match_;
}

struct Pat_List const* generalize_bug_generalize_bug_doInferPats(struct Pat_List const* pats_) {
    struct Pat_List const* call_2 = generalize_bug_generalize_bug_doInferPats_go(NULL, pats_);
    return call_2;
}

struct Pat_ generalize_bug_Program_inferPat(struct Pat_ pat_3) {
    return pat_3;
}

int main(int argc, char** argv) {
    milone_start(argc, argv);
    struct Pat_List const* list_1 = milone_mem_alloc(1, sizeof(struct Pat_List));
    (*(((struct Pat_List*)list_1))) = (struct Pat_List){.head = (struct Pat_){.discriminant = Pat_}, .tail = NULL};
    struct UnitList const* call_3 = generalize_bug_generalize_bug_doInferPats(list_1);
    return 0;
}
