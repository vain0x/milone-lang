#include <milone.h>

typedef int(*VoidConstPtrIntFunPtr1)(void const*);

struct UnitIntFun1;

struct F_;

typedef struct F_(*VoidConstPtrF_FunPtr1)(void const*);

struct UnitF_Fun1;

int newtype_of_fun_ty_bug_newtype_of_fun_ty_bug_main_fun_fun(void);

int newtype_of_fun_ty_bug_newtype_of_fun_ty_bug_eta2_main_fun_fun(void const* env_);

struct F_ newtype_of_fun_ty_bug_newtype_of_fun_ty_bug_main_fun(void);

struct F_ newtype_of_fun_ty_bug_newtype_of_fun_ty_bug_eta2_main_fun(void const* env_1);

int main(int argc, char** argv);

struct UnitIntFun1 {
    VoidConstPtrIntFunPtr1 fun;
    void const* env;
};

enum F_Discriminant {
    F_,
};

struct F_ {
    enum F_Discriminant discriminant;
    union {
        struct UnitIntFun1 F_;
    };
};

struct UnitF_Fun1 {
    VoidConstPtrF_FunPtr1 fun;
    void const* env;
};

int newtype_of_fun_ty_bug_newtype_of_fun_ty_bug_main_fun_fun(void) {
    return 42;
}

int newtype_of_fun_ty_bug_newtype_of_fun_ty_bug_eta2_main_fun_fun(void const* env_) {
    int call_ = newtype_of_fun_ty_bug_newtype_of_fun_ty_bug_main_fun_fun();
    return call_;
}

struct F_ newtype_of_fun_ty_bug_newtype_of_fun_ty_bug_main_fun(void) {
    struct UnitIntFun1 fun_ = (struct UnitIntFun1){.fun = newtype_of_fun_ty_bug_newtype_of_fun_ty_bug_eta2_main_fun_fun, .env = NULL};
    struct F_ variant_ = (struct F_){.discriminant = F_, .F_ = fun_};
    return variant_;
}

struct F_ newtype_of_fun_ty_bug_newtype_of_fun_ty_bug_eta2_main_fun(void const* env_1) {
    struct F_ call_1 = newtype_of_fun_ty_bug_newtype_of_fun_ty_bug_main_fun();
    return call_1;
}

int main(int argc, char** argv) {
    milone_start(argc, argv);
    struct UnitF_Fun1 fun_1 = (struct UnitF_Fun1){.fun = newtype_of_fun_ty_bug_newtype_of_fun_ty_bug_eta2_main_fun, .env = NULL};
    struct UnitF_Fun1 getF_ = fun_1;
    struct F_ app_ = getF_.fun(getF_.env);
    struct UnitIntFun1 f_ = app_.F_;
    int app_1 = f_.fun(f_.env);
    milone_assert((app_1 == 42), (struct String){.str = "newtype_of_fun_ty_bug/newtype_of_fun_ty_bug.milone", .len = 50}, 10, 2);
    return 0;
}
