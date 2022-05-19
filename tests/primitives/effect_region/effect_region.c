#include <stdio.h>
#include <stdlib.h>
#include <milone.h>

struct Int32Cons;

struct Int32Cons;

typedef int32_t(*VoidConstPtrInt32FunPtr1)(void const *);

struct UnitInt32Fun1;

struct Int32Cons const *effect_region_effect_region_doAction_fun_go(struct Int32Cons const *acc_, int32_t i_);

int32_t effect_region_effect_region_doAction_fun(void);

int32_t effect_region_effect_region_eta2_doAction_fun(void const *env_);

int32_t Std_Region_Region_run(struct UnitInt32Fun1);

int32_t effect_region_effect_region_doAction(void);

int main(int argc, char **argv);

struct Int32Cons {
    int32_t head;
    struct Int32Cons const *tail;
};

struct UnitInt32Fun1 {
    VoidConstPtrInt32FunPtr1 fun;
    void const *env;
};

struct Int32Cons const *effect_region_effect_region_doAction_fun_go(struct Int32Cons const *acc_, int32_t i_) {
    struct Int32Cons const *if_;
    struct Int32Cons const *list_;
    struct Int32Cons const *arg_1;
    int32_t arg_2;
tailrec_4:;
    if ((i_ >= 0)) {
        goto then_6;
    } else {
        goto else_7;
    }
then_6:;
    if_ = acc_;
    goto if_next_5;
else_7:;
    list_ = ((struct Int32Cons const *)milone_region_alloc(1, sizeof(struct Int32Cons)));
    (*(((struct Int32Cons *)list_))) = (struct Int32Cons){.head = i_, .tail = acc_};
    arg_1 = list_;
    arg_2 = (i_ + 1);
    acc_ = arg_1;
    i_ = arg_2;
    goto tailrec_4;
if_next_5:;
    return if_;
}

int32_t effect_region_effect_region_doAction_fun(void) {
    struct Int32Cons const *result_;
    struct Int32Cons const *call_;
    call_ = effect_region_effect_region_doAction_fun_go(NULL, 0);
    result_ = call_;
    return 0;
}

int32_t effect_region_effect_region_eta2_doAction_fun(void const *env_) {
    int32_t call_1;
    call_1 = effect_region_effect_region_doAction_fun();
    return call_1;
}

int32_t effect_region_effect_region_doAction(void) {
    struct UnitInt32Fun1 fun_;
    int32_t call_2;
    fun_ = (struct UnitInt32Fun1){.fun = effect_region_effect_region_eta2_doAction_fun, .env = NULL};
    call_2 = Std_Region_Region_run(fun_);
    return call_2;
}

int main(int argc, char **argv) {
    milone_start(argc, argv);
    int32_t call_3;
    call_3 = effect_region_effect_region_doAction();
    return 0;
}
