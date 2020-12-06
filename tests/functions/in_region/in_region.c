#include "milone.h"

struct IntList;

struct IntList const* go_(struct IntList const* acc_, int i_);

int fun_(int arg_3);

int fun_1(void const* env_, int arg_);

struct UnitIntFun1;

int doAction_(int arg_4);

int main();

struct IntList {
    int head;
    struct IntList const* tail;
};

struct IntList const* go_(struct IntList const* acc_, int i_) {
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
    if_ = NULL;
    goto if_next_2;
if_next_2:;
    return if_;
}

int fun_(int arg_3) {
    struct IntList const* call_ = go_(NULL, 0);
    struct IntList const* result_ = call_;
    return 0;
}

int fun_1(void const* env_, int arg_) {
    int call_1 = fun_(0);
    return call_1;
}

struct UnitIntFun1 {
    int(*fun)(void const*, int);
    void const* env;
};

int doAction_(int arg_4) {
    void const* box_ = milone_mem_alloc(1, sizeof(int));
    (*(((int*)box_))) = 0;
    void const* env_1 = box_;
    struct UnitIntFun1 fun_2 = (struct UnitIntFun1){.fun = fun_1, .env = env_1};
    milone_enter_region();
    int region_result_ = fun_2.fun(fun_2.env, 0);
    milone_leave_region();
    return region_result_;
}

int main() {
    int call_2 = doAction_(0);
    return 0;
}
