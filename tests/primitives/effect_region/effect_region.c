#include <stdio.h>
#include <stdlib.h>
#include <milone.h>

struct Int32List;

struct Int32List;

typedef int32_t(*VoidConstPtrInt32FunPtr1)(void const*);

struct UnitInt32Fun1;

struct Int32List const* effect_region_effect_region_doAction_fun_go(struct Int32List const* acc_, int32_t i_);

int32_t effect_region_effect_region_doAction_fun(void);

int32_t effect_region_effect_region_eta2_doAction_fun(void const* env_);

int32_t effect_region_effect_region_doAction(void);

int main(int argc, char** argv);

struct Int32List {
    int32_t head;
    struct Int32List const* tail;
};

struct UnitInt32Fun1 {
    VoidConstPtrInt32FunPtr1 fun;
    void const* env;
};

struct Int32List const* effect_region_effect_region_doAction_fun_go(struct Int32List const* acc_, int32_t i_) {
    struct Int32List const* if_;
    struct Int32List const* list_;
    struct Int32List const* arg_1;
    int32_t arg_2;
tailrec_1:;
    if ((i_ >= 0)) {
        goto then_3;
    } else {
        goto else_4;
    }
then_3:;
    if_ = acc_;
    goto if_next_2;
else_4:;
    list_ = ((struct Int32List const*)milone_region_alloc(1, sizeof(struct Int32List)));
    (*(((struct Int32List*)list_))) = (struct Int32List){.head = i_, .tail = acc_};
    arg_1 = list_;
    arg_2 = (i_ + 1);
    acc_ = arg_1;
    i_ = arg_2;
    goto tailrec_1;
if_next_2:;
    return if_;
}

int32_t effect_region_effect_region_doAction_fun(void) {
    struct Int32List const* result_;
    struct Int32List const* call_;
    call_ = effect_region_effect_region_doAction_fun_go(NULL, 0);
    result_ = call_;
    return 0;
}

int32_t effect_region_effect_region_eta2_doAction_fun(void const* env_) {
    int32_t call_1;
    call_1 = effect_region_effect_region_doAction_fun();
    return call_1;
}

int32_t effect_region_effect_region_doAction(void) {
    struct UnitInt32Fun1 fun_;
    int32_t region_result;
    fun_ = (struct UnitInt32Fun1){.fun = effect_region_effect_region_eta2_doAction_fun, .env = NULL};
    milone_region_enter();
    region_result = fun_.fun(fun_.env);
    milone_region_leave();
    return region_result;
}

int main(int argc, char** argv) {
    milone_start(argc, argv);
    int32_t call_2;
    call_2 = effect_region_effect_region_doAction();
    return 0;
}
