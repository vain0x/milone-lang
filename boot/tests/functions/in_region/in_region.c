#include "milone.h"

struct IntList;

struct IntList* go_(struct IntList* acc_, int i_);

int fun_(int arg_1);

int fun_1(void* env_, int arg_);

struct UnitIntFun1;

int doAction_(int arg_2);

int main();

struct IntList {
    int head;
    struct IntList* tail;
};

struct IntList* go_(struct IntList* acc_, int i_) {
    struct IntList* match_;
    if ((i_ < 0)) goto next_2;
    match_ = acc_;
    goto end_match_1;
next_2:;
    if ((i_ >= 0)) goto next_3;
    struct IntList* list_ = (struct IntList*)milone_mem_alloc(1, sizeof(struct IntList));
    list_->head = i_;
    list_->tail = acc_;
    struct IntList* call_ = go_(list_, (i_ + 1));
    match_ = call_;
    goto end_match_1;
next_3:;
    exit(1);
end_match_1:;
    return match_;
}

int fun_(int arg_1) {
    struct IntList* call_1 = go_(NULL, 0);
    struct IntList* result_ = call_1;
    return 0;
}

int fun_1(void* env_, int arg_) {
    int call_2 = fun_(0);
    return call_2;
}

struct UnitIntFun1 {
    int(*fun)(void*, int);
    void* env;
};

int doAction_(int arg_2) {
    void* box_ = (void*)milone_mem_alloc(1, sizeof(int));
    (*(((int*)box_))) = 0;
    void* env_1 = box_;
    struct UnitIntFun1 fun_2 = (struct UnitIntFun1){.fun = fun_1, .env = env_1};
    milone_enter_region();
    int call_3 = fun_2.fun(fun_2.env, 0);
    milone_leave_region();
    return call_3;
}

int main() {
    int call_4 = doAction_(0);
    return 0;
}
