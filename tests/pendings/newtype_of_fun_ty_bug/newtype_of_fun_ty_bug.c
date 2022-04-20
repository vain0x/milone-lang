#include <stdio.h>
#include <stdlib.h>
#include <milone.h>

typedef int32_t(*VoidConstPtrInt32FunPtr1)(void const *);

struct UnitInt32Fun1;

struct F_;

typedef struct F_(*VoidConstPtrF_FunPtr1)(void const *);

struct UnitF_Fun1;

int32_t newtype_of_fun_ty_bug_newtype_of_fun_ty_bug_main_fun_fun(void);

int32_t newtype_of_fun_ty_bug_newtype_of_fun_ty_bug_eta2_main_fun_fun(void const *env_);

struct F_ newtype_of_fun_ty_bug_newtype_of_fun_ty_bug_main_fun(void);

struct F_ newtype_of_fun_ty_bug_newtype_of_fun_ty_bug_eta2_main_fun(void const *env_1);

int main(int argc, char **argv);

struct UnitInt32Fun1 {
    VoidConstPtrInt32FunPtr1 fun;
    void const *env;
};

enum F_Discriminant {
    F_,
};

struct F_ {
    enum F_Discriminant discriminant;
    union {
        struct UnitInt32Fun1 F_;
    };
};

struct UnitF_Fun1 {
    VoidConstPtrF_FunPtr1 fun;
    void const *env;
};

int32_t newtype_of_fun_ty_bug_newtype_of_fun_ty_bug_main_fun_fun(void) {
    return 42;
}

int32_t newtype_of_fun_ty_bug_newtype_of_fun_ty_bug_eta2_main_fun_fun(void const *env_) {
    int32_t call_;
    call_ = newtype_of_fun_ty_bug_newtype_of_fun_ty_bug_main_fun_fun();
    return call_;
}

struct F_ newtype_of_fun_ty_bug_newtype_of_fun_ty_bug_main_fun(void) {
    struct UnitInt32Fun1 fun_;
    struct F_ variant_;
    fun_ = (struct UnitInt32Fun1){.fun = newtype_of_fun_ty_bug_newtype_of_fun_ty_bug_eta2_main_fun_fun, .env = NULL};
    variant_ = (struct F_){.discriminant = F_, .F_ = fun_};
    return variant_;
}

struct F_ newtype_of_fun_ty_bug_newtype_of_fun_ty_bug_eta2_main_fun(void const *env_1) {
    struct F_ call_1;
    call_1 = newtype_of_fun_ty_bug_newtype_of_fun_ty_bug_main_fun();
    return call_1;
}

int main(int argc, char **argv) {
    milone_start(argc, argv);
    struct UnitF_Fun1 getF_;
    struct UnitInt32Fun1 f_;
    struct UnitF_Fun1 fun_1;
    struct F_ app_;
    int32_t app_1;
    fun_1 = (struct UnitF_Fun1){.fun = newtype_of_fun_ty_bug_newtype_of_fun_ty_bug_eta2_main_fun, .env = NULL};
    getF_ = fun_1;
    app_ = getF_.fun(getF_.env);
    f_ = app_.F_;
    app_1 = f_.fun(f_.env);
    if ((app_1 != 42)) milone_assert_error("newtype_of_fun_ty_bug/newtype_of_fun_ty_bug.milone", 10, 2);
    return 0;
}
