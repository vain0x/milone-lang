#include "milone.h"

struct IntList;

struct IntList* go_(struct IntList* acc_, int i_);

int fun_(int arg_3);

int fun_1(void* env_, int arg_);

struct UnitIntFun1;

int doAction_(int arg_4);

int main();

struct IntList {
    int head;
    struct IntList* tail;
};

struct IntList* go_(struct IntList* acc_, int i_) {
tailrec_1:;
    struct IntList* match_;
    if ((i_ < 0)) goto next_3;
    match_ = acc_;
    goto end_match_2;
next_3:;
    if ((i_ >= 0)) goto next_4;
    struct IntList* list_ = (struct IntList*)milone_mem_alloc(1, sizeof(struct IntList));
    list_->head = i_;
    list_->tail = acc_;
    struct IntList* arg_1 = list_;
    int arg_2 = (i_ + 1);
    acc_ = arg_1;
    i_ = arg_2;
    goto tailrec_1;
    match_ = NULL;
    goto end_match_2;
next_4:;
    exit(1);
end_match_2:;
    return match_;
}

int fun_(int arg_3) {
    struct IntList* call_ = go_(NULL, 0);
    struct IntList* result_ = call_;
    return 0;
}

int fun_1(void* env_, int arg_) {
    int call_1 = fun_(0);
    return call_1;
}

struct UnitIntFun1 {
    int(*fun)(void*, int);
    void* env;
};

int doAction_(int arg_4) {
    void* box_ = (void*)milone_mem_alloc(1, sizeof(int));
    (*(((int*)box_))) = 0;
    void* env_1 = box_;
    struct UnitIntFun1 fun_2 = (struct UnitIntFun1){.fun = fun_1, .env = env_1};
    milone_enter_region();
    int call_2 = fun_2.fun(fun_2.env, 0);
    milone_leave_region();
    return call_2;
}

int main() {
    int call_3 = doAction_(0);
    return 0;
}
