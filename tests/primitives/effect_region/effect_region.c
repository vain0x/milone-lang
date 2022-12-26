#include <stdio.h>
#include <stdlib.h>
#include <milone.h>

struct Int32Cons;

struct Int32Cons;

typedef int32_t(*VoidConstPtrInt32FunPtr1)(void const *);

struct UnitInt32Fun1;


      static char s_mark[64];
      static int s_index;
    
typedef void(*VoidConstPtrVoidFunPtr1)(void const *);

struct UnitUnitFun1;

struct Int32Cons const *effect_region_effect_region_testRegionRun_fun_go(struct Int32Cons const *acc_, int32_t i_);

int32_t effect_region_effect_region_testRegionRun_fun(void);

int32_t effect_region_effect_region_eta2_testRegionRun_fun(void const *env_);

int32_t Std_Region_Region_run(struct UnitInt32Fun1);

void MiloneCore_Prelude_Int32UnitFun1_ignore(int32_t);

void effect_region_effect_region_testRegionRun(void);

void effect_region_effect_region_staticVars(void);

void effect_region_effect_region_testRegionDefer_mark(int32_t i_1);

void effect_region_effect_region_testRegionDefer_fun_fun(void);

void effect_region_effect_region_eta2_testRegionDefer_fun_fun(void const *env_1);

void effect_region_effect_region_testRegionDefer_fun_fun_fun(void);

void effect_region_effect_region_eta2_testRegionDefer_fun_fun_fun(void const *env_2);

void Std_Region_Region_defer(struct UnitUnitFun1);

int32_t effect_region_effect_region_testRegionDefer_fun_fun_1(void);

int32_t effect_region_effect_region_eta2_testRegionDefer_fun_fun_1(void const *env_3);

void effect_region_effect_region_testRegionDefer_fun_fun_fun_1(void);

void effect_region_effect_region_eta2_testRegionDefer_fun_fun_fun_1(void const *env_4);

int32_t effect_region_effect_region_testRegionDefer_fun_fun_2(void);

int32_t effect_region_effect_region_eta2_testRegionDefer_fun_fun_2(void const *env_5);

void effect_region_effect_region_testRegionDefer_fun_fun_3(void);

void effect_region_effect_region_eta2_testRegionDefer_fun_fun_3(void const *env_6);

int32_t effect_region_effect_region_testRegionDefer_fun(void);

int32_t effect_region_effect_region_eta2_testRegionDefer_fun(void const *env_7);

void effect_region_effect_region_testRegionDefer(void);

int main(int argc, char **argv);

struct Int32Cons {
    int32_t head;
    struct Int32Cons const *tail;
};

struct UnitInt32Fun1 {
    VoidConstPtrInt32FunPtr1 fun;
    void const *env;
};


struct UnitUnitFun1 {
    VoidConstPtrVoidFunPtr1 fun;
    void const *env;
};

struct Int32Cons const *effect_region_effect_region_testRegionRun_fun_go(struct Int32Cons const *acc_, int32_t i_) {
    struct Int32Cons const *if_;
    struct Int32Cons const *list_;
    struct Int32Cons const *arg_8;
    int32_t arg_9;
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
    list_ = ((struct Int32Cons const *)milone_region_alloc(1, sizeof(struct Int32Cons)));
    (*(((struct Int32Cons *)list_))) = (struct Int32Cons){.head = i_, .tail = acc_};
    arg_8 = list_;
    arg_9 = (i_ + 1);
    acc_ = arg_8;
    i_ = arg_9;
    goto tailrec_1;
if_next_2:;
    return if_;
}

int32_t effect_region_effect_region_testRegionRun_fun(void) {
    struct Int32Cons const *result_;
    struct Int32Cons const *call_;
    call_ = effect_region_effect_region_testRegionRun_fun_go(NULL, 0);
    result_ = call_;
    return 0;
}

int32_t effect_region_effect_region_eta2_testRegionRun_fun(void const *env_) {
    int32_t call_1;
    call_1 = effect_region_effect_region_testRegionRun_fun();
    return call_1;
}

void effect_region_effect_region_testRegionRun(void) {
    struct UnitInt32Fun1 fun_;
    int32_t call_2;
    fun_ = (struct UnitInt32Fun1){.fun = effect_region_effect_region_eta2_testRegionRun_fun, .env = NULL};
    call_2 = Std_Region_Region_run(fun_);
    MiloneCore_Prelude_Int32UnitFun1_ignore(call_2);
    return;
}

void effect_region_effect_region_staticVars(void) {
    return;
}

void effect_region_effect_region_testRegionDefer_mark(int32_t i_1) {

        s_mark[s_index++] = '0' + i_1;
          return;
}

void effect_region_effect_region_testRegionDefer_fun_fun(void) {
    effect_region_effect_region_testRegionDefer_mark(2);
    return;
}

void effect_region_effect_region_eta2_testRegionDefer_fun_fun(void const *env_1) {
    effect_region_effect_region_testRegionDefer_fun_fun();
    return;
}

void effect_region_effect_region_testRegionDefer_fun_fun_fun(void) {
    effect_region_effect_region_testRegionDefer_mark(5);
    return;
}

void effect_region_effect_region_eta2_testRegionDefer_fun_fun_fun(void const *env_2) {
    effect_region_effect_region_testRegionDefer_fun_fun_fun();
    return;
}

int32_t effect_region_effect_region_testRegionDefer_fun_fun_1(void) {
    struct UnitUnitFun1 fun_1;
    effect_region_effect_region_testRegionDefer_mark(4);
    fun_1 = (struct UnitUnitFun1){.fun = effect_region_effect_region_eta2_testRegionDefer_fun_fun_fun, .env = NULL};
    Std_Region_Region_defer(fun_1);
    effect_region_effect_region_testRegionDefer_mark(6);
    return 0;
}

int32_t effect_region_effect_region_eta2_testRegionDefer_fun_fun_1(void const *env_3) {
    int32_t call_3;
    call_3 = effect_region_effect_region_testRegionDefer_fun_fun_1();
    return call_3;
}

void effect_region_effect_region_testRegionDefer_fun_fun_fun_1(void) {
    effect_region_effect_region_testRegionDefer_mark(7);
    return;
}

void effect_region_effect_region_eta2_testRegionDefer_fun_fun_fun_1(void const *env_4) {
    effect_region_effect_region_testRegionDefer_fun_fun_fun_1();
    return;
}

int32_t effect_region_effect_region_testRegionDefer_fun_fun_2(void) {
    struct UnitUnitFun1 fun_2;
    fun_2 = (struct UnitUnitFun1){.fun = effect_region_effect_region_eta2_testRegionDefer_fun_fun_fun_1, .env = NULL};
    Std_Region_Region_defer(fun_2);
    return 0;
}

int32_t effect_region_effect_region_eta2_testRegionDefer_fun_fun_2(void const *env_5) {
    int32_t call_4;
    call_4 = effect_region_effect_region_testRegionDefer_fun_fun_2();
    return call_4;
}

void effect_region_effect_region_testRegionDefer_fun_fun_3(void) {
    effect_region_effect_region_testRegionDefer_mark(8);
    return;
}

void effect_region_effect_region_eta2_testRegionDefer_fun_fun_3(void const *env_6) {
    effect_region_effect_region_testRegionDefer_fun_fun_3();
    return;
}

int32_t effect_region_effect_region_testRegionDefer_fun(void) {
    struct UnitUnitFun1 fun_3;
    struct UnitInt32Fun1 fun_4;
    int32_t call_5;
    struct UnitInt32Fun1 fun_5;
    int32_t call_6;
    struct UnitUnitFun1 fun_6;
    effect_region_effect_region_testRegionDefer_mark(1);
    fun_3 = (struct UnitUnitFun1){.fun = effect_region_effect_region_eta2_testRegionDefer_fun_fun, .env = NULL};
    Std_Region_Region_defer(fun_3);
    effect_region_effect_region_testRegionDefer_mark(3);
    fun_4 = (struct UnitInt32Fun1){.fun = effect_region_effect_region_eta2_testRegionDefer_fun_fun_1, .env = NULL};
    call_5 = Std_Region_Region_run(fun_4);
    MiloneCore_Prelude_Int32UnitFun1_ignore(call_5);
    fun_5 = (struct UnitInt32Fun1){.fun = effect_region_effect_region_eta2_testRegionDefer_fun_fun_2, .env = NULL};
    call_6 = Std_Region_Region_run(fun_5);
    MiloneCore_Prelude_Int32UnitFun1_ignore(call_6);
    fun_6 = (struct UnitUnitFun1){.fun = effect_region_effect_region_eta2_testRegionDefer_fun_fun_3, .env = NULL};
    Std_Region_Region_defer(fun_6);
    effect_region_effect_region_testRegionDefer_mark(9);
    return 0;
}

int32_t effect_region_effect_region_eta2_testRegionDefer_fun(void const *env_7) {
    int32_t call_7;
    call_7 = effect_region_effect_region_testRegionDefer_fun();
    return call_7;
}

void effect_region_effect_region_testRegionDefer(void) {
    struct String s_;
    struct UnitInt32Fun1 fun_7;
    int32_t call_8;
    fun_7 = (struct UnitInt32Fun1){.fun = effect_region_effect_region_eta2_testRegionDefer_fun, .env = NULL};
    call_8 = Std_Region_Region_run(fun_7);
    MiloneCore_Prelude_Int32UnitFun1_ignore(call_8);
    s_ = string_of_raw_parts(s_mark, s_index);
    if ((string_compare(s_, (struct String){.ptr = "134657982", .len = 9}) != 0)) milone_assert_error("effect_region/effect_region.milone", 57, 2);
    return;
}

int main(int argc, char **argv) {
    milone_start(argc, argv);
    effect_region_effect_region_testRegionRun();
    effect_region_effect_region_testRegionDefer();
    return 0;
}
