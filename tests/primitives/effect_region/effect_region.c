#include <milone.h>

struct IntList;

struct IntList;

typedef int(*VoidConstPtrIntFunPtr1)(void const*);

struct UnitIntFun1;

struct IntList const* effect_region_effect_region_doAction_fun_go(struct IntList const* acc_, int i_);

int effect_region_effect_region_doAction_fun(void);

int effect_region_effect_region_eta2_doAction_fun(void const* env_);

int effect_region_effect_region_doAction(void);

int main(int argc, char** argv);

struct IntList {
    int head;
    struct IntList const* tail;
};

struct UnitIntFun1 {
    VoidConstPtrIntFunPtr1 fun;
    void const* env;
};

struct IntList const* effect_region_effect_region_doAction_fun_go(struct IntList const* acc_, int i_) {
tailrec_1:;
    struct IntList const* if_;
    if ((i_ >= 0)) {
        goto then_3;
    } else {
        goto else_4;
    }
then_3:;
    if_ = acc_;
    goto if_next_2;
else_4:;
    struct IntList const* list_ = milone_mem_alloc(1, sizeof(struct IntList));
    (*(((struct IntList*)list_))) = (struct IntList){.head = i_, .tail = acc_};
    struct IntList const* arg_1 = list_;
    int arg_2 = (i_ + 1);
    acc_ = arg_1;
    i_ = arg_2;
    goto tailrec_1;
if_next_2:;
    return if_;
}

int effect_region_effect_region_doAction_fun(void) {
    struct IntList const* call_ = effect_region_effect_region_doAction_fun_go(NULL, 0);
    struct IntList const* result_ = call_;
    return 0;
}

int effect_region_effect_region_eta2_doAction_fun(void const* env_) {
    int call_1 = effect_region_effect_region_doAction_fun();
    return call_1;
}

int effect_region_effect_region_doAction(void) {
    struct UnitIntFun1 fun_ = (struct UnitIntFun1){.fun = effect_region_effect_region_eta2_doAction_fun, .env = NULL};
    milone_enter_region();
    int region_result = fun_.fun(fun_.env);
    milone_leave_region();
    return region_result;
}

int main(int argc, char** argv) {
    milone_start(argc, argv);
    int call_2 = effect_region_effect_region_doAction();
    return 0;
}
